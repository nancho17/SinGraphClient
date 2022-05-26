#ifndef RESOCCKET_H
#define RESOCCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>


class Soccket : public QObject
{
    Q_OBJECT
public:
    explicit Soccket(QObject *parent = nullptr);
    void Basic();
    void Test();

signals:

public slots:

    void	connected();
    void	disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    /*
    void	errorOccurred(QAbstractSocket::SocketError socketError)
    void	hostFound()
    void	proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
    void	stateChanged(QAbstractSocket::SocketState socketState)
    */


private:
    QTcpSocket *socket;

};

#endif // RESOCCKET_H
