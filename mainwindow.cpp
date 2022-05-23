#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->addGraph();
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->widget->xAxis->setLabel("time");
    ui->widget->yAxis->setLabel("Y");
    ui->widget->xAxis->setRange(-100,600);
    ui->widget->yAxis->setRange(-100,100);
    QVector<double> x = {1.5,2.66,3.61,4.23,8.62,6.6,5.45},y = {1.5,2.66,3.61,4.23,8.62,6.6,5.45};
    ui->widget->graph(0)->addData(x,y);
    //ui->widget->rescaleAxes();
    ui->widget->replot();
    ui->widget->update();

    //ui->widget->graph(0)->addData(x,y);


}

MainWindow::~MainWindow()
{
    delete ui;
}

