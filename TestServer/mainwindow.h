#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QSettings>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDialog>

#include "Clog.h"
#include "dialogsettings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createMenu();
    void createAction();
private slots:

    void newuser();
    void slotReadClient();
    void slotDisconectClient();
    void on_StopServerButton_clicked();
    void on_StartServerButton_clicked();
    void on_ResponseTextBrowser_textChanged();
    void on_RequestTextBrowser_textChanged();
    void on_getLengthSelectedTextResponse_clicked();
    void slotSetting();

private:
    Ui::MainWindow *ui;
    Clog * clog;
    QTcpServer * tcpServer;
    int server_status;
    QMap<int,QTcpSocket *> SClients;
    int numClients;
    QMenu * mainMenu;
    QAction * actionSetting;
    DialogSettings * dialogSettings;

};

#endif // MAINWINDOW_H
