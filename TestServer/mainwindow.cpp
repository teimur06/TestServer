#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    clog(NULL),
    tcpServer(NULL),
    server_status(0),
    numClients(0),
    dialogSettings(NULL)
{

    QSettings s("TestSerer", "TestSerer");

    ui->setupUi(this);
    createAction();
    createMenu();

    try {
        clog = new Clog(QApplication::applicationName(),QApplication::applicationDirPath()+"\\TestServer.log",10);
    } catch (int) {
      QMessageBox::about(this,"Ошибка создания лога","clog = new Clog ошибка");
    }
    *clog << "Поехали";

    connect(ui->StartServerButton,SIGNAL(clicked()),this,SLOT(on_StartServerButton_clicked()));
    connect(ui->StopServerButton,SIGNAL(clicked()),this,SLOT(on_StopServerButton_clicked()));
    connect(ui->ResponseTextBrowser,SIGNAL(textChanged()),this,SLOT(on_ResponseTextBrowser_textChanged()));
    connect(ui->RequestTextBrowser,SIGNAL(textChanged()),this,SLOT(on_RequestTextBrowser_textChanged()));

    connect(ui->getLengthSelectedTextResponse,SIGNAL(clicked()),this,SLOT(on_getLengthSelectedTextResponse_clicked()));

    ui->PortSpinBox->setValue(s.value("PortSpinBox",5522).toInt());
    ui->ResponseTextBrowser->setText(s.value("ResponseTextBrowser","Hi").toString());
    ui->checkOutLengthInt32->setChecked(s.value("checkOutLengthInt32",false).toBool());
    ui->checkOutNull->setChecked(s.value("checkOutNull",false).toBool());
    ui->checkCloseAfterAnswer->setChecked(s.value("checkCloseAfterAnswer",false).toBool());
    bool bStartServerButtonIsEnable = s.value("StartServerButton",false).toBool();
    if (!bStartServerButtonIsEnable)
    {
        on_StartServerButton_clicked();
    }
}

void MainWindow::createMenu()
{
    mainMenu = this->menuBar()->addMenu(tr("&Tools"));
    mainMenu->addAction(actionSetting);

}

void MainWindow::createAction()
{
   actionSetting = new QAction(tr("&Setting"),this);
   actionSetting->setShortcut(QKeySequence::Preferences);
   connect(actionSetting,&QAction::triggered, this, &MainWindow::slotSetting);

}


void MainWindow::slotSetting()
{
    dialogSettings = new DialogSettings(this);
    if(dialogSettings->exec() == QDialog::Accepted)
    {
        QMessageBox::information(this, "dialogSettings", "QDialog::accept()");
    }
    if (dialogSettings != NULL) delete dialogSettings;



}


MainWindow::~MainWindow()
{
    QSettings s("TestSerer", "TestSerer");
    s.setValue("PortSpinBox",ui->PortSpinBox->value());
    s.setValue("ResponseTextBrowser",ui->ResponseTextBrowser->toPlainText());
    s.setValue("checkOutLengthInt32",ui->checkOutLengthInt32->isChecked());
    s.setValue("checkOutNull",ui->checkOutNull->isChecked());
    s.setValue("checkCloseAfterAnswer",ui->checkCloseAfterAnswer->isChecked());
    s.setValue("StartServerButton",ui->StartServerButton->isEnabled());

    if (tcpServer)
    {
        on_StopServerButton_clicked();
    }
    if (clog)
    {
        *clog << "Завершения работы";
        delete clog;
    }

    delete ui;
}




void MainWindow::newuser()
{
    if(server_status==1){
        QTcpSocket* clientSocket=tcpServer->nextPendingConnection();
        int idusersocs=clientSocket->socketDescriptor();
        *clog << "Новый клиент ip: " + clientSocket->peerAddress().toString();
        SClients[idusersocs]=clientSocket;
        connect(SClients[idusersocs],SIGNAL(readyRead()),this, SLOT(slotReadClient()));
        connect(SClients[idusersocs],SIGNAL(disconnected()),this, SLOT(slotDisconectClient()));
        numClients++;
        ui->ClientNumlabel->setText(QString::number(numClients));
    }
}

void MainWindow::slotDisconectClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    numClients--;
    ui->ClientNumlabel->setText(QString::number(numClients));
    SClients.remove(clientSocket->socketDescriptor());
}

void MainWindow::slotReadClient()
{
    // Получаем объект сокета, который вызвал данный слот
       QTcpSocket* clientSocket = (QTcpSocket*)sender();
       // Получаем дескриптор, для того, чтоб в случае закрытия сокета удалить его из карты
       ui->RequestTextBrowser->setPlainText(clientSocket->readAll());
       *clog << "Клиент " +clientSocket->peerAddress().toString() + " прислал данные";
       ui->RequestGroupBox->setTitle("Пришол запрос от: "+clientSocket->peerAddress().toString());
       // Пример отправки ответа клиенту
       QTextStream os(clientSocket);
       QDataStream ds(clientSocket);
       os.setAutoDetectUnicode(true);
       os.setCodec("UTF-8");
       // Если установлена галочка, то отправляем колличества символов
       if (ui->checkOutLengthInt32->isChecked())
       {
          ds << quint32(ui->ResponseTextBrowser->document()->toPlainText().length());

       }
       os << ui->ResponseTextBrowser->document()->toPlainText();
       os.flush();
       if (ui->checkOutNull->isChecked())
       {
           ds << qint8(0);
       }

       if (ui->checkCloseAfterAnswer->isChecked())
       {
           clientSocket->close();
           SClients.remove(clientSocket->socketDescriptor());
       }


}


void MainWindow::on_StopServerButton_clicked()
{
    ui->StopServerButton->setEnabled(false);
    if(server_status==1){
         foreach(int i,SClients.keys()){
             SClients[i]->close();
             SClients.remove(i);
         }
         tcpServer->close();
         *clog << "Сервер остановлен!";
         server_status=0;
         delete tcpServer;
         tcpServer = NULL;
         ui->StartServerButton->setEnabled(true);
         ui->StopServerButton->setEnabled(false);
     }
}

void MainWindow::on_StartServerButton_clicked()
{
        if(server_status==0){
           tcpServer = new QTcpServer(this);
            connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
            if (!tcpServer->listen(QHostAddress::Any, ui->PortSpinBox->value()) && server_status==0) {
                *clog << "Сервер не запущен: " + tcpServer->errorString();

            } else {
                server_status=1;
                ui->StartServerButton->setEnabled(false);
                ui->StopServerButton->setEnabled(true);
                *clog << "Сервер запущен!";
            }
        }
}

void MainWindow::on_ResponseTextBrowser_textChanged()
{
    QString str = ui->ResponseTextBrowser->toPlainText();
    int lengthTextResponse = str.length();
    ui->plainTextEditLengthResponse->setPlainText(QString::number(lengthTextResponse));
}



void MainWindow::on_RequestTextBrowser_textChanged()
{
    int lengthTextRequest = ui->RequestTextBrowser->toPlainText().length();
    ui->plainTextEditLengthRequest->setPlainText(QString::number(lengthTextRequest));
}



void MainWindow::on_getLengthSelectedTextResponse_clicked()
{
    QString selectedText = ui->ResponseTextBrowser->textCursor().selectedText();
    int length = selectedText.length();
    QMessageBox::about(this,"Количество символов в выделенном тексте: ",QString::number(length));
}
