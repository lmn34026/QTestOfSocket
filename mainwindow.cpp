#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_TXDatasForm.h"
#include <QDebug>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QList>
#include <QHostInfo>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTime>
//#include <iostream>


using namespace utilCommToolsNS;
using namespace utilSocketNS;
//using namespace utilSerialPortNS;
using namespace utilUiElementNS;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->txDatasForm = NULL;

    this->isConnected = false;

    this->ui->teLog->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    ui->cbbModeSelect->addItem("UDP");
    ui->cbbModeSelect->addItem("TCP Client");
    ui->cbbModeSelect->addItem("TCP Server");
    ui->cbbModeSelect->setCurrentIndex(0);
    socket_type = this->ui->cbbModeSelect->currentIndex();

    this->udp = NULL;
    this->tcpClient = NULL;
    this->tcpServer = NULL;
    this->thTCPSeverWaitConnection = NULL;

    this->cbbLocalIPChangedEvent();

//    txEndWithSL << "" << "\\r\\n" << "\\r";
//    this->ui->cbbTXEndWith->addItems(txEndWithSL);


    this->mapTxEndWith.insert("", "");
    this->mapTxEndWith.insert("\\r\\n", "\r\n");
    this->mapTxEndWith.insert("\\r", "\r");
//    // Now use QMap.keys() and combobox.addItems() instead
//    QMap<QString, QString>::const_iterator _mapIt = mapTxEndWith.constBegin();
//    while(_mapIt != mapTxEndWith.constEnd()){
//        this->ui->cbbTXEndWith->addItem(_mapIt.key());
//        ++_mapIt;
//    }
    this->ui->cbbTXEndWith->addItems(this->mapTxEndWith.keys());

    this->cfgLoadToUI();

    connect(this->ui->btnOC, SIGNAL(clicked()), this, SLOT(socketOCEvent()));
    connect(this->ui->cbbModeSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(cbbModeChangedEvent(int)));
    connect(this->ui->cbbLocalIP, SIGNAL(clicked()), this, SLOT(cbbLocalIPChangedEvent()));
    connect(this->ui->btnTX, SIGNAL(clicked()), this, SLOT(txEvent()));
    connect(this->ui->btnClear, SIGNAL(clicked()), this->ui->teLog, SLOT(clear()));
    connect(this->ui->btnTXDatasOC, SIGNAL(clicked()), this, SLOT(txDatasFormOCEvent()));


}

MainWindow::~MainWindow()
{
    this->cfgSaveFromUI();

    if(this->txDatasForm != nullptr){
        delete this->txDatasForm;
    }

    delete ui;
}

bool MainWindow::UDPInit()
{
    if(this->udp == NULL)
    {
        this->udp = new udpUtil();
        if(this->udp == NULL)
        {
            qDebug() << __func__ << "failed";
            return false;
        }
        connect(this->udp, SIGNAL(readyRead()), this, SLOT(rxEvent()));
    }

    return true;
}

bool MainWindow::TCPClientInit()
{
    if(this->tcpClient == NULL)
    {
        this->tcpClient = new QTcpSocket();
        if(this->tcpClient == NULL)
        {
            return false;
        }

        connect(this->tcpClient, SIGNAL(readyRead()), this, SLOT(rxEvent()));
        connect(this->tcpClient, SIGNAL(disconnected()), this, SLOT(TCPClientDisconnectedEvent()));
    }

    return true;
}

bool MainWindow::TCPServerInit()
{
    if(this->tcpServer == NULL)
    {
        this->tcpServer = new QTcpServer();
        if(this->tcpServer == NULL)
        {
            return false;
        }

        connect(this->tcpServer, SIGNAL(newConnection()), this, SLOT(TCPServerNewConnectionEvent()));
    }

    return true;
}


bool MainWindow::refreshIPPortFromUI()
{
    QString localIP = this->ui->cbbLocalIP->currentText();
    quint16 localPort = this->ui->leLocalPort->text().toShort();
    QString remoteIP = this->ui->leRemoteIP->text();
    quint16 remotePort = this->ui->leRemotePort->text().toShort();

    //    qDebug() << __func__ << " local" << " IP:" << localIP << " port:" << localPort << " remote" << " IP:" << remoteIP << " port:" << remotePort;

    this->localIP = localIP;
    this->localPort = localPort;
    this->remoteIP = remoteIP;
    this->remotePort = remotePort;

    return true;
}


int MainWindow::__socketOCEventUDP()
{
    bool r = false;

    this->UDPInit();

    if(this->isConnected)
    {
        this->udp->disconnectFromHost();
        this->isConnected = false;
        r = true;
    }
    else
    {
        if( this->refreshIPPortFromUI() && \
                isIpV4(this->localIP, this->localPort) && \
                this->udp->bindUtil(this->localIP, this->localPort) )
        {
            this->isConnected = true;
            r = true;
        }
        else
        {
            qDebug() << __func__ << "failed";
        }
    }

    return r;
}

int MainWindow::__socketOCEventTCPClient()
{
    qDebug() << __func__;

    bool r = false;

    this->TCPClientInit();

    if(this->isConnected)
    {
        this->tcpClient->disconnectFromHost();
        this->isConnected = false;
        r = true;
    }
    else
    {
        if( this->refreshIPPortFromUI() && \
                isIpV4(this->remoteIP, this->remotePort) )
        {
            this->tcpClient->connectToHost(this->remoteIP, this->remotePort);
            if(this->tcpClient->waitForConnected(3000))
            {
                this->isConnected = true;
                r = true;

//                this->tcpClient->write((QString("hello from QT:") + __func__).toAscii());
                this->tcpClient->write((QString("hello from QT:") + __func__).toUtf8());
            }
            else
            {
                this->tcpClient->abort();
                this->isConnected = false;
                r = false;
                qDebug() << __func__ << "failed!\r\n";
            }
        }
    }

    return r;
}

int MainWindow::__socketOCEventTCPServer()
{
    this->TCPServerInit();

    bool r = false;

    if(this->isConnected)
    {
        this->tcpServer->close();
        this->deleteTCPServerInClients();
        this->isConnected = false;
        r = true;
    }
    else
    {
        if( this->refreshIPPortFromUI() && \
                this->remotePort > 0 && \
                this->tcpServer->listen(QHostAddress::Any, this->localPort) )
        {
            this->isConnected = true;

            r = true;
        }
    }

    return r;
}

int MainWindow::__rxEventUDP(QByteArray &rxBuffer, QString &msg)
{
    int rxSize = 0;

    if(this->udp->hasPendingDatagrams())
    {
        QHostAddress sender;
        quint16 senderPort;
        rxSize = this->udp->rxUtil(rxBuffer, &sender, &senderPort);

        msg += (this->localIP + ":" + QString::number(this->localPort) \
                + " <- " \
                + sender.toString() + ":" + QString::number(senderPort) \
                + " [" + QString::number(rxSize) + "]" \
                + "\r\n" \
                );
        msg += QString(rxBuffer);
        msg += QString("\r\n");

    }

    return rxSize;
}

int MainWindow::__rxEventTCPClient(QByteArray &rxBuffer, QTcpSocket* tcpClient, QString &msg)
{
    int rxSize = 0;
    int sizeToRead = 0;

    if((tcpClient != NULL) && (sizeToRead = tcpClient->bytesAvailable()))
    {
        rxBuffer.clear();
        rxBuffer.resize(sizeToRead);
        rxBuffer = tcpClient->read(sizeToRead);
        rxSize = rxBuffer.size();

        msg += (tcpClient->localAddress().toString() + ":" + QString::number(tcpClient->localPort()) \
                + " <- " \
                +  tcpClient->peerAddress().toString() + ":" + QString::number(tcpClient->peerPort()) \
                + " [" + QString::number(rxSize) + "]" \
                + "\r\n" \
                );
        msg += QString(rxBuffer);
        msg += QString("\r\n");
    }

    return rxSize;
}

int MainWindow::__rxEventTCPServer(QByteArray &rxBuffer, QTcpSocket* tcpClient, QString &msg)
{
    return this->__rxEventTCPClient(rxBuffer, tcpClient, msg);
}

int MainWindow::__txEventUDP(QByteArray &txBuffer, QString &msg)
{
    int txSize = 0;
    QString remoteIP = this->ui->leRemoteIP->text();
    quint16 remotePort = this->ui->leRemotePort->text().toShort();

    if(txBuffer.size() && this->isConnected)
    {
        txSize = this->udp->txUtil(txBuffer, remoteIP, remotePort);

        msg += (this->udp->localAddress().toString() + ":" + QString::number(this->udp->localPort()) \
                + " -> " \
                +  remoteIP + ":" + QString::number(remotePort) \
                + " [" + QString::number(txSize) + "]" \
                + "\r\n" \
                );
        msg += QString(txBuffer);
        msg += QString("\r\n");
    }

    return txSize;
}

int MainWindow::__txEventTCPClient(QByteArray &txBuffer, QString &msg)
{
    int txSize = 0;
    QString clientIP = this->tcpClient->localAddress().toString();
    quint16 clientPort = this->tcpClient->localPort();
    QString serverIP = this->tcpClient->peerAddress().toString();
    quint16 serverPort = this->tcpClient->peerPort();

    if(txBuffer.size() && isIpV4(clientIP, clientPort) && isIpV4(serverIP, serverPort) && this->isConnected)
    {
        txSize = this->tcpClient->write(txBuffer.data(), txBuffer.size());

        msg += (clientIP + ":" + QString::number(clientPort) \
                + " -> " \
                +  serverIP + ":" + QString::number(serverPort) \
                + " [" + QString::number(txSize) + "]" \
                + "\r\n" \
                );
        msg += QString(txBuffer);
        msg += QString("\r\n");
    }

    return txSize;
}

int MainWindow::__txEventTCPServer(QByteArray &txBuffer, QTcpSocket *tcpClient, QString &msg)
{
    int txCnt = 0;
    int txSize = 0;
    QString serverIP = this->tcpServer->serverAddress().toString();
    quint16 serverPort = this->tcpServer->serverPort();

    if(txBuffer.size() && isIpV4(serverIP, serverPort) && this->isConnected)
    {
        if(NULL != tcpClient)
        {
            txSize = tcpClient->write(txBuffer.data(), txBuffer.size());
            if(txSize > 0)
            {
                txCnt = 1;
            }
        }
        else
        {
            foreach(QTcpSocket* __client, this->tcpServerInClients)
            {
                txSize = __client->write(txBuffer.data(), txBuffer.size());

                msg += (serverIP + ":" + QString::number(serverPort) \
                        + " -> " \
                        +  __client->peerAddress().toString() + ":" + QString::number(__client->peerPort()) \
                        + " [" + QString::number(txSize) + "]" \
                        + "\r\n" \
                        );
                msg += QString(txBuffer);
                msg += QString("\r\n");

                txCnt += 1;
            }
        }
    }

    return txCnt;
}

bool MainWindow::deleteTCPServerInClients()
{
    qDebug() << __func__ << "socket cnt: " << this->tcpServerInClients.count();

    if(this->tcpServerInClients.isEmpty())
        return true;

    foreach(QTcpSocket* __tcpSocket, this->tcpServerInClients)
    {
        if(__tcpSocket == nullptr) continue;

        disconnect(__tcpSocket);

        //        this->tcpServerInClients.removeOne(__tcpSocket);
        this->tcpServerInClients.removeFirst();

        __tcpSocket->close();

        //        socket will be deleted in close slot, but its safe to call deleteLater() again
        __tcpSocket->deleteLater();
    }

    return !(this->tcpServerInClients.count());
}

void MainWindow::cfgLoadToUI()
{
    configUtil cfg = configUtil("config.ini");
//    cfg.dump();

    this->ui->cbbLocalIP->setCurrentIndex(this->ui->cbbLocalIP->findText(cfg.getValue("IPPORT", "localIP")));
    this->ui->leLocalPort->setText(cfg.getValue("IPPORT", "localPort"));
    this->ui->leRemoteIP->setText(cfg.getValue("IPPORT", "remoteIP"));
    this->ui->leRemotePort->setText(cfg.getValue("IPPORT", "remotePort"));
    this->ui->cbbTXEndWith->setCurrentIndex(cfg.getValue("SETTING", "txEndWithIndex").toInt());
    this->ui->teTXData->setPlainText(cfg.getValue("DATA", "txData"));

}

void MainWindow::cfgSaveFromUI()
{
    static const int maxSizeForSave = 16;

    configUtil cfg = configUtil("config.ini");

    QString __localIP = this->ui->cbbLocalIP->currentText();
    QString __localPort = this->ui->leLocalPort->text();
    if(isIpV4(__localIP, __localPort))
    {
        cfg.setValue("IPPORT", "localIP", __localIP);
        cfg.setValue("IPPORT", "localPort", __localPort);
    }

    QString __remoteIP = this->ui->leRemoteIP->text();
    QString __remotePort = this->ui->leRemotePort->text();
    if(isIpV4(__remoteIP, __remotePort))
    {
        cfg.setValue("IPPORT", "remoteIP", __remoteIP);
        cfg.setValue("IPPORT", "remotePort", __remotePort);
    }

    QString __txEndWithIndex = QString::number(this->ui->cbbTXEndWith->currentIndex());
    cfg.setValue("SETTING", "txEndWithIndex", __txEndWithIndex);

    QString __txData = this->ui->teTXData->toPlainText();
    if(__txData.size() > 16) __txData = __txData.mid(0, maxSizeForSave);
    cfg.setValue("DATA", "txData", __txData);

    if(this->txDatasForm != nullptr)
    {

    }
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    if((this->txDatasForm != NULL) && !(this->txDatasForm->isHidden()))
    {
        QPoint pos = event->pos();
        pos.setX(pos.x() + this->frameGeometry().width());
        ((TXDatasForm*)(this->txDatasForm))->move(pos);
    }
}



void MainWindow::cbbLocalIPChangedEvent()
{
    this->ui->cbbLocalIP->clear();

    QStringList ips;
    getLocalIPV4s(ips);

    this->ui->cbbLocalIP->addItems(ips);
//    if(ips.length() > 0) this->ui->cbbLocalIP->setCurrentIndex(0);
}

void MainWindow::socketOCEvent()
{
    switch(this->socket_type)
    {
    case SOCKET_TYPE_UDP:
        this->__socketOCEventUDP();
        break;
    case SOCKET_TYPE_TCP_CLIENT:
        this->__socketOCEventTCPClient();
        break;
    case SOCKET_TYPE_TCP_SERVER:
        this->__socketOCEventTCPServer();
    default:
        break;
    }

    this->socketOCUIEvent();

}

void MainWindow::socketOCUIEvent()
{
    if(this->isConnected)
    {
        this->ui->btnOC->setText("Close");
        this->ui->cbbModeSelect->setEnabled(false);
        this->ui->cbbLocalIP->setEnabled(false);
        this->ui->leLocalPort->setEnabled(false);
        this->ui->leRemoteIP->setEnabled(false);
        this->ui->leRemotePort->setEnabled(false);
    }
    else
    {
        this->ui->btnOC->setText("Open");
        this->ui->cbbModeSelect->setEnabled(true);
        this->ui->cbbLocalIP->setEnabled(true);
        this->ui->leLocalPort->setEnabled(true);
        this->ui->leRemoteIP->setEnabled(true);
        this->ui->leRemotePort->setEnabled(true);
    }
}


void MainWindow::rxEvent()
{
    QByteArray rxBuffer;
    QString msg = getDateTimeForLog();

    switch(this->socket_type)
    {
    case SOCKET_TYPE_UDP:
        msg += "UDP RX: ";
        this->__rxEventUDP(rxBuffer, msg);
        break;
    case SOCKET_TYPE_TCP_CLIENT:
        msg += "TCPClient RX: ";
        this->__rxEventTCPServer(rxBuffer, this->tcpClient, msg);
        break;
    case SOCKET_TYPE_TCP_SERVER:
        msg += "TCPServer RX: ";
        this->__rxEventTCPServer(rxBuffer, qobject_cast<QTcpSocket*>(sender()), msg);
        break;
    default:
        break;
    }

    if(rxBuffer.size() > 0)
    {
        this->ui->teLog->appendPlainText(msg);
    }
}

// get from ui
void MainWindow::txEvent()
{
    QString s = this->ui->teTXData->toPlainText();
    s += this->mapTxEndWith.value(this->ui->cbbTXEndWith->currentText());
    QByteArray b = s.toUtf8();
    this->txEvent(b);
}

void MainWindow::txEvent(QString s)
{
    QByteArray b = s.toUtf8();
    this->txEvent(b);
}

void MainWindow::txEvent(QByteArray b)
{
    QString msg = getDateTimeForLog();

    switch(this->socket_type)
    {
    case SOCKET_TYPE_UDP:
        msg += "UDP TX: ";
        this->__txEventUDP(b, msg);
        break;
    case SOCKET_TYPE_TCP_CLIENT:
        msg += "TCPClient TX: ";
        this->__txEventTCPClient(b, msg);
        break;
    case SOCKET_TYPE_TCP_SERVER:
        msg += "TCPServer TX: ";
        this->__txEventTCPServer(b, NULL, msg);
        break;
    default:
        break;
    }

    if(b.size() > 0)
    {
        this->ui->teLog->appendPlainText(msg);
    }
}

void MainWindow::cbbModeChangedEvent(int i)
{
    i = i;
    this->socket_type = this->ui->cbbModeSelect->currentIndex();
    this->modeChangedUIEvent(this->socket_type);
}

void MainWindow::modeChangedUIEvent(int socket_type)
{
    switch(socket_type)
    {
    case SOCKET_TYPE_UDP:
        this->ui->lbLocalIP->setHidden(false);
        this->ui->cbbLocalIP->setHidden(false);
        this->ui->lbLocalPort->setHidden(false);
        this->ui->leLocalPort->setHidden(false);
        this->ui->lbRemoteIP->setHidden(false);
        this->ui->leRemoteIP->setHidden(false);
        this->ui->lbRemotePort->setHidden(false);
        this->ui->leRemotePort->setHidden(false);
        break;
    case SOCKET_TYPE_TCP_CLIENT:
        this->ui->lbLocalIP->setHidden(true);
        this->ui->cbbLocalIP->setHidden(true);
        this->ui->lbLocalPort->setHidden(true);
        this->ui->leLocalPort->setHidden(true);
        this->ui->lbRemoteIP->setHidden(false);
        this->ui->leRemoteIP->setHidden(false);
        this->ui->lbRemotePort->setHidden(false);
        this->ui->leRemotePort->setHidden(false);
        break;
    case SOCKET_TYPE_TCP_SERVER:
        this->ui->lbLocalIP->setHidden(false);
        this->ui->cbbLocalIP->setHidden(false);
        this->ui->lbLocalPort->setHidden(false);
        this->ui->leLocalPort->setHidden(false);
        this->ui->lbRemoteIP->setHidden(true);
        this->ui->leRemoteIP->setHidden(true);
        this->ui->lbRemotePort->setHidden(true);
        this->ui->leRemotePort->setHidden(true);
        break;
    }
}

void MainWindow::TCPClientDisconnectedEvent()
{
    qDebug() << __func__;
    this->tcpClient->close();
    this->isConnected = false;
    this->socketOCUIEvent();
}

void MainWindow::TCPServerNewConnectionEvent()
{
    QTcpSocket* __tcpClient = this->tcpServer->nextPendingConnection();
    qDebug() << __func__ << __tcpClient->peerAddress().toString() << __tcpClient->peerPort();

    this->tcpServerInClients.append(__tcpClient);
    connect(__tcpClient, SIGNAL(readyRead()), this, SLOT(rxEvent()));
    connect(__tcpClient, SIGNAL(disconnected()), this, SLOT(TCPServerCloseConnectionEvent()));
}

void MainWindow::TCPServerCloseConnectionEvent()
{
    QTcpSocket* __tcpSocket = qobject_cast<QTcpSocket*>(sender());

    qDebug() << __func__ << __tcpSocket << __tcpSocket->peerAddress().toString() << __tcpSocket->peerPort();

    this->tcpServerInClients.removeOne(__tcpSocket);

    __tcpSocket->deleteLater();
}

void MainWindow::txDatasFormOCEvent()
{
    qDebug() << "txDatasFormOCEvent";
    if(this->txDatasForm == NULL)
    {
        qDebug() << "create ";
        this->txDatasForm = new TXDatasForm(this);
        connect(this->txDatasForm, SIGNAL(tx(QString)), this, SLOT(txEvent(QString)));
    }

    this->txDatasForm->isHidden() ? \
                this->txDatasForm->show(this->x() + this->frameGeometry().width(), this->y()) \
              :
                this->txDatasForm->hide();
}






