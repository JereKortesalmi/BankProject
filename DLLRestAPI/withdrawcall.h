#ifndef WITHDRAWCALL_H
#define WITHDRAWCALL_H

#include<dllrestapi.h>

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class DLLRESTAPI_EXPORT withdrawCall : public QObject
{
    Q_OBJECT
public:
    //explicit withdrawCall(QObject *parent = nullptr);
    withdrawCall();
    ~withdrawCall();
    void sendTransaction(QByteArray token, int id, int atm_id, double sum);
    void getAtmInfo(QByteArray token,int id);

    // print in qdebug();
    void printAtmSetBills();
    void printAtmBills();

    QByteArray getResponse_data() const;

    double atmBalance = 0;
    int bills_20 = 100;
    int bills_50 = 100;
    int bills_100 = 10;
    int bills_200 = 10;
    int bills_500 = 0;

    int set_500_bills = 0;
    int set_200_bills = 0;
    int set_100_bills = 0;
    int set_50_bills = 0;
    int set_20_bills = 0;

    int amount_20;
    int amount_50;
    int amount_100;
    int amount_200;

    bool usable_20;
    bool usable_50;
    bool usable_100;
    bool usable_200;
    bool usable_500;

    int withdrawAmount = 0;

    void checkBills(int withdrawal);
    bool checkBillsAvailable();
    void clearBills();
    void removeBills();
    void updateBills(QByteArray token,int id, double sum);

private:
    QNetworkAccessManager *w_manager;
    QNetworkAccessManager *atm_manager;
    QNetworkAccessManager *atm_write_manager;
    QNetworkReply *w_reply;
    QNetworkReply *atm_reply;
    QByteArray response_data;

    QByteArray myToken;

private slots:

    void onManagerFinished(QNetworkReply* reply);
    void onErrorOccurred(QNetworkReply::NetworkError code);
    void atmManagerFinished(QNetworkReply* reply);
    void atmErrorOccurred(QNetworkReply::NetworkError code);
    void onbillsManagerFinished(QNetworkReply* reply);
    void onBillsErrorOccurred(QNetworkReply::NetworkError code);
signals:
    void dataRead();
    void billsdataWritten();
    void atmInfoSent();
    void billsOK(bool);
};

#endif // WITHDRAWCALL_H
