#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "DLLRestAPI_global.h"
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork>
#include <QJsonDocument>

//#include <../bank-automat/data.h>


namespace Ui {
class Transactions;
}

class DLLRESTAPI_EXPORT Transactions : public QDialog
{
    Q_OBJECT

public:
    //explicit Transactions(QWidget *parent = nullptr);
    Transactions();
    //explicit Transactions(QList<transactions> *table);
    ~Transactions();

    void requestTrasactions(QByteArray token,int accountId, int offsetInteger);

private slots:
    void clickHandler();
    void onManagerFinished(QNetworkReply* reply);
    void onErrorOccurred(QNetworkReply::NetworkError code);

private:
    Ui::Transactions *ui;
    QNetworkAccessManager* manager;
    QNetworkReply* reply;
    QByteArray response_data;
    QByteArray myToken;

signals:
    void ResponseToMain(QJsonArray reply);
    void handleEmptyResponse();
    void noMoreTransactions();
};

#endif // TRANSACTIONS_H
