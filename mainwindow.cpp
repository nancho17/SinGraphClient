#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>


void aplotInit(QCustomPlot * plotGraph ,int n_graph){

    plotGraph->addGraph();
    plotGraph->graph(n_graph)->setScatterStyle(QCPScatterStyle::ssCircle);
    plotGraph->graph(n_graph)->setLineStyle(QCPGraph::lsLine);
    plotGraph->xAxis->setLabel("time");
    plotGraph->yAxis->setLabel("Y");
    plotGraph->xAxis->setRange(0, 2000);
    plotGraph->yAxis->setRange(-2,2);
    plotGraph->rescaleAxes();
    plotGraph->replot();
    plotGraph->update();

    //QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);

};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    aplotInit(ui->widget,0);
    aplotInit(ui->widget,1);
    ui->widget->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    aplotInit(ui->widget_2,0);
    //_mTimer= new QTimer(this);
    //_mTimer->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::parseData(QByteArray Data)
{
    //qDebug() << "Got data:" << Data << "is: " << data_l;
    //key = key -_mTimer->elapsed();


    //Filter Calc
    double delta_time=0.002;
    double cut_frequency=20;//Hz
    double RC=1/(cut_frequency*2*M_PI);

    double alpha= delta_time/(RC+delta_time);

    double data_l;
    memcpy(&data_l, Data.constData(), 8);

    x.append(time);
    time=time+0.002;
    y.append(data_l);

    //Apply a filter
    //z.append(y.last()* (-1) + qCos(x.last() * 1.9 * 2 * M_PI));
    if (z.empty()){

        //y[0] := α * x[0]
        z.append(alpha * y.last());
    }
    else{
        //y[i] := α * x[i] + (1-α) * y[i-1]
        z.append( alpha * y.last() + (1-alpha ) * z.last());
    }


    if (true)
    {

        ui->widget->graph(0)->setData(x,y);
        //ui->widget->xAxis->setRange(x.last(), 0.150, Qt::AlignRight);
        //ui->widget->replot();
        ui->widget->graph(1)->setData(x,z);
        ui->widget->xAxis->setRange(x.last(), 0.150, Qt::AlignRight);
        ui->widget->replot();

        ui->widget_2->graph(0)->setData(x,z);
        ui->widget_2->xAxis->setRange(x.last(), 0.150, Qt::AlignRight);
        ui->widget_2->replot();
    }
    else
    {
        //ui->widget->graph(0)->addData(x.last(), y.last());
        ui->widget->graph(0)->setData(x,y);
        ui->widget->xAxis->setRange(0, 3000);
        ui->widget->yAxis->setRange(-2, 2);
        ui->widget->replot();
        ui->widget->update();
    }

    if (x.size() >= 150)
    {
        x.pop_front();
        y.pop_front();
        z.pop_front();
    }
}
