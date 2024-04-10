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

void login::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    QMessageBox msgBox;
    //qDebug()<<response_data;
    if(response_data=="-4078" || response_data.length()==0){

        msgBox.setText("Virhe tietoyhteydessä");
        msgBox.exec();
    }
    else{
        if(response_data!="false"){
            //kirjautuminen onnistui
            emit sendSignalLogin(response_data);
        }
        else{
            msgBox.setText("Korttinumero/pin ei täsmää");
            msgBox.exec();
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();
}

