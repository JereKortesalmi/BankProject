#ifndef LOGIN_H
#define LOGIN_H
#include "DLLRestAPI_global.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QObject>
#include <QDebug>



class DLLRESTAPI_EXPORT login : public QObject
{
    Q_OBJECT
public:
    login();
    ~login();
    QString pinCode;
    QString cardNumber;
    void pinCodeLog(QString);
    void cardNumberLog(QString);
    void loginHandler(QString,QString);



signals:
    //void sendSignalLogin(QString,QString);

public slots:
    //void loginSlot(QNetworkReply *reply);
private slots:



private:
    QNetworkAccessManager *loginmanager;
    QNetworkReply *reply;
    QByteArray response_data;


};

#endif // LOGIN_H
