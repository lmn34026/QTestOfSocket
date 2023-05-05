#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QTcpSocket>
#include <QTcpServer>
#include <QThread>
#include <QList>
#include "utilCommTools.h"
//#include "utilSerialPort.h"
#include "utilSocket.h"
#include "utilUiElement.h"
#include "QDragMoveEvent"
#include "TXDatasForm.h"
#include "QStringList"
#include <QMap>

namespace Ui {
class MainWindow;
}
//using namespace utilsSocket;

enum SOCKET_TYPE_EM
{
    SOCKET_TYPE_UDP,
    SOCKET_TYPE_TCP_CLIENT,
    SOCKET_TYPE_TCP_SERVER
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    TXDatasForm* txDatasForm;
    int socket_type;
//    QStringList txEndWithSL;
    // key as UI and value as value
    QMap<QString, QString> mapTxEndWith;
    Ui::MainWindow *ui;
    bool isConnected;
    QString localIP;
    quint16 localPort;
    QString remoteIP;
    quint16 remotePort;
    udpUtil *udp;
    QTcpSocket *tcpClient;
    QTcpServer *tcpServer;
    bool UDPInit();
    bool TCPClientInit();
    bool TCPServerInit();
    bool refreshIPPortFromUI();
    int __socketOCEventUDP();
    int __socketOCEventTCPClient();
    int __socketOCEventTCPServer();
    int __rxEventUDP(QByteArray &rxBuffer, QString &msg);
    int __rxEventTCPClient(QByteArray &rxBuffer, QTcpSocket* tcpClient, QString &msg);
    int __rxEventTCPServer(QByteArray &rxBuffer, QTcpSocket* tcpClient, QString &msg);
    int __txEventUDP(QByteArray &txBuffer, QString &msg);
    int __txEventTCPClient(QByteArray &txBuffer, QString &msg);
    int __txEventTCPServer(QByteArray &txBuffer, QTcpSocket* tcpClient, QString &msg);
    QThread* thTCPSeverWaitConnection;
//    bool isTCPServerConnected;
    QList<QTcpSocket*> tcpServerInClients;
    bool deleteTCPServerInClients();
    void cfgLoadToUI();
    void cfgSaveFromUI();
    void moveEvent(QMoveEvent *event) override;





private slots:
    void cbbLocalIPChangedEvent();
    void socketOCEvent();
    void socketOCUIEvent();
    void rxEvent();
    void txEvent();
    void txEvent(QString s);
    void txEvent(QByteArray b);
    void cbbModeChangedEvent(int);
    void modeChangedUIEvent(int);
    void TCPClientDisconnectedEvent();
    void TCPServerNewConnectionEvent();
    void TCPServerCloseConnectionEvent();
    void txDatasFormOCEvent();



};

#endif // MAINWINDOW_H
