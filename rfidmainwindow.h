#ifndef RFIDMAINWINDOW_H
#define RFIDMAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtCore/QtGlobal>

namespace Ui {
class RfidMainWindow;
}

class RfidMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RfidMainWindow(QWidget *parent = 0);
    ~RfidMainWindow();

private slots:
    void on_pushButtonAddUser_clicked();
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();
    void handleError(QSerialPort::SerialPortError error);

    void on_pushButtonSerialConnect_clicked();

    void on_pushButtonDisconnectSerial_clicked();

    void on_lineEdit_portName_editingFinished();

    void on_lineEdit_baudRate_editingFinished();

private:
    void showStatusMessage(const QString &message);

    Ui::RfidMainWindow *ui;
    QSerialPort *serial;
    QString serialPortName = "";
    QSerialPort::BaudRate serialBaudrate = QSerialPort::Baud9600;
};

#endif // RFIDMAINWINDOW_H
