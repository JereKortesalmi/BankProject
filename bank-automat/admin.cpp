#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::admin)
{
    ui->setupUi(this);
    connect(ui->btnSaveBills,SIGNAL(clicked(bool)),this,SLOT(saveBillsToAtm()));

    connect(ui->btnPlus,SIGNAL(clicked(bool)),this,SLOT(btnHandler()));
    connect(ui->btnMinus,SIGNAL(clicked(bool)),this,SLOT(btnHandler()));


    connect(ui->N1,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N2,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N3,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N4,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N5,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N6,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N7,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N8,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N9,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));

    connect(ui->btn20,SIGNAL(clicked(bool)),this,SLOT(selectedLineEdit()));
    connect(ui->btn50,SIGNAL(clicked(bool)),this,SLOT(selectedLineEdit()));
    connect(ui->btn100,SIGNAL(clicked(bool)),this,SLOT(selectedLineEdit()));
    connect(ui->btn200,SIGNAL(clicked(bool)),this,SLOT(selectedLineEdit()));
    connect(ui->btn500,SIGNAL(clicked(bool)),this,SLOT(selectedLineEdit()));

    connect(ui->btnLogout, SIGNAL(clicked(bool)), this, SLOT(onBtnlogoutAdminClicked()));
    qDebug()<<"Admin luotu";
}

admin::~admin()
{
    delete ui;
}

void admin::btnHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString push = button->objectName();
    qDebug() <<"Button: "<<push;

    if(state == 1){
        if(push == "btnPlus"){
            twenty ++;
            ui->amountEdit->setText(QString::number(twenty));
            ui->twentyEdit->setText(QString::number(twenty));
        }else{
            twenty --;
            ui->amountEdit->setText(QString::number(twenty));
            ui->twentyEdit->setText(QString::number(twenty));
        }
    }else if(state == 2){
        if(push == "btnPlus"){
            fifty ++;
            ui->amountEdit->setText(QString::number(fifty));
            ui->fiftyEdit->setText(QString::number(fifty));
        }else{
            fifty --;
            ui->amountEdit->setText(QString::number(fifty));
            ui->fiftyEdit->setText(QString::number(fifty));
        }
    }else if(state == 3){
        if(push == "btnPlus"){
            hundred ++;
            ui->amountEdit->setText(QString::number(hundred));
            ui->hundredEdit->setText(QString::number(hundred));
        }else{
            hundred --;
            ui->amountEdit->setText(QString::number(hundred));
            ui->hundredEdit->setText(QString::number(hundred));
        }
    }else if(state == 4){
        if(push == "btnPlus"){
            twoHundred ++;
            ui->amountEdit->setText(QString::number(twoHundred));
            ui->twoHundredEdit->setText(QString::number(twoHundred));
        }else{
            twoHundred --;
            ui->amountEdit->setText(QString::number(twoHundred));
            ui->twoHundredEdit->setText(QString::number(twoHundred));
        }
    }else if(state == 5){
        if(push == "btnPlus"){
            fiveHundred ++;
            ui->amountEdit->setText(QString::number(fiveHundred));
            ui->fiveHundredEdit->setText(QString::number(fiveHundred));
        }else{
            fiveHundred --;
            ui->amountEdit->setText(QString::number(fiveHundred));
            ui->fiveHundredEdit->setText(QString::number(fiveHundred));
        }
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
        twenty = num.toInt();
        ui->amountEdit->setText(QString::number(twenty));
        ui->twentyEdit->setText(num);
        ui->amountEdit->setText(num);
    }else if(state == 2){
        fifty = num.toInt();
        ui->amountEdit->setText(QString::number(fifty));
        ui->fiftyEdit->setText(num);
    }else if(state == 3){
        hundred = num.toInt();
        ui->amountEdit->setText(QString::number(hundred));
        ui->hundredEdit->setText(num);
    }else if(state == 4){
        twoHundred = num.toInt();
        ui->amountEdit->setText(QString::number(twoHundred));
        ui->twoHundredEdit->setText(num);
    }else if(state == 5){
        fiveHundred = num.toInt();
        ui->amountEdit->setText(QString::number(fiveHundred));
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
        ui->billSelected->setText("20 bills Selected");
        ui->amountEdit->setText(QString::number(twenty));
    }else if(btn == "btn50"){
        state = 2;
        num = 0;
        ui->billSelected->setText("50 bills Selected");
        ui->amountEdit->setText(QString::number(fifty));
    }else if(btn == "btn100"){
        state = 3;
        num = 0;
        ui->billSelected->setText("100 bills Selected");
        ui->amountEdit->setText(QString::number(hundred));
    }else if(btn == "btn200"){
        state = 4;
        num = 0;
        ui->billSelected->setText("200 bills Selected");
        ui->amountEdit->setText(QString::number(twoHundred));
    }else if(btn == "btn500"){
        state = 5;
        num = 0;
        ui->billSelected->setText("500 bills Selected");
        ui->amountEdit->setText(QString::number(fiveHundred));
    }else{
        state = 0;
        num = 0;
        ui->billSelected->setText("no bills Selected");
        ui->amountEdit->clear();
    }
}

void admin::onBtnlogoutAdminClicked()
{
    state = 0;
    twenty = 0;
    ui->twentyEdit->setText(QString::number(twenty));
    fifty = 0;
    ui->fiftyEdit->setText(QString::number(fifty));
    hundred = 0;
    ui->hundredEdit->setText(QString::number(hundred));
    twoHundred = 0;
    ui->twoHundredEdit->setText(QString::number(twoHundred));
    fiveHundred = 0;
    ui->fiveHundredEdit->setText(QString::number(fiveHundred));
    ui->amountEdit->clear();
    ui->btn20->setChecked(false);
    ui->btn50->setChecked(false);
    ui->btn100->setChecked(false);
    ui->btn200->setChecked(false);
    ui->btn500->setChecked(false);

    emit logOutAdmin();

}
