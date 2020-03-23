#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    port = new QSerialPort();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPort(QString portName)
{
    port->setPortName(portName);
    port->setBaudRate(QSerialPort::Baud115200);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
}

QString MainWindow::TCHARToQString(const TCHAR *ptsz)
{
    int len = wcslen((wchar_t*)ptsz);
    char* psz = new char[2 * len + 1];
    wcstombs(psz, (wchar_t*)ptsz, 2 * len + 1);
    QString s = psz;

    delete[] psz;

    return s;
}

void MainWindow::displayChangeBnW()
{
    QString buf = port->read(1);

    if (buf == 0x10) {
        ui->lbDisplay->setStyleSheet("QLabel {background-color: rgb(255, 255, 255);}");
        QTimer::singleShot(200, this, [&]() {
            ui->lbDisplay->setStyleSheet("QLabel {background-color: rgb(0, 0, 0);}");
        });
    }
}

void MainWindow::on_btnTestStart_toggled(bool checked)
{
    if (checked) {
        connect(port, SIGNAL(readyRead()), this, SLOT(displayChangeBnW()));
        ui->btnTestStart->setText("Testing...");
    }
    else {
        disconnect(port, SIGNAL(readyRead()), this, SLOT(displayChangeBnW()));
        ui->btnTestStart->setText("Test start");
        ui->lbDisplay->setStyleSheet("QLabel {background-color: rgb(0, 0, 0);}");
    }
}

void MainWindow::on_btnConnect_toggled(bool checked)
{
    if(checked) {
            setPort(ui->cbPortName->currentText());
            if(!port->open(QIODevice::ReadWrite)) {
                QMessageBox::information(this, "Error", "Cannot connect!", "OK");
                ui->btnConnect->setChecked(false);
                ui->btnConnect->setText("Connect");
            }
            else {
                ui->btnConnect->setText("Clear");
                ui->cbPortName->setEnabled(false);
                ui->btnPortScan->setEnabled(false);
            }
        }
        else {
            port->close();
            ui->btnConnect->setText("Connect");
            ui->cbPortName->setEnabled(true);
            ui->btnPortScan->setEnabled(true);
        }
}

void MainWindow::on_btnPortScan_clicked()
{
    ui->cbPortName->clear();

    HKEY hKey;
    RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &hKey);

    TCHAR szData[20], szName[100];
    DWORD index = 0, dwSize = 100, dwSize2 = 20, dwType = REG_SZ;
    memset(szData, 0x00, sizeof(szData));
    memset(szName, 0x00, sizeof(szName));

    while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL)) {
        index++;

        RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
        QString tem = TCHARToQString(szData);
        ui->cbPortName->addItem(tem);

        memset(szData, 0x00, sizeof(szData));
        memset(szName, 0x00, sizeof(szName));
        dwSize = 100;
        dwSize2 = 20;
    }

    RegCloseKey(hKey);
}
