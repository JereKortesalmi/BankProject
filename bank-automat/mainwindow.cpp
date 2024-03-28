#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectSerial();
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

void MainWindow::receiveCardNumber(QString val)
{
    cardNumber=val;
}
