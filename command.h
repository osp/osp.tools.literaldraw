#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QPainter>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QPainterPath>
#include <QTime>
#include <QImage>
#include <QPointF>
#include <QList>
#include <QTransform>

class Command : public QObject
{
	Q_OBJECT

	static Command * instance;
	Command();
	QPainter * painter;
	QPainterPath painterPath;
	QPainterPath  * highlightPath;

	bool coordAbsolute;

	QTime tDbg;

	QList<QTransform> transforms;

	QMap<QString, QImage> imgCache;
	bool skipImages;

	QMap<QString, int> commands;
	QMap<QString, QString> alias;
	QString getFromAlias(const QString& a) const;
	bool checkVars(const QVariantList& vars);

	void highlightPre(QPointF& point);
	void highlightPost(QPointF& point);
public:
	static Command * getInstance();
	void clearAlias();
	void setPainter(QPainter * p){painter = p;}
	void setPP(QPainterPath& pp){painterPath = pp;}
	QPainterPath& PP(){return painterPath;}

	void setHighlightPP(QPainterPath *pp){highlightPath = pp;}

	void Draw(const QVariantList& vars, bool higlight = false);
//	void GraphicState(const QVariantList& vars);

	const QMap<QString, QString>& getAliases() const{return alias;}
	void setAlias(const QString& key, const QString& val){alias[key] = val;}
	bool setSkipImages(bool b){skipImages = b;}

	void clearTrans(){transforms.clear();}
	QList<QTransform> getTrans(){return transforms;}

	void resetAbsolute(){coordAbsolute = true;}

signals:
	void namesChanged();
};

#endif // COMMAND_H
