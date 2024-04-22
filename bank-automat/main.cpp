#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir dir("../");
    QString stylesFolder = dir.absolutePath();
    QString cssFilePath = stylesFolder + "/myStyle.qss";
    qDebug()<<cssFilePath;

    QFile file(cssFilePath);
    if (!file.open(QFile::ReadOnly)) {
        // Tiedoston avaaminen epäonnistui
        qDebug()<<"Tyylitiedoston avaus epäonnistui";
        return -1;
    }

    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
