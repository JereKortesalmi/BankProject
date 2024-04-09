#ifndef MAINMENU_H
#define MAINMENU_H

#include "transactions.h"
#include "withdrawcall.h"
#include <QDialog>

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

    //restapi
    DLLRestAPI *restApi = nullptr;

private:
    Ui::mainMenu *ui;
    Transactions *p_Transactions = nullptr; //transactions
    //withdrawCall
    withdrawCall *p_withdrawCall = nullptr;

    //tableview
    QList<transactions> tableTransactions;  //transactions
    QList<database> tableData;
    QList<transfer> tableTransfer;          //transactions

private slots:
    //withdrawCall
    void withdrawSignalReceived();

    //tableview
    void sendTransactionRequest();
    void receiveTransactionData(QJsonArray);
    void displayData();

public slots:
    void readTransactionValues(); // transactions

signals:
    void transactionsComplete();        //transactions
    void transactionsTableReady();      //transactions
};

#endif // MAINMENU_H
