#ifndef HEADWINDOW_H
#define HEADWINDOW_H

#include <QDialog>

namespace Ui {
class headwindow;
}

class headwindow : public QDialog
{
    Q_OBJECT

public:
    explicit headwindow(QWidget *parent = nullptr);
    ~headwindow();

private:
    Ui::headwindow *ui;
};

#endif // HEADWINDOW_H
