#include "data.h"

database::database() {
    qDebug()<<"database Class Constructor";

}

database::~database()
{
    qDebug()<<"database Class Destructor";
}

transactions::transactions()
{
    qDebug()<<"transactions Class Constructor";
}

transactions::~transactions()
{
    qDebug()<<"transactions Class Destructor";
}

QString transactions::getTransaction_account_id() const
{
    return transaction_account_id;
}

void transactions::setTransaction_account_id(const QString &newTransaction_account_id)
{
    transaction_account_id = newTransaction_account_id;
}

QString transactions::getTransactions_atm_id() const
{
    return transactions_atm_id;
}

void transactions::setTransactions_atm_id(const QString &newTransactions_atm_id)
{
    transactions_atm_id = newTransactions_atm_id;
}

QString transactions::getTransaction_time() const
{
    return transaction_time;
}

void transactions::setTransaction_time(const QString &newTransaction_time)
{
    transaction_time = newTransaction_time;
}

QString transactions::getTransaction_type() const
{
    return transaction_type;
}

void transactions::setTransaction_type(const QString &newTransaction_type)
{
    transaction_type = newTransaction_type;
}

QString transactions::getTransaction_amount() const
{
    return transaction_amount;
}

void transactions::setTransaction_amount(const QString &newTransaction_amount)
{
    transaction_amount = newTransaction_amount;
}

transfer::transfer()
{
    qDebug()<<"transfer Class Constructor";
}

transfer::~transfer()
{
    qDebug()<<"transfer Class Destructor";
}

screensize::screensize()
{

}

screensize::~screensize()
{

}

int screensize::getScreenheight() const
{
    return screenheight;
}

void screensize::setScreenheight(int newScreenheight)
{
    screenheight = newScreenheight;
}

int screensize::getScreenwidth() const
{
    return screenwidth;
}

void screensize::setScreenwidth(int newScreenwidth)
{
    screenwidth = newScreenwidth;
}

