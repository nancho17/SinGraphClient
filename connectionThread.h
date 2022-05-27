#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>

#include <QDebug>

class connectionThread : public QThread
{
    Q_OBJECT
public:
    connectionThread(QObject *parent = 0);
    void run();
    //
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
signals:

    void toGraphData(QByteArray);

private:
    QTcpSocket *socket;
};

#endif // CONNECTIONTHREAD_H
