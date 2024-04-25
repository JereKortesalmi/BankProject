#include "creditdebitq.h"
#include "ui_creditdebitq.h"

creditdebitq::creditdebitq(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creditdebitq)
{
    ui->setupUi(this);
    QSize size = qApp->screens()[0]->size();
    screenSize.setScreenwidth(size.width());
    screenSize.setScreenheight(size.height());

    ui->btnCredit->move((screenSize.getScreenwidth()/2) - 150,(screenSize.getScreenheight()/2) + 50);
    ui->btnDebit->move((screenSize.getScreenwidth()/2) + 50,(screenSize.getScreenheight()/2) + 50);
    ui->labelInfo->move((screenSize.getScreenwidth()/2) - 100,(screenSize.getScreenheight()/2) - 100);

    connect(ui->btnCredit,SIGNAL(clicked(bool)),this,SLOT(onCreditButtonClicked()));
    connect(ui->btnDebit,SIGNAL(clicked(bool)),this,SLOT(onDebitButtonClicked()));
    mainmenu = new mainMenu(this);
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
    QString balance;
    QString type;
    for(const auto& value : jsonArray){
        if(value.isObject()){
            QJsonObject jsonObject = value.toObject();
            // bothId + "," +
            type = jsonObject["account_type"].toString();
            bothId = bothId + "," + QString::number(jsonObject["account_id"].toInt());
            qDebug()<<"type:"<<type<<" accountType:"<<accountType;
            if(type == accountType){
                accountId = jsonObject["account_id"].toInt();
                balance = jsonObject["account_balance"].toString();
                qDebug()<<"account_id:"<<accountId;
                hide();


            }
        }
    }
    emit sendAccountId(accountId, balance, type, bothId, true);

}

void creditdebitq::selectAccountHandler(const QJsonArray jsonArray)
{
    this->jsonArray = jsonArray;
}
