#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

void aplotInit(QCustomPlot *plotGraph, int n_graph)
{

    plotGraph->addGraph();
    plotGraph->graph(n_graph)->setScatterStyle (QCPScatterStyle(QCPScatterStyle::ssDisc, 2));//ssDisc

    plotGraph->graph(n_graph)->setLineStyle(QCPGraph::lsLine);
    plotGraph->xAxis->setLabel("time");
    plotGraph->yAxis->setLabel("Y");
    plotGraph->xAxis->setRange(0, 2000);
    plotGraph->yAxis->setRange(-2, 2);
    plotGraph->rescaleAxes();
    plotGraph->replot();
    plotGraph->update();
    //20ms /100 0.2ms
    // QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    aplotInit(ui->widget, 0);
    aplotInit(ui->widget, 1);
    ui->widget->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    aplotInit(ui->widget_2, 0);
    ui->widget_2->graph(0)->setPen(QPen(QColor(255, 110, 40)));

    //_mTimer= new QTimer(this);
    //_mTimer->start();
    time=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::parseData(QByteArray Data)
{
    memcpy((char *) &receivedDataPacket, Data.constData(), sizeof(protocolStruct));

    // Filter Calc
    double delta_time = 0.001;
    double cut_frequency = 20; // Hz
    double RC = 1 / (cut_frequency * 2 * M_PI);

    double alpha = delta_time / (RC + delta_time);


    for (size_t i = 0; i < receivedDataPacket.validCount; i++)
    {   
        
        //qDebug()<<receivedDataPacket.image_var[i];
        y.append(receivedDataPacket.image_var[i]);

        x.append(time);
        time = time + delta_time;
        // Apply a filter
        if (z.empty())
        {

            // y[0] := α * x[0]
            z.append(alpha * y.last());
        }
        else
        {
            // y[i] := α * x[i] + (1-α) * y[i-1]
            z.append(alpha * y.last() + (1 - alpha) * z.last());
        }
    }


    if (true)
    {

        ui->widget->graph(0)->setData(x, y);
        // ui->widget->xAxis->setRange(x.last(), 0.150, Qt::AlignRight);
        // ui->widget->replot();
        ui->widget->graph(1)->setData(x, z);
        ui->widget->xAxis->setRange(x.last(), 0.150, Qt::AlignRight);
        ui->widget->replot();

        ui->widget_2->graph(0)->setData(x, z);
        ui->widget_2->xAxis->setRange(x.last(), 0.150, Qt::AlignRight);
        ui->widget_2->replot();
    }
    else
    {
        // ui->widget->graph(0)->addData(x.last(), y.last());
        ui->widget->graph(0)->setData(x, y);
        ui->widget->xAxis->setRange(0, 3000);
        ui->widget->yAxis->setRange(-2, 2);
        ui->widget->replot();
        ui->widget->update();
    }

    while (x.size() >= 150)
    {
        x.pop_front();
        y.pop_front();
        z.pop_front();
    }
}
