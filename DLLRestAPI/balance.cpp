#include "balance.h"
#include "ui_balance.h"

balance::balance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::balance)
{
    ui->setupUi(this);
    qDebug()<<"balance konstruktori";
    connect(ui->btnBalance,SIGNAL(clicked(bool)),this,SLOT(showBalance()));
}

balance::~balance()
{
    delete ui;
}

void balance::showBalance()
{

}
