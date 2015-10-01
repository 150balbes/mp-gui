#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);

    QApplication a(argc, argv);
    MainWindow w;
    w.resize(740, 480);
    w.move(0, 0);
    w.show();
    return a.exec();
}
