#ifndef UTILSERIALPORT_H
#define UTILSERIALPORT_H

//#include <QSerialPort>
//#include <QSerialPortInfo>
#include <QString>
#include <QByteArray>

//add this to pro file
//CONFIG   += serialport
//greaterThan(QT_MAJOR_VERSION, 4): QT += serialport




class serialPortUtil : public QSerialPort
{
    Q_OBJECT
public:
    serialPortUtil(QString port="");
    ~serialPortUtil();
    static void showSerialPorts();
    bool configUtil(const QString &name, QSerialPort::BaudRate baudrate=QSerialPort::Baud115200, QSerialPort::FlowControl flowControl=QSerialPort::NoFlowControl);
    bool openUtil(QSerialPort::OpenModeFlag openMode=QIODevice::ReadWrite);
    void closeUtil();
    bool txUtil(const char* data);  // Its not thread-safe. Use SIGNAL and SLOT instead
    QByteArray rxUtil();

private:
    QByteArray __rx();
    bool __tx(QByteArray s, int delayMs=100);

public slots:
    // QObject and all of its subclasses are not thread-safe.
    // Its Recommend to use SLOT to prevent "QObject: Cannot create children for a parent that is in a different thread" ERROR in QThread
    // Return value performs NOTHING when its used as SLOT func
    bool txEvent(QString s, int delayMs);
    bool txEvent(QByteArray s, int delayMs);

};


namespace utilSerialPortNS{
}




#endif // UTILSERIALPORT_H
