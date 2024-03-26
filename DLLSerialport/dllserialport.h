#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include "DLLSerialport_global.h"
#include <QSerialPort>
#include <QSerialportInfo>
#include <QWidget>
#include <QDebug>
#include <QObject>
#include <QDebug>

class DLLSERIALPORT_EXPORT DLLSerialport : public QWidget
{
    Q_OBJECT
public:
    DLLSerialport();
    ~DLLSerialport();
private:
    QString name;
    quint16 vendor;
    QList<QSerialPortInfo> serialPorts;

    qint32 baudRate = QSerialPort::Baud9600;
    QSerialPort::DataBits dataBits = QSerialPort::Data8;
    QSerialPort::Parity parity = QSerialPort::NoParity;
    QSerialPort::StopBits stopBits = QSerialPort::OneStop;
    QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl;
    QSerialPort * serialPort = nullptr;

public slots:
    quint16 getVendorID();
    QString getName();
    void getVendor();
    void setName(QString);
    void setVendor(quint16);

private slots:
    void openSerialPort();
    void closeSerialPort();
    void readData();

signals:
    void sendCardNumber();
    void signalNameSet();
    void signalVendorSet();

};

#endif // DLLSERIALPORT_H
