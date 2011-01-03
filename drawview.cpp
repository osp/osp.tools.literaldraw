#include "drawview.h"
#include <QMouseEvent>
#include <QPoint>
#include <QPointF>

DrawView::DrawView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void DrawView::mouseReleaseEvent(QMouseEvent *event)
{
	QPointF p(mapToScene(event->pos()));
	emit posClick(p.x(), p.y());
}

void DrawView::mouseMoveEvent(QMouseEvent *event)
{
	emit posChanged(event->pos());
}

void DrawView::resizeEvent(QResizeEvent *event)
{
	emit sizeChanged(0);
//	QGraphicsView::resizeEvent(event);
}
