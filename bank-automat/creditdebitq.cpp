#include "creditdebitq.h"
#include "ui_creditdebitq.h"

creditdebitq::creditdebitq(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::creditdebitq)
{
    ui->setupUi(this);
}

creditdebitq::~creditdebitq()
{
    delete ui;
}



void creditdebitq::on_creditbtn_clicked()
{

}
