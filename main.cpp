#include "mainwindow.h"
#include <QApplication>
#include "connectionThread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connectionThread *task = new connectionThread;
    MainWindow w;

    QObject::connect(task, SIGNAL(toGraphData(QByteArray)), &w, SLOT(parseData(QByteArray)));

    w.show();
    task->run();

    return a.exec();
}
