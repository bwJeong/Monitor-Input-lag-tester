#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QTimer>
#include "windows.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setPort(QString portName);
    QString TCHARToQString(const TCHAR* ptsz);

    QSerialPort *port;

private slots:
    void displayChangeBnW();

    void on_btnTestStart_toggled(bool checked);

    void on_btnConnect_toggled(bool checked);

    void on_btnPortScan_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
