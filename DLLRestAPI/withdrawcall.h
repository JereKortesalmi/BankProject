#ifndef WITHDRAWCALL_H
#define WITHDRAWCALL_H

#include<dllrestapi.h>

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class DLLRESTAPI_EXPORT withdrawCall : public QObject
{
    Q_OBJECT
public:
    explicit withdrawCall(QObject *parent = nullptr);    
    ~withdrawCall();
    void sendTransaction(QByteArray token, int id, double sum);
    void getAtmInfo(QByteArray token,int id);

    QByteArray getResponse_data() const;


    int bills_20 = 10;
    int bills_50 = 10;
    int bills_100 = 10;
    int bills_200 = 10;

    int set_200_bills = 0;
    int set_100_bills = 0;
    int set_50_bills = 0;
    int set_20_bills = 0;

    int amount_20;
    int amount_50;
    int amount_100;
    int amount_200;

    int withdrawAmount = 0;

    void checkBills(int withdrawal);

private:
    QNetworkAccessManager *w_manager;
    QNetworkReply *w_reply;
    QByteArray response_data;

    QByteArray myToken;

private slots:

    void onManagerFinished(QNetworkReply* reply);
    void onErrorOccurred(QNetworkReply::NetworkError code);
signals:
    void dataRead();
};

#endif // WITHDRAWCALL_H
