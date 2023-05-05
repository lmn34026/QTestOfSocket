#include "TXDatasForm.h"
#include "ui_TXDatasForm.h"
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "utilCommTools.h"
#include <algorithm>

bool compareQObjPropertyFunc(QObject *a, QObject *b)
{
    return (*((int*)(a->property("SN").data()))) < (*((int*)(b->property("SN").data())));
}

struct
{
    bool operator()(QObject *a, QObject *b) const
    {
        return (*((int*)(a->property("SN").data()))) < (*((int*)(b->property("SN").data())));
    }
}
compareQObjPropertyStruct;


TXDatasForm::TXDatasForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TXDatasForm)
{
    ui->setupUi(this);

    this->collection();

    std::sort(this->leList.begin(), this->leList.end(), compareQObjPropertyStruct);
    std::sort(this->leList.begin(), this->leList.end(), compareQObjPropertyStruct);

    foreach(QPushButton* __btn, this->btnList)
    {
        //        qDebug() << "QPushButton: " << __btn->objectName();
        connect(__btn, SIGNAL(clicked()), this, SLOT(btnClicked()));
    }
    //    foreach(QLineEdit* __le, this->leList)
    //    {
    //        qDebug() << "QLineEdit: " << __le->objectName();
    //    }

    this->cfgLoadToUI();
}

TXDatasForm::~TXDatasForm()
{
    this->cfgSaveFromUI();
    delete ui;
}

void TXDatasForm::show()
{
    this->show(0, 0);
}

void TXDatasForm::show(int x, int y)
{
    QDialog::show();
    this->move(x, y);
}

void TXDatasForm::collection()
{
    static char QPushButtonNameS[] = "QPushButton";
    static char QLineEditNameS[] = "QLineEdit";
    static QString patternForBtnNMatch("btnTXData(\\d+)");
    static QString patternForLeNMatch("leTXData(\\d+)");

    this->leList.clear();
    this->btnList.clear();

    foreach(QObject* obj, this->ui->gridLayoutWidget->children())
    {
        if(memcmp(QPushButtonNameS, obj->metaObject()->className(), sizeof(QPushButtonNameS)) == 0)
        {
            QPushButton* __btn = qobject_cast<QPushButton*>(obj);
            this->btnList.append(__btn);
            if(__btn != nullptr){
                this->__reAndSetSNOfObjProperty(patternForBtnNMatch, __btn);
                //                qDebug() << __btn->metaObject()->className() << __btn->objectName() << __btn->property("SN") << QString::number(*((int*)(__btn->property("SN").data())));
            }
        }
        else if(memcmp(QLineEditNameS, obj->metaObject()->className(), sizeof(QLineEditNameS)) == 0)
        {
            QLineEdit* __le = qobject_cast<QLineEdit*>(obj);
            this->leList.append(__le);
            if(__le != nullptr){
                this->__reAndSetSNOfObjProperty(patternForLeNMatch, __le);
                //                qDebug() << __le->metaObject()->className() << __le->objectName() << __le->property("SN") << QString::number(*((int*)(__le->property("SN").data())));
            }
        }
    }


}

void TXDatasForm::cfgLoadToUI()
{
    configUtil cfg = configUtil("config.ini");

    foreach(QLineEdit* __le, this->leList)
    {
        __le->setText(cfg.getValue("DATA", QString("txData") + QString::number(__getSNOfObjProperty(__le))));
    }
}

void TXDatasForm::cfgSaveFromUI()
{
    configUtil cfg = configUtil("config.ini");

    foreach(QLineEdit* __le, this->leList)
    {
        QString __text = __le->text();
        cfg.setValue("DATA", QString("txData") + QString::number(*((int*)(__le->property("SN").data()))), __text);
    }
}

bool TXDatasForm::__reAndSetSNOfObjProperty(QString pattrn, QObject* obj)
{
    bool r = false;
    QRegularExpression re(pattrn);
    QRegularExpressionMatch match = re.match(obj->objectName());
    QString sInt;
    int iInt;
    if (match.hasMatch())
    {
        bool isInt;
        sInt = match.captured(1);
        iInt = sInt.toInt(&isInt);
        if(isInt){
            r = obj->setProperty("SN", iInt);
        }
    }

    return r;
}

int TXDatasForm::__getSNOfObjProperty(QObject *obj)
{

    return *((int*)(obj->property("SN").data()));
}


void TXDatasForm::btnClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    static QRegularExpression reForBtnTxMatch("btnTXData(\\d+)");
    QRegularExpressionMatch match = reForBtnTxMatch.match(btn->objectName());
    QString btnNumS;
    int btnNumI;
    if (match.hasMatch())
    {
        QString btnNumS;
        bool isInt;
        btnNumS = match.captured(1);
        btnNumI = btnNumS.toInt(&isInt);
        if(isInt){
            QLineEdit* le = this->findChild<QLineEdit*>(QString("leTXData") + btnNumS);
            qDebug() << "btnClicked find: " << le;
            if(le != 0) {
                qDebug() << "emit: " << le->text();
                emit tx(le->text());
            }
        }
    }
}
