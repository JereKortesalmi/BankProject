#include "balance.h"
#include "ui_balance.h"

balance::balance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::balance)
{
    ui->setupUi(this);
    qDebug()<<"balance luotu";
}

balance::~balance()
{
    delete ui;
}

void balance::onErrorOccurred(QNetworkReply::NetworkError code)
{
    qDebug()<<"Network error:" << code;
}

void balance::balanceUpdateFinished(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();
    qDebug()<<response;
}

void balance::fetchAccountDetails(QByteArray token,QString cardn)
{
    QString cardNumber = cardn;
    QString url="http://localhost:3000/accounts/getaccountid/" + cardNumber;
    QNetworkRequest request(url);
    //WEBTOKEN ALKU
    myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    accountManager = new QNetworkAccessManager(this);
        connect(accountManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(saveAccountDetails(QNetworkReply*)));
        reply = accountManager->get(request);
        qDebug() << "Fetching account details...";
}

void balance::saveAccountDetails(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<"Response data: "<<response_data;
    QJsonDocument jsonResponse_data = QJsonDocument::fromJson(response_data);
    QJsonArray jsonArray = jsonResponse_data.array();
    if(jsonArray.size() == 1){
        QJsonObject jsonObject = jsonArray[0].toObject();
        accountId = jsonObject["account_id"].toInt();
        QString balance = jsonObject["account_balance"].toString();
        accountType = jsonObject["account_type"].toString();
        qDebug()<<"account id saveACcountDetailsissä: "<<accountId;
        qDebug()<<"account balance: "<<balance;
        qDebug()<<"accountType: "<<accountType;
        if(accountType == "ADMIN"){
            emit openAdmin();
        }else{
            emit sendAccountIdBalance(accountId, balance, accountType, "", false);
        }
    } else if(jsonArray.size() == 2){
        QJsonArray jsonArray = jsonResponse_data.array();
        emit opencreditdebitq(jsonArray);
    }
}

void balance::fetchBalance(QByteArray token,int accountId)
{
    int id = accountId;
    QString url="http://localhost:3000/accounts/" + QString::number(id);
    QNetworkRequest request(url);
    //WEBTOKEN ALKU
    myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    balanceManager = new QNetworkAccessManager(this);
    connect(balanceManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getBalance(QNetworkReply*)));
    reply = balanceManager->get(request);
    qDebug() << "Fetching balance...";
}

void balance::getBalance(QNetworkReply *reply){
        QByteArray response_data=reply->readAll();
        qDebug()<<"Response data: "<<response_data;
        QJsonDocument jsonResponse_data = QJsonDocument::fromJson(response_data);
        //QJsonArray jsonArray = jsonResponse_data.array();
            //QJsonObject jsonObject = jsonArray[0].toObject();
        QJsonObject jsonObj = jsonResponse_data.object();
            QString balance = jsonObj["account_balance"].toString();
            qDebug()<<"account balance: "<<balance;
            emit balanceToMainmenu(balance);
}

void balance::updateBalance(QByteArray token, int accountId, QString balance)
{
    int id = accountId;
    QString bal = balance;
    qDebug()<<"id ja balance updateBalance:"<<id<<bal;
    QJsonObject jsonObject;
    jsonObject.insert("account_balance", bal);
    if(accountType == "CREDIT"){
    //    creditCurrent = creditMax - bal;
    //    jsonObject.insert("account_credit_current", creditCurrent);
    }else{
        qDebug()<<"ei ollut creditti tili";
    }
    //QByteArray accountBalance = QJsonDocument(jsonObject).toJson();

    QUrl url("http://localhost:3000/accounts/updateBalance/" + QString::number(id));
    QNetworkRequest request(url);

    //WEBTOKEN ALKU
    myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    balanceManager = new QNetworkAccessManager(this);
    //QNetworkAccessManager *balanceManager = new QNetworkAccessManager(this);
    reply = balanceManager->put(request, QJsonDocument(jsonObject).toJson());
    connect(balanceManager, SIGNAL(finished(QNetworkReply*)),this,SLOT(balanceUpdateFinished(QNetworkReply*)));



    //balanceManager->put(request, accountBalance);

}
