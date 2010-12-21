#include "draw.h"
#include "ui_draw.h"

#include <QDebug>

Draw::Draw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Draw)
{
    ui->setupUi(this);

    QRect r(0,0,2000, 2000);
    scene = new QGraphicsScene(r);
    ui->graphicsView->setScene(scene);

    pixmap = new QImage(r.size(), QImage::Format_ARGB32);
    pixmap->fill(qRgb(255,255,255));
    item = 0;

    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

Draw::~Draw()
{
    delete ui;
}


void Draw::updateScene()
{
	if(item)
		scene->removeItem(item);
	QPixmap p = QPixmap::fromImage(*pixmap);
	item = scene->addPixmap(p);
	item->setPos(0,0);
	qDebug()<<scene<<item->scene();
}
