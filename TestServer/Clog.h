#ifndef CLOG_H
#define CLOG_H

#include <QString>
#include <QFile>
#include <QDateTime>
#include <QTextStream>

// ����� ����
class Clog
{
private:
    QFile fout;
    QString module;
	int level;
public:
	// ����������� ��������� ���� ����
    Clog(QString module, QString pathLog, int level = 10);
	// ���������� ��������� ���� ����
	~Clog();
	// ������� ��������� ����� � ���
    void writeLn(QString text);
    void writeLn(QString text, int level);
	// �������������, ���������� ������� ������ ����
	void setLevel(int level);
	int getLevel();
    void operator << (QString text);
};

#endif // CLOG_H
