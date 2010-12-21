#ifndef COMMAND_H
#define COMMAND_H

#include <QPainter>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QPainterPath>

class Command
{
	Command(){}
	QPainter * painter;
	QPainterPath painterPath;

	QMap<QString, int> commands;
	bool checkVars(const QVariantList& vars);
public:
	Command(QPainter * p);
	void setPP(QPainterPath& pp){painterPath = pp;}
	QPainterPath& PP(){return painterPath;}

	void Draw(const QVariantList& vars);
//	void GraphicState(const QVariantList& vars);
};

#endif // COMMAND_H
