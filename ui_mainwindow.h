/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "utilUiElement.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPlainTextEdit *teLog;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lbLocalIP;
    QComboBoxPlus *cbbLocalIP;
    QLabel *lbLocalPort;
    QLineEdit *leLocalPort;
    QLabel *lbRemoteIP;
    QLineEdit *leRemoteIP;
    QLabel *lbRemotePort;
    QLineEdit *leRemotePort;
    QPushButton *btnOC;
    QComboBox *cbbModeSelect;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPlainTextEdit *teTXData;
    QComboBox *cbbTXEndWith;
    QPushButton *btnTX;
    QPushButton *btnClear;
    QPushButton *btnTXDatasOC;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(840, 566);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        teLog = new QPlainTextEdit(centralWidget);
        teLog->setObjectName(QStringLiteral("teLog"));
        teLog->setGeometry(QRect(310, 50, 511, 461));
        teLog->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 90, 291, 241));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lbLocalIP = new QLabel(verticalLayoutWidget);
        lbLocalIP->setObjectName(QStringLiteral("lbLocalIP"));

        verticalLayout->addWidget(lbLocalIP);

        cbbLocalIP = new QComboBoxPlus(verticalLayoutWidget);
        cbbLocalIP->setObjectName(QStringLiteral("cbbLocalIP"));
        cbbLocalIP->setEditable(true);

        verticalLayout->addWidget(cbbLocalIP);

        lbLocalPort = new QLabel(verticalLayoutWidget);
        lbLocalPort->setObjectName(QStringLiteral("lbLocalPort"));

        verticalLayout->addWidget(lbLocalPort);

        leLocalPort = new QLineEdit(verticalLayoutWidget);
        leLocalPort->setObjectName(QStringLiteral("leLocalPort"));

        verticalLayout->addWidget(leLocalPort);

        lbRemoteIP = new QLabel(verticalLayoutWidget);
        lbRemoteIP->setObjectName(QStringLiteral("lbRemoteIP"));

        verticalLayout->addWidget(lbRemoteIP);

        leRemoteIP = new QLineEdit(verticalLayoutWidget);
        leRemoteIP->setObjectName(QStringLiteral("leRemoteIP"));

        verticalLayout->addWidget(leRemoteIP);

        lbRemotePort = new QLabel(verticalLayoutWidget);
        lbRemotePort->setObjectName(QStringLiteral("lbRemotePort"));

        verticalLayout->addWidget(lbRemotePort);

        leRemotePort = new QLineEdit(verticalLayoutWidget);
        leRemotePort->setObjectName(QStringLiteral("leRemotePort"));

        verticalLayout->addWidget(leRemotePort);

        btnOC = new QPushButton(centralWidget);
        btnOC->setObjectName(QStringLiteral("btnOC"));
        btnOC->setGeometry(QRect(10, 360, 289, 23));
        cbbModeSelect = new QComboBox(centralWidget);
        cbbModeSelect->setObjectName(QStringLiteral("cbbModeSelect"));
        cbbModeSelect->setGeometry(QRect(10, 50, 289, 20));
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 410, 281, 131));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        teTXData = new QPlainTextEdit(verticalLayoutWidget_2);
        teTXData->setObjectName(QStringLiteral("teTXData"));

        verticalLayout_2->addWidget(teTXData);

        cbbTXEndWith = new QComboBox(verticalLayoutWidget_2);
        cbbTXEndWith->setObjectName(QStringLiteral("cbbTXEndWith"));

        verticalLayout_2->addWidget(cbbTXEndWith);

        btnTX = new QPushButton(verticalLayoutWidget_2);
        btnTX->setObjectName(QStringLiteral("btnTX"));

        verticalLayout_2->addWidget(btnTX);

        btnClear = new QPushButton(centralWidget);
        btnClear->setObjectName(QStringLiteral("btnClear"));
        btnClear->setGeometry(QRect(310, 520, 75, 23));
        btnTXDatasOC = new QPushButton(centralWidget);
        btnTXDatasOC->setObjectName(QStringLiteral("btnTXDatasOC"));
        btnTXDatasOC->setGeometry(QRect(750, 520, 75, 23));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lbLocalIP->setText(QApplication::translate("MainWindow", "LocalIP", 0));
        lbLocalPort->setText(QApplication::translate("MainWindow", "LocalPort", 0));
        leLocalPort->setText(QString());
        lbRemoteIP->setText(QApplication::translate("MainWindow", "Remote IP:", 0));
        lbRemotePort->setText(QApplication::translate("MainWindow", "Remote Port:", 0));
        btnOC->setText(QApplication::translate("MainWindow", "OK", 0));
        btnTX->setText(QApplication::translate("MainWindow", "Send", 0));
        btnClear->setText(QApplication::translate("MainWindow", "Clear", 0));
        btnTXDatasOC->setText(QApplication::translate("MainWindow", ">>", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
