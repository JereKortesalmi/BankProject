#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainMenu)
{
    //requestRec = new requestReceiver;
    //requestRec->sendResult();


    ui->setupUi(this);
    //Transactions *p_Transactions = new Transactions();

    // näytetään Transactions-ikkuna
    //p_Transactions->show();

    //webtoken
    //QByteArray token = "2386028485693820asdjfklöaueiwolsdfjklasdfjkasödjfkl(/";
    // withdrawCall
    //withdrawCall *p_withdrawCall = new withdrawCall(this);




    //p_withdrawCall->sendTransaction(token, 5, 20.00);

    //requestRec->wit.getAtmInfo(token,1);
    //p_withdrawCall->getAtmInfo(token,1);

    //transactions signals and slots with button push
    connect(ui->btn_transactions,SIGNAL(clicked(bool)),
            this,SLOT(sendTransactionRequest()));

    connect(this,SIGNAL(transactionsTableReady()), this, SLOT(readTransactionValues()));
    connect(this,SIGNAL(transactionsComplete()),this,SLOT(displayData()));

    //balance signals
    connect(ui->btnBalance,SIGNAL(clicked(bool)),ui->balanceLabel,SLOT(show()));

    //Kikkoja esityksen osoittamiseen..
    ui->tableViewTransactions->hide();
    ui->balanceLabel->hide();
    ui->btn_transactions->move(800,200);
    //ui->tableViewTransactions->size() = QSize(100,100);
    //ui->btn_withdraw
    connect(ui->btn_withdraw, SIGNAL(clicked(bool)), this, SLOT(withdrawClicked()));
    ui->label_withdraw->hide();
    ui->label_withdraw->move(80,200);


    connect(p_withdrawCall, SIGNAL(atmInfoSent()), this, SLOT(atmSignalReceived()));

    connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(hideShown()));

    //int atmId=1;
    //p_withdrawCall->getAtmInfo(token, atmId);

    hideShown();

    connect(ui->btn_other, SIGNAL(clicked(bool)), this, SLOT(otherClicked()));
    connect(ui->btnWithdrawOther, SIGNAL(clicked(bool)), this, SLOT(withdrawOtherPressed()));
    connect(ui->btn_20eur, SIGNAL(clicked(bool)), this, SLOT(eur20Pressed()));
    connect(ui->btn_40eur, SIGNAL(clicked(bool)), this, SLOT(eur40Pressed()));
    connect(ui->btn_60eur, SIGNAL(clicked(bool)), this, SLOT(eur60Pressed()));
    connect(ui->btn_100eur, SIGNAL(clicked(bool)), this, SLOT(eur100Pressed()));
}

mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::withdrawSignalReceived()
{


}

void mainMenu::atmSignalReceived()
{
    qDebug()<<"ATM info was read. So no error was received.";

    // print bills available on ATM
    p_withdrawCall->printAtmBills();
    p_withdrawCall->printAtmSetBills();

}

void mainMenu::withdrawClicked()
{
    qDebug()<<"Withdraw clicked";
    //QByteArray token = "2386028485693820asdjfklöaueiwolsdfjklasdfjkasödjfkl(/";
    //int atmId = 1;
    //requestRec->wit.getAtmInfo(token, atmId);
    p_withdrawCall = new withdrawCall(this);
    p_withdrawCall->getAtmInfo(token,1);


    // 20 € - 100 € napit ja labelit yhdistettynä widgettinä.
    ui->eur20->show();
    ui->eur20->move(300,300);
    ui->eur40->show();
    ui->eur40->move(300,340);
    ui->eur60->show();
    ui->eur60->move(300,380);
    ui->eur100->show();
    ui->eur100->move(480,300);
    if(p_withdrawCall->bills_20 > 0) {
        //ui->btn_20eur->show();
        //ui->btn_20eur->move(200,200);
        //ui->label_20->show();
        //ui->label_20->move(200,220);
        //ui->eur20->hide();
    }
    if(p_withdrawCall->bills_20 > 2) {
        //ui->btn_40eur->show();
        //ui->label_40->show();
    }
    if(p_withdrawCall->bills_20 > 3) {
        //ui->btn_60eur->show();
        //ui->label_60->show();
    }
    if(p_withdrawCall->bills_100 > 0) {
        //ui->btn_100eur->show();
        //ui->label_100->show();
    }


    //ui->btn_other->show();
    //ui->label_other->show();
    //ui->text_other->show();

    // btn_other ja text_other yhdessä widgettinä.
    ui->eurOther->show();
    ui->eurOther->move(480,380);



    ui->label_withdraw->show();
    ui->label_withdraw->setText("Valitse haluamasi määrä");
    ui->label_withdraw->move(400,100);


    //p_withdrawCall->sendTransaction(token,5,20.00);
    //p_withdrawCall->clearBills();
    //p_withdrawCall->checkBills(220);

    /*
    qDebug() << "Setelien määrä 20: " <<requestRec->wit.bills_20;
    qDebug() << "setelien määrä 50: " << requestRec->wit.bills_50;
    qDebug() << "Setelien määrä 100: " << requestRec->wit.bills_100;
    qDebug() << "Setelien määrä 200: " << requestRec->wit.bills_200;

    qDebug() << "Noston määräämät setelit: ";
    qDebug() << "20: " << requestRec->wit.set_20_bills;
    qDebug() << "50: " << requestRec->wit.set_50_bills;
    qDebug() << "100: " << requestRec->wit.set_100_bills;
    qDebug() << "200: " << requestRec->wit.set_200_bills;
    */

}

void mainMenu::otherClicked()
{
    //ui->text_other->show();
    //ui->text_other->move(200,200);
    ui->withdrawOther->show();
    ui->withdrawOther->move(300,200);
    ui->eurOther->hide();
    ui->eur20->hide();
    ui->eur40->hide();
    ui->eur60->hide();
    ui->eur100->hide();
    ui->label_withdraw->setText("Give amount");
}

void mainMenu::withdrawOtherPressed()
{
    qDebug()<<"withdraw other pressed.";
    qDebug()<< ui->text_other->text().toInt() << "€";
    p_withdrawCall->clearBills();
    p_withdrawCall->checkBills(ui->text_other->text().toInt());

    p_withdrawCall->printAtmBills();
}

void mainMenu::eur20Pressed()
{
    qDebug() << "20  €";
    p_withdrawCall->clearBills();
    p_withdrawCall->checkBills(20);

    p_withdrawCall->printAtmBills();
}

void mainMenu::eur40Pressed()
{
    qDebug() << "40  €";
    p_withdrawCall->clearBills();
    p_withdrawCall->checkBills(40);

    p_withdrawCall->printAtmBills();
}

void mainMenu::eur60Pressed()
{
    qDebug() << "60  €";
    p_withdrawCall->clearBills();
    p_withdrawCall->checkBills(60);

    p_withdrawCall->printAtmBills();
}

void mainMenu::eur100Pressed()
{
    qDebug() << "100  €";
    p_withdrawCall->clearBills();
    p_withdrawCall->checkBills(100);

    p_withdrawCall->printAtmBills();
}

void mainMenu::sendTransactionRequest()
{
    if(!tableTransactions.isEmpty()) {
        tableTransactions.clear();
    }
    test = new Transactions();
    test->requestTrasactions(accountId);
    connect(test,SIGNAL(ResponseToMain(QJsonArray)), this, SLOT(receiveTransactionData(QJsonArray)));
    //test->show();
}

void mainMenu::receiveTransactionData(QJsonArray reply)
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

void mainMenu::displayData()
{
    ui->tableViewTransactions->setModel(table_model);
    //ui->tableViewTransactions->resizeColumnToContents(0);
    //ui->tableViewTransactions->resizeColumnToContents(1);
    //ui->tableViewTransactions->resizeColumnToContents(2);
    //ui->tableViewTransactions->resizeColumnToContents(3);
    //ui->tableViewTransactions->resizeColumnToContents(4);
    // 1920*1080    full hd
    // 3840*2160    4k
    ui->tableViewTransactions->resizeColumnsToContents();
    ui->tableViewTransactions->setGeometry(350,0,450,200);
    ui->tableViewTransactions->move(280,200);
    ui->tableViewTransactions->show();

}

void mainMenu::readTransactionValues()
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

void mainMenu::showBalance(QString bal)
{
    QString balance1 = bal;
    //QString text = QString::number(balance1);
    qDebug()<<"mainmenu balance1: "<<balance1;
    ui->balanceLabel->setText(balance1);
    ui->balanceLabel->adjustSize();
    ui->balanceLabel->repaint();
    //ui->balanceLabel->show();
}

void mainMenu::hideShown()
{
    ui->balanceLabel->hide();
    ui->label_withdraw->hide();
    ui->tableViewTransactions->hide();

    ui->eur20->hide();
    ui->eur40->hide();
    ui->eur60->hide();
    ui->eur100->hide();
    ui->eurOther->hide();

    //ui->text_other->hide();
    ui->withdrawOther->hide();

    /*
    ui->btn_20eur->hide();
    ui->label_20->hide();
    ui->btn_40eur->hide();
    ui->label_40->hide();
    ui->btn_60eur->hide();
    ui->label_60->hide();
    ui->btn_100eur->hide();
    ui->label_100->hide();
    ui->btn_other->hide();
    ui->label_other->hide();
    ui->text_other->hide();
    */
}
