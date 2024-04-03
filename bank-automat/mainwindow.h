#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <dllserialport.h>
#include <QList>
#include "data.h"

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

private:
    Ui::MainWindow *ui;

    QString cardNumber;
    DLLSerialport * sPort = nullptr;
    void connectSerial();
    void disconnectSerial();
    QList<transactions> tableTransactions;
    QList<database> tableData;
    QList<transfer> tableTransfer;

private slots:
    void receiveCardNumber(QString);

};
#endif // MAINWINDOW_H
