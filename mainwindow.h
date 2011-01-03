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

private slots:
	void parseAndPaint();
	void loadText();
	void saveTxt();
	void saveSVG();
};

#endif // MAINWINDOW_H
