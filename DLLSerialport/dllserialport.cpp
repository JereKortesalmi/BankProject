#include "dllserialport.h"

DLLSerialport::DLLSerialport() {
    qDebug() << "SerialDLL constructor";
    serialPort = new QSerialPort(this);
    pTimer = new QTimer(this);
    connect(pTimer,SIGNAL(timeout()),this,SLOT(runTimer()));
    pTimer->start(1000);
}

DLLSerialport::~DLLSerialport()
{
    qDebug() << "SerialDLL destructor";
    closeSerialPort();
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

            //qDebug()<<"SerialNumber: " << portInfo.serialNumber();
            //qDebug()<<"Description: " << portInfo.description();
            //qDebug()<<"VendorIdentifier: "<<portInfo.vendorIdentifier();

            //sets values for the vendor and portname. Setters send signals.
            setVendor(portInfo.vendorIdentifier());
            setName(portInfo.portName());
        }
    }
}

void DLLSerialport::setName(QString n)
{
    name=n;
    emit signalNameSet();
    if(name != "") {
        openSerialPort();
    }
    else {
        qDebug()<< "Name was empty";
    }

}

void DLLSerialport::setVendor(quint16 v)
{
    vendor = v;
    emit signalVendorSet();
}

void DLLSerialport::setCardNumber(QString val)
{
    cardNumber=val;
    emit sendCardNumber(cardNumber);
}

void DLLSerialport::openSerialPort()
{

    qDebug() << "Opening Serialport";
    serialPort->setPortName(name);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(dataBits);
    serialPort->setParity(parity);
    serialPort->setStopBits(stopBits);
    serialPort->setFlowControl(flowControl);

    if(serialPort->open(QIODevice::ReadOnly)) {
        qDebug()<<"SerialPort in read mode, connected.";
        connect(serialPort,SIGNAL(readyRead()),this,SLOT(readData()));
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
    const QByteArray data = serialPort->readAll();
    //qDebug() << "data: " << data;

    QString dataString(data);


    qDebug()<<""<<dataString;
    QList dlist=dataString.split("\r\n");
    //qDebug() << dlist[0];
    qDebug() << dlist[1];
    //qDebug()<< dlist[2];
    QList cardnumberSplit=dlist[1].split("-");
    qDebug()<<cardnumberSplit[1];
    setCardNumber(cardnumberSplit[1]);

}

void DLLSerialport::runTimer()
{
    if(name=="") {
        qDebug()<<"Not yet connected.";
        getVendor();
    }
    else {
        qDebug()<<"connected";
    }
}
