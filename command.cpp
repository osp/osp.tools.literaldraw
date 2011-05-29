#include "command.h"

#include <QColor>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QFont>
#include <QFile>
#include <QSvgRenderer>
#include <cmath>
#include <QLineF>

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
	commands.insert("svg", 1);
	commands.insert("svg-effect", 4);
	commands.insert("page-size", 2);
	commands.insert("turn", 2);
	commands.insert("var", 2);
	commands.insert("rotate", 1);
	commands.insert("save",0);
	commands.insert("restore",0);

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

void Command::clearImageCache()
{
	foreach(QString i, imgCache.keys())
		imgWatcher.removePath(i);
	imgCache.clear();
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


double Command::number(QVariant v)
{
	if(varMap.contains(v.toString()))
		return varMap.value(v.toString());
	return v.toDouble();
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
	if(command == QString("var"))
	{
		varMap.insert(vars.at(1).toString(), number(vars.at(2)));
	}
	else if(command == QString("move"))
	{
		QPointF target(number(vars.at(1)), number(vars.at(2)));
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
		QPointF target(number(vars.at(1)), number(vars.at(2)));
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
	else if(command == QString("turn"))
	{
		QString angleStr(vars.at(1).toString());
		double distance( number(vars.at(2)) );
		int ec(painterPath.elementCount());
		QPointF curPosMinus1(curPos);
		if(ec > 1) // we want at least 2 points
		{
			curPosMinus1 = QPointF(painterPath.elementAt(ec - 2).x, painterPath.elementAt(ec - 2).y);
		}

		QLineF l1(curPosMinus1, curPos);
		double startAngle(l1.angle());

		double extra(0);
		if(vars.count() > 3)
			extra = number(vars.at(3));
		bool process(true);
		double angle(0);
		if(angleStr == QString("s"))
			angle = startAngle + extra;
		else if(angleStr == QString("r"))
			angle = startAngle + 270 + extra;
		else if(angleStr == QString("b"))
			angle = startAngle + 180 + extra;
		else if(angleStr == QString("l"))
			angle = startAngle + 90 + extra;
		else
			process = false;

		if(process)
		{
			QLineF l2(curPos, QPointF(curPos.x() +1, 0));
			l2.setLength(distance);
			l2.setAngle(angle);
			painterPath.lineTo(l2.p2());
		}
	}
	else if(command == QString("cubic"))
	{
		QPointF target(number(vars.at(5)), number(vars.at(6)));
		QPointF c1(number(vars.at(1)), number(vars.at(2)));
		QPointF c2(number(vars.at(3)), number(vars.at(4)));
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
		double width(number(vars.at(4)));
		painter->setPen(QPen(QBrush(c), width));
	}
	else if(command == QString("transform"))
	{
		painter->drawPath(painterPath);
		painterPath = QPainterPath();
		painterPath.moveTo(curPos);
		QTransform t(number(vars.at(1)), number(vars.at(2)),
			     number(vars.at(3)), number(vars.at(4)),
			     number(vars.at(5)), number(vars.at(6)));
		painter->setWorldTransform(t, true);
		transforms << t;
	}
	else if(command == QString("rotate"))
	{
		painter->drawPath(painterPath);
		painterPath = QPainterPath();
		painterPath.moveTo(curPos);
		QTransform t;
		t.rotate(number(vars.at(1)));
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
		f.setPointSizeF(number(vars.at(1)));
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
		int width(number(vars.at(1)));
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
					if(!imgWatcher.files().contains(imgFile))
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
	else if(command == QString("page-size"))
	{
		emit changeSceneRect(number(vars.at(1)), number(vars.at(2)));
	}
	else if(command == QString("svg"))
	{
		QString svgfile(vars.at(1).toString());
		if(QFile::exists(svgfile))
		{
			QSvgRenderer svgRdr(svgfile);
			QRectF r(svgRdr.viewBoxF());
			svgRdr.render(painter, r);
		}

	}
	else if(command == QString("svg-effect"))
	{
		// @1 svg file
		// @2 raster file
		// @3 effect: rotate;...
		QString svgfile(vars.at(1).toString());
		QString effectfile(vars.at(2).toString());
		QString effect(vars.at(3).toString());
		bool eRotate(effect == QString("r") || effect == QString("R"));
		bool eScale(effect == QString("s") || effect == QString("S"));
		bool eScaleAndRotate(effect == QString("w") || effect == QString("W"));
		bool eInvert(effect == QString("R") || effect == QString("S") || effect == QString("W"));

		ColorComponent cc(NoColorComponent);
		QString ccString(vars.at(4).toString());
		if(ccString == QString("r") || ccString == QString("R"))
			cc = Red;
		else if(ccString == QString("g") || ccString == QString("G"))
			cc = Green;
		else if(ccString == QString("b") || ccString == QString("B"))
			cc = Blue;
		else if(ccString == QString("h") || ccString == QString("H"))
			cc = Hue;
		else if(ccString == QString("s") || ccString == QString("S"))
			cc = Saturation;
		else if(ccString == QString("l") || ccString == QString("L"))
			cc = Lightness;

		if(QFile::exists(svgfile) && QFile::exists(effectfile)
			&& (eRotate || eScale || eScaleAndRotate)
			&& cc != NoColorComponent)
		{
			if(!imgCache.contains(svgfile))
			{
				imgCache.insert(svgfile, QImage());
				if(!imgWatcher.files().contains(svgfile))
					imgWatcher.addPath(svgfile);
			}
			QImage img;
			if(imgCache.contains(effectfile))
				img = imgCache.value(effectfile);
			else
			{
				img.load(effectfile);
				if(!img.isNull())
				{
					imgCache.insert(effectfile, img);
					if(!imgWatcher.files().contains(effectfile))
						imgWatcher.addPath(effectfile);
				}
			}
			QSvgRenderer svgRdr(svgfile);
			QRectF r(svgRdr.viewBoxF());
			int cols(qRound(img.width() / r.width()));
			int rows(qRound(img.height() / r.height()));
			if(cols == 0 || rows == 0)
				return;
			qDebug()<< "E"<<cols<<rows;
			for(int y(0); y < rows; ++y)
			{
				for(int x(0); x < cols; ++x)
				{
//					qDebug()<<"I"<<x<<y;
					int cxOrigin(x * r.width());
					int cyOrigin(y * r.height());
					int cRight(qMin(qRound(r.width()) + cxOrigin, img.width()));
					int cBottom(qMin(qRound(r.height()) + cyOrigin, img.height()));
					double val(0);
					double nVal(0);
					for(int cy(cyOrigin); cy < cBottom; ++cy)
					{
						for(int cx(cxOrigin); cx < cRight; ++cx)
						{
							QColor ccolor(img.pixel(cx,cy));
							if(cc == Red)
								val += ccolor.redF();
							else if(cc == Green)
								val += ccolor.greenF();
							else if(cc == Blue)
								val += ccolor.blueF();
							else if(cc == Hue)
								val += ccolor.hslHueF();
							else if(cc == Saturation)
								val += ccolor.hslSaturationF();
							else if(cc == Lightness)
								val += ccolor.lightnessF();
							++nVal;
						}
					}
					double cMean(val / nVal);
					qDebug()<<val<<cMean<<nVal;
					if(eInvert)
						cMean = 1 - cMean;
					if(cMean == 0)
						continue;

					double tx(x * r.width() );
					double ty(y * r.height());
					double hW(r.width() / 2.0);
					double hH(r.height() / 2.0);
					painter->save();
					painter->translate(tx, ty);
					if(eRotate)
					{
						double rotVal(cMean * 360.0);
						painter->setTransform(QTransform().translate(hW, hH).rotate(rotVal).translate(-hW, -hH), true);
					}
					else if(eScale)
					{
//						painter->scale(cMean, cMean);
						painter->setTransform(QTransform().translate(hW, hH).scale(cMean, cMean).translate(-hW, -hH), true);
					}
					else if(eScaleAndRotate)
					{
						double rotVal(cMean * 360.0);
						QTransform srTrans(QTransform().translate(hW, hH).scale(cMean, cMean).rotate(rotVal).translate(-hW, -hH));
						qDebug()<<srTrans;
						painter->setTransform(srTrans, true);

					}
					svgRdr.render(painter, r);
					painter->restore();
				}
			}

		}

	}
	else if(command == QString("save"))
	{
		painter->save();
	}
	else if(command == QString("restore"))
	{
		painter->restore();
	}
	B = tDbg.elapsed() - A;


//	qDebug()<<"A"<<A<<"B"<<B;
}

void Command::endDraw()
{
	if(painter)
		painter->drawPath(painterPath);
}

void Command::updateImgCache(const QString &fn)
{
	qDebug()<<"updateImgCache"<<fn;
	imgCache.remove(fn);
//	imgWatcher.removePath(fn);
	emit imageChanged();
}






