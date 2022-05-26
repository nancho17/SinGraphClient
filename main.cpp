#include "mainwindow.h"
#include <QApplication>
#include "connectionThread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connectionThread* task = new connectionThread;
    MainWindow w;
    w.show();
    task->run();



    //QObject::connect(&server,SIGNAL(newDataRecieved(QByteArray)),&w,SLOT(parseData(QByteArray)));

        return a.exec();
}
