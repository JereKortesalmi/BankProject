#include "pincode.h"
#include "ui_pincode.h"

PinCode::PinCode(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PinCode)
{
    ui->setupUi(this);
}

PinCode::~PinCode()
{
    delete ui;
}
