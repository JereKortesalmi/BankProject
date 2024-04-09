#include "login.h"


login::login()
{
    qDebug()<<"login luotu";
}

login::~login()
{
    qDebug()<<"login tuhottu";
}

void login::pinCodeLog(QString val)
{
    pinCode=val;
    qDebug()<<"login pin: "<<pinCode;
}

void login::cardNumberLog(QString val)
{
    cardNumber=val;
    qDebug()<<"login cardnumber: "<<cardNumber;
}


/*
void login::loginHandler(QString pin,QString cardNum)
{
    pin=pinCode;
    qDebug()<<"login pin: "<<pinCode;
    cardNum=cardNumber;
    qDebug()<<"login cardnumber: "<<cardNumber;
}

void login::loginSlot(QNetworkReply *reply)
{

}
*/
