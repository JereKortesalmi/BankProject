#include "withdrawcall.h"

withdrawCall::withdrawCall(QObject *parent)
    : QObject{parent}
{
      qDebug()<<"withdrawCall was constructed.";
}

void withdrawCall::sendRequest(QByteArray token, int id, double sum)
{


    qDebug()<<"sendRequest from withdrawCall()";
    //Esimerkkidata
    QDateTime current = QDateTime::currentDateTime();
    QJsonObject jsonObj;
    jsonObj.insert("transaction_account_id", id);
    jsonObj.insert("transaction_atm_id","1");           // read from file will be added somewhere else, so will need to add variable here
    jsonObj.insert("transaction_time", current.toString());
    jsonObj.insert("transaction_type","WITHDRAW");
    jsonObj.insert("transaction_amount", QString::number(sum));


    QUrl url("http://localhost:3000/withdraw/" + QString::number(id));
    QNetworkRequest request(url);

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU


    w_manager = new QNetworkAccessManager(this);
    w_reply = w_manager->put(request,QJsonDocument(jsonObj).toJson());
    connect(w_manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(onManagerFinished(QNetworkReply*)));
    connect(w_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)),
            this, SLOT(onErrorOccurred(QNetworkReply::NetworkError)));
    w_manager->deleteLater();
}

withdrawCall::~withdrawCall()
{
    qDebug()<<"witdrawManager was destroyed";
}

QByteArray withdrawCall::getResponse_data() const
{
    return response_data;
}

void withdrawCall::onManagerFinished(QNetworkReply *reply)
{
    if(reply->error()) {
        qDebug() << reply->errorString();
        return;
    }
    response_data = reply->readAll();

    emit dataRead();


}

void withdrawCall::onErrorOccurred(QNetworkReply::NetworkError code)
{
    qDebug()<<"Network error:" << code;
}
