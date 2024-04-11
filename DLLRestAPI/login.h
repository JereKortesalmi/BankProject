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



signals:
    void sendSignalLogin(QString);
    void loginError(QString);
    void loginWrong(QString);

public slots:
    void loginSlot(QNetworkReply *reply);
private slots:



private:
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;


};

#endif // LOGIN_H
