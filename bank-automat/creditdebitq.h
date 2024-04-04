#ifndef CREDITDEBITQ_H
#define CREDITDEBITQ_H

#include <QDialog>


namespace Ui {
class creditdebitq;
}

class creditdebitq : public QDialog
{
    Q_OBJECT

public:
    explicit creditdebitq(QWidget *parent = nullptr);
    ~creditdebitq();

private slots:
    void on_creditbtn_clicked();

private:
    Ui::creditdebitq *ui;
};

#endif // CREDITDEBITQ_H
