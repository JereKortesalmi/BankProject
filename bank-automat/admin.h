#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include "data.h"
#include <QScreen>

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();

    screensize screenSize;
    int sHeight;
    int sWidth;

    QByteArray token;
public slots:
    void fetchBalance(int atmId, QByteArray token);
signals:
    void logOutAdmin();
private slots:
    void onBtnlogoutAdminClicked();
    void btnHandler();
    void saveBillsToAtm();
    void atmManagerFinished(QNetworkReply*);
    void getBalance(QNetworkReply *reply);
    void clickHandler();
    void selectedLineEdit();

private:
    Ui::admin *ui;
    QNetworkAccessManager *atmManager;
    QNetworkReply *reply;
    QByteArray myToken;
    int balance;
    int twenty = 0;
    int dataTwenty;
    int fifty = 0;
    int dataFifty;
    int hundred = 0;
    int dataHundred;
    int twoHundred = 0;
    int dataTwoHundred;
    int fiveHundred = 0;
    int dataFiveHundred;
    int atmId = 1;
    int state = 0;
    QString num = 0;
};



#endif // ADMIN_H
