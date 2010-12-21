#ifndef DRAWVIEW_H
#define DRAWVIEW_H

#include <QGraphicsView>

class DrawView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit DrawView(QWidget *parent = 0);

protected:
	void mouseReleaseEvent ( QMouseEvent * event );
signals:
	void posClick(double, double);
public slots:

};

#endif // DRAWVIEW_H
