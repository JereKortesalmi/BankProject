#ifndef CREDITORDEBIT_H
#define CREDITORDEBIT_H
#include "DLLRestAPI_global.h"
#include <QDialog>
#include <QtNetwork>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonArray>
#include <QString>
#include <QDebug>
#include <QObject>

class DLLRESTAPI_EXPORT creditOrDebit : public QObject
{
    Q_OBJECT
public:
    explicit creditOrDebit(QWidget *parent = nullptr);
    ~creditOrDebit();
    QString getCardType();
    QString cardNumber;
private:
    QByteArray response_data;
public slots:
    QString getCardType(QString cn);
private slots:
    void onManagerFinished(QNetworkReply *reply);
signals:
    void cardTypeSent(QString jsonString);
};

#endif // CREDITORDEBIT_H
