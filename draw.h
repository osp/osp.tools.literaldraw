#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsPathItem>
#include <QGraphicsLineItem>
#include <QPoint>

namespace Ui {
    class Draw;
}

class Draw : public QWidget
{
    Q_OBJECT

public:
    explicit Draw(QWidget *parent = 0);
    ~Draw();

    QImage *pixmap;
    QGraphicsScene * scene;
    QGraphicsPixmapItem * item;
    QGraphicsTextItem *coordItem;
    QGraphicsPathItem * frameItem;
    QGraphicsLineItem * horizontalLine;
    QGraphicsLineItem * verticalLine;
    QGraphicsPathItem * crossItem;
    QGraphicsPathItem * highlightItem;

    QPainterPath * getHightlightPath();

    QPointF pixmapShift;

private slots:
    void moveCoord(int);
    void updateCoord(QPoint pos);
    void moveCross(double x, double y);
    void updateSize(int);

public slots:
    void updateScene();


signals:
    void posClick(double, double);
    void somethingChange();

private:
    Ui::Draw *ui;
    QPainterPath * highlightPath;
};

#endif // DRAW_H
