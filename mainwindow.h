#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef struct {
    uint8_t validCount;
    double imageVar[30];
    double timeVar[30];
}protocolStruct;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void graphData();

public slots:
    void parseData(QByteArray);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector <double> x,y,z;
    double time;
    double cutFrequency;
    QTimer *_mTimer;
    protocolStruct receivedDataPacket;
    QMutex *graphMutex, *evntMutex;


};
#endif // MAINWINDOW_H
