#ifndef PINCODE_H
#define PINCODE_H
#include "DLLPinCode_global.h"
#include <QDialog>
/*#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtNetwork>
#include <QJsonDocument>*/


namespace Ui {
class PinCode;
}

class DLLPINCODE_EXPORT PinCode : public QDialog
{
    Q_OBJECT

public:
    explicit PinCode(QWidget *parent = nullptr);
    ~PinCode();
signals:
    void sendPinCodeToMainWindow(QString);
private slots:
    void clickHandler();
    void enterHandler();
    void resetHandler();
    //void loginSlot(QNetworkReply *reply);

private:
    Ui::PinCode *ui;
    QString number;

   /* QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;*/

};

#endif // PINCODE_H
