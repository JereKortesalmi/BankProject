#include "transactions.h"
#include "ui_transactions.h"
#include <QDebug>

Transactions::Transactions(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Transactions)
{
    qDebug()<<"Transactions luotu";
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(ui->btn_transactions, &QPushButton::clicked, this, &Transactions::clickHandler);
    //connect(ui->btn_transactions,SIGNAL(clicked(bool)),
    //        this,SLOT(clickHandler()));
    connect(manager, &QNetworkAccessManager::finished,
            this, &Transactions::onManagerFinished);
    //connect(manager, SIGNAL(finished(QNetworkReply*)),
    //        this, SLOT(onManagerFinished(QNetworkReply*)));
}
/*
Transactions::Transactions(QList<transactions> *table)
{
    qDebug()<<"table should be received.";
    //qDebug() << table[0].getTransactions_atm_id();
}
*/
Transactions::~Transactions()
{
    qDebug()<<"Tuhottu";
    delete ui;
}

void Transactions::clickHandler()
{
    qDebug()<<"Painettu";
    QUrl url("http://localhost:3000/transaction");
    QNetworkRequest request(url);
    reply = manager->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, &Transactions::onErrorOccurred);
}

void Transactions::onManagerFinished(QNetworkReply *reply)
{
    if (reply->error())
    {
        qDebug() << reply->errorString();
        return;
    }
    response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString transactions;
    transactions = "Account | ATM | Time                                     | Type        | Amount \n";
    foreach (const QJsonValue &value, json_array)
    {
        QJsonObject json_obj = value.toObject();
        transactions += QString::number(json_obj["transaction_account_id"].toInt())+"              | ";
        transactions += QString::number(json_obj["transaction_atm_id"].toInt())+"       | ";
        transactions += json_obj["transaction_time"].toString()+" | ";
        transactions += json_obj["transaction_type"].toString()+" | ";
        transactions += json_obj["transaction_amount"].toString()+"\n";
    }
    ui->txt_transactions->setText(transactions);

    emit ResponseToMain(json_array);
    qDebug()<<"Vastattu";
}

void Transactions::onErrorOccurred(QNetworkReply::NetworkError code)
{
    qDebug()<<"Network error:" << code;
}
