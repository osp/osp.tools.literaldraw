#ifndef DRAWVIEW_H
#define DRAWVIEW_H

#include <QGraphicsView>
#include <QPoint>

class DrawView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit DrawView(QWidget *parent = 0);

protected:
	void mouseReleaseEvent ( QMouseEvent * event );
	void mouseMoveEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);

signals:
	void posClick(double, double);
	void posChanged(QPoint);
	void sizeChanged(int);


};

#endif // DRAWVIEW_H
