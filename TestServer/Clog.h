#ifndef CLOG_H
#define CLOG_H

#include <QString>
#include <QFile>
#include <QDateTime>
#include <QTextStream>

// Класс лога
class Clog
{
private:
    QFile fout;
    QString module;
	int level;
public:
	// Конструктор открывает файл лога
    Clog(QString module, QString pathLog, int level = 10);
	// Деструктор закрывает файл лога
	~Clog();
	// Функция добовляет текст в лог
    void writeLn(QString text);
    void writeLn(QString text, int level);
	// Устанавливает, возвращает уровень вывода лога
	void setLevel(int level);
	int getLevel();
    void operator << (QString text);
};

#endif // CLOG_H
