#include "utilUiElement.h"



QComboBoxPlus::QComboBoxPlus(QWidget *parent) :
    QComboBox(parent)
{
//    this->connect(this, SIGNAL(clicked()), this, SLOT(clickEvent()));
}

void QComboBoxPlus::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }

    //    调用父类的方法，处理事件
    QComboBox::mousePressEvent(event);
}


void QComboBoxPlus::clickEvent()
{
//    qDebug() << "clickEvent";
}


#ifdef USE_QSERIALPORT

CBBSerialPortSelectUtil::CBBSerialPortSelectUtil(QWidget *parent) : QComboBoxPlus(parent)
{
    //    qDebug() << "create serialPortCBB";
}



void CBBSerialPortSelectUtil::clickEvent()
{
    this->clear();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        this->addItem(info.portName());
    }

}

#endif
