#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include "DLLSerialport_global.h"
#include <QSerialPort>
#include <QSerialportInfo>
#include <QWidget>
#include <QDebug>
#include <QObject>
#include <QDebug>
#include <QTimer>

class DLLSERIALPORT_EXPORT DLLSerialport : public QWidget
{
    Q_OBJECT
public:
    DLLSerialport();
    ~DLLSerialport();
private:
    QString name;
    quint16 vendor;
    QString cardNumber;
    QList<QSerialPortInfo> serialPorts;
    bool disconnected = true;
    bool connected = false;

    qint32 baudRate = QSerialPort::Baud9600;
    QSerialPort::DataBits dataBits = QSerialPort::Data8;
    QSerialPort::Parity parity = QSerialPort::NoParity;
    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
    QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl;
    QSerialPort * serialPort = nullptr;

    QTimer * pTimer = nullptr;
    //QTimer * rTimer = nullptr;

public slots:
    quint16 getVendorID();
    QString getName();
    void getVendor();
    void setName(QString);
private slots:
    void setVendor(quint16);
    void setCardNumber(QString);
    void checkConnection();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void readData();
    void runTimer();


signals:
    void sendCardNumber(QString);
    void signalNameSet();
    void signalVendorSet();

};

#endif // DLLSERIALPORT_H
