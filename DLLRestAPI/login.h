#ifndef LOGIN_H
#define LOGIN_H
#include "DLLRestAPI_global.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QObject>
#include <QDebug>
#include <QMessageBox>



class DLLRESTAPI_EXPORT login : public QObject
{
    Q_OBJECT
public:
    login();
    ~login();
    QString pinCode;
    QString cardNumber;
    void cardNumberLog(QString);
    void loginHandler(QString);
    int accountLock;
    QString cardState;


public slots:
    void loginSlot(QNetworkReply *reply);
    void lockSlot(QNetworkReply *replys);
    void cardStateSlot(QNetworkReply *repl);
signals:
    void sendSignalLogin(QString);
    void loginMessage(QString);
private slots:



private:
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
/*
    QNetworkAccessManager *stateManager;
    QNetworkReply *repl;
    QByteArray response_datas;
*/

};

#endif // LOGIN_H
