#include "pincode.h"
#include "ui_pincode.h"

PinCode::PinCode(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PinCode)
{
    QSize size = qApp->screens()[0]->size();
    //screenSize.setScreenwidth(size.width());
    //screenSize.setScreenheight(size.height());
    screenWidth = size.width();
    screenHeight = size.height();

    ui->setupUi(this);
    ui->signIn->move((screenWidth/2) - 250,(screenHeight/2) - 220);
    connect(ui->N0,SIGNAL(clicked(bool)),this,SLOT(clickHandler()));
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
    connect(ui->Reset,SIGNAL(clicked(bool)),this,SLOT(onBtnCancel()));
    connect(ui->btnRevert,SIGNAL(clicked(bool)),this,SLOT(revertHandler()));
}

PinCode::~PinCode()
{
    delete ui;
    qDebug()<<"Pincode pincode destruktori";
}

void PinCode::pinMessage(QString message)
{
    QString mes = message;
    ui->messageLabel->setText(mes);
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
    number=ui->pinLine->text();
    emit sendPinCodeToMainWindow(number);
}

void PinCode::resetHandler()
{
    ui->pinLine->clear();
    number=ui->pinLine->text();
    ui->messageLabel->clear();
    close();
}


void PinCode::revertHandler()
{
    number.removeLast();
    ui->pinLine->setText(number);
    ui->messageLabel->clear();
}

void PinCode::onBtnCancel()
{
    emit pinLogout();
    ui->pinLine->clear();
    number=ui->pinLine->text();
    ui->messageLabel->clear();
    close();
}


