#include "command.h"

#include <QColor>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QFont>
#include <QFile>

Command * Command::instance = 0;
Command::Command():
	QObject(0)
{
	coordAbsolute = true;

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
	commands.insert("textblock", 3);
	commands.insert("image", 1);
	commands.insert("absolute", 1);

	clearAlias();

	connect(&imgWatcher, SIGNAL(fileChanged(QString)), this, SLOT(updateImgCache(QString)));

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

void Command::setAlias(const QString &key, const QString &val)
{
	if(alias.contains(key))
		alias[key] = val;
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
	const QPointF curPos(painterPath.currentPosition());
	if(command == QString("move"))
	{
		QPointF target(vars.at(1).toDouble(), vars.at(2).toDouble());
		if(!coordAbsolute)
			target = curPos + target;
		if(higlight)
		{
			QPointF p0(curPos);
			QPointF p1(target);
			QLineF r(p0,p1);
			foreach(QTransform t, transforms)
			{
				r = t.map(r);
			}
			highlightPath->moveTo(r.x1(),r.y1());
			highlightPath->lineTo(r.x2(),r.y2());
			QRectF targetRect(r.x2() - 4, r.y2() - 4, 8 , 8);
			highlightPath->addEllipse(targetRect);

		}
		painterPath.moveTo(target);
	}
	else if(command == QString("line"))
	{
		QPointF target(vars.at(1).toDouble(), vars.at(2).toDouble());
		if(!coordAbsolute)
			target = curPos + target;
		if(higlight)
		{
			QPointF p0(curPos);
			QPointF p1(target);
			QLineF r(p0,p1);
			foreach(QTransform t, transforms)
			{
				r = t.map(r);
			}
			highlightPath->moveTo(r.x1(),r.y1());
			highlightPath->lineTo(r.x2(),r.y2());

		}
		painterPath.lineTo(target);
	}
	else if(command == QString("cubic"))
	{
		QPointF target(vars.at(5).toDouble(), vars.at(6).toDouble());
		QPointF c1(vars.at(1).toDouble(), vars.at(2).toDouble());
		QPointF c2(vars.at(3).toDouble(), vars.at(4).toDouble());
		if(!coordAbsolute)
		{
			target = curPos + target;
			c1 = c1 + curPos;
			c2 = c2 + curPos;
		}
		if(higlight)
		{
			QPainterPath path;
			path.moveTo(curPos);
			path.lineTo(c1);
			path.moveTo(curPos);
			path.cubicTo(c1,c2,target);
//			path.moveTo(p1);
			path.lineTo(c2);
			foreach(QTransform t, transforms)
			{
				path = t.map(path);
			}
			highlightPath->addPath(path);

		}
		painterPath.cubicTo(c1,c2,target);

	}
	else if(command == QString("fill"))
	{
		painter->drawPath(painterPath);
		painterPath = QPainterPath();
		painterPath.moveTo(curPos);
		QColor c(vars.at(1).toInt(), vars.at(2).toInt(), vars.at(3).toInt());
		if(vars.count() == 5)
			c.setAlpha(vars.at(4).toInt());
		painter->setBrush(c);
	}
	else if(command == QString("stroke"))
	{
		painter->drawPath(painterPath);
		painterPath = QPainterPath();
		painterPath.moveTo(curPos);
		QColor c(vars.at(1).toInt(), vars.at(2).toInt(), vars.at(3).toInt());
		if(vars.count() == 6)
			c.setAlpha(vars.at(5).toInt());
		double width(vars.at(4).toDouble());
		painter->setPen(QPen(QBrush(c), width));
	}
	else if(command == QString("transform"))
	{
		painter->drawPath(painterPath);
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
		painterPath = QPainterPath();
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
		QRect res;
		QString text;
		bool first(true);
		for(int i(1); i < vars.count(); ++i)
		{
			if(first)
			{
				first = false;
				text +=  vars.at(i).toString();
			}
			else
				text +=  QString(" ") + vars.at(i).toString();
		}
		painter->drawText(qRound(curPos.x()), qRound(curPos.y()), 99999, 99999, Qt::AlignLeft | Qt::AlignTop ,text , &res );
		if(higlight)
		{
			QRectF r(res);
			foreach(QTransform t, transforms)
			{
				r = t.mapRect(r);
			}
			highlightPath->addRect(r);

		}
		painterPath.moveTo(curPos.x(), res.bottom());

	}
	else if(command == QString("textblock"))
	{
		int width(vars.at(1).toDouble());
		Qt::Alignment align(Qt::AlignLeft);
		QString ua(vars.at(2).toString());
		if(ua == QString("right"))
			align = Qt::AlignRight;
		else if(ua == QString("center"))
			align = Qt::AlignCenter;
		else if(ua == QString("justify"))
			align = Qt::AlignJustify;
		QRect res;
		QString text;
		bool first(true);
		for(int i(3); i < vars.count(); ++i)
		{
			if(first)
			{
				first = false;
				text +=  vars.at(i).toString();
			}
			else
				text +=  QString(" ") + vars.at(i).toString();
		}
		painter->drawText(qRound(curPos.x()), qRound(curPos.y()), width, 99999, align | Qt::AlignTop | Qt::TextWordWrap , text , &res );
		if(higlight)
		{
			QRectF r(res);
			foreach(QTransform t, transforms)
			{
				r = t.mapRect(r);
			}
			highlightPath->addRect(r);

		}
		painterPath.moveTo(curPos.x(), res.bottom());

	}
	else if(command == QString("image")
		&& !skipImages)
	{
		QString imgFile(vars.at(1).toString());
		if(QFile::exists(imgFile))
		{
			QImage img;
			if(imgCache.contains(imgFile))
				img = imgCache.value(imgFile);
			else
			{
				img.load(imgFile);
				if(!img.isNull())
				{
					imgCache.insert(imgFile, img);
					imgWatcher.addPath(imgFile);
				}
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
	}
	else if(command == QString("absolute"))
	{
		coordAbsolute = vars.at(1).toBool();
	}
	B = tDbg.elapsed() - A;


//	qDebug()<<"A"<<A<<"B"<<B;
}


void Command::updateImgCache(const QString &fn)
{
	imgCache.remove(fn);
}






