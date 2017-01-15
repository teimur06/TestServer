#include "settings.h"



Settings::Settings()
{
    loadSettings();
}


void Settings::loadSettings()
{
    QSettings qSettings(organization, application);
    settings.PortSpinBox = qSettings.value("PortSpinBox",1313).toInt();
    settings.ResponseTextBrowser = qSettings.value("ResponseTextBrowser","Hi").toString();
    settings.checkOutLengthInt32 = qSettings.value("checkOutLengthInt32",false).toBool();
    settings.checkOutNull = qSettings.value("checkOutNull",false).toBool();
    settings.checkCloseAfterAnswer = qSettings.value("checkCloseAfterAnswer",false).toBool();
    settings.StartServerButton = qSettings.value("StartServerButton",false).toBool();
    settings.logFile = qSettings.value("logFile","%temp%\\TestServer.log").toString();
}


void Settings::saveSettings(StructSetting * structSetting)
{
    if (!structSetting)
        structSetting = &this->settings;
    else
        setStructSetting(structSetting);

    QSettings qSettings(organization, application);
    qSettings.setValue("PortSpinBox",structSetting->PortSpinBox);
    qSettings.setValue("ResponseTextBrowser",structSetting->ResponseTextBrowser);
    qSettings.setValue("checkOutLengthInt32",structSetting->checkOutLengthInt32);
    qSettings.setValue("checkOutNull",structSetting->checkOutNull);
    qSettings.setValue("checkCloseAfterAnswer",structSetting->checkCloseAfterAnswer);
    qSettings.setValue("StartServerButton",structSetting->StartServerButton);
    qSettings.setValue("logFile",structSetting->logFile);
}


StructSetting * Settings::getStructSetting()
{
    return &this->settings;
}


void Settings::setStructSetting(StructSetting * structSetting)
{
    this->settings.checkCloseAfterAnswer = structSetting->checkCloseAfterAnswer;
    this->settings.checkOutLengthInt32 = structSetting->checkOutLengthInt32;
    this->settings.checkOutNull = structSetting->checkOutNull;
    this->settings.PortSpinBox = structSetting->PortSpinBox;
    this->settings.ResponseTextBrowser = structSetting->ResponseTextBrowser;
    this->settings.StartServerButton = structSetting->StartServerButton;
    this->settings.logFile = structSetting->logFile;
}
