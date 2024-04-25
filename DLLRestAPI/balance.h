#ifndef BALANCE_H
#define BALANCE_H
#include "DLLRestAPI_global.h"
#include <QDialog>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
extern "C" DLLRESTAPI_EXPORT void clickBalanceHandler(int);

namespace Ui {
class balance;
}

class DLLRESTAPI_EXPORT balance : public QDialog
{
    Q_OBJECT

public:
    explicit balance(QWidget *parent = nullptr);
    ~balance();
    void fetchAccountDetails(QByteArray,QString);
    void fetchBalance(QByteArray,int);
public slots:
    void saveAccountDetails(QNetworkReply *reply);
    void getBalance(QNetworkReply *reply);
    void updateBalance(QByteArray, int, QString, QString);
signals:
    void sendAccountIdBalance(int,QString, QString, QString, bool);
    void opencreditdebitq(QJsonArray);
    void openAdmin();
    void balanceToMainmenu(QString);

private slots:
    void onErrorOccurred(QNetworkReply::NetworkError code);
    void balanceUpdateFinished(QNetworkReply*);

private:
    Ui::balance *ui;
    QNetworkAccessManager *accountManager;
    QNetworkAccessManager *balanceManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray myToken;
    QString bal;
    int accountId;
    int creditMax;
    int creditCurrent;
    //QString balance;
    QString accountType;
};

#endif // BALANCE_H
