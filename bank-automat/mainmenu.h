#ifndef MAINMENU_H
#define MAINMENU_H

#include "requestreceiver.h"
#include "transactions.h"
#include "withdrawcall.h"
#include <QDialog>
#include "balance.h"

//tarvitaan esittämään data tableviewssä
#include <QList>
#include "data.h"
#include <QString>
#include <QStandarditemModel>
#include <QStandardItem>
#include <QScreen>

namespace Ui {
class mainMenu;
}

class mainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit mainMenu(QWidget *parent = nullptr);
    ~mainMenu();

    //tableview
    QStandardItemModel *table_model;
    //transactions
    Transactions *test = nullptr;           //transactions
    //balance
    balance *bal = nullptr;
    screensize screenSize;
    //restapi
    DLLRestAPI *restApi = nullptr;

    //requestReceiver
    requestReceiver *requestRec = nullptr;

    int accountId;
    QByteArray token;
    QString accountType;
    int offsetInteger;
    int transactionCount;
    int automatID;
    bool showTransferButton = false;
    QString bothId;


private:
    Ui::mainMenu *ui;
    Transactions *p_Transactions = nullptr; //transactions
    //withdrawCall
    withdrawCall *p_withdrawCall = nullptr;
    //balance
    balance *saldo = nullptr;
    //tableview
    QList<transactions> tableTransactions;  //transactions
    QList<database> tableData;
    QList<transfer> tableTransfer;          //transactions
    bool checkBalance(double amount);
    void reduceBalance(double amount);

    short kbstate = 0;
    QString balance1;
    bool billsready;

    QString w_other_num = "";
    QString t_num = "";

public slots:
    //withdrawCall
    void withdrawSignalReceived();
    void atmSignalReceived();
    void withdrawClicked();
    void otherClicked();
    void withdrawOtherPressed();
    void eur20Pressed();
    void eur40Pressed();
    void eur60Pressed();
    void eur100Pressed();
    void onBtnlogoutClicked();
    void withdrawReady();
    void next5Transactions();
    void previous5Transactions();
    void closeWithdrawCall();
    void billsOk (bool);

    void clickHandler();

    //tableview
    void sendTransactionRequest();
    void receiveTransactionData(QJsonArray);
    void displayData();
    //balance slots
    void showBalance(QString);
    void fetchBalance();
    //hide
    void hideShown();
    void resetView();
    void noOlderTransactions();

    void showTransfer(); // transfer


public slots:
    void readTransactionValues(); // transactions


signals:
    void transactionsComplete();        //transactions
    void transactionsTableReady();      //transactions
    void logOutSignal();
private slots:
};

#endif // MAINMENU_H
