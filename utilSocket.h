#ifndef UTILSOCKET_H
#define UTILSOCKET_H

#include <QString>
#include <QHostAddress>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>


class udpUtil : public QUdpSocket
{
    Q_OBJECT
public:
    explicit udpUtil();
    ~udpUtil(){}
    bool bindUtil(QString &localIP, quint16 &localPort);
    qint64 txUtil(QByteArray &txBuffer, QString remoteIP, quint16 remotePort);
    qint64 rxUtil(QByteArray &rxBuffer);
    qint64 rxUtil(QByteArray &rxBuffer, size_t size, qint64 timeoutMS);
    qint64 rxUtil(QByteArray &rxBuffer, QHostAddress *sender, quint16 *senderPort);
    qint64 rxUtil(QByteArray &rxBuffer, QString *remoteIP, quint16 *remotePort);

private:
    qint64 __txUtil(QByteArray &txBuffer, QString remoteIP, quint16 remotePort);
    qint64 __rxUtil(QByteArray &rxBuffer, size_t maxSize, qint64 timeoutMS, QHostAddress *sender, quint16 *senderPort);

signals:

public slots:

};


namespace utilSocketNS{

void getLocalIPV4s(QStringList &qsl);
bool isIpV4(QString & ip, quint16 & port);
bool isIpV4(QString & ip, QString & port);

}




#endif // UTILSOCKET_H
