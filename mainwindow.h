#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPainterPath>

#include <QString>
#include <QStringList>
#include <QList>
#include <QtSvg/QSvgGenerator>
#include <QBuffer>

#include "command.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	QPainter * painter;
	QSvgGenerator * svg;

	QBuffer buffer;

	QList<QPaintDevice*> devices;

	Command * command;

	QString currentFilename;
	void setCurrentFile(const QString& fn = QString());

private slots:
	void parseAndPaint();
	void newText();
	void loadText();
	void saveTxt();
	void saveTxtAs();
	void saveSVG();
};

#endif // MAINWINDOW_H
