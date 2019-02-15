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
    ui->actualizarEstado->setEnabled(true);

    if (action->getRequestSuccess()) {
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
        ui->estadosCmBox->addItem(status.first, status.second);
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
/*
void MainWindow::fillMarcasVector(InfoType infoType, Action *action) {
    if (!action->getRequestSuccess()) {
        showErrorMsgBox("Error al recibir la información de marcas/modelos/reparaciones");
        return;
    }

    static int marcaIndex = 0;
    static int numMarcas = 0;
    static int modeloIndex = 0;
    static int numModelos = 0;

    switch (infoType) {
    case InfoType::MARCA:
        for (auto marcaXml : action->getMarcasInfo()) {
            Marca marca{};
            marca.id = marcaXml.first;
            marca.nombre = marcaXml.second;

            m_marcas.push_back(marca);
        }

        numMarcas = m_marcas.count();
        if (numMarcas > 0) {
            m_serverConnection->sendMessage(Action::askModelosInfo(m_marcas[0].id));
        } else {
            fillMarcasCmBox();
        }
        break;

    case InfoType::MODELO:
        for (auto modeloXml : action->getModelosInfo()) {
            Modelo modelo{};
            modelo.id = modeloXml.first;
            modelo.nombre = modeloXml.second;

            m_marcas[marcaIndex].modelos.push_back(modelo);
        }

        numModelos = m_marcas[marcaIndex].modelos.count();
        if (numModelos > 0) {
            m_serverConnection->sendMessage(Action::askReparacionInfo(m_marcas[marcaIndex].modelos[0].id));
        } else {
            modeloIndex = 0;
            marcaIndex++;
            if (marcaIndex < numMarcas) {
                m_serverConnection->sendMessage(Action::askModelosInfo(m_marcas[marcaIndex].id));
            } else {
                fillMarcasCmBox();
            }
        }
        break;

    case InfoType::REPARACION:
        for (auto reparacionXml : action->getReparacionesInfo()) {
            Reparacion reparacion{reparacionXml.first, reparacionXml.second};
            m_marcas[marcaIndex].modelos[modeloIndex].reparaciones.push_back(reparacion);
        }

        modeloIndex++;
        if (modeloIndex < numModelos) {
            m_serverConnection->sendMessage(Action::askReparacionInfo(m_marcas[marcaIndex].modelos[modeloIndex].id));
        } else {
            modeloIndex = 0; numModelos = 0;
            marcaIndex++;
            if (marcaIndex < numMarcas) {
                m_serverConnection->sendMessage(Action::askModelosInfo(m_marcas[marcaIndex].id));
            } else {
                fillMarcasCmBox();
            }
        }
        break;
    }
}

void MainWindow::fillMarcasCmBox() {
    ui->marcasCmBox->clear();

    for (int idx = 0; idx < m_marcas.count(); idx++) {
        ui->marcasCmBox->addItem(m_marcas[idx].nombre, idx);
    }

    ui->tabWidget->setEnabled(true);
}

void MainWindow::fillModelosCmBox(QVector<Modelo> &modelos) {
    ui->modelosCmBox->clear();

    for (int idx = 0; idx < modelos.count(); idx++) {
        ui->modelosCmBox->addItem(modelos[idx].nombre, idx);
    }
}

void MainWindow::clearReparacionesLists() {
    ui->reparacionesElegidas->clear();
    ui->reparacionesPosibles->clear();
}

void MainWindow::fillReparacionesPosiblesList(QVector<Reparacion> &reparaciones) {
    clearReparacionesLists();

    for (auto reparacion : reparaciones) {
        QListWidgetItem *listItem = new QListWidgetItem(reparacion.nombre);
        listItem->setData(QListWidgetItem::UserType, reparacion.id);
        ui->reparacionesPosibles->addItem(listItem);
    }
}

void MainWindow::addNewOrden(Action *action) {
    ui->hacerPedido->setEnabled(true);

    if (!action->getRequestSuccess()) {
        showErrorMsgBox("Tu pedido no se ha podido realizar");
    } else {
        auto orden = action->getOrdenRequestInfo();

        int numRows = ui->ordersTable->rowCount();
        ui->ordersTable->setRowCount(numRows+1);

        ui->ordersTable->setItem(numRows, 0, new QTableWidgetItem(QString::number(orden.first)));
        ui->ordersTable->setItem(numRows, 1, new QTableWidgetItem(orden.second));

        showErrorMsgBox("El id de tu nuevo pedido es: " + QString::number(orden.first));
    }
}*/

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
/*
void MainWindow::on_marcasCmBox_currentIndexChanged(int index)
{
    int idx = ui->marcasCmBox->itemData(index).toInt();
    fillModelosCmBox(m_marcas[idx].modelos);
}

void MainWindow::on_modelosCmBox_currentIndexChanged(int index)
{
    int marcaIdx = ui->marcasCmBox->itemData(ui->marcasCmBox->currentIndex()).toInt();
    if (m_marcas[marcaIdx].modelos.count()) {
        int modeloIdx = ui->modelosCmBox->itemData(index).toInt();
        fillReparacionesPosiblesList(m_marcas[marcaIdx].modelos[modeloIdx].reparaciones);
    } else {
        clearReparacionesLists();
    }
}

void MainWindow::on_reparacionesPosibles_itemDoubleClicked(QListWidgetItem *item)
{
    ui->reparacionesElegidas->addItem(ui->reparacionesPosibles->takeItem(ui->reparacionesPosibles->row(item)));
}

void MainWindow::on_reparacionesElegidas_itemDoubleClicked(QListWidgetItem *item)
{
    ui->reparacionesPosibles->addItem(ui->reparacionesElegidas->takeItem(ui->reparacionesElegidas->row(item)));
}

void MainWindow::on_hacerPedido_clicked()
{
    if (!ui->modelosCmBox->count()) {
        showErrorMsgBox("No hay modelos");
        return;
    }

    ui->hacerPedido->setEnabled(false);

    int marcaIdx = ui->marcasCmBox->itemData(ui->marcasCmBox->currentIndex()).toInt();
    int modeloIdx = ui->modelosCmBox->itemData(ui->modelosCmBox->currentIndex()).toInt();
    int modeloId = m_marcas[marcaIdx].modelos[modeloIdx].id;
    QVector<int> reparacionesId;
    int numReparaciones = ui->reparacionesElegidas->count();
    if (numReparaciones == 0) {
        showErrorMsgBox("No has elegido ninguna reparación");
    } else {
        for (int i = 0; i < numReparaciones; i++) {
            reparacionesId.push_back(ui->reparacionesElegidas->item(i)->data(QListWidgetItem::UserType).toInt());
        }
        m_serverConnection->sendMessage(Action::askOrdenRequest(modeloId, reparacionesId));
        fillReparacionesPosiblesList(m_marcas[marcaIdx].modelos[modeloIdx].reparaciones);
    }
}
*/

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
            statusDetails.first = ui->estadosCmBox->currentData();
            statusDetails.second = ui->estadosCmBox->currentText();

            if (statusDetails.second != orderDetails.second) {
                m_serverConnection->sendMessage(Action::changeOrderStatus(orderDetails.first, statusDetails.first));
            }
        }


    }
}
