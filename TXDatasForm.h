#ifndef TXDATASFORM_H
#define TXDATASFORM_H

#include <QDialog>
#include <QList>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class TXDatasForm;
}

class TXDatasForm : public QDialog
{
    Q_OBJECT

public:
    explicit TXDatasForm(QWidget *parent = nullptr);
    ~TXDatasForm();
    void show();
    void show(int x, int y);
    QList<QPushButton*> btnList;
    QList<QLineEdit*> leList;

private:
    Ui::TXDatasForm *ui;
    void collection();
    void cfgLoadToUI();
    void cfgSaveFromUI();
    static bool __reAndSetSNOfObjProperty(QString pattrn, QObject* obj);
    static int __getSNOfObjProperty(QObject* obj);

signals:
    void tx(QString);

public slots:
    void btnClicked();
};

#endif // TXDATASFORM_H
