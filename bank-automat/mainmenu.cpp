#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);
    Transactions *p_Transactions = new Transactions(this);

    // näytetään Transactions-ikkuna
    // p_Transactions->show();

    //webtoken
    QByteArray token = "2386028485693820asdjfklöaueiwolsdfjklasdfjkasödjfkl(/";
    // withdrawCall
    withdrawCall *p_withdrawCall = new withdrawCall(this);
    connect(p_withdrawCall, SIGNAL(dataRead()), this, SLOT(signalReceived()));
    p_withdrawCall->sendRequest(token, 5, 20.00);
}

mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::signalReceived()
{
    qDebug()<<"Reading was done. So no error was received.";

}
