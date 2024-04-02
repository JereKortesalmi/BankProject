#include "pincode.h"
#include "ui_pincode.h"

PinCode::PinCode(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PinCode)
{
    ui->setupUi(this);
    connect(ui->N1,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N2,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N3,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N4,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N5,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N6,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N7,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N8,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
    connect(ui->N9,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));

    connect(ui->Enter,SIGNAL(clicked(bool)),this,SLOT(enterHandler()));
    connect(ui->Reset,SIGNAL(clicked(bool)),this,SLOT(resetHandler()));
}

PinCode::~PinCode()
{
    delete ui;
    qDebug()<<"Pincode pincode destruktori";
}

void PinCode::clickHandler()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString pin = button->objectName();
    qDebug() <<"Button: "<<pin;

    QString a= pin.last(1);
    number = number + a;

    ui->pinLine->setText(number);
}

void PinCode::enterHandler()
{
    emit sendPinCodeToMainWindow(number);
    QJsonObject jsonObj;
    //jsonObj.insert("username",uname);
    //jsonObj.insert("password",password);

    //QString site_url="http://"
}

void PinCode::resetHandler()
{
    ui->pinLine->setText(0);
    emit sendPinCodeToMainWindow(0);
    number = 0;
}

void PinCode::loginSlot(QNetworkReply *reply)
{

}
