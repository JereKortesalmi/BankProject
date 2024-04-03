#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <DLLSerialport_global.h>

//Korttien numerot
//  -0600062211
//  -0500CB1EF8
//  -0500CB1FF3

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectSerial();
    sendTransactionRequest();
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
    test = new Transactions(&tableTransactions);


}

void MainWindow::receiveCardNumber(QString val)
{
    cardNumber=val;
}



