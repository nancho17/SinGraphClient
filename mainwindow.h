#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void parseData(QByteArray);

private:
    Ui::MainWindow *ui;
    QVector <double> x,y,z;
    double time;
    QTime *_mTimer;

};
#endif // MAINWINDOW_H
