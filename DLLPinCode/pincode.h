#ifndef PINCODE_H
#define PINCODE_H
#include "DLLPinCode_global.h"
#include <QDialog>
//#include "mainwindow.h"

namespace Ui {
class PinCode;
}

class DLLPINCODE_EXPORT PinCode : public QDialog
{
    Q_OBJECT

public:
    explicit PinCode(QWidget *parent = nullptr);
    ~PinCode();

    void cardNumberHandler(QString);


signals:
    void sendPinCodeToMainWindow(QString);
private slots:
    void clickHandler();
    void enterHandler();
    void resetHandler();



private:
    Ui::PinCode *ui;
    QString number;
    QString cardNumber;

    //mainwindow *card;
};

#endif // PINCODE_H
