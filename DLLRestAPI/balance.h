#ifndef BALANCE_H
#define BALANCE_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class balance;
}

class balance : public QDialog
{
    Q_OBJECT

public:
    explicit balance(QWidget *parent = nullptr);
    ~balance();

private slots:
    void showBalance();

private:
    Ui::balance *ui;
};

#endif // BALANCE_H
