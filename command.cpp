#include "command.h"

#include <QColor>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QFont>

Command * Command::instance = 0;
Command::Command():
	QObject(0)
{
	commands.insert("move", 2);
	commands.insert("line", 2);
	commands.insert("cubic", 6);
	commands.insert("stroke", 4);
	commands.insert("fill", 3);
	commands.insert("close", 0);
	commands.insert("end", 0);
	commands.insert("transform", 6);
	commands.insert("change", 2);
	commands.insert("font", 4);
	commands.insert("text", 1);
	commands.insert("image", 1);

	foreach(QString c, commands.keys())
		alias.insert(c,c);
}

Command * Command::getInstance()
{
	if(!instance)
		instance = new Command;
	return instance;
}

QString Command::getFromAlias(const QString &a) const
{
	foreach(const QString& s, alias.keys())
	{
		QString av(alias.value(s));
//		qDebug()<<"ALIAS"<<av << a;
		if(av == a)
			return s;
	}
	return QString();
}

bool Command::checkVars(const QVariantList &vars)
{
	if(vars.isEmpty())
		return false;
	QString command(getFromAlias(vars.first().toString()));
	if(commands.contains(command)
			&& vars.count() - 1 >= commands.value(command))
		return true;
	return false;
}

void Command::Draw(const QVariantList &vars)
{
	int A, B, C;
	tDbg.restart();
	if(!checkVars(vars))
		return;
	QString command(getFromAlias(vars.first().toString()));

	A = tDbg.elapsed();
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
	else if(command == QString("transform"))
	{
		painter->drawPath(painterPath);
		curPos = painterPath.currentPosition();
		painterPath = QPainterPath();
		painterPath.moveTo(curPos);
		QTransform t(vars.at(1).toDouble(), vars.at(2).toDouble(),
			     vars.at(3).toDouble(), vars.at(4).toDouble(),
			     vars.at(5).toDouble(), vars.at(6).toDouble());
		painter->setWorldTransform(t, true);
	}
	else if(command == QString("end"))
	{
		painter->drawPath(painterPath);
	}
	else if(command == QString("close"))
	{
		painterPath.closeSubpath();
	}
	else if(command == QString("change"))
	{
		setAlias(vars.at(1).toString(), vars.at(2).toString());
		emit namesChanged();
	}
	else if(command == QString("font"))
	{
		QStringList familyName;
		for(int i(4); i < vars.count(); ++i)
		{
			familyName << vars.at(i).toString();
		}
		QFont f(familyName.join(" "));
		f.setPointSizeF(vars.at(1).toDouble());
		f.setWeight(vars.at(2).toInt());
		f.setItalic(vars.at(3).toBool());
		painter->setFont(f);
	}
	else if(command == QString("text"))
	{
		QRectF res(painterPath.currentPosition(), QSizeF(0,0));
		for(int i(1); i < vars.count(); ++i)
		{
			painter->drawText(QRectF(res.topRight(), QSizeF(10000.0, 10000.0)), Qt::AlignLeft | Qt::AlignTop , vars.at(i).toString() + QString(" "), &res );
		}
		painterPath.moveTo(painterPath.currentPosition().x(), res.bottom());
	}
	else if(command == QString("image")
		&& !skipImages)
	{
		QString imgFile(vars.at(1).toString());
		QImage img;
		if(imgCache.contains(imgFile))
			img = imgCache.value(imgFile);
		else
		{
			img.load(imgFile);
			if(!img.isNull())
				imgCache.insert(imgFile, img);
		}
		if(!img.isNull())
		{
			if(vars.count() >= 4)
			{
				painter->drawImage(painterPath.currentPosition(), img.scaled(vars.at(2).toInt(),vars.at(3).toInt()));
			}
			else
				painter->drawImage(painterPath.currentPosition(), img);
		}
	}
	B = tDbg.elapsed() - A;
//	qDebug()<<"A"<<A<<"B"<<B;
}

