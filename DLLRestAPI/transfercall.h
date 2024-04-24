#ifndef TRANSFERCALL_H
#define TRANSFERCALL_H

#include<dllrestapi.h>

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class DLLRESTAPI_EXPORT transfercall : public QObject
{
    Q_OBJECT
public:
    transfercall();
    ~transfercall();

    void sendTransferRequest(QByteArray token, int senderId, int receiverId, int transferAmount);

    QByteArray myToken;

private:

    QNetworkAccessManager *t_manager;
    QNetworkReply *t_reply;
    QByteArray response_data;

public slots:
    void onManagerFinished(QNetworkReply*);
    void onError(QNetworkReply::NetworkError);

signals:
    void TransferFinished(QString);

};

#endif // TRANSFERCALL_H
