#include "utilSerialPort.h"
#include <QDebug>



serialPortUtil::serialPortUtil(QString port) : QSerialPort(port)
{
    this->setBaudRate(QSerialPort::Baud115200);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);
    this->setStopBits(QSerialPort::OneStop);
    this->setFlowControl(QSerialPort::NoFlowControl);

    connect(this, SIGNAL(txData(QByteArray, int)), this, SLOT(txEvent(QByteArray, int)));
    connect(this, SIGNAL(txData(QString, int)), this, SLOT(txEvent(QString, int)));
}

serialPortUtil::~serialPortUtil()
{
    QSerialPort::close();
}

void serialPortUtil::showSerialPorts()
{
    qDebug() << "showSerialPorts >>>";

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "serialNumber: " << info.serialNumber();
        qDebug() << "systemLocation: " << info.systemLocation();
        qDebug() << "isBusy: " << info.isBusy() << endl;
    }

    qDebug() << "<<< showSerialPorts";
}

bool serialPortUtil::configUtil(const QString &name, QSerialPort::BaudRate baudrate, QSerialPort::FlowControl flowControl)
{
    this->setPortName(name);
    this->setBaudRate(baudrate);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);
    this->setStopBits(QSerialPort::OneStop);
    this->setFlowControl(flowControl);

    return true;
}

bool serialPortUtil::openUtil(QSerialPort::OpenModeFlag openMode)
{
    if(this->isOpen())
    {
        return true;
    }
    else if(QSerialPort::open(openMode))
    {
        qDebug() << "open ok ";
        return true;
    }
    else
    {
        qDebug() << "open ng!";
        return false;
    }
}

void serialPortUtil::closeUtil()
{
    QSerialPort::close();
}

bool serialPortUtil::txUtil(const char* data)
{
    return this->__tx(QByteArray(data));
}

QByteArray serialPortUtil::rxUtil()
{
    return this->__rx();
}

QByteArray serialPortUtil::__rx()
{
    int sizeToRead = this->bytesAvailable();

    return (sizeToRead ? this->read(sizeToRead) : QByteArray());
}

bool serialPortUtil::txEvent(QString s, int delayMs)
{
    return this->__tx(QByteArray(s.toUtf8()), delayMs);
}

bool serialPortUtil::txEvent(QByteArray s, int delayMs)
{
    return this->__tx(s, delayMs);
}

bool serialPortUtil::__tx(QByteArray s, int delayMs)
{
    int retry = 5;
    while(!(this->isOpen()) && (retry--))
    {
        this->openUtil();
    }

    if(retry <= 0) return false;

    this->write(s);

    return this->waitForBytesWritten(delayMs);
}














