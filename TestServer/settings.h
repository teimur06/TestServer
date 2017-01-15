#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QSettings>

typedef struct StructSetting
{
    int PortSpinBox;
    QString ResponseTextBrowser;
    bool checkOutLengthInt32;
    bool checkOutNull;
    bool checkCloseAfterAnswer;
    bool StartServerButton;
    QString logFile;

} StructSetting;



class Settings
{
public:
    Settings();
    void loadSettings();
    void saveSettings(StructSetting * structSetting = NULL);
    StructSetting * getStructSetting();
    void setStructSetting(StructSetting * structSetting);
private:
   StructSetting  settings;
   const QString organization = "TestSerer";
   const QString application = "TestSerer";
};

#endif // SETTINGS_H
