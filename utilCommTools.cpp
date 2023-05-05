#include "utilCommTools.h"
#include <QTime>
#include <QDateTime>
#include <QFile>
#include <QStringList>



QString utilCommToolsNS::getDateTimeForLog()
{
    QString format = "[yyyy-MM-dd HH:mm:ss:zzz] ";

    return utilCommToolsNS::getNowDateTime(format);
}


QString utilCommToolsNS::getNowDateTime(QString &format)
{
    return QDateTime::currentDateTime().toString(format);
}


threadUtil::threadUtil()
{
    this->needToTerminate = false;

//    注意:此时线程暂未跑起来,因此currentThreadId返回的是主线程的id
//    但是this->isRunning返回的是当前线程的运行状态
//    qDebug() << "create threadUtil: caller th id:" << this->currentThreadId() << " new th isRunning: " << this->isRunning();

//    connect(this, SIGNAL(finished()), this, SLOT(threadOverEvent()));
}

void threadUtil::run()
{
//     The starting point for the thread. After calling start(), the newly created thread calls this function. The default implementation simply calls exec().
//     You can reimplement this function to facilitate advanced thread management. Returning from this method will end the execution of the thread.

    int sleepMs = 1000;
    do
    {
        qDebug() << "go sleep: " << sleepMs << "ms by th: << this->currentThreadId()";
        this->msleep(1000);
        qDebug() << "after sleep" << this->currentThreadId();
    }while(!this->needToTerminate);

}

void threadUtil::tellToTerminate()
{
    this->needToTerminate = true;
}

void threadUtil::waitForTerminate()
{
//    do
//    {
//        this->msleep(1);
//    }while(!this->isFinished());

    this->wait();
}

void threadUtil::setToResume()
{
    this->needToTerminate = false;
}

threadUtil::~threadUtil()
{
    this->quit();
    this->wait();
}


configUtil::configUtil(QString configFileName)
{
    this->cfg = nullptr;
    this->isInit = false;

    if(!QFile::exists(configFileName))
    {
        QFile __file(configFileName);
        if(!__file.open(QIODevice::ReadWrite))
        {
            return;
        }
        __file.close();
    }

    this->configFileName = configFileName;
    this->cfg = new QSettings(this->configFileName, QSettings::IniFormat);

//    DEBUG_MSG("isWritable:" << this->cfg->isWritable());
//    this->dump();

    this->isInit = true;
}

configUtil::~configUtil()
{
    if(nullptr != this->cfg)
    {
        delete this->cfg;
    }
}

bool configUtil::setValue(QString group, QString key, QString & value)
{
    if((this->cfg == nullptr) || !this->isInit) return false;

    this->cfg->beginGroup(group);
    if(value.compare(this->cfg->value(key).toString()) != 0){
        this->cfg->setValue(key, value);
    }
    this->cfg->endGroup();

    return true;
}

void configUtil::dump()
{
    qDebug() << __func__;
    if((this->cfg == nullptr) || !this->isInit) return;

    foreach(QString __group, this->cfg->childGroups())
    {
        qDebug() << QString("[") + __group + "]";
        this->cfg->beginGroup(__group);

        foreach(QString __key, this->cfg->childKeys())
        {
            qDebug() << (QString("\t[") + __key + "]:[" + this->cfg->value(__key).toString() + "]");
        }

        this->cfg->endGroup();
    }
}

QString configUtil::getValue(QString group, QString key)
{
    if((this->cfg == nullptr) || !this->isInit) return "";

    this->cfg->beginGroup(group);
    QString value = this->cfg->value(key).toString();
    this->cfg->endGroup();

    return value;
}
