#include "Clog.h"



Clog::Clog(QString module, QString pathLog, int level)
	{
        fout.setFileName(pathLog);
        fout.open(QIODevice::Append | QIODevice::Text);
		this->module = module;
		level > 10 ? this->level = 10 : this->level = level;
		level <  1 ? this->level = 1 : this->level = level;
        if (!fout.isOpen()) throw - 2;
		
	}

	Clog::~Clog()
	{
		fout.close(); // закрываем файл
	}


    void Clog::writeLn(QString text)
	{
        QTextStream out(&fout);
		
        out << QDateTime::currentDateTime().date().day() << '.' << QDateTime::currentDateTime().date().month() << '.' << QDateTime::currentDateTime().date().year() << ' ' \
            << QDateTime::currentDateTime().time().hour() << ':' << QDateTime::currentDateTime().time().minute() << ':' << QDateTime::currentDateTime().time().second() << ' ' \
			 <<	module << " > " << text << '\n';
        out.flush();

	}


    void Clog::writeLn(QString text, int level)
	{
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
