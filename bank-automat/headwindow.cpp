#include "headwindow.h"
#include "ui_headwindow.h"

headwindow::headwindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::headwindow)
{
    ui->setupUi(this);
}

headwindow::~headwindow()
{
    delete ui;
}
