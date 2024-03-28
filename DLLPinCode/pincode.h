#ifndef PINCODE_H
#define PINCODE_H

#include <QDialog>

namespace Ui {
class PinCode;
}

class PinCode : public QDialog
{
    Q_OBJECT

public:
    explicit PinCode(QWidget *parent = nullptr);
    ~PinCode();

private:
    Ui::PinCode *ui;
};

#endif // PINCODE_H
