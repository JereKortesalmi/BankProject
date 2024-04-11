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

class DLLRESTAPI_EXPORT requestReceiver
{
public:
    requestReceiver();
    ~requestReceiver();

    login log;
    Transactions tra;
    withdrawCall wit;
    balance bal;

private:

    /*
    login *log = nullptr;
    Transactions *tra = nullptr;
    withdrawCall *wit = nullptr;
    QNetworkAccessManager *RManager = nullptr;
    */

signals:
    void sendResult();
};

#endif // REQUESTRECEIVER_H
