#include "transfercall.h"

transfercall::transfercall() {
    qDebug() << "transfercall constructor";
}

transfercall::~transfercall()
{
    qDebug() << "transfercall destructor";
}

void transfercall::sendTransferRequest(QByteArray token, int senderId, int receiverId, int transferAmount)
{
    qDebug() << "Sending transfer request to backend.";
    qDebug() << "sender: " << senderId
             << "receiver: " << receiverId
             << "transferAmount: " << transferAmount;


    QString wUrl = "http://localhost:3000/transfer/";
    QUrl url(wUrl);
    QNetworkRequest request(url);
    QJsonObject obj;

    obj.insert("sender_id", senderId);
    obj.insert("recipient_id", receiverId);
    obj.insert("amount", transferAmount);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU


    t_manager = new QNetworkAccessManager(this);
    t_reply = t_manager->post(request, QJsonDocument(obj).toJson());
    connect(t_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onManagerFinished(QNetworkReply*)));
    connect(t_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
}

void transfercall::onManagerFinished(QNetworkReply *reply)
{
    response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    qDebug()<<json_doc;
    emit TransferFinished(QString::fromStdString(response_data.toStdString()));
}

void transfercall::onError(QNetworkReply::NetworkError code)
{
    qDebug()<<"Network error:" << code;
}
