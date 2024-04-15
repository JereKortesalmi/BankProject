#include "login.h"

login::login()
{
    qDebug()<<"login luotu";
    accountLock =0;
}

login::~login()
{
    qDebug()<<"login tuhottu";
}

void login::cardNumberLog(QString val)
{
    cardNumber=val;
    qDebug()<<"login cardnumber: "<<cardNumber;

   QString cardStateurl="http://localhost:3000/card/getCardState" + cardNumber;
    QNetworkRequest request(cardStateurl);
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(cardStateSlot(QNetworkReply*)));
    reply = loginManager->get(request);
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
    qDebug()<<"jdkjgbfjbgkdbgjfdbgdkjbgfdbgkjfd::::card_state= "<<cardState;
    //qDebug()<<response_data;
    if(response_data=="-4078" || response_data.length()==0){
        QString message = "Virhe tietoyhteydessä";
        emit loginMessage(message);
        /*msgBox.setText("Virhe tietoyhteydessä");
        msgBox.exec();*/
    }
    else{
        if(response_data!="false" && cardState == "1"){
            //kirjautuminen onnistui
            emit sendSignalLogin(response_data);
        }
        else{
            QString message = "Korttinumero/pin ei täsmää";
            accountLock++;
            emit loginMessage(message);

            if(accountLock == 3){
                QString message="Kortti lukittu, ota yhteyttä pankkiin";
                emit loginMessage(message);

                QJsonObject jsonObj;
                jsonObj.insert("card_number",cardNumber);
                QString site_url_="http://localhost:3000/card/loginLock/"+ cardNumber;
                QNetworkRequest request((site_url_));
                request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

                loginManager = new QNetworkAccessManager(this);
                connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(lockSlot(QNetworkReply*)));

                reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
            }

                if(response_data == "kortti lukittu"){
                    QString message="Kortti lukittu, ota yhteyttä pankkiin";
                    emit loginMessage(message);

            }

            /*msgBox.setText("Korttinumero/pin ei täsmää");
            msgBox.exec();*/
        }
    }
  reply->deleteLater();
  loginManager->deleteLater();
}

void login::lockSlot(QNetworkReply *replys)
{
   response_data=replys->readAll();
    qDebug()<<"lock Slotin response data: "<<response_data;

    replys->deleteLater();
    loginManager->deleteLater();

}

void login::cardStateSlot(QNetworkReply *repl)
{
    response_data=repl->readAll();
    cardState=response_data;
    qDebug()<<"cardState response data: "<<response_data;

    repl->deleteLater();
    loginManager->deleteLater();
}

