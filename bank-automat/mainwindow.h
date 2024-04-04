#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <dllserialport.h>
#include <dllrestapi.h>
#include <QList>
#include "data.h"
#include <QString>
#include <QStandarditemModel>
#include <QStandardItem>

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

    QString cardNumber;
    DLLSerialport * sPort = nullptr;
    DLLRestAPI *restApi = nullptr;
    Transactions *test = nullptr;
    void connectSerial();
    void disconnectSerial();

    //DLLRestAPI

    QList<transactions> tableTransactions;
    QList<database> tableData;
    QList<transfer> tableTransfer;





signals:
    void transactionsComplete();
    void transactionsTableReady();
    void sendCardSignal(QString);

private slots:
    void receiveCardNumber(QString);
    void receiveData(QJsonArray);
    void displayData();
    void sendTransactionRequest();
public slots:
    void readTransactionValues();
};
#endif // MAINWINDOW_H
