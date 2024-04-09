#ifndef BALANCE_H
#define BALANCE_H
#include "DLLRestAPI_global.h"
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
signals:
    void sendToMain(QString reply);

private slots:
    void getBalance(QNetworkReply *reply);

    void on_btnBalance_clicked();

private:
    Ui::balance *ui;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // BALANCE_H
