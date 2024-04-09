#ifndef BALANCE_H
#define BALANCE_H
#include "DLLRestAPI_global.h"
#include <QDialog>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class balance;
}

class DLLRESTAPI_EXPORT balance : public QDialog
{
    Q_OBJECT

public:
    explicit balance(QWidget *parent = nullptr);
    ~balance();
signals:
    void sendToMain(QString);

private slots:
    void getBalance(QNetworkReply *reply);
    void clickHandler();
    void onErrorOccurred(QNetworkReply::NetworkError code);

private:
    Ui::balance *ui;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // BALANCE_H
