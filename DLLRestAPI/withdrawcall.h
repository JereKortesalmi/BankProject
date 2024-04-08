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
    withdrawCall(QByteArray, int, double);
    ~withdrawCall();

    QByteArray getResponse_data() const;

private:
    QNetworkAccessManager *w_manager;
    QNetworkReply *w_reply;
    QByteArray response_data;

private slots:

    void onManagerFinished(QNetworkReply* reply);
    void onErrorOccurred(QNetworkReply::NetworkError code);
signals:
    void dataRead();
};

#endif // WITHDRAWCALL_H
