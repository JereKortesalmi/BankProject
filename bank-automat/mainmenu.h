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

    //restapi
    DLLRestAPI *restApi = nullptr;

    //requestReceiver
    requestReceiver *requestRec = nullptr;

    int accountId;
    QByteArray token;
    QString accountType;

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
    void withdrawReady();

    //tableview
    void sendTransactionRequest();
    void receiveTransactionData(QJsonArray);
    void displayData();
    //balance slots
    void showBalance(QString);
    void fetchBalance();
    //hide
    void hideShown();

public slots:
    void readTransactionValues(); // transactions


signals:
    void transactionsComplete();        //transactions
    void transactionsTableReady();      //transactions
};

#endif // MAINMENU_H
