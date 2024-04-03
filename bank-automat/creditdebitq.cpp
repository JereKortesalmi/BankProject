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

void creditdebitq::setUsername(const QString &newUsername)
{
    username = newUsername;
    ui->labelInfo->setText(username);
}

void creditdebitq::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
    qDebug()<<webToken;
}

void creditdebitq::on_creditbtn_clicked()
{
    QString site_url="http://localhost:3000/book";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    infoManager = new QNetworkAccessManager(this);

    connect(infoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(infoSlot(QNetworkReply*)));

    reply = infoManager->get(request);
}

void creditdebitq::infoSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    //qDebug()<<response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    //CreditInfo *objectStudentInfo=new StudentInfo(this);
    //objectCreditInfo->set..(json_obj[""].toString());

    //objectCreditInfo->show();
    QString fname=json_obj["fname"].toString();
    qDebug()<<fname;
    reply->deleteLater();
    infoManager->deleteLater();

}

