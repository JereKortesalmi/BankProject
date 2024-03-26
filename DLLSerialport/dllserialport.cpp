#include "dllserialport.h"

DLLSerialport::DLLSerialport() {
    qDebug() << "SerialDLL constructor";
    serialPort = new QSerialPort(this);
}

DLLSerialport::~DLLSerialport()
{
    qDebug() << "SerialDLL destructor";
}

quint16 DLLSerialport::getVendorID()
{
    qDebug() << "getVendorSlot() -> Returning quint16.";
    return vendor;
}

QString DLLSerialport::getName()
{
    qDebug() << "getName() -> returning value QString:";
    return name;
}

void DLLSerialport::getVendor()
{
    serialPorts = QSerialPortInfo::availablePorts();
    foreach(const QSerialPortInfo &portInfo, serialPorts ) {
        if(portInfo.vendorIdentifier() == 5562) {
            //qDebug()<<"PortInfo: " << portInfo.manufacturer();
            //qDebug()<<"PortName: " << portInfo.portName();
            setName(portInfo.portName());
            //qDebug()<<"SerialNumber: " << portInfo.serialNumber();
            //qDebug()<<"Description: " << portInfo.description();
            //qDebug()<<"VendorIdentifier: "<<portInfo.vendorIdentifier();
            setVendor(portInfo.vendorIdentifier());
        }
    }
}

void DLLSerialport::setName(QString n)
{
    name=n;
    emit signalNameSet();
}

void DLLSerialport::setVendor(quint16 v)
{
    vendor = v;
    emit signalVendorSet();
}

void DLLSerialport::openSerialPort()
{
    qDebug() << "OpenSerialPort";
    serialPort->setPortName(name);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(dataBits);
    serialPort->setParity(parity);
    serialPort->setStopBits(stopBits);
    serialPort->setFlowControl(flowControl);
    if(serialPort->open(QIODevice::ReadOnly)) {
        qDebug()<<"SerialPort read mode";
    }
    else {
        qDebug()<<"Error";
    }
}

void DLLSerialport::closeSerialPort()
{
    qDebug() << "closeSerialPort()";

    if(serialPort->isOpen()) {
        serialPort->close();
        qDebug()<<"Serialport was closed.";
    }
    else {
        qDebug()<<"Serialport was already closed.";
    }
}

void DLLSerialport::readData()
{
    qDebug() << "readData()";
}
