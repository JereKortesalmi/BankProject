#ifndef PINCODE_H
#define PINCODE_H
#include "DLLPinCode_global.h"
#include <QDialog>
#include <QScreen>


namespace Ui {
class PinCode;
}

class DLLPINCODE_EXPORT PinCode : public QDialog
{
    Q_OBJECT

public:
    explicit PinCode(QWidget *parent = nullptr);
    ~PinCode();

    void pinMessage(QString);

signals:
    void sendPinCodeToMainWindow(QString);
    void pinLogout();
public slots:
    void resetHandler();
private slots:
    void onBtnCancel();
    void clickHandler();
    void enterHandler();
    void revertHandler();



private:
    Ui::PinCode *ui;
    QString number;
    int screenWidth;
    int screenHeight;
};

#endif // PINCODE_H
