#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <dllserialport.h>
#include <dllrestapi.h>
#include <QList>
#include "data.h"
#include <QString>
#include <QStandarditemModel>
#include <QStandardItem>

//lisätyt h tiedostot.
#include "mainmenu.h"
#include <dllpincode.h>
#include <pincode.h>
#include <login.h>
#include <creditdebitq.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QStandardItemModel *table_model;

private:
    Ui::MainWindow *ui;

    mainMenu *p_mainMenu = nullptr;

    QString cardNumber;
    QString pinCode;
    QByteArray token;
    DLLSerialport * sPort = nullptr;
    DLLRestAPI *restApi = nullptr;
    Transactions *test = nullptr;
    balance *bal = nullptr;
    void connectSerial();
    void disconnectSerial();

    //DLLRestAPI

    QList<transactions> tableTransactions;
    QList<database> tableData;
    QList<transfer> tableTransfer;

    login *log;
    creditdebitq *creditDebit;

    //PINCODE
    PinCode *pin;

    QNetworkAccessManager *accountManager;
    QNetworkReply *reply;

signals:
    void transactionsComplete();
    void transactionsTableReady();
    void sendCardSingal(QString);
    void sendSignal(QString);

private slots:
    void receiveCardNumber(QString);
    void receivePinNumber(QString);
    void receiveData(QJsonArray);
    void displayData();
    void sendTransactionRequest();
    void cardNumberHand();
    void loginInfo(QString);
    void loginMessageToPinCode(QString);
    void accountIdSender(int, QString);
    void creditdebitchoose(QJsonArray);

public slots:
    void readTransactionValues();
};
#endif // MAINWINDOW_H
