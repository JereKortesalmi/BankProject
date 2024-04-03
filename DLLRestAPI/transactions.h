#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "DLLRestAPI_global.h"
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork>
#include <QJsonDocument>

#include <../bank-automat/data.h>


namespace Ui {
class Transactions;
}

class DLLRESTAPI_EXPORT Transactions : public QDialog
{
    Q_OBJECT

public:
    explicit Transactions(QWidget *parent = nullptr);
    explicit Transactions(QList<transactions> *table);
    ~Transactions();

private slots:
    void clickHandler();
    void onManagerFinished(QNetworkReply* reply);
    void onErrorOccurred(QNetworkReply::NetworkError code);

private:
    Ui::Transactions *ui;
    QNetworkAccessManager* manager;
    QNetworkReply* reply;
    QByteArray response_data;

signals:
    void ResponseToMain(QJsonArray reply);
};

#endif // TRANSACTIONS_H
