#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::admin)
{
    ui->setupUi(this);
    connect(ui->btnMinus20,SIGNAL(clicked(bool)),this,SLOT(twentyHandler()));
    connect(ui->btnPlus20,SIGNAL(clicked(bool)),this,SLOT(twentyHandler()));
    connect(ui->btnMinus50,SIGNAL(clicked(bool)),this,SLOT(fiftyHandler()));
    connect(ui->btnPlus50,SIGNAL(clicked(bool)),this,SLOT(fiftyHandler()));
    connect(ui->btnMinus100,SIGNAL(clicked(bool)),this,SLOT(hundredHandler()));
    connect(ui->btnPlus100,SIGNAL(clicked(bool)),this,SLOT(hundredHandler()));
    connect(ui->btnMinus200,SIGNAL(clicked(bool)),this,SLOT(twoHundredHandler()));
    connect(ui->btnPlus200,SIGNAL(clicked(bool)),this,SLOT(twoHundredHandler()));
    connect(ui->btnMinus500,SIGNAL(clicked(bool)),this,SLOT(fiveHundredHandler()));
    connect(ui->btnPlus500,SIGNAL(clicked(bool)),this,SLOT(fiveHundredHandler()));
    connect(ui->btnSaveBills,SIGNAL(clicked(bool)),this,SLOT(saveBillsToAtm()));

    connect(ui->N1,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N2,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N3,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N4,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N5,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N6,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N7,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N8,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N9,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    qDebug()<<"Admin luotu";
}

admin::~admin()
{
    delete ui;
}

void admin::twentyHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString push = button->objectName();
    qDebug() <<"Button: "<<push;

    if(push == "btnPlus20"){
        twenty ++;
        ui->twentyEdit->setText(QString::number(twenty));
    }else{
        twenty --;
        ui->twentyEdit->setText(QString::number(twenty));
    }
}

void admin::fiftyHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString push = button->objectName();
    qDebug() <<"Button: "<<push;

    if(push == "btnPlus50"){
        fifty ++;
        ui->fiftyEdit->setText(QString::number(fifty));
    }else{
        fifty --;
        ui->fiftyEdit->setText(QString::number(fifty));
    }
}

void admin::hundredHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString push = button->objectName();
    qDebug() <<"Button: "<<push;

    if(push == "btnPlus100"){
        hundred ++;
        ui->hundredEdit->setText(QString::number(hundred));
    }else{
        hundred --;
        ui->hundredEdit->setText(QString::number(hundred));
    }
}

void admin::twoHundredHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString push = button->objectName();
    qDebug() <<"Button: "<<push;

    if(push == "btnPlus200"){
        twoHundred ++;
        ui->twoHundredEdit->setText(QString::number(twoHundred));
    }else{
        twoHundred --;
        ui->twoHundredEdit->setText(QString::number(twoHundred));
    }
}

void admin::fiveHundredHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString push = button->objectName();
    qDebug() <<"Button: "<<push;

    if(push == "btnPlus500"){
        fiveHundred ++;
        ui->fiveHundredEdit->setText(QString::number(fiveHundred));
    }else{
        fiveHundred --;
        ui->fiveHundredEdit->setText(QString::number(fiveHundred));
    }
}

void admin::saveBillsToAtm()
{
    QString bal = QString::number(balance);
    QString twent = ui->twentyEdit->text();
    QString fift = ui->fiftyEdit->text();
    QString hund = ui->hundredEdit->text();
    QString twoHund = ui->twoHundredEdit->text();
    QString fiveHund = ui->fiveHundredEdit->text();
    int newBalance = bal.toInt() + (twent.toInt() * 20) + (fift.toInt() * 50) + (hund.toInt() * 100) + (twoHund.toInt() * 200) + (fiveHund.toInt() * 500);
    int newTwenty = twent.toInt() + dataTwenty;
    int newFifty = fift.toInt() + dataFifty;
    int newHund = hund.toInt() + dataHundred;
    int newTwoHund = twoHund.toInt() + dataTwoHundred;
    int newFiveHund = fiveHund.toInt() + dataFiveHundred;
    qDebug()<<"new atm balance: "<<newBalance;
    int id = 1;
    QJsonObject jsonObj;
    jsonObj.insert("atm_balance", QString::number(newBalance));
    jsonObj.insert("atm_20eur", QString::number(newTwenty));
    jsonObj.insert("atm_50eur", QString::number(newFifty));
    jsonObj.insert("atm_100eur", QString::number(newHund));
    jsonObj.insert("atm_200eur", QString::number(newTwoHund));
    jsonObj.insert("atm_500eur", QString::number(newFiveHund));

    QUrl url("http://localhost:3000/atm/"+ QString::number(id));
    QNetworkRequest request(url);

    //WEBTOKEN ALKU
    myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    atmManager = new QNetworkAccessManager(this);
    reply = atmManager->put(request, QJsonDocument(jsonObj).toJson());
    connect(atmManager, SIGNAL(finished(QNetworkReply*)),this,SLOT(atmManagerFinished(QNetworkReply*)));
}

void admin::atmManagerFinished(QNetworkReply *reply)
{
    QByteArray response = reply->readAll();
    qDebug()<<response;
}
void admin::fetchBalance(int atmId, QByteArray token)
{
    int id = atmId;
    QString url="http://localhost:3000/atm/" + QString::number(id);
    QNetworkRequest request(url);

    //WEBTOKEN ALKU
    myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    atmManager = new QNetworkAccessManager(this);
    connect(atmManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getBalance(QNetworkReply*)));
    reply = atmManager->get(request);
    qDebug() << "Fetching balance...";
}

void admin::getBalance(QNetworkReply *reply){
    QByteArray response_data=reply->readAll();
    qDebug()<<"Response data: "<<response_data;
    QJsonDocument jsonResponse_data = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObject = jsonResponse_data.object();
    balance = jsonObject["atm_balance"].toInt();
    dataTwenty = jsonObject["atm_20eur"].toInt();
    dataFifty = jsonObject["atm_50eur"].toInt();
    dataHundred = jsonObject["atm_100eur"].toInt();
    dataTwoHundred = jsonObject["atm_200eur"].toInt();
    dataFiveHundred = jsonObject["atm_500eur"].toInt();
    qDebug()<<"atm balance: "<<balance;
}

void admin::clickHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString btn = button->objectName();
    qDebug() <<"Button: "<<btn;
    QString a = btn.last(1);
    num = num + a;
    if(state == 1){
        ui->twentyEdit->setText(num);
    }else if(state == 2){
        ui->fiftyEdit->setText(num);
    }else if(state == 3){
        ui->hundredEdit->setText(num);
    }else if(state == 4){
        ui->twoHundredEdit->setText(num);
    }else if(state == 5){
        ui->fiveHundredEdit->setText(num);
    }
}

void admin::selectedLineEdit()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString btn = button->objectName();
    qDebug() <<"Button: "<<btn;

    if(btn == "btn20"){
        state = 1;
        num = 0;
    }else if(btn == "btn50"){
        state = 2;
        num = 0;
    }else if(btn == "btn100"){
        state = 3;
        num = 0;
    }else if(btn == "btn200"){
        state = 4;
        num = 0;
    }else if(btn == "btn 500"){
        state = 5;
        num = 0;
    }
}
