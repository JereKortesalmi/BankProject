#include "withdrawcall.h"

withdrawCall::withdrawCall(QObject *parent)
    : QObject{parent}
{
      qDebug()<<"withdrawCall was constructed.";
}

void withdrawCall::sendTransaction(QByteArray token, int id, double sum)
{


    qDebug()<<"sendRequest from withdrawCall()";
    //Esimerkkidata
    QDateTime current = QDateTime::currentDateTime();
    QString formattedTime = current.toString("yyyy-MM-dd hh:mm:ss");
    qDebug() << formattedTime;
    QJsonObject jsonObj;
    jsonObj.insert("transaction_account_id", id);
    jsonObj.insert("transaction_atm_id","1");           // read from file will be added somewhere else, so will need to add variable here
    jsonObj.insert("transaction_time", formattedTime);
    jsonObj.insert("transaction_type","WITHDRAW");
    jsonObj.insert("transaction_amount", sum);


    QUrl url("http://localhost:3000/transaction/");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU


    w_manager = new QNetworkAccessManager(this);
    w_reply = w_manager->post(request,QJsonDocument(jsonObj).toJson());
    connect(w_manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(onManagerFinished(QNetworkReply*)));
    connect(w_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)),
            this, SLOT(onErrorOccurred(QNetworkReply::NetworkError)));
    //w_manager->deleteLater();

}

void withdrawCall::getAtmInfo(QByteArray token, int id)
{
    /*qDebug()<<"getAtmInfo()";
    if (token.isEmpty()) {
        return;
    }
    else {
    */
        qDebug() << "sending request for getAtmInfo with atmID: " << id;
        QString wUrl = "http://localhost:3000/atm/" + QString::number(id);
        QUrl url(wUrl);
        QNetworkRequest request(url);

        //WEBTOKEN ALKU
        myToken="Bearer "+token;
        qDebug() << "before crash";
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEBTOKEN LOPPU


        atm_manager = new QNetworkAccessManager(this);
        //connect(atm_manager, SIGNAL(finished(QNetworkReply*)),this,SLOT(onManagerFinished(QNetworkReply*)));
        //connect(atm_reply,SIGNAL(errorOccurred(QNetworkReply::NetworkError)),
        //        this, SLOT(onErrorOccurred(QNetworkReply::NetworkError)));
        connect(atm_manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(atmManagerFinished(QNetworkReply*)));
        atm_reply = atm_manager->get(request);
        connect(atm_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)),
                this,SLOT(atmErrorOccurred(QNetworkReply::NetworkError)));

                qDebug() << "Is crash here?";
        //}
}

void withdrawCall::printAtmSetBills()
{
    qDebug()<<" Bills set on ATM:";
    qDebug() << "ATM balance: " << atmBalance;
    qDebug()<< "20 €: " << set_200_bills;
    qDebug()<< "50 €: " << set_50_bills;
    qDebug()<< "100 €: " << set_100_bills;
    qDebug()<< "200 €: " << set_200_bills;
}

void withdrawCall::printAtmBills()
{
    qDebug()<<" Bills on ATM:";
    qDebug() << "ATM balance: " << atmBalance;
    qDebug()<< "20 €: " << bills_20;
    qDebug()<< "50 €: " << bills_50;
    qDebug()<< "100 €: " << bills_100;
    qDebug()<< "200 €: " << bills_200;
}

withdrawCall::~withdrawCall()
{
    qDebug()<<"witdrawManager was destroyed";
}

QByteArray withdrawCall::getResponse_data() const
{
    return response_data;
}

void withdrawCall::checkBills(int withdrawal)
{
    qDebug()<<"checkBills()";
    //int original = withdrawal;
    withdrawAmount = withdrawal;
    bool test = checkBillsAvailable();
    if(test==true) {
        removeBills();
    }
    else {
        qDebug()<<"No bills to give";
    }
}

bool withdrawCall::checkBillsAvailable()
{
    qDebug()<<"checkBillsAvailable()";
    qDebug() << "withdraw Amount = " << withdrawAmount;
    int original = 0;

// WITHDRAW SET BILLS

    if(bills_200 > 0) {
        usable_200 = true;
    }
    else {
        usable_200 = false;
    }
    if(bills_100 > 0) {
        usable_100 = true;
    }
    else {
        usable_100=false;
    }
    if(bills_50 > 0) {
        usable_50 = true;
    }
    else {
        usable_50 = false;
    }
    if(bills_20 > 0) {

        usable_20 = true;
    }
    else {
        usable_20 = false;
    }

    while(withdrawAmount >= 200 && usable_200) {
        qDebug() << "withdraw Amount =" << withdrawAmount << " current=" << original;
        if(bills_200 >= set_200_bills) {
                usable_200 = true;
        }
        else {
            usable_200 = false;
            break;
        }

        if(usable_200==true) {
            if(((withdrawAmount) >= 200)) {
                if((withdrawAmount % 200) == 10) {
                    if(bills_20 >= (set_20_bills + 3)) {
                        set_20_bills = set_20_bills+3;
                        withdrawAmount = withdrawAmount-60;
                    }
                }
                else if(((withdrawAmount) % 200) > 100) {
                    if(bills_200>=set_200_bills) {
                        set_200_bills++;
                        withdrawAmount = withdrawAmount - 200;
                        usable_200 = true;
                    }
                }
                else {
                    if(bills_200 >= set_200_bills+1) {
                        set_200_bills++;
                        withdrawAmount = withdrawAmount -200;
                    }
                }

            }

            else {

            }

        }
        else {
            break;
        }

    } // while 200


    while(withdrawAmount >= 100 && usable_100) {
        qDebug() << "withdraw Amount =" << withdrawAmount << " current=" << original;

        if(bills_100 >= set_100_bills) {
            usable_100 = true;
        }
         else {
            usable_100 = false;
            break;
        }
        if(usable_100 == true) {
            if(((withdrawAmount) >= 100) && usable_100) {
                if(((withdrawAmount-original) % 100) == 10) {
                    if(bills_20 >= (set_20_bills+3)) {
                        set_20_bills = set_20_bills +3;
                        withdrawAmount = withdrawAmount -60;
                        usable_20=true;
                    }

                }
                else {
                    if(bills_100 >= (set_100_bills +1 )) {
                        set_100_bills++;
                        withdrawAmount = withdrawAmount -100;
                        usable_100 = true;
                    }
                    else {
                        usable_100 = false;
                    }
                }
            }
            else {

            }
        }
        else {
            //break;
        }
    } // while 100

    while(withdrawAmount >= 50 && usable_50)  {

        qDebug() << "withdraw Amount =" << withdrawAmount << " current=" << original;

        if(bills_50 >= set_50_bills) {
            usable_50 = true;
        }
        else {
            usable_50 = false;
            break;
        }
        if((withdrawAmount) >= 50 && usable_50) {
            if((withdrawAmount % 50) == 10) {
                if(bills_20 >= (set_20_bills+3)) {
                        set_20_bills = set_20_bills+3;
                        withdrawAmount=withdrawAmount-60;
                }
                else {
                    //return false;
                }
            }
            else {
                if(bills_50 >= (set_50_bills + 1)) {
                    set_50_bills++;
                    withdrawAmount=withdrawAmount-50;
                    usable_50 = true;
                }
                else {
                    usable_50 = false;
                    //return false;
                }
            }

        }
        else {
            //usable_50 = false;
            //return false;
        }
    } // while 50
    while(withdrawAmount>=20 && usable_20) {

        qDebug() << "withdraw Amount =" << withdrawAmount << " current=" << original;

        if(bills_20 >= set_20_bills) {
            usable_20 = true;
        }
        else {
            usable_20 = false;
            return false;
        }
        if(usable_20 == true) {

            if((withdrawAmount) >= 20) {
                if(((withdrawAmount) % 20 ) == 10) {

                    set_20_bills = false;
                    return false;
                    break;
                }
                else {
                    if(bills_20 >= set_20_bills + 1) {
                        set_20_bills++;
                        withdrawAmount = withdrawAmount-20;
                        usable_20=true;
                    }
                    else {
                        usable_20=false;
                        return false;
                    }
                }
            }
            else {
                //usable_20 = false;
            }
        }
        else {
            break;
        }
    } // while 20

    if(!usable_200 && !usable_100 && !usable_50 && !usable_20) {
        return false;
    }
    else {
        return true;
    }
}
void withdrawCall::clearBills()
{
    set_20_bills = 0;
    set_50_bills = 0;
    set_100_bills = 0;
    set_200_bills = 0;
}

void withdrawCall::removeBills()
{

    qDebug()<<"Remove bills: ";
    printAtmBills();
    bills_200 = bills_200-set_200_bills;
    bills_100 = bills_100-set_100_bills;
    bills_50 = bills_50-set_50_bills;
    bills_20 = bills_20-set_20_bills;
    printAtmBills();
    qDebug() << "Bills removed";

}

void withdrawCall::updateBills(QByteArray token,int id, double sum)
{
    qDebug() << "Writing to database bill values.";

    qDebug() << "updateBills with atmID: " << id;
    QString wUrl = "http://localhost:3000/atm/" + QString::number(id);
    QUrl url(wUrl);
    QNetworkRequest request(url);
    QJsonObject obj;

    qDebug()<<"atmBalance: "<<atmBalance;

    int result = atmBalance-sum;
    if(result < 0) {
        result = 0;
    }
    qDebug() << "result: " << result;

    // inserting values to object
    obj.insert("atm_500eur", 0);
    obj.insert("atm_200eur", bills_200);
    obj.insert("atm_100eur", bills_100);
    obj.insert("atm_50eur", bills_50);
    obj.insert("atm_20eur", bills_20);
    obj.insert("atm_balance", result);
    //obj.insert("atm_id", id);

    //header
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // debug print object
    qDebug() << "object: " << obj;

    //WEBTOKEN ALKU
    myToken="Bearer "+token;
    qDebug() << "before crash";
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    atm_write_manager = new QNetworkAccessManager(this);
    connect(atm_write_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onbillsManagerFinished(QNetworkReply*)));


    qDebug()<<"JsonDocument: " << QJsonDocument(obj).toJson();
    atm_reply = atm_write_manager->put(request, QJsonDocument(obj).toJson());
    connect(atm_reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)),
            this,SLOT(onBillsErrorOccurred(QNetworkReply::NetworkError)));

}

void withdrawCall::onManagerFinished(QNetworkReply *reply)
{
    if(reply->error()) {
        qDebug() << reply->errorString();
        return;
    }
    response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    //QJsonArray json_array = json_doc.array();
    //qDebug() << json_doc["atm_20eur"];
    qDebug() << "set Bills: ";
    atmBalance = json_doc["atm_balance"].toDouble();
    bills_20 = json_doc["atm_20eur"].toInt();
    bills_50 = json_doc["atm_50eur"].toInt();
    bills_100 = json_doc["atm_100eur"].toInt();
    bills_200 = json_doc["atm_200eur"].toInt();
    qDebug() << "Bills were set";
    w_manager->deleteLater();
    reply->deleteLater();
    //qDebug() << json_array.toVariantList();
    emit dataRead();


}

void withdrawCall::onErrorOccurred(QNetworkReply::NetworkError code)
{
    qDebug()<<"Network error:" << code;
}

void withdrawCall::atmManagerFinished(QNetworkReply *reply)
{
    /*if(reply->error()) {
        qDebug() << reply->errorString();
        return;
    }
    */
    response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    //QJsonArray json_array = json_doc.array();
    //qDebug() << json_doc["atm_20eur"];
    atmBalance = json_doc["atm_balance"].toDouble();
    bills_20 = json_doc["atm_20eur"].toInt();
    bills_50 = json_doc["atm_50eur"].toInt();
    bills_100 = json_doc["atm_100eur"].toInt();
    bills_200 = json_doc["atm_200eur"].toInt();
    qDebug()<<json_doc;
    //w_manager->deleteLater();
    //reply->deleteLater();
    //qDebug() << json_array.toVariantList();
    emit atmInfoSent();
}

void withdrawCall::atmErrorOccurred(QNetworkReply::NetworkError code)
{
    qDebug() << "atmError" << code;
}

void withdrawCall::onbillsManagerFinished(QNetworkReply *reply)
{
    response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    qDebug()<<json_doc;
    emit billsdataWritten();
}

void withdrawCall::onBillsErrorOccurred(QNetworkReply::NetworkError code)
{
    qDebug()<<"Network error:" << code;
}
