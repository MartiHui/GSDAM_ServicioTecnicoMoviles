#include "mainwindow.h"
#include <QApplication>
#include <QWebSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    QWebSocket socket;
    socket.open(QUrl("ws://localhost:1234"));

    return a.exec();
}
