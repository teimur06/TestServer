#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QSettings>
#include "Clog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void newuser();
    void slotReadClient();
    void slotDisconectClient();
    void on_StopServerButton_clicked();

    void on_StartServerButton_clicked();

    void on_ResponseTextBrowser_textChanged();



    void on_RequestTextBrowser_textChanged();



    void on_getLengthSelectedTextResponse_clicked();

private:
    Ui::MainWindow *ui;
    Clog * clog;
    QTcpServer * tcpServer;
    int server_status;
    QMap<int,QTcpSocket *> SClients;
    int numClients;
};

#endif // MAINWINDOW_H
