#include "dialogsettings.h"
#include "ui_dialogsettings.h"

DialogSettings::DialogSettings(Settings * settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings),
    settings(NULL)
{
    ui->setupUi(this);
    this->settings = settings;
    connect(ui->buttonBox, SIGNAL(accepted()),this,SLOT(on_accept()));
    ui->lineEdit->setText(settings->getStructSetting()->logFile);

}

DialogSettings::~DialogSettings()
{
    delete ui;
}


void DialogSettings::on_accept()
{
    StructSetting * structSetting = settings->getStructSetting();
    structSetting->logFile = ui->lineEdit->text();
    settings->saveSettings(structSetting);
}

void DialogSettings::on_pushButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getSaveFileName(this,"Log File",QApplication::applicationDirPath(),"*.log"));
}
