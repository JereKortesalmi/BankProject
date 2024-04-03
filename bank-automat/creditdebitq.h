#ifndef CREDITDEBITQ_H
#define CREDITDEBITQ_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>


namespace Ui {
class creditdebitq;
}

class creditdebitq : public QDialog
{
    Q_OBJECT

public:
    explicit creditdebitq(QWidget *parent = nullptr);
    ~creditdebitq();

    void setUsername(const QString &newUsername);

    void setWebToken(const QByteArray &newWebToken);

private slots:
    void on_creditbtn_clicked();
    void infoSlot(QNetworkReply *reply);

private:
    Ui::creditdebitq *ui;
    QString username;
    QByteArray webToken;
    QNetworkAccessManager *infoManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // CREDITDEBITQ_H
