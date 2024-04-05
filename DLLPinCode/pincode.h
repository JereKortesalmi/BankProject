#ifndef PINCODE_H
#define PINCODE_H
#include "DLLPinCode_global.h"
#include <QDialog>
//#include <mainwindow.h>

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
    void cardNumberHandler(QString);

private:
    Ui::PinCode *ui;
    QString number;
};

#endif // PINCODE_H
