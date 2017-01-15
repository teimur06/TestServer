#include "Clog.h"


    Clog::Clog()
    {

    };


    Clog::Clog(QString module, QString pathLog, int level)
	{
        init(module, pathLog, level);
	}


    Clog::~Clog()
	{
		fout.close(); // закрываем файл
	}


    bool Clog::init(QString module, QString pathLog, int level)
    {
        QString fileLog = pathLog;
        if (fileLog.isEmpty()) fileLog = "%temp%/TestServer.log";
        fileLog = fileLog.replace("%temp%",QDir::tempPath());
        fileLog = fileLog.replace("%programmdir%",QApplication::applicationDirPath());
        fout.setFileName(fileLog);
        this->module = module;
        level > 10 ? this->level = 10 : this->level = level;
        level <  1 ? this->level = 1 : this->level = level;
        return fout.open(QIODevice::Append | QIODevice::Text);
    }

    bool Clog::isOpenLog()
    {
        return fout.isOpen();
    }

    void Clog::writeLn(QString text)
	{
        if (!fout.isOpen()) return;
        QTextStream out(&fout);
		
        out << QDateTime::currentDateTime().date().day() << '.' << QDateTime::currentDateTime().date().month() << '.' << QDateTime::currentDateTime().date().year() << ' ' \
            << QDateTime::currentDateTime().time().hour() << ':' << QDateTime::currentDateTime().time().minute() << ':' << QDateTime::currentDateTime().time().second() << ' ' \
			 <<	module << " > " << text << '\n';
        out.flush();

	}


    QString Clog::getErrorString()
    {
        return fout.errorString();
    }

    void Clog::writeLn(QString text, int level)
	{
         if (!fout.isOpen()) return;
		if (level <= this->level)
			this->writeLn(text);
	}


	void Clog::setLevel(int level)
	{
		level > 10 ? this->level = 10 : this->level = level;
		level <  1 ? this->level = 1 : this->level = level;
	}

	int Clog::getLevel()
	{
		return this->level;
	}

    void Clog::operator << (QString text)
	{
		this->writeLn(text);
	}
