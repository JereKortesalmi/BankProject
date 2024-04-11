#include "login.h"

login::login()
{
    qDebug()<<"login luotu";
}

login::~login()
{
    qDebug()<<"login tuhottu";
}

void login::cardNumberLog(QString val)
{
    cardNumber=val;
    qDebug()<<"login cardnumber: "<<cardNumber;

}

void login::loginHandler(QString p)
{
    pinCode=p;
    qDebug()<<"kortti: "<<cardNumber<<"pin: "<<pinCode;
    QJsonObject jsonObj;
    jsonObj.insert("card_number",cardNumber);
    jsonObj.insert("card_pin",pinCode);

    QString site_url="http://localhost:3000/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void login::fetchAccountDetails()
{
    QString url="http://localhost:3000/id/" + cardNumber;
    QNetworkRequest request(url);
    //QUrlQuery query;
    //query.addQueryItem("card_number",cardNumber);

    //QUrl requestUrl(url);
    //requestUrl.setQuery(query.query());

    //QNetworkRequest request(requestUrl);
    accountManager = new QNetworkAccessManager(this);
    connect(accountManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(saveAccountDetails(QNetworkReply*)));
    reply = accountManager->get(request);
    qDebug() << "Fetching account details...";

}

void login::saveAccountDetails(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<"Response data: "<<response_data;
    QJsonDocument jsonResponse_data = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObject = jsonResponse_data.object();
    QString acc;
    /*acc = "Account | Type | Balance";
    foreach (const QJsonValue &value, jsonResponse_data) {
        QJsonObject json_obj = value.toObject();
        acc += QString::number(json_obj["account_id"].toInt())+"  |  ";
        acc += QString::number(json_obj["account_customer_id"].toInt())+"   | ";
        acc +=json_obj["account_type"].toString()+" | ";
        acc +=json_obj["account_balance"].toString()+"\n";
    }*/
    qDebug()<<"Response data: "<<response_data;
}

void login::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    QMessageBox msgBox;
    //qDebug()<<response_data;
    if(response_data=="-4078" || response_data.length()==0){
        QString message = "Virhe tietoyhteydessä";
        emit loginMessage(message);
        /*msgBox.setText("Virhe tietoyhteydessä");
        msgBox.exec();*/
    }
    else{
        if(response_data!="false"){
            //kirjautuminen onnistui
            emit sendSignalLogin(response_data);
            fetchAccountDetails();
        }
        else{
            QString message = "Korttinumero/pin ei täsmää";
            emit loginMessage(message);
            /*msgBox.setText("Korttinumero/pin ei täsmää");
            msgBox.exec();*/
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

