#include "balance.h"
#include "ui_balance.h"

balance::balance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::balance)
{
    ui->setupUi(this);
    qDebug()<<"balance konstruktori";
    getManager = new QNetworkAccessManager(this);
    connect(ui->btnBalance,SIGNAL(clicked(bool)),this,SLOT(getBalance()));
    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getBalance(QNetworkReply*)));
}

balance::~balance()
{
    delete ui;
}

void balance::getBalance(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObj = json_doc.object();
    QString balance = jsonObj.value("balance").toString();

    qDebug()<<"balance is: "<<balance;

    //ui->label->setText(balance);

    reply->deleteLater();
    getManager->deleteLater();

    emit sendToMain(balance);
}

void balance::on_btnBalance_clicked()
{
    QUrl url("http://localhost:3000/balance");
    QNetworkRequest request(url);
    reply = getManager->get(request);
}

