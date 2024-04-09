#include "balance.h"
#include "ui_balance.h"

balance::balance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::balance)
{
    ui->setupUi(this);
    qDebug()<<"balance konstruktori";
    getManager = new QNetworkAccessManager(this);
    connect(ui->btnBalance,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(getManager,SIGNAL(finished (QNetworkReply*)),this,SLOT(getBalance(QNetworkReply*)));
}

balance::~balance()
{
    delete ui;
}

void balance::getBalance(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString bal = json_obj.value("account_balance").toString();
    //QString id =QString::number(json_obj.value("account_id").toInt());
    //QString type = json_obj.value("account_type").toString();
    QString type = "DEBIT";
    //balance =QString::number(json_obj["balance"]).toString();
    ui->label->setText(bal);
    if(type == "DEBIT"){

    }else{

    }
    qDebug()<<"balance is: "<<bal;

    ui->label->setText(bal);

    reply->deleteLater();
    getManager->deleteLater();

    emit sendToMain(bal);
    /*QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString bal;
    bal = "Account | Type | Balance";
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        bal += QString::number(json_obj["account_customer_id"].toInt())+"   | ";
        bal +=json_obj["account_type"].toString()+" | ";
        bal +=json_obj["account_balance"].toString()+"\n";
    }

    qDebug()<<bal;

    ui->textEdit->setText(bal);
    //emit sendToMain(json_array)

    reply->deleteLater();
    getManager->deleteLater();*/

}

void balance::clickHandler()
{
    int id = 1;
    qDebug()<<"nappia painettu";
    QUrl url("http://localhost:3000/accounts/"+ QString::number(id));
    QNetworkRequest request(url);
    reply = getManager->get(request);
    connect(reply,SIGNAL(errorOccurred(QNetworkReply::NetworkError)),
            this, SLOT(onErrorOccurred(QNetworkReply::NetworkError)));
}

void balance::onErrorOccurred(QNetworkReply::NetworkError code)
{
    qDebug()<<"Network error:" << code;
}

