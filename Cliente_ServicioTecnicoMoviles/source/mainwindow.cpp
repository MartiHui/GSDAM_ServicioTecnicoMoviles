#include <QDebug>
#include <QTimer>
#include <QWebSocket>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverconnection.h"
#include "action.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_serverConnection = new ServerConnection("ws://localhost:1234");
    //m_serverConnection->m_conectado = true;
    //QTimer::singleShot(0, this, SLOT(pruebas()));
    //m_serverConnection->sendMessage(Action::establishConnection("EDIB"));
    //qDebug() << m_serverConnection->m_xmlReply;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pruebas() {
    qDebug() << "enviando mensaje";
    m_serverConnection->m_webSocket->sendTextMessage("hola");
    //m_serverConnection->sendMessage(Action::establishConnection("EDIB"));
    //qDebug() << m_serverConnection->m_xmlReply;
}
