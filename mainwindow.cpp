#include "mainwindow.h"
#include "ui_mainwindow.h"

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

};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("300 Hz");
    ui->comboBox->addItem("60 Hz");
    ui->comboBox->addItem("40 Hz");
    ui->comboBox->addItem("20 Hz");
    ui->comboBox->addItem("5 Hz");
    ui->comboBox->addItem("1 Hz");

    aplotInit(ui->widget, 0);
    aplotInit(ui->widget, 1);
    ui->widget->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    aplotInit(ui->widget_2, 0);
    ui->widget_2->graph(0)->setPen(QPen(QColor(255, 110, 40)));

    _mTimer= new QTimer(this);
    _mTimer->start(100);

    connect(_mTimer, &QTimer::timeout, this, &MainWindow::graphData);
    time=0;

    graphMutex=new QMutex;
    evntMutex=new QMutex;
    x.append(0.0);
    y.append(0.0);
    z.append(0.0);
    cutFrequency = 300; // Hz

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::graphData(void)
{

    graphMutex->lock();
    ui->widget->graph(0)->setData(x, y);
    ui->widget->graph(1)->setData(x, z);
    graphMutex->unlock();
    ui->widget->xAxis->setRange(x.last(), 0.090, Qt::AlignRight);
    ui->widget->replot();

    graphMutex->lock();
    ui->widget_2->graph(0)->setData(x, z);
    graphMutex->unlock();
    ui->widget_2->xAxis->setRange(x.last(), 0.090, Qt::AlignRight);
    ui->widget_2->replot();

}

void MainWindow::parseData(QByteArray Data)
{
    memcpy((char *) &receivedDataPacket, Data.constData(), sizeof(protocolStruct));

    // Filter Calc
    double delta_time = 0.0002;
    evntMutex->lock();
    double RC = 1 / (cutFrequency * 2 * M_PI);
    evntMutex->unlock();
    double alpha = delta_time / (RC + delta_time);


    for (size_t i = 0; i < receivedDataPacket.validCount; i++)
    {
        graphMutex->lock();
        y.append(receivedDataPacket.imageVar[i]);
        x.append(time);
        graphMutex->unlock();

        time = time + delta_time;
        // Apply a filter
        if (z.empty())
        {
            // y[0] := α * x[0]
            graphMutex->lock();
            z.append(alpha * y.last());
            graphMutex->unlock();
        }
        else
        {
            // y[i] := α * x[i] + (1-α) * y[i-1]
            graphMutex->lock();
            z.append(alpha * y.last() + (1 - alpha) * z.last());
            graphMutex->unlock();
        }

        if (x.size() >= 400)
        {
            graphMutex->lock();
            x.pop_front();
            y.pop_front();
            z.pop_front();
            graphMutex->unlock();
        }
    }

    while (x.size() >= 400)
    {
        graphMutex->lock();
        x.pop_front();
        y.pop_front();
        z.pop_front();
        graphMutex->unlock();
    }
}

void MainWindow::on_pushButton_clicked()
{
    switch (ui->comboBox->currentIndex()) {
    case 0:
        evntMutex->lock();
        cutFrequency=300;
        evntMutex->unlock();
        break;
    case 1:
        evntMutex->lock();
        cutFrequency=60;
        evntMutex->unlock();
        break;
    case 2:
        evntMutex->lock();
        cutFrequency=40;
        evntMutex->unlock();
        break;
    case 3:
        evntMutex->lock();
        cutFrequency=20;
        evntMutex->unlock();
        break;
    case 4:
        evntMutex->lock();
        cutFrequency=5;
        evntMutex->unlock();
        break;
    case 5:
        evntMutex->lock();
        cutFrequency=1;
        evntMutex->unlock();
        break;
    default:
        break;
    }
}
