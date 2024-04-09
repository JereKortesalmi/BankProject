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
