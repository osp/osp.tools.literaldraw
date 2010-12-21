#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColor>
#include <QPointF>
#include <QPaintDevice>
#include <QVariantList>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	painter = new QPainter;
	command = new Command(painter);

	connect(ui->L, SIGNAL(textChanged()), this, SLOT(parseAndPaint()));
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::parseAndPaint()
{
	QByteArray ba;
	buffer.setBuffer(&ba);
	buffer.open(QIODevice::ReadWrite);
	svg = new QSvgGenerator;
	svg->setOutputDevice(&buffer);
	svg->setSize(QSize(2000, 2000));
	devices.clear();
	devices << svg << ui->D->pixmap;
	foreach(QPaintDevice* pd, devices)
	{
		painter->begin(pd);
		painter->eraseRect(QRect(0,0,pd->width(),pd->height()));
		QString text(ui->L->text());
		QStringList tl(text.split(QChar('\n'), QString::SkipEmptyParts));
		QPainterPath pp;
		command->setPP(pp);
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
	}
	buffer.close();
	ui->D->updateScene();
	ui->S->updateSvg(ba);
	delete svg;

}
