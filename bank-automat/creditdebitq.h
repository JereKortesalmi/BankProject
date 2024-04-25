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
#include <QScreen>
#include "data.h"

namespace Ui {
class creditdebitq;
}

class creditdebitq : public QDialog
{
    Q_OBJECT

public:
    explicit creditdebitq(QWidget *parent = nullptr);
    ~creditdebitq();

    screensize screenSize;
    int sHeight;
    int sWidth;

    void selectAccountHandler(const QJsonArray jsonArray);
signals:

    void sendAccountId(int, QString, QString, QString, bool);


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
    QString bothId;

};

#endif // CREDITDEBITQ_H
