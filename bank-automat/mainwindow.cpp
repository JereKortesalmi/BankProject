#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <DLLSerialport_global.h>
#include <QCursor>
#include <QApplication>
#include <QScreen>
#include <QFile>

//Korttien numerot
//  -0600062211
//  -0500CB1EF8
//  -0500CB1FF3

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    QSize size = qApp->screens()[0]->size();

    qDebug()<<"Screensize" << size;
    screenSize.setScreenwidth(size.width());
    screenSize.setScreenheight(size.height());
    qDebug() << "width" << screenSize.getScreenwidth();
    qDebug() << "height" << screenSize.getScreenheight();
    ui->setupUi(this);
    connectSerial();

    //readTransactionValues();
    connect(ui->btn_transactions,SIGNAL(clicked(bool)),
            this,SLOT(sendTransactionRequest()));

    connect(this,SIGNAL(transactionsTableReady()), this, SLOT(readTransactionValues()));
    connect(this,SIGNAL(transactionsComplete()),this,SLOT(displayData()));

    //kortti numero käsin
    connect(ui->btnCardEdit,SIGNAL(clicked(bool)),this,SLOT(cardNumberHand()));

    //yhdistetään pinCode
    pin = new PinCode(this);
    connect(pin,SIGNAL(sendPinCodeToMainWindow(QString)),this,SLOT(receivePinNumber(QString)));
    connect(pin,SIGNAL(pinLogout()),this,SLOT(pinLogSlot()));

    //yhditetään login
    log = new login;
    connect(log,SIGNAL(sendSignalLogin(QString)),this,SLOT(loginInfo(QString)));
    connect(log,SIGNAL(loginMessage(QString)),this,SLOT(loginMessageToPinCode(QString)));

    //luodaan creditdebitq
    creditDebit= new creditdebitq(this);
    connect(creditDebit,SIGNAL(sendAccountId(int,QString,QString,QString,bool)),this,SLOT(accountIdSender(int,QString,QString,QString,bool)));

    // luodaan mainmenu (ei vielä näytetä)
    p_mainMenu = new mainMenu(this);
    //p_mainMenu->show();
    connect(p_mainMenu,SIGNAL(logOutSignal()),this,SLOT(logOutSlot()));

    //luodaan balance
    bal = new balance;
    connect(bal,SIGNAL(sendAccountIdBalance(int,QString,QString,QString,bool)),this,SLOT(accountIdSender(int,QString,QString,QString,bool)));
    connect(bal,SIGNAL(opencreditdebitq(QJsonArray)),this,SLOT(creditdebitchoose(QJsonArray)));
    connect(bal,SIGNAL(openAdmin()),this,SLOT(adminState()));
    //luodaan admin

    ui->tableViewTransactions->hide();
    ui->btn_transactions->hide();

    ui->label_2->move(screenSize.getScreenwidth()/2, screenSize.getScreenheight()/2-200);
    ui->label->move(screenSize.getScreenwidth()/2 - 40, screenSize.getScreenheight()/2 - 100);
    ui->cardEdit->move(screenSize.getScreenwidth()/2 - 120, screenSize.getScreenheight()/2);
    ui->btnCardEdit->move(screenSize.getScreenwidth()/2 + 80, screenSize.getScreenheight()/2);


    QFile file("automatid.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "unable to open file";
        return;
    }
    else {
        while (!file.atEnd()) {
            QByteArray line = file.readAll();
            qDebug() << line;
            automatID = line.toInt();
            qDebug() << "automatID: " << automatID;
        }
    }

    if(automatID != 0) {
        qDebug() << "automatID was not set, please add automatid.txt file and enter numerical id.";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    disconnectSerial();
}

void MainWindow::connectSerial()
{
    sPort= new DLLSerialport;
    connect(sPort,SIGNAL(sendCardNumber(QString)), this,SLOT(receiveCardNumber(QString)));
}

void MainWindow::disconnectSerial()
{
    delete sPort;
    sPort = nullptr;
}

void MainWindow::sendTransactionRequest()
{
    test = new Transactions();
    connect(test,SIGNAL(ResponseToMain(QJsonArray)), this, SLOT(receiveData(QJsonArray)));
    //test->show();
}

void MainWindow::cardNumberHand()
{
    cardNumber=ui->cardEdit->text();
    qDebug()<<"Käsin korttinumero: "<<cardNumber;
    log->cardNumberLog(cardNumber);
    pin->showFullScreen();
}


void MainWindow::loginInfo(QString res)
{
    //token=QByteArray::fromStdString(res);
    token = QByteArray::fromStdString(res.toStdString());
    qDebug()<<"login vastaus: "<<token;
    pin->hide();
    //creditDebit->show();
    //p_mainMenu->show();
    qDebug()<<cardNumber;
    bal->fetchAccountDetails(token,cardNumber);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this, SLOT(checkMousePosition()));
    mouseTime = 0;
    timer->start(1000);
}

void MainWindow::loginMessageToPinCode(QString message)
{
    QString mes = message;
    pin->pinMessage(mes);
}

void MainWindow::accountIdSender(int accountId, QString balance, QString type, QString bothId, bool showTransferButton)
{
    int id = accountId;
    //QString bal = balance;
    //QString accountType = type;
    qDebug()<<"accountIdSender id:"<<id;
    p_mainMenu->accountId = id;
    //p_mainMenu->showBalance(bal);
    p_mainMenu->showTransferButton = showTransferButton;
    p_mainMenu->bothId = bothId;
    p_mainMenu->token = token;
    p_mainMenu->accountType = type;
    p_mainMenu->resetView();
    p_mainMenu->showFullScreen();
    p_mainMenu->automatID = automatID;
    //p_mainMenu->sHeight = screenSize.getScreenheight();
    //p_mainMenu->sWidth = screenSize.getScreenwidth();

}

void MainWindow::creditdebitchoose(QJsonArray array)
{
    QJsonArray jsonArray = array;
    creditDebit->showFullScreen();
    creditDebit->selectAccountHandler(jsonArray);
}

void MainWindow::adminState()
{
    adm = new admin;
    connect(adm,SIGNAL(logOutAdmin()),this,SLOT(logOutSlot()));
    adm->showFullScreen();
    adm->token = token;
    adm->fetchBalance(automatID, token);
}

void MainWindow::logOutSlot()
{
    qDebug()<<"logoutSLot toimii";
    ui->cardEdit->clear();
    token=nullptr;
    pin->resetHandler();
    pin->close();
    p_mainMenu->close();
    p_mainMenu->resetView();
    p_mainMenu->bothId = "";
    //delete p_mainMenu;
    //p_mainMenu = nullptr;
    creditDebit->close();
    if(adm != nullptr){
        adm->close();
        delete adm;
        adm = nullptr;
    }
    timer->stop();
}

void MainWindow::checkMousePosition()
{
    QPoint currentPos = QCursor::pos();
    if (currentPos == lastPos) {
        mouseTime++;
        if (mouseTime == 12) {
            qDebug() << "Hiiri oli paikallaan 10 sekunttia!";
            logOutSlot();
            p_mainMenu->onBtnlogoutClicked();
        }
    } else {
        mouseTime = 0;
        lastPos = currentPos;
    }
}

void MainWindow::pinLogSlot()
{
    ui->cardEdit->clear();
}

void MainWindow::readTransactionValues()
{
    qDebug()<<"Setting up Model: ";
    table_model = new QStandardItemModel(tableTransactions.size(),5);
    table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("atm_id"));
    table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("account_id"));
    table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("time"));
    table_model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
    table_model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));

    for (int row = 0; row < tableTransactions.size();row++ ) {
        QStandardItem *atm_id = new QStandardItem((tableTransactions[row].getTransactions_atm_id()));
        table_model->setItem(row,0,atm_id);
        QStandardItem *account_id = new QStandardItem((tableTransactions[row].getTransaction_account_id()));
        table_model->setItem(row,1,account_id);
        QStandardItem *time = new QStandardItem((tableTransactions[row].getTransaction_time()));
        table_model->setItem(row,2,time);
        QStandardItem *type= new QStandardItem((tableTransactions[row].getTransaction_type()));
        table_model->setItem(row,3,type);
        QStandardItem *amount= new QStandardItem((tableTransactions[row].getTransaction_amount()));
        table_model->setItem(row,4,amount);
    }
    emit transactionsComplete();

}

void MainWindow::receiveData(QJsonArray reply)
{
    qDebug() << "Vastaus Mainille: "<<reply;
    transactions obj;

    foreach (const QJsonValue &value, reply) {
        QJsonObject json_obj = value.toObject();

        obj.setTransactions_atm_id(QString::number(json_obj["transaction_id"].toDouble()));
        qDebug()<<"json: atm_id: "<<json_obj["transaction_id"];
        //obj.setTransactions_atm_id("1");
        obj.setTransaction_account_id(QString::number(json_obj["transaction_account_id"].toDouble()));
        //obj.setTransactions_atm_id("1");
        obj.setTransaction_time(json_obj["transaction_time"].toString());
        obj.setTransaction_type(json_obj["transaction_type"].toString());
        obj.setTransaction_amount(json_obj["transaction_amount"].toString());

        tableTransactions.append(obj);
    }

    qDebug()<<"Eka Alkio" << tableTransactions[0].getTransaction_amount();
    emit transactionsTableReady();

}

void MainWindow::displayData()
{
    qDebug()<<"displayData:";
    ui->tableViewTransactions->setModel(table_model);
    ui->tableViewTransactions->show();
}

void MainWindow::receiveCardNumber(QString val)
{
    cardNumber=val;
    qDebug()<<"korttinumero main: "<<cardNumber;
    log->cardNumberLog(cardNumber);
    pin->showFullScreen();

}

void MainWindow::receivePinNumber(QString val)
{
    pinCode=val;
    qDebug()<<"pin numero main: "<<pinCode;
    qDebug()<<"korttinumero main: "<<cardNumber;
    //log->cardNumberLog(cardNumber);
    log->loginHandler(pinCode);
    //log->pinCodeLog(pinCode);


}
