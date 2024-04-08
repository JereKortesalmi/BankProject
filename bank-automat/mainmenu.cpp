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
}

mainMenu::~mainMenu()
{
    delete ui;
}
