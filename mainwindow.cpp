#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "literalmodel.h"

#include <QColor>
#include <QPointF>
#include <QPaintDevice>
#include <QVariantList>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	highlight = new QCheckBox("Highlight");
	highlight->setChecked(false);
	statusBar()->addPermanentWidget(highlight);

	painter = new QPainter;
	command = Command::getInstance();
	command->setPainter(painter);

	ui->L->setModel(new LiteralModel(command, this));

	connect(command, SIGNAL(imageChanged()), this, SLOT(parseAndPaint()));
	connect(command, SIGNAL(changeSceneRect(double,double)), ui->D, SLOT(sceneRect(double,double)));

	connect(highlight, SIGNAL(toggled(bool)), this, SLOT(switchHighlight(bool)));

	connect(ui->L, SIGNAL(textChanged()), this, SLOT(parseAndPaint()));
	connect(ui->D, SIGNAL(somethingChange()), this, SLOT(parseAndPaint()));
	connect(ui->D, SIGNAL(posClick(double,double)), ui->L, SLOT(insertPoint(double,double)));

	connect(ui->actionNew_Text, SIGNAL(triggered()), this, SLOT(newText()));
	connect(ui->actionLoad_Text, SIGNAL(triggered()), this, SLOT(loadText()));
	connect(ui->actionSave_Text, SIGNAL(triggered()), this, SLOT(saveTxt()));
	connect(ui->actionSave_Text_As, SIGNAL(triggered()), this, SLOT(saveTxtAs()));
	connect(ui->actionSave_SVG, SIGNAL(triggered()), this, SLOT(saveSVG()));

	connect(command, SIGNAL(namesChanged()), ui->L, SLOT(updateNamesView()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::switchHighlight(bool h)
{
	if(h)
		connect(ui->L, SIGNAL(posChanged()), this, SLOT(parseAndPaint()));
	else
		disconnect(ui->L, SIGNAL(posChanged()), this, SLOT(parseAndPaint()));

}

void MainWindow::parseAndPaint()
{
	QByteArray ba;
	buffer.setBuffer(&ba);
	buffer.open(QIODevice::ReadWrite);
	svg = new QSvgGenerator;
	svg->setOutputDevice(&buffer);
	svg->setViewBox(ui->D->scene->sceneRect());
	devices.clear();
	devices << svg << ui->D->pixmap;
	foreach(QPaintDevice* pd, devices)
	{
		if(pd == svg)
			command->setSkipImages(true);
		else
		{
			command->setSkipImages(false);
		}
		command->clearTrans();
		if(highlight->isChecked())
			command->setHighlightPP(ui->D->getHightlightPath());
		command->resetAbsolute();
		painter->begin(pd);
		if(pd == ui->D->pixmap)
		{
			painter->eraseRect(QRect(0,0,pd->width(),pd->height()));
			painter->translate(-ui->D->pixmapShift.x(), -ui->D->pixmapShift.y());
		}
		QPainterPath pp;
		command->setPP(pp);
		painter->setRenderHint(QPainter::Antialiasing);
		int cline(ui->L->currentLine());
		int lc(0);
		foreach(QString s, ui->L->lines())
		{
			if(!s.isEmpty())
			{
				QStringList args(s.simplified().split(" ", QString::SkipEmptyParts));
				QVariantList vl;
				foreach(const QString& a, args)
				{
					vl << a;
				}
				command->Draw(vl, lc == cline ? true : false);
			}
			++lc;
		}
		painter->end();
	}
	buffer.close();
	ui->D->updateScene();
	ui->S->updateSvg(ba);
	delete svg;

}

void MainWindow::newText()
{
	command->clearAlias();
	command->clearImageCache();
	ui->L->setText(QString());
	setCurrentFile();
}

void MainWindow::loadText()
{
	QString fn(QFileDialog::getOpenFileName(this, QString("Load Text"), QDir::homePath()));
	if(fn.isEmpty())
		return;

	setCurrentFile(fn);
	QFile f(fn);
	if(f.open(QIODevice::ReadOnly))
	{
		command->clearAlias();
		command->clearImageCache();
		ui->L->blockSignals(true);
		ui->L->setText(f.readAll());
		ui->L->blockSignals(false);
		parseAndPaint();
	}
}

void MainWindow::saveTxt()
{
	if(currentFilename.isEmpty())
	{
		saveTxtAs();
		return;
	}
	QFile f(currentFilename);
	if(f.open(QIODevice::WriteOnly))
	{
		f.write(ui->L->text().toUtf8());
		f.close();
	}
}

void MainWindow::saveTxtAs()
{
	QString fn = QFileDialog::getSaveFileName ( this,  QString("Save File"), QDir::homePath());
	if(fn.isEmpty())
		return;
	setCurrentFile(fn);
	QFile f(currentFilename);
	if(f.open(QIODevice::WriteOnly))
	{
		f.write(ui->L->text().toUtf8());
		f.close();
	}
}

void MainWindow::saveSVG()
{
	QString	fn(QFileDialog::getSaveFileName ( this,  QString("Save SVG"), QDir::homePath()));
	if(fn.isEmpty())
		return;

	QFile f(fn);
	if(f.open(QIODevice::WriteOnly))
	{
		QByteArray ba;
		buffer.setBuffer(&ba);
		buffer.open(QIODevice::ReadWrite);
		svg = new QSvgGenerator;
		svg->setOutputDevice(&buffer);
		svg->setViewBox(ui->D->scene->sceneRect());
		painter->begin(svg);
		painter->eraseRect(QRect(0,0,svg->width(),svg->height()));
		QString text(ui->L->text());
		QStringList tl(text.split(QChar('\n'), QString::SkipEmptyParts));
		QPainterPath pp;
		command->setPP(pp);
		command->clearTrans();
		command->resetAbsolute();
		painter->setRenderHint(QPainter::Antialiasing);
		foreach(QString s, tl)
		{
			QStringList args(s.simplified().split(" ", QString::SkipEmptyParts));
			QVariantList vl;
			foreach(const QString& a, args)
			{
				vl << a;
			}
			command->Draw(vl);

		}
		painter->end();
		buffer.close();
		delete svg;
		f.write(ba);
		f.close();
	}
}


void MainWindow::setCurrentFile(const QString &fn)
{
	currentFilename = fn;
	QFileInfo info(currentFilename);
	if(fn.isEmpty())
		setWindowTitle(QString("New File - LiteralDraw"));
	else
		setWindowTitle(QString("%1 - LiteralDraw").arg(info.fileName()));
}

