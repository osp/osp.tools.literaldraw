#include "draw.h"
#include "ui_draw.h"

#include <QScrollBar>
#include <QDebug>
#include <QPainterPath>
#include <QCursor>

Draw::Draw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Draw)
{
    ui->setupUi(this);

    highlightPath = 0;
    QRect r(0,0,2000, 2000);
    scene = new QGraphicsScene(r);
    ui->graphicsView->setScene(scene);

    pixmap = new QImage(r.size(), QImage::Format_ARGB32);
    pixmap->fill(qRgb(255,255,255));
    item = 0;

    QPainterPath p;
    p.addRect(0,0,120,24);
    frameItem = scene->addPath(p,Qt::NoPen,Qt::lightGray);
    frameItem->setZValue(999998.0);
    coordItem = scene->addText("0 0");
    coordItem->setZValue(999999.0);
    coordItem->setDefaultTextColor(Qt::white);

    QPen bPen(Qt::blue, 0.5);
    bPen.setCosmetic(true);
    horizontalLine = scene->addLine(0,0, scene->width(), 0, bPen);
    verticalLine = scene->addLine(0,0,0,scene->height(), bPen);
    horizontalLine->setZValue(99999);
    verticalLine->setZValue(99999);

    QPainterPath c;
    c.lineTo(0,-5);
    c.moveTo(0,0);
    c.lineTo(5,0);
    c.moveTo(0,0);
    c.lineTo(0,5);
    c.moveTo(0,0);
    c.lineTo(-5,0);
    c.moveTo(0,0);
    crossItem = scene->addPath(c, QPen(Qt::black, 0), Qt::NoBrush);
    crossItem->setZValue(999999);

    highlightItem = scene->addPath(QPainterPath(), QPen(Qt::green, 2, Qt::DashLine), Qt::NoBrush);
    highlightItem->setZValue(999999);

    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    connect(ui->graphicsView, SIGNAL(posClick(double, double)), this, SIGNAL(posClick(double,double)));
    connect(ui->graphicsView, SIGNAL(posClick(double, double)), this, SLOT(moveCross(double,double)));

    connect(ui->graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(moveCoord(int)));
    connect(ui->graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(moveCoord(int)));
    connect(ui->graphicsView, SIGNAL(sizeChanged(int)), this, SLOT(moveCoord(int)));

    connect(ui->graphicsView, SIGNAL(posChanged(QPoint)), this, SLOT(updateCoord(QPoint)));

    ui->graphicsView->ensureVisible(0,0,1,1);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
}

Draw::~Draw()
{
    delete ui;
}

QPainterPath * Draw::getHightlightPath()
{
	if(highlightPath)
		delete highlightPath;
	highlightPath = new QPainterPath;
	return highlightPath;
}

void Draw::updateScene()
{
	if(item)
	{
		scene->removeItem(item);
		delete item;
	}
	QPixmap p = QPixmap::fromImage(*pixmap);
	item = scene->addPixmap(p);
	item->setPos(0,0);
	if(highlightPath)
	{
		highlightItem->setPath(*highlightPath);
		qDebug()<< "HL" << (*highlightPath);
	}
}

void Draw::moveCross(double x, double y)
{
	crossItem->setPos(x,y);
}

void Draw::moveCoord(int)
{
	int hsH(ui->graphicsView->horizontalScrollBar()->height());
	int vsW(ui->graphicsView->verticalScrollBar()->width());
	int x(ui->graphicsView->width() - ( vsW + frameItem->boundingRect().width()));
	int y(ui->graphicsView->height() - ( hsH + frameItem->boundingRect().height()));
	frameItem->setPos(ui->graphicsView->mapToScene(x,y));
	coordItem->setPos(ui->graphicsView->mapToScene(x,y));
	QPoint c(QCursor::pos());
	updateCoord(ui->graphicsView->mapFromGlobal(c));
}

void Draw::updateCoord(QPoint pos)
{
	QPointF p(ui->graphicsView->mapToScene(pos));
	QString s("<div style=\"text-align:center\"> x:%1 y:%2 </div>");
	coordItem->setHtml(s.arg(p.x()).arg(p.y()));

	verticalLine->setPos(p.x(), 0);
	horizontalLine->setPos(0,p.y());
}
