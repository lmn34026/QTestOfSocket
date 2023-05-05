#ifndef UTILCOMMTOOLS_H
#define UTILCOMMTOOLS_H

#include <QString>
#include <QDebug>
//#include <QSerialPort>
#include <QThread>
#include <QSettings>



// 实现多线程
// 方法1：继承QThread并重载run(即下面的实现方法)
// 方法2：创建QThread对象，调用QObject的moveToThread方法，connect(doSomething, finished, result...)，之后obj发射信号，开始线程
class threadUtil : public QThread
{

    Q_OBJECT
public:
    threadUtil();
    virtual void run();
    virtual void tellToTerminate();
    virtual void waitForTerminate();
    virtual void setToResume();
    ~threadUtil();

protected:
    bool needToTerminate;

public slots:

signals:

private:

};


class configUtil
{
public:
    configUtil(QString configFileName);
    ~configUtil();
    QString getValue(QString group, QString key);
    bool setValue(QString group, QString key, QString & value);
    void dump();

private:
    bool isInit;
    QString configFileName;
    QSettings *cfg;
};


namespace utilCommToolsNS{
QString getDateTimeForLog();
QString getNowDateTime(QString&);
}


#endif // UTILCOMMTOOLS_H
