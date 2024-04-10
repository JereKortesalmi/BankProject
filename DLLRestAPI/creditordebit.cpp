#include "creditordebit.h"
#include "requestreceiver.h"
#include
creditOrDebit::creditOrDebit() {}

QString getCardType(QString cn)
{
    QUrl url("http://localhost:3000/credit_or_debit/"+cn);
    QNetworkRequest request(url);
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply* reply;
    reply = manager->get(request);
    return 0;
}

void creditOrDebit::onManagerFinished(QNetworkReply *reply)
{
    if (reply->error())
    {
        qDebug() << reply->errorString();
        return;
    }
    response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    if (json_doc.isArray())
    {
        QJsonArray jsonArray = json_doc.array();

        QString jsonString = QJsonDocument(jsonArray).toJson(QJsonDocument::Compact);
        emit cardTypeSent(jsonString);
    }

}


