#include <QDebug>
#include <QTimer>
#include <QWebSocket>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QComboBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverconnection.h"
#include "action.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actualizarEstado->setEnabled(false);

    m_serverConnection = new ServerConnection("ws://localhost:1234");
    connect(m_serverConnection, SIGNAL(messageReceived(QString)), this, SLOT(replyReceived(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::replyReceived(QString message) {
    Action *action = new Action(message);

    switch (action->getActionType()) {
    case ActionType::ERROR:
        showErrorMsgBox("No te has identificado al servidor");
        ui->conectarServidor->setEnabled(true);
        break;

    case ActionType::ESTABLISH_CONNECTION:
        establishConnectionReply(action);
        break;

    case ActionType::LISTA_ORDENES_REPLY:
        fillListaOrdenes(action);
        break;

    case ActionType::LISTA_STATUS_REPLY:
        fillStatusCmBox(action);
        break;

    case ActionType::NEW_ORDER_REQUEST:
        newOrderReceived(action);
        break;
    }

    delete action;
}

void MainWindow::showErrorMsgBox(QString msg) {
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}

void MainWindow::establishConnectionReply(Action *action) {
    ui->conectarServidor->setEnabled(true);

    if (action->getRequestSuccess()) {
        ui->actualizarEstado->setEnabled(true);
        ui->nombreTecnico->setText(action->getNombreCliente());

        m_serverConnection->sendMessage(Action::askListaOrdenes());
    } else {
        showErrorMsgBox("Error al identificarse al servidor");
    }
}

void MainWindow::fillListaOrdenes(Action *action) {
    ui->ordersTable->clearContents();

    if (action->getRequestSuccess()) {
        auto ordenes = action->getListaOrdenes();
        ui->ordersTable->setRowCount(ordenes.count());
        int idx = 0;
        for (auto orden : ordenes) {
            ui->ordersTable->setItem(idx, 0, new QTableWidgetItem(QString::number(orden.first)));
            ui->ordersTable->setItem(idx, 1, new QTableWidgetItem(orden.second));
            idx++;
        }

        m_serverConnection->sendMessage(Action::askListaStatus());
    } else {
        showErrorMsgBox("Error al recibir la lista de órdenes,");
    }
}

void MainWindow::fillStatusCmBox(Action *action) {
    ui->estadosCmBox->clear();

    for (auto status : action->getListaStatus()) {
        ui->estadosCmBox->addItem(status.second, status.first);
    }
}

void MainWindow::newOrderReceived(Action *action) {
    int numRows = ui->ordersTable->rowCount();
    auto newOrder = action->getNewOrderRequest();

    ui->ordersTable->setRowCount(numRows + 1);
    ui->ordersTable->setItem(numRows, 0, new QTableWidgetItem(QString::number(newOrder.first)));
    ui->ordersTable->setItem(numRows, 1, new QTableWidgetItem(newOrder.second));

    showErrorMsgBox("Has recibido una nueva órden de trabajo");
}

void MainWindow::on_conectarServidor_clicked()
{
    ui->conectarServidor->setEnabled(false);

    QString user = ui->usuario->text();
    ui->usuario->setText("");
    QString password = ui->password->text();
    ui->password->setText("");

    if (!m_serverConnection->sendMessage(Action::establishConnection(user, password))) {
        ui->conectarServidor->setEnabled(true);
    }
}

void MainWindow::on_actualizarEstado_clicked()
{
    auto order = ui->ordersTable->selectedItems();
    if (!order.empty()) {
        QPair<int, QString> orderDetails;
        int tableRow = order.first()->row();

        orderDetails.first = ui->ordersTable->item(tableRow, 0)->text().toInt();
        orderDetails.second = ui->ordersTable->item(tableRow, 1)->text();

        if (ui->estadosCmBox->currentData().isValid()) {
            QPair<int, QString> statusDetails;
            statusDetails.first = ui->estadosCmBox->currentData().toInt();
            statusDetails.second = ui->estadosCmBox->currentText();

            if (statusDetails.second != orderDetails.second) {
                m_serverConnection->sendMessage(Action::changeOrderStatus(orderDetails.first, statusDetails.first));
            }
        }


    }
}
