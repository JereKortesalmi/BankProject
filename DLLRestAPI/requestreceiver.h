#ifndef REQUESTRECEIVER_H
#define REQUESTRECEIVER_H

#include <QDebug>
#include "DLLRestAPI_global.h"
#include "login.h"
#include "transactions.h"
#include "withdrawcall.h"
#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork>
#include <QJsonDocument>

class requestReceiver
{
public:
    requestReceiver();
    ~requestReceiver();

private:
    login *log = nullptr;
    Transactions *tra = nullptr;
    withdrawCall *wit = nullptr;
    QNetworkAccessManager *RManager = nullptr;

signals:
    void sendResult();
};

#endif // REQUESTRECEIVER_H
