#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::admin)
{
    QSize size = qApp->screens()[0]->size();
    screenSize.setScreenwidth(size.width());
    screenSize.setScreenheight(size.height());

    ui->setupUi(this);
    connect(ui->btnSaveBills,SIGNAL(clicked(bool)),this,SLOT(saveBillsToAtm()));

    connect(ui->btnPlus,SIGNAL(clicked(bool)),this,SLOT(btnHandler()));
    connect(ui->btnMinus,SIGNAL(clicked(bool)),this,SLOT(btnHandler()));

    connect(ui->N0,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
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
    connect(ui->btnClear, SIGNAL(clicked(bool)), this, SLOT(clearHandler()));
    connect(ui->btnClearAll, SIGNAL(clicked(bool)), this, SLOT(clearAll()));

    ui->allbillframe->move((screenSize.getScreenwidth()/2) - 145,(screenSize.getScreenheight()/2) - 200);
    ui->keyboard_2->move((screenSize.getScreenwidth()/2) - 120,(screenSize.getScreenheight()/2) + 150);
    ui->amount->move((screenSize.getScreenwidth()/2) - 90,(screenSize.getScreenheight()/2) + 70);
    ui->btnLogout->move((screenSize.getScreenwidth()/2) + 500,(screenSize.getScreenheight()/2) + 400);
    ui->billSelected->move((screenSize.getScreenwidth()/2) - 100,(screenSize.getScreenheight()/2));
    ui->label_5->move((screenSize.getScreenwidth()/2) - 60,(screenSize.getScreenheight()/2) - 350);
    ui->btnSaveBills->move((screenSize.getScreenwidth()/2) + 400,(screenSize.getScreenheight()/2) - 200);
    ui->clear->move((screenSize.getScreenwidth()/2) + 160, (screenSize.getScreenheight()/2) + 160);
    ui->savedLabel->move((screenSize.getScreenwidth()/2) + 160, (screenSize.getScreenheight()/2) + 50);
    ui->currentbills->move((screenSize.getScreenwidth()/2) - 450, (screenSize.getScreenheight()/2) - 215);

    //ui->amount->move((screenSize.getScreenwidth()/2) - 400, screenSize.getScreenheight()+200);
    //ui->gridWidget->move((screenSize.getScreenwidth()/2) - 400, screenSize.getScreenheight()+300);
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
    int newTwenty = twent.toInt() + dataTwenty;
    int newFifty = fift.toInt() + dataFifty;
    int newHund = hund.toInt() + dataHundred;
    int newTwoHund = twoHund.toInt() + dataTwoHundred;
    int newFiveHund = fiveHund.toInt() + dataFiveHundred;
    int newBalance = (newTwenty * 20) + (newFifty * 50) + (newHund * 100) + (newTwoHund * 200) + (newFiveHund * 500);
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
    if(response == "1"){
        clearAll();
        ui->savedLabel->setText("Saving succesful");
    }else{
        ui->savedLabel->setText("Error saving bills");
    }
    qDebug()<<response;
    fetchBalance(atmId, token);
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
    ui->currentTwentyEdit->setText(QString::number(dataTwenty));
    ui->currentFiftyEdit->setText(QString::number(dataFifty));
    ui->currentHundredEdit->setText(QString::number(dataHundred));
    ui->currentTwoHundredEdit->setText(QString::number(dataTwoHundred));
    ui->currentFiveHundredEdit->setText(QString::number(dataFiveHundred));
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

void admin::clearHandler()
{
    if(state == 1){
        twenty = 0;
        num = 0;
        ui->amountEdit->clear();
        ui->twentyEdit->clear();
    }else if(state == 2){
        num = 0;
        fifty = 0;
        ui->amountEdit->clear();
        ui->fiftyEdit->clear();
    }else if(state == 3){
        num = 0;
        hundred = 0;
        ui->amountEdit->clear();
        ui->hundredEdit->clear();
    }else if(state == 4){
        num = 0;
        twoHundred = 0;
        ui->amountEdit->clear();
        ui->twoHundredEdit->clear();
    }else if(state == 5){
        num = 0;
        fiveHundred = 0;
        ui->amountEdit->clear();
        ui->fiveHundredEdit->clear();
    }
}

void admin::onBtnlogoutAdminClicked()
{
    clearAll();
    emit logOutAdmin();

}

void admin::clearAll()
{
    state = 0;
    twenty = 0;
    ui->twentyEdit->clear();
    fifty = 0;
    ui->fiftyEdit->clear();
    hundred = 0;
    ui->hundredEdit->clear();
    twoHundred = 0;
    ui->twoHundredEdit->clear();
    fiveHundred = 0;
    ui->fiveHundredEdit->clear();
    ui->amountEdit->clear();
    ui->billSelected->clear();
    ui->btn20->setChecked(false);
    ui->btn50->setChecked(false);
    ui->btn100->setChecked(false);
    ui->btn200->setChecked(false);
    ui->btn500->setChecked(false);
}
