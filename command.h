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

class Command : public QObject
{
	Q_OBJECT

	static Command * instance;
	Command();
	QPainter * painter;
	QPainterPath painterPath;

	QTime tDbg;

	QMap<QString, QImage> imgCache;
	bool skipImages;

	QMap<QString, int> commands;
	QMap<QString, QString> alias;
	QString getFromAlias(const QString& a) const;
	bool checkVars(const QVariantList& vars);
public:
	static Command * getInstance();
	void setPainter(QPainter * p){painter = p;}
	void setPP(QPainterPath& pp){painterPath = pp;}
	QPainterPath& PP(){return painterPath;}

	void Draw(const QVariantList& vars);
//	void GraphicState(const QVariantList& vars);

	const QMap<QString, QString>& getAliases() const{return alias;}
	void setAlias(const QString& key, const QString& val){alias[key] = val;}
	bool setSkipImages(bool b){skipImages = b;}

signals:
	void namesChanged();
};

#endif // COMMAND_H
