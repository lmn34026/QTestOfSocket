#include "utilSocket.h"
#include <QDebug>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QList>
#include <QNetworkInterface>
#include <QStringList>
//#include <QElapsedTimer>
//#include <QDeadlineTimer>
#include <QElapsedTimer>

udpUtil::udpUtil() :
    QUdpSocket()
{

}

bool udpUtil::bindUtil(QString &localIP, quint16 &localPort)
{
    if(!utilSocketNS::isIpV4(localIP, localPort)) return false;

    QHostAddress haLocalIP(localIP);
    quint16 u16LocalPort = localPort;
    bool r = this->bind(haLocalIP, u16LocalPort);

    if(r != true){
        qDebug() << __func__ << "failed" << r;
    }

    return r;
}

qint64 udpUtil::txUtil(QByteArray &txBuffer, QString remoteIP, quint16 remotePort)
{
    return this->__txUtil(txBuffer, remoteIP, remotePort);
}

qint64 udpUtil::rxUtil(QByteArray &rxBuffer)
{
    QHostAddress sender;
    quint16 senderPort;

    return this->__rxUtil(rxBuffer, 1024, 0U, &sender, &senderPort);
}

qint64 udpUtil::rxUtil(QByteArray &rxBuffer, size_t size, qint64 timeoutMS)
{
    QHostAddress sender;
    quint16 senderPort;

    return this->__rxUtil(rxBuffer, size, timeoutMS, &sender, &senderPort);
}

qint64 udpUtil::rxUtil(QByteArray &rxBuffer, QHostAddress *haSender, quint16 *u16Port)
{
    return this->__rxUtil(rxBuffer, 1024, 0U, haSender, u16Port);
}

qint64 udpUtil::rxUtil(QByteArray &rxBuffer, QString *remoteIP, quint16 *remotePort)
{
    QHostAddress haSender;
    remoteIP->clear();
    remotePort = 0;

    qint64 rxSize = this->__rxUtil(rxBuffer, 1024, 0U, &haSender, remotePort);
    if(rxSize > 0){
        remoteIP->append(haSender.toString());
    }

    return rxSize;
}

qint64 udpUtil::__txUtil(QByteArray &txBuffer, QString remoteIP, quint16 remotePort)
{
    if(!utilSocketNS::isIpV4(remoteIP, remotePort)) return 0;

    QHostAddress haRemoteIP(remoteIP);
    quint16 u16RemotePort = remotePort;

    return this->writeDatagram(txBuffer, haRemoteIP, u16RemotePort);
}

qint64 udpUtil::__rxUtil(QByteArray &rxBuffer, size_t rxSize, qint64 timeoutMS, QHostAddress *sender, quint16 *senderPort)
{
    volatile size_t sizePending = this->pendingDatagramSize();              // avoid compare between singed and unsigned warning
    size_t sizeToRead = 0;

    rxBuffer.clear();

    if(timeoutMS > 0)
    {
//        QDeadlineTimer timer(timeoutMS);

        QElapsedTimer timer;
        timer.start();
        do
        {
            sizePending = this->pendingDatagramSize();
            if(sizePending >= rxSize)
            {
                sizeToRead = rxSize;
                break;
            }
        }while(!timer.hasExpired(timeoutMS));
    }
    else if(timeoutMS == 0)                             // no timeout
    {
        sizePending = this->pendingDatagramSize();
        sizeToRead = (sizePending >= rxSize) ? (rxSize) : (sizePending);
    }
    else
    {
        do{
            sizePending = this->pendingDatagramSize();
        } while(sizePending >= rxSize);

        sizeToRead = sizePending;
    }

    rxBuffer.resize(sizeToRead);
    sizeToRead = this->readDatagram(rxBuffer.data(), rxBuffer.size(), sender, senderPort);

    return (qint64)sizeToRead;
}

void utilSocketNS::getLocalIPV4s(QStringList &qsl)
{
    QList<QHostAddress> hostAddrs = QNetworkInterface::allAddresses();

    qsl.clear();

    foreach(QHostAddress hostAddr, hostAddrs)
    {
        if(hostAddr.protocol() == QAbstractSocket::IPv4Protocol)
        {
            QString __ip = hostAddr.toString();
            if(__ip.startsWith("169.")) continue;
            else qsl.append(__ip);
        }
    }
}

bool utilSocketNS::isIpV4(QString &ip, quint16 &port)
{
    bool r = false;
    QHostAddress qip(ip);

    if((QAbstractSocket::IPv4Protocol != qip.protocol()) || !(port)){
        r = false;
    }else{
        r = true;
    }

    return r;
}

bool utilSocketNS::isIpV4(QString &ip, QString &port)
{
    quint16 __port = port.toShort();

    return isIpV4(ip, __port);
}




