#include "command.h"

#include <QColor>
#include <QPen>
#include <QBrush>

Command::Command(QPainter * p)
	:painter(p)
{
	commands.insert("move", 2);
	commands.insert("line", 2);
	commands.insert("cubic", 6);
	commands.insert("stroke", 4);
	commands.insert("fill", 3);
	commands.insert("close", 0);
	commands.insert("end", 0);
}

bool Command::checkVars(const QVariantList &vars)
{
	QString command(vars.first().toString());
	if(commands.contains(command)
			&& vars.count() - 1 == commands.value(command))
		return true;
	return false;
}

void Command::Draw(const QVariantList &vars)
{
	if(!checkVars(vars))
		return;
	QString command(vars.first().toString());

	QPointF curPos;
	if(command == QString("move"))
	{
		painterPath.moveTo(vars.at(1).toDouble(), vars.at(2).toDouble());
	}
	else if(command == QString("line"))
	{
		painterPath.lineTo(vars.at(1).toDouble(), vars.at(2).toDouble());
	}
	else if(command == QString("cubic"))
	{
		painterPath.cubicTo(vars.at(1).toDouble(), vars.at(2).toDouble(),
				    vars.at(3).toDouble(), vars.at(4).toDouble(),
				    vars.at(5).toDouble(), vars.at(6).toDouble());
	}
	else if(command == QString("fill"))
	{
		painter->drawPath(painterPath);
		curPos = painterPath.currentPosition();
		painterPath = QPainterPath();
		painterPath.moveTo(curPos);
		QColor c(vars.at(1).toInt(), vars.at(2).toInt(), vars.at(3).toInt());
		painter->setBrush(c);
	}
	else if(command == QString("stroke"))
	{
		painter->drawPath(painterPath);
		curPos = painterPath.currentPosition();
		painterPath = QPainterPath();
		painterPath.moveTo(curPos);
		QColor c(vars.at(1).toInt(), vars.at(2).toInt(), vars.at(3).toInt());
		double width(vars.at(4).toDouble());
		painter->setPen(QPen(QBrush(c), width));
	}
	else if(command == QString("end"))
	{
		painter->drawPath(painterPath);
	}
	else if(command == QString("close"))
	{
		painterPath.closeSubpath();
	}
}

