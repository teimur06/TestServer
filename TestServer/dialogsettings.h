#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include "settings.h"

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(Settings * settings, QWidget *parent = 0);
    ~DialogSettings();

private slots:
    void on_accept();

    void on_pushButton_clicked();

private:
    Ui::DialogSettings *ui;
    Settings * settings;
};

#endif // DIALOGSETTINGS_H
