#ifndef UTILUIELEMENT_H
#define UTILUIELEMENT_H

#include <QString>
#include <QDebug>
#include <QComboBox>
#include <QMouseEvent>

//#define USE_QSERIALPORT


class QComboBoxPlus : public QComboBox
{
    Q_OBJECT
public:
    explicit QComboBoxPlus(QWidget *parent = 0);

protected:
    virtual void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();

public slots:
    virtual void clickEvent();
};



#ifdef USE_QSERIALPORT
#include <QSerialPort>
#include <QSerialPortInfo>

class CBBSerialPortSelectUtil : public QComboBoxPlus
{
    Q_OBJECT
public:
    explicit CBBSerialPortSelectUtil(QWidget *parent = 0);

signals:

protected slots:
    void clickEvent();
};

#endif


namespace utilUiElementNS{
}



#endif // UTILUIELEMENT_H
