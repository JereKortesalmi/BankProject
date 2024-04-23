#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainMenu)
{
    QSize size = qApp->screens()[0]->size();
    screenSize.setScreenwidth(size.width());
    screenSize.setScreenheight(size.height());

    ui->setupUi(this);
    // connect transaction buttons and signals so they are timed after one another.
    connect(ui->btn_transactions,SIGNAL(clicked(bool)),
            this,SLOT(sendTransactionRequest()));
    connect(this,SIGNAL(transactionsTableReady()), this, SLOT(readTransactionValues()));
    connect(this,SIGNAL(transactionsComplete()),this,SLOT(displayData()));

    // buttons for next and previous 5 transactions
    connect(ui->btnnext5,SIGNAL(clicked(bool)), this, SLOT(next5Transactions()));
    connect(ui->btnprevious5,SIGNAL(clicked(bool)), this, SLOT(previous5Transactions()));
    ui->btnnext5->setEnabled(false);

    //balance signals
    bal = new balance;
    connect(ui->btnBalance,SIGNAL(clicked(bool)),this,SLOT(fetchBalance()));
    connect(bal,SIGNAL(balanceToMainmenu(QString)),this,SLOT(showBalance(QString)));

    //Trics to show stuff
    ui->tableViewTransactions->hide();
    ui->balanceLabel->hide();
    ui->btn_transactions->move((screenSize.getScreenwidth()/2) - 400, 200);
    ui->btnBalance->move((screenSize.getScreenwidth()/2) - 400, screenSize.getScreenheight()-200);
    ui->btn_withdraw->move((screenSize.getScreenwidth()/2) + 400, screenSize.getScreenheight()-200);
    ui->btnlogout->move((screenSize.getScreenwidth()/2) + 400, 200);
    ui->btnClose->move((screenSize.getScreenwidth()/2) + 520, 200);
    ui->balanceLabel->move((screenSize.getScreenwidth()/2), screenSize.getScreenheight()/2);

    // withdraw button connection
    connect(ui->btn_withdraw, SIGNAL(clicked(bool)), this, SLOT(withdrawClicked()));

    ui->label_withdraw->hide();
    ui->label_withdraw->move(screenSize.getScreenwidth()/2-80,screenSize.getScreenheight()-200);



    // connect btnClose
    connect(ui->btnClose, SIGNAL(clicked(bool)), this, SLOT(resetView()));

    //hide all shown windows.
    resetView();
    // withdraw call buttons connects
    connect(ui->btn_other, SIGNAL(clicked(bool)), this, SLOT(otherClicked()));
    connect(ui->btnWithdrawOther, SIGNAL(clicked(bool)), this, SLOT(withdrawOtherPressed()));
    connect(ui->btn_20eur, SIGNAL(clicked(bool)), this, SLOT(eur20Pressed()));
    connect(ui->btn_40eur, SIGNAL(clicked(bool)), this, SLOT(eur40Pressed()));
    connect(ui->btn_60eur, SIGNAL(clicked(bool)), this, SLOT(eur60Pressed()));
    connect(ui->btn_100eur, SIGNAL(clicked(bool)), this, SLOT(eur100Pressed()));

    this->offsetInteger = 0;
    //hide close button
    ui->btnClose->hide();
    // logout
    connect(ui->btnlogout, SIGNAL(clicked(bool)), this, SLOT(onBtnlogoutClicked()));

    connect(ui->b0, SIGNAL(clicked(bool)), this, SLOT(clickHandler()));
    connect(ui->b1, SIGNAL(clicked(bool)), this, SLOT(clickHandler()));
    connect(ui->b2, SIGNAL(clicked(bool)), this, SLOT(clickHandler()));
    connect(ui->b3, SIGNAL(clicked(bool)), this, SLOT(clickHandler()));
    connect(ui->b4, SIGNAL(clicked(bool)), this, SLOT(clickHandler()));
    connect(ui->b5, SIGNAL(clicked(bool)), this, SLOT(clickHandler()));
    connect(ui->b6, SIGNAL(clicked(bool)), this, SLOT(clickHandler()));
    connect(ui->b7, SIGNAL(clicked(bool)), this, SLOT(clickHandler()));
    connect(ui->b8, SIGNAL(clicked(bool)), this, SLOT(clickHandler()));
    connect(ui->b9, SIGNAL(clicked(bool)), this, SLOT(clickHandler()));
}

mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::withdrawSignalReceived()
{
    hideShown();
    ui->label_withdraw->show();
    ui->label_withdraw->setText("Withdraw complete. Have a good day");
    delete p_withdrawCall;
    p_withdrawCall = nullptr;
    fetchBalance();
    ui->balanceLabel->hide();
}

void mainMenu::atmSignalReceived()
{
    qDebug()<<"ATM info was read. So no error was received.";

    // print bills available on ATM
    //p_withdrawCall->printAtmBills();
    //p_withdrawCall->printAtmSetBills();

}

void mainMenu::withdrawClicked()
{
    qDebug()<<"Withdraw clicked";
    fetchBalance();
    ui->btnBalance->hide();
    ui->btn_withdraw->hide();
    ui->btn_transactions->hide();
    hideShown();
    ui->balanceLabel->hide();
    //QByteArray token = "2386028485693820asdjfklöaueiwolsdfjklasdfjkasödjfkl(/";
    //int atmId = 1;
    //requestRec->wit.getAtmInfo(token, atmId);

    p_withdrawCall = new withdrawCall();
    p_withdrawCall->getAtmInfo(token,1);
    connect(p_withdrawCall, SIGNAL(atmInfoSent()), this, SLOT(atmSignalReceived()));
    connect(p_withdrawCall, SIGNAL(billsdataWritten()), this, SLOT(withdrawReady()));
    connect(p_withdrawCall, SIGNAL(billsOK(bool)), this, SLOT(billsOk(bool)));

    // 20 € - 100 € napit ja labelit yhdistettynä widgettinä.
    ui->eur20->show();
    ui->eur20->move(screenSize.getScreenwidth()/2 - 300,screenSize.getScreenheight()/2 + 300);
    ui->eur40->show();
    ui->eur40->move(screenSize.getScreenwidth()/2  - 300,screenSize.getScreenheight()/2 + 340);
    ui->eur60->show();
    ui->eur60->move(screenSize.getScreenwidth()/2 - 300,screenSize.getScreenheight()/2 + 380);
    ui->eur100->show();
    ui->eur100->move(screenSize.getScreenwidth()/2 - 120,screenSize.getScreenheight()/2 + 300);

    // btn_other ja text_other yhdessä widgettinä.
    ui->eurOther->show();
    ui->eurOther->move(screenSize.getScreenwidth()/2 - 120,screenSize.getScreenheight()/2 + 380);

    ui->label_withdraw->show();
    ui->label_withdraw->setText("Valitse haluamasi määrä");
    ui->label_withdraw->move(screenSize.getScreenwidth()/2 - 400,screenSize.getScreenheight()/2 + 100);

}

void mainMenu::otherClicked()
{
    //ui->text_other->show();
    //ui->text_other->move(200,200);
    w_other_num="";
    //ui->label_other->setText("");
    ui->text_other->setText("");
    ui->balanceLabel->hide();
    ui->withdrawOther->show();
    ui->wKeyboard->show();
    ui->withdrawOther->move((screenSize.getScreenwidth() / 2) + 150,(screenSize.getScreenheight() / 2) + 50);
    ui->wKeyboard->move((screenSize.getScreenwidth() / 2 ) + 200,(screenSize.getScreenheight() / 2 ) + 100);
    ui->eurOther->hide();
    ui->eur20->hide();
    ui->eur40->hide();
    ui->eur60->hide();
    ui->eur100->hide();
    ui->label_withdraw->setText("Give amount");


}

void mainMenu::clickHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString btn = button->objectName();
    qDebug() <<"Button: "<<btn;
    QString a = btn.last(1);
    w_other_num = w_other_num+a;

    ui->text_other->setText(w_other_num);
}


void mainMenu::withdrawOtherPressed()
{
    qDebug()<<"withdraw other pressed.";
    qDebug()<< ui->text_other->text().toInt() << "€";
    p_withdrawCall->clearBills();
    p_withdrawCall->checkBills(ui->text_other->text().toInt());

    if(ui->text_other->text().toDouble() > 19) {

        if(checkBalance(ui->text_other->text().toDouble())&& billsready) {
            p_withdrawCall->sendTransaction(token,accountId,ui->text_other->text().toDouble());
            p_withdrawCall->updateBills(token,1, ui->text_other->text().toDouble());
            hideShown();
            ui->label_withdraw->setText("Withdraw succesful");
            ui->label_withdraw->show();
            reduceBalance(ui->text_other->text().toDouble());
        }
        else {
            hideShown();
            ui->label_withdraw->setText("Withdraw failed");
            ui->label_withdraw->show();
        }
    }
    else {
        hideShown();
        ui->label_withdraw->setText("withdraw failed");
        ui->label_withdraw->show();
    }
}

void mainMenu::eur20Pressed()
{
    qDebug() << "20  €";
    p_withdrawCall->clearBills();
    p_withdrawCall->checkBills(20);
    if(checkBalance(20)&& billsready) {
        //p_withdrawCall->printAtmBills();
        p_withdrawCall->sendTransaction(token,accountId,20.00);
        p_withdrawCall->updateBills(token,1,20);
        hideShown();
        ui->label_withdraw->setText("Withdraw succesful");
        ui->label_withdraw->show();
        reduceBalance(20);
    }
    else {
        hideShown();
        ui->label_withdraw->setText("Withdraw failed");
        ui->label_withdraw->show();
    }
}

void mainMenu::eur40Pressed()
{
    qDebug() << "40  €";
    p_withdrawCall->clearBills();
    p_withdrawCall->checkBills(40);
    if(checkBalance(40)&& billsready) {
        p_withdrawCall->sendTransaction(token,accountId,40.00);
        p_withdrawCall->updateBills(token,1,40);
        hideShown();
        ui->label_withdraw->setText("Withdraw succesful");
        ui->label_withdraw->show();
        reduceBalance(40);
    }
    else {
        hideShown();
        ui->label_withdraw->setText("Withdraw failed");
        ui->label_withdraw->show();
    }
}

void mainMenu::eur60Pressed()
{
    qDebug() << "60  €";
    p_withdrawCall->clearBills();
    p_withdrawCall->checkBills(60);
    if(checkBalance(40) && billsready) {
        p_withdrawCall->sendTransaction(token,accountId,60.00);
        p_withdrawCall->updateBills(token,1,60);
        connect(p_withdrawCall, SIGNAL(billsdataWritten()), this, SLOT(withdrawReady()));
        hideShown();
        ui->label_withdraw->setText("Withdraw succesful");
        ui->label_withdraw->show();
        reduceBalance(60);
    }
    else {
        hideShown();
        ui->label_withdraw->setText("Withdraw failed");
        ui->label_withdraw->show();
    }

    //hideShown();
}

void mainMenu::eur100Pressed()
{
    qDebug() << "100  €";
    p_withdrawCall->clearBills();
    p_withdrawCall->checkBills(100);
    if(checkBalance(100) && billsready) {
        p_withdrawCall->sendTransaction(token,accountId,100.00);
        p_withdrawCall->updateBills(token,1,100);
        connect(p_withdrawCall, SIGNAL(billsdataWritten()), this, SLOT(withdrawReady()));
        hideShown();
        ui->label_withdraw->setText("Withdraw succesful");
        ui->label_withdraw->show();
        reduceBalance(100);
    }
    else {
        hideShown();
        ui->label_withdraw->setText("Withdraw failed");
        ui->label_withdraw->show();
    }

    //hideShown();
}

void mainMenu::withdrawReady()
{
    //p_withdrawCall->deleteLater();
    //p_withdrawCall = nullptr;
    //resetView();
    ui->btn_withdraw->hide();
    ui->btnBalance->hide();
    ui->btn_transactions->hide();
    ui->label_withdraw->setText("Withdraw complete. Logging out.");
    ui->label_withdraw->show();



}

void mainMenu::closeWithdrawCall()
{
    delete p_withdrawCall;
    p_withdrawCall = nullptr;
}

void mainMenu::billsOk(bool a)
{
    billsready = a;
}


bool mainMenu::checkBalance(double amount)
{

    qDebug() << amount;
    if(amount > balance1.toDouble()) {
        qDebug() <<"Balance failed :" << balance1.toDouble();
        //ui->label_withdraw->setText("Withdraw failed.");
        //ui->label_withdraw->show();
        return false;
    }
    else {
        qDebug() << "Balance success :" << balance1.toDouble();
        return true;
    }

}

void mainMenu::reduceBalance(double amount)
{
    qDebug() << amount;
    double newBalance = 0;
    newBalance = balance1.toDouble();
    newBalance = newBalance-amount;
    ui->btnClose->hide();

    bal->updateBalance(token, accountId, QString::number(newBalance));
    QTimer::singleShot(1000, this, SLOT(closeWithdrawCall()));
    QTimer::singleShot(3000, this, SLOT(onBtnlogoutClicked()));
}

void mainMenu::resetView()
{

    ui->balanceLabel->hide();
    ui->label_withdraw->hide();
    ui->tableViewTransactions->hide();

    ui->eur20->hide();
    ui->eur40->hide();
    ui->eur60->hide();
    ui->eur100->hide();
    ui->eurOther->hide();
    ui->btnnext5->hide();
    ui->btnprevious5->hide();

    //ui->text_other->hide();
    ui->withdrawOther->hide();
    ui->balanceBrowser->hide();

    ui->btnClose->hide();

    ui->btnBalance->show();
    ui->btn_transactions->show();
    //ui->btnClose->show();
    ui->btn_withdraw->show();
    if(p_withdrawCall != nullptr) {
        delete p_withdrawCall;
        p_withdrawCall = nullptr;
    }

    ui->wKeyboard->hide();
}

void mainMenu::noOlderTransactions()
{
    qDebug() << "Ei vanhempia tilitapahtumia";
    ui->btnprevious5->setEnabled(false);
    ui->btnprevious5->setText("No older transactions");
    QStandardItemModel *model = new QStandardItemModel();
    model->clear();
    ui->tableViewTransactions->setModel(model);
    ui->tableViewTransactions->show();
    return;
}

void mainMenu::next5Transactions()
{
    if(!tableTransactions.isEmpty()) {
        tableTransactions.clear();
    }
    test = new Transactions();
    this->offsetInteger -= 5;
    if (this->offsetInteger == 0)
    {
        ui->btnnext5->setEnabled(false);
    }
    ui->btnprevious5->setEnabled(true);
    ui->btnprevious5->setText("Previous 5 transactions");
    test->requestTrasactions(token,accountId,this->offsetInteger);
    connect(test,SIGNAL(ResponseToMain(QJsonArray)), this, SLOT(receiveTransactionData(QJsonArray)));
    //test->show();
}

void mainMenu::previous5Transactions()
{
    if(!tableTransactions.isEmpty()) {
        tableTransactions.clear();
    }
    test = new Transactions();
    this->offsetInteger += 5;
    ui->btnnext5->setEnabled(true);
    test->requestTrasactions(token,accountId,this->offsetInteger);
    connect(test,SIGNAL(ResponseToMain(QJsonArray)), this, SLOT(receiveTransactionData(QJsonArray)));
    connect(test,SIGNAL(noMoreTransactions()), this, SLOT(noOlderTransactions()));
    //test->show();
}

void mainMenu::sendTransactionRequest()
{
    hideShown();
    ui->btnBalance->hide();
    ui->btn_transactions->hide();
    ui->btn_withdraw->hide();

    if(!tableTransactions.isEmpty()) {
        tableTransactions.clear();
    }
    test = new Transactions();
    this->offsetInteger = 0;
    test->requestTrasactions(token,accountId,this->offsetInteger);
    connect(test,SIGNAL(ResponseToMain(QJsonArray)), this, SLOT(receiveTransactionData(QJsonArray)));
    //test->show();
}

void mainMenu::receiveTransactionData(QJsonArray reply)
{
    qDebug() << "Vastaus Mainille: "<<reply;
    if (reply.isEmpty())
    {
        qDebug() << "Ei vanhempia tilitapahtumia";
        ui->btnprevious5->setEnabled(false);
        ui->btnprevious5->setText("No older transactions");
        QStandardItemModel *model = new QStandardItemModel();
        model->clear();
        ui->tableViewTransactions->setModel(model);
        ui->tableViewTransactions->show();
        return;
    }
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
    ui->tableViewTransactions->setGeometry(350,0,420,200);
    ui->tableViewTransactions->move((screenSize.getScreenwidth()/2) - 280,(screenSize.getScreenheight()/2) - 100);
    ui->tableViewTransactions->show();
    ui->btnnext5->move((screenSize.getScreenwidth()/2) + 250, (screenSize.getScreenheight()/2) - 150);
    ui->btnprevious5->move((screenSize.getScreenwidth()/2)+ 250, (screenSize.getScreenheight()/2) - 100);
    ui->btnnext5->show();
    ui->btnprevious5->show();

}

void mainMenu::readTransactionValues()
{
    qDebug()<<"Setting up Model: ";
    table_model = new QStandardItemModel(tableTransactions.size(),5);
    table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("event id"));
    table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("account id"));
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
    //fetchBalance();
    ui->btnClose->show();
    ui->btn_withdraw->hide();
    ui->btnBalance->hide();
    ui->btn_transactions->hide();
    balance1 = bal;
    //QString text = QString::number(balance1);
    qDebug()<<"mainmenu balance1: "<<balance1;
    ui->balanceLabel->move((screenSize.getScreenwidth()/2) + 100,(screenSize.getScreenheight()/2) - 200);
    ui->balanceLabel->setText("Balance :" + balance1);
    ui->balanceLabel->adjustSize();
    ui->balanceLabel->repaint();
    ui->balanceLabel->show();
}

void mainMenu::fetchBalance()
{
    bal->fetchBalance(accountId);
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
    ui->balanceBrowser->hide();

    ui->btnClose->show();

    ui->wKeyboard->hide();
    ui->btnprevious5->hide();
    ui->btnnext5->hide();
/*    ui->btnBalance->show();
    ui->btn_transactions->show();

    ui->btn_withdraw->show();
*/
}

void mainMenu::onBtnlogoutClicked()
{
    hideShown();
    emit logOutSignal();

}

