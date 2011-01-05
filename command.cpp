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

	clearAlias();

}

Command * Command::getInstance()
{
	if(!instance)
		instance = new Command;
	return instance;
}

void Command::clearAlias()
{
	alias.clear();

	foreach(QString c, commands.keys())
		alias.insert(c,c);
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


void Command::highlightPre(QPointF& point)
{
	QColor hcol(Qt::green);
	painter->drawPath(painterPath);
	point = painterPath.currentPosition();
	painterPath = QPainterPath();
	painterPath.moveTo(point);
	painter->setPen(hcol);
	painter->setBrush(QBrush(hcol));
}

void Command::highlightPost(QPointF& point)
{
	painter->drawPath(painterPath);
	point = painterPath.currentPosition();
	painterPath = QPainterPath();
	painterPath.moveTo(point);
}


void Command::Draw(const QVariantList &vars, bool higlight)
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
		if(higlight)
		{
			QPointF p0(painterPath.currentPosition());
			QPointF p1(vars.at(1).toDouble(), vars.at(2).toDouble());
			QLineF r(p0,p1);
			foreach(QTransform t, transforms)
			{
				r = t.map(r);
			}
			highlightPath->moveTo(r.x1(),r.y1());
			highlightPath->lineTo(r.x2(),r.y2());
			QRectF target(r.x2() - 4, r.y2() - 4, 8 , 8);
			highlightPath->addEllipse(target);

		}
		painterPath.moveTo(vars.at(1).toDouble(), vars.at(2).toDouble());
	}
	else if(command == QString("line"))
	{
		if(higlight)
		{
			QPointF p0(painterPath.currentPosition());
			QPointF p1(vars.at(1).toDouble(), vars.at(2).toDouble());
			QLineF r(p0,p1);
			foreach(QTransform t, transforms)
			{
				r = t.map(r);
			}
			highlightPath->moveTo(r.x1(),r.y1());
			highlightPath->lineTo(r.x2(),r.y2());

		}
		painterPath.lineTo(vars.at(1).toDouble(), vars.at(2).toDouble());
	}
	else if(command == QString("cubic"))
	{
		if(higlight)
		{
			QPainterPath path;
			QPointF p0(painterPath.currentPosition());
			QPointF c0(vars.at(1).toDouble(), vars.at(2).toDouble());
			QPointF c1(vars.at(3).toDouble(), vars.at(4).toDouble());
			QPointF p1(vars.at(5).toDouble(), vars.at(6).toDouble());
			path.moveTo(p0);
			path.lineTo(c0);
			path.moveTo(p0);
			path.cubicTo(vars.at(1).toDouble(), vars.at(2).toDouble(),
					      vars.at(3).toDouble(), vars.at(4).toDouble(),
					      vars.at(5).toDouble(), vars.at(6).toDouble());
			path.moveTo(p1);
			path.lineTo(c1);
			foreach(QTransform t, transforms)
			{
				path = t.map(path);
			}
			highlightPath->addPath(path);

		}
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
		transforms << t;
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
		if(higlight)
		{
			curPos = painterPath.currentPosition();
			QRectF r(curPos.x(),curPos.y(),
					  res.right() - curPos.x(),res.bottom() - curPos.y());
			foreach(QTransform t, transforms)
			{
				r = t.mapRect(r);
			}
			highlightPath->addRect(r);

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
			if(higlight)
			{
				QRectF r;
				QPointF curPos = painterPath.currentPosition();
				if(vars.count() >= 4)
				{
					QImage simg(img.scaled(vars.at(2).toInt(),vars.at(3).toInt()));
					r = QRectF(curPos.x(),curPos.y(),
						  simg.width(), simg.height());
				}
				else
					r = QRectF(curPos.x(),curPos.y(),
						   img.width(), img.height());
				foreach(QTransform t, transforms)
				{
					r = t.mapRect(r);
				}
				highlightPath->addRect(r);

			}
		}
	}
	B = tDbg.elapsed() - A;


//	qDebug()<<"A"<<A<<"B"<<B;
}

