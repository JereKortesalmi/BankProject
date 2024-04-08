#ifndef MAINMENU_H
#define MAINMENU_H

#include "transactions.h"
#include "withdrawcall.h"
#include <QDialog>

namespace Ui {
class mainMenu;
}

class mainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit mainMenu(QWidget *parent = nullptr);
    ~mainMenu();

private:
    Ui::mainMenu *ui;
    Transactions *p_Transactions = nullptr;
    withdrawCall *p_withdrawCall = nullptr;

private slots:
    void signalReceived();
};

#endif // MAINMENU_H
