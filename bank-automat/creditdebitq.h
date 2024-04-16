#ifndef CREDITDEBITQ_H
#define CREDITDEBITQ_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QObject>
#include <QDebug>
#include <mainmenu.h>

namespace Ui {
class creditdebitq;
}

class creditdebitq : public QDialog
{
    Q_OBJECT

public:
    explicit creditdebitq(QWidget *parent = nullptr);
    ~creditdebitq();

    void selectAccountHandler(const QJsonArray jsonArray);
signals:
    void sendAccountId(int, QString, QString);

private slots:
    void onCreditButtonClicked();
    void onDebitButtonClicked();

private:
    Ui::creditdebitq *ui;
    int accountId = -1;
    void selectAccount();
    QJsonArray jsonArray;
    mainMenu *mainmenu;
    QString accountType;
};

#endif // CREDITDEBITQ_H
