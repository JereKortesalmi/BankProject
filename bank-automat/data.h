#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QDebug>

class database
{
public:
    database();
    ~database();

private:
    int id;
    QString forKey;
};

class transactions
{
public:
    transactions();
    ~transactions();

    QString getTransaction_account_id() const;
    void setTransaction_account_id(const QString &newTransaction_account_id);

    QString getTransactions_atm_id() const;
    void setTransactions_atm_id(const QString &newTransactions_atm_id);

    QString getTransaction_time() const;
    void setTransaction_time(const QString &newTransaction_time);

    QString getTransaction_type() const;
    void setTransaction_type(const QString &newTransaction_type);

    QString getTransaction_amount() const;
    void setTransaction_amount(const QString &newTransaction_amount);

private:
    QString transaction_account_id;
    QString transactions_atm_id;
    QString transaction_time;
    QString transaction_type;
    QString transaction_amount;

private:
    int id;
    QString forKey;
};

class screensize
{
public:
    screensize();
    ~screensize();
    int screenwidth;
    int screenheight;



    int getScreenwidth() const;
    void setScreenwidth(int newScreenwidth);
    int getScreenheight() const;
    void setScreenheight(int newScreenheight);
};

class transfer
{
public:
    transfer();
    ~transfer();
};

#endif // DATA_H
