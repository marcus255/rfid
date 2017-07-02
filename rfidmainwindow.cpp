#include "rfidmainwindow.h"
#include "ui_rfidmainwindow.h"
#include "adduserdialog.h"
#include "qserialport.h"

#include <QMessageBox>


RfidMainWindow::RfidMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RfidMainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    serialPortName = ui->lineEdit_portName->text();

    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
                this, &RfidMainWindow::handleError);
    connect(serial, &QSerialPort::readyRead, this, &RfidMainWindow::readData);
}

RfidMainWindow::~RfidMainWindow()
{
    closeSerialPort();
    delete ui;
}

void RfidMainWindow::on_pushButtonAddUser_clicked()
{
    writeData(QByteArray("CMDadduser"));
    AddUserDialog adduserdialog;
    adduserdialog.setModal(true);
    adduserdialog.exec();
}

void RfidMainWindow::openSerialPort()
{
    serial->setPortName(serialPortName);
    serial->setBaudRate(serialBaudrate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        /*console->setEnabled(true);
        console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);*/
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(serial->portName()).arg(serial->baudRate()).arg(serial->dataBits())
                          .arg(serial->parity()).arg(serial->stopBits()).arg(serial->flowControl()));
        QMessageBox::information(this, "Connecting status", "Successfully connected");
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        showStatusMessage(tr("Open error"));
    }
}

void RfidMainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    /*console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);*/
    showStatusMessage(tr("Disconnected"));
}

void RfidMainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}

void RfidMainWindow::readData()
{
    QByteArray data = serial->readAll();
    //console->putData(data);
}

void RfidMainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void RfidMainWindow::showStatusMessage(const QString &message)
{
    //status->setText(message);
    printf(message.toStdString().c_str());
}

void RfidMainWindow::on_pushButtonSerialConnect_clicked()
{
    openSerialPort();
}

void RfidMainWindow::on_pushButtonDisconnectSerial_clicked()
{
    closeSerialPort();
}

void RfidMainWindow::on_lineEdit_portName_editingFinished()
{
    serialPortName = ui->lineEdit_portName->text();
}

void RfidMainWindow::on_lineEdit_baudRate_editingFinished()
{
    serialBaudrate = QSerialPort::BaudRate(ui->lineEdit_baudRate->text().toInt());
}
