#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>


void aplotInit(QCustomPlot * plotGraph){

    plotGraph->addGraph();
    plotGraph->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    plotGraph->graph(0)->setLineStyle(QCPGraph::lsLine);
    plotGraph->xAxis->setLabel("time");
    plotGraph->yAxis->setLabel("Y");
    plotGraph->xAxis->setRange(0, 2000);
    plotGraph->yAxis->setRange(-2,2);
    plotGraph->rescaleAxes();
    plotGraph->replot();
    plotGraph->update();



};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    aplotInit(ui->widget);
    aplotInit(ui->widget_2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::parseData(QByteArray Data)
{
    quint32 data_l;
    memcpy(&data_l, Data.constData(), 4);
    qDebug() << "Got data:" << Data << "is: " << data_l;
    x.append(data_l);
    y.append(1.4142* qSin(data_l * 20 * M_PI / 180));

    //Apply a filter
    z.append(y.last()* (-1)*qCos(data_l * 20 * M_PI / 180));

    if (data_l < 500)
    {

        // qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843)
        //ui->widget->graph(0)->addData(x.last(), y.last());
        ui->widget->graph(0)->setData(x,y);
        ui->widget->xAxis->setRange(x.last(), 40, Qt::AlignRight);
        ui->widget->replot();

        ui->widget_2->graph(0)->setData(x,z);
        ui->widget_2->xAxis->setRange(x.last(), 40, Qt::AlignRight);
        ui->widget_2->replot();
    }
    else
    {
        //ui->widget->graph(0)->addData(x.last(), y.last());
        ui->widget->graph(0)->setData(x,y);
        ui->widget->xAxis->setRange(400, 3000);
        ui->widget->yAxis->setRange(-2, 2);
        ui->widget->replot();
        ui->widget->update();
    }

    if (x.size() >= 40)
    {
        x.pop_front();
        y.pop_front();
        z.pop_front();
    }
}
