#include "creditdebitq.h"
#include "ui_creditdebitq.h"

creditdebitq::creditdebitq(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creditdebitq)
{
    ui->setupUi(this);
    connect(ui->btnCredit,SIGNAL(clicked(bool)),this,SLOT(onCreditButtonClicked()));
    connect(ui->btnDebit,SIGNAL(clicked(bool)),this,SLOT(onDebitButtonClicked()));
    mainmenu = new mainMenu;
}

creditdebitq::~creditdebitq()
{
    delete ui;
}

void creditdebitq::onCreditButtonClicked()
{
    accountType = "CREDIT";
    selectAccount();
}

void creditdebitq::onDebitButtonClicked()
{
    accountType = "DEBIT";
    selectAccount();
}

void creditdebitq::selectAccount()
{
    for(const auto& value : jsonArray){
        if(value.isObject()){
            QJsonObject jsonObject = value.toObject();
            QString type = jsonObject["account_type"].toString();
            qDebug()<<"type:"<<type<<" accountType:"<<accountType;
            if(type == accountType){
                selectedAccountId = jsonObject["account_id"].toInt();
                qDebug()<<"account_id:"<<selectedAccountId;
                hide();
                mainmenu->show();
                return;
            }
        }
    }
}

void creditdebitq::selectAccountHandler(const QJsonArray jsonArray)
{
    this->jsonArray = jsonArray;
}
