#include <QDebug>
#include <QTimer>
#include <QWebSocket>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverconnection.h"
#include "action.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setEnabled(false);

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

    case ActionType::MARCAS_INFO_REPLY:
        fillMarcasVector(InfoType::MARCA, action);
        break;

    case ActionType::MODELOS_INFO_REPLY:
        fillMarcasVector(InfoType::MODELO, action);
        break;

    case ActionType::REPARACION_INFO_REPLY:
        fillMarcasVector(InfoType::REPARACION, action);
        break;

    case ActionType::ORDEN_REQUEST_REPLY:
        addNewOrden(action);
        break;

    case ActionType::ORDEN_STATUS_CHANGED:
        updateOrderStatus(action);
        break;

    }

    delete action;
}

/*void MainWindow::replyReceived(QString message) {
    switchCentralWidgetEnabled(); // Desbloqueamos el programa
    Action *action = new Action(&message);
    QMessageBox msgBox;

    switch (action->getActionType()) {
    case ActionType::ERROR:
        msgBox.setText(action->getElementText("message"));
        msgBox.exec();
        break;

    case ActionType::ESTABLISH_CONNECTION:
        switchCentralWidgetEnabled(); // Bloqueamos el programa hasta recibir las marcas
        m_serverConnection->sendMessage(Action::askMarcasInfo());

        msgBox.setText(action->getElementText("tienda"));
        msgBox.exec();
        break;

    case ActionType::LISTA_ORDENES_REPLY:
        break;

    case ActionType::MARCAS_INFO_REPLY:
        fillMarcasCmbBox(action->getMarcasInfo());
        break;

    case ActionType::MODELOS_INFO_REPLY:
        fillModelosCmbBox(action->getModelosInfo());
        break;

    case ActionType::REPARACION_INFO_REPLY:
        fillReparacionesPosiblesList(action->getReparacionesInfo());
        break;

    case ActionType::ORDEN_REQUEST_REPLY:
        msgBox.setText(QString("El código de tu pedido es: ") + action->getElementText("orden_id"));
        msgBox.exec();
        break;

    case ActionType::ORDEN_STATUS_REPLY:
        msgBox.setText(QString("Estado del pedido: " + action->getElementText("respuesta")));
        msgBox.exec();
        break;
    }

    delete action;
}*/

void MainWindow::showErrorMsgBox(QString msg) {
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}

void MainWindow::establishConnectionReply(Action *action) {
    ui->conectarServidor->setEnabled(true);

    if (action->getRequestSuccess()) {
        ui->nombreTienda->setText(action->getNombreCliente());

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

        m_serverConnection->sendMessage(Action::askMarcasInfo());
    } else {
        showErrorMsgBox("Error al recibir la lista de órdenes,");
    }
}

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
}

void MainWindow::updateOrderStatus(Action *action) {
    auto order = action->getOrderNewStatus();

    for (int i = 0; i < ui->ordersTable->rowCount(); i++) {
        if (ui->ordersTable->item(i, 0)->text().toInt() == order.first) {
            ui->ordersTable->setItem(i, 1, new QTableWidgetItem(order.second));
            showErrorMsgBox(QString("El pedido %1 se ha actualizado").arg(QString::number(order.first)));
            break;
        }
    }
}
/*
void MainWindow::switchCentralWidgetEnabled() {
    static bool isEnabled = true;
    if (m_serverConnection->m_webSocket->isValid()) {
        isEnabled = !isEnabled;
        ui->centralWidget->setEnabled(isEnabled);
    }
}

void MainWindow::fillMarcasCmbBox(QVector<QPair<QString, int> > marcas) {
    ui->marcasCmbBox->clear();
    for (auto marca : marcas) {
        ui->marcasCmbBox->addItem(marca.first, marca.second);
    }
}

void MainWindow::fillModelosCmbBox(QVector<QPair<QString, int> > modelos) {
    ui->modelosCmbBox->clear();
    for (auto modelo : modelos) {
        ui->modelosCmbBox->addItem(modelo.first, modelo.second);
    }
}

void MainWindow::fillReparacionesPosiblesList(QVector<QPair<QString, int> > reparaciones) {
    clearLists();
    for (auto reparacion : reparaciones) {
        QListWidgetItem *listItem = new QListWidgetItem(reparacion.first);
        listItem->setData(0x0100, reparacion.second);
        ui->reparacionesPosibles->addItem(listItem);
    }
}

void MainWindow::clearLists() {
    ui->reparacionesPosibles->clear();
    ui->reparacionesElegidas->clear();
}

void MainWindow::resetLists() {
    for (int i = ui->reparacionesElegidas->count()-1; i >= 0; i--) {
        ui->reparacionesPosibles->addItem(ui->reparacionesElegidas->takeItem(i));
    }
}

void MainWindow::on_conectarServidor_clicked()
{
    QString nombreTienda = ui->nombreTienda->text();
    m_serverConnection->sendMessage(Action::establishConnection(nombreTienda));
    switchCentralWidgetEnabled();
}

void MainWindow::on_marcasCmbBox_currentIndexChanged(int index)
{
    int marcaId = ui->marcasCmbBox->itemData(index).toInt();
    m_serverConnection->sendMessage(Action::askModelosInfo(marcaId));
    switchCentralWidgetEnabled();
}

void MainWindow::on_modelosCmbBox_currentIndexChanged(int index)
{
    int modeloId = ui->modelosCmbBox->itemData(index).toInt();
    m_serverConnection->sendMessage(Action::askReparacionInfo(modeloId));
    switchCentralWidgetEnabled();
}

void MainWindow::on_ordenRequest_clicked()
{
    int modeloId = ui->modelosCmbBox->itemData(ui->modelosCmbBox->currentIndex()).toInt();
    QVector<int> reparacionesId;
    int numReparaciones = ui->reparacionesElegidas->count();
    if (numReparaciones == 0) {
        QMessageBox msgBox;
        msgBox.setText("No has elegido ninguna reparación");
        msgBox.exec();
    } else {
        for (int i = 0; i < numReparaciones; i++) {
            reparacionesId.push_back(ui->reparacionesElegidas->item(i)->data(0x0100).toInt());
        }
        m_serverConnection->sendMessage(Action::askOrdenRequest(modeloId, &reparacionesId));
        resetLists();
        switchCentralWidgetEnabled();
    }
}

void MainWindow::on_ordenEstado_clicked()
{
    QString ordenId = ui->numOrden->text();
    ui->numOrden->setText("");
    m_serverConnection->sendMessage(Action::askOrdenStatus(ordenId));
    switchCentralWidgetEnabled();
}

void MainWindow::on_reparacionesPosibles_itemDoubleClicked(QListWidgetItem *item)
{
    ui->reparacionesElegidas->addItem(ui->reparacionesPosibles->takeItem(ui->reparacionesPosibles->row(item)));
}

void MainWindow::on_reparacionesElegidas_itemDoubleClicked(QListWidgetItem *item)
{
    ui->reparacionesPosibles->addItem(ui->reparacionesElegidas->takeItem(ui->reparacionesElegidas->row(item)));
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
        ui->hacerPedido->setEnabled(true);
    } else {
        for (int i = 0; i < numReparaciones; i++) {
            reparacionesId.push_back(ui->reparacionesElegidas->item(i)->data(QListWidgetItem::UserType).toInt());
        }
        m_serverConnection->sendMessage(Action::askOrdenRequest(modeloId, reparacionesId));
        fillReparacionesPosiblesList(m_marcas[marcaIdx].modelos[modeloIdx].reparaciones);
    }
}
