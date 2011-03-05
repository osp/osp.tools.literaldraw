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
    QRect r(0,0,10000, 10000);
    scene = new QGraphicsScene(r);
    ui->graphicsView->setScene(scene);

    pixmap = new QImage(ui->graphicsView->size(), QImage::Format_ARGB32);
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
    connect(ui->graphicsView, SIGNAL(sizeChanged(int)), this, SLOT(updateSize(int)));

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
	QPointF itemPos;
	if(item)
	{
		itemPos = item->pos();
		scene->removeItem(item);
		delete item;
	}
	QPixmap p = QPixmap::fromImage(*pixmap);
	item = scene->addPixmap(p);
	item->setPos(itemPos);
	if(highlightPath)
	{
		highlightItem->setPath(*highlightPath);
		qDebug()<< "HL" << (*highlightPath);
	}
}

void Draw::updateSize(int)
{
	delete pixmap;
	pixmap = new QImage(ui->graphicsView->size(), QImage::Format_ARGB32);
	emit somethingChange();
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
	pixmapShift = ui->graphicsView->mapToScene(QPoint(0,0));
	if(item)
		item->setPos(pixmapShift);
	emit somethingChange();
}

void Draw::updateCoord(QPoint pos)
{
	QPointF p(ui->graphicsView->mapToScene(pos));
	QString s("<div style=\"text-align:center\"> x:%1 y:%2 </div>");
	coordItem->setHtml(s.arg(p.x()).arg(p.y()));

	verticalLine->setPos(p.x(), 0);
	horizontalLine->setPos(0,p.y());
}

void Draw::sceneRect(double w, double h)
{
	scene->setSceneRect(0, 0, w, h);
}
