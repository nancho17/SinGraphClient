#include "connectionThread.h"



connectionThread::connectionThread(QObject *parent)
{
}


void connectionThread::run(){

    socket =new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()) );

    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()) );

    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()) );

    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)) );

    qDebug()<<"Connecting...";
    socket->connectToHost("127.0.0.1",5400);
    if(! socket->waitForConnected(3000)){
    qDebug()<<"Not C";
    }


    
    exec();
}



void connectionThread:: connected(){
    qDebug()<<"Connected!";


   //socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n\r\n\r\n");

}

void connectionThread:: disconnected(){
    qDebug()<<"Disconnected";

}

void connectionThread:: bytesWritten(qint64 bytes){
    qDebug()<<"Connecting..."<< bytes;

}

void connectionThread:: readyRead(){
    qDebug()<<"Reading";
    QByteArray Data = socket->readAll();


    quint32 data_l;
     memcpy(&data_l,Data.constData(),4);

    qDebug()<<Data<<"is: "<<data_l;

    emit(newDataReceived());

}
