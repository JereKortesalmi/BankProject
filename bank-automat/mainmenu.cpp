#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);
    Transactions *p_Transactions = new Transactions(this);

    // näytetään Transactions-ikkuna
    //p_Transactions->show();

    //webtoken
    QByteArray token = "2386028485693820asdjfklöaueiwolsdfjklasdfjkasödjfkl(/";
    // withdrawCall
    withdrawCall *p_withdrawCall = new withdrawCall(this);
    connect(p_withdrawCall, SIGNAL(dataRead()), this, SLOT(withdrawSignalReceived()));
    p_withdrawCall->sendTransaction(token, 5, 20.00);
    p_withdrawCall->getAtmInfo(token,1);

    //transactions signals and slots with button push
    connect(ui->btn_transactions,SIGNAL(clicked(bool)),
            this,SLOT(sendTransactionRequest()));

    connect(this,SIGNAL(transactionsTableReady()), this, SLOT(readTransactionValues()));
    connect(this,SIGNAL(transactionsComplete()),this,SLOT(displayData()));
    ui->tableViewTransactions->hide();
}

mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::withdrawSignalReceived()
{
    qDebug()<<"Reading was done. So no error was received.";

}

void mainMenu::sendTransactionRequest()
{
    test = new Transactions(this);
    connect(test,SIGNAL(ResponseToMain(QJsonArray)), this, SLOT(receiveTransactionData(QJsonArray)));
    test->show();
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
