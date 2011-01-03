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

private slots:
    void moveCoord(int);
    void updateCoord(QPoint pos);

public slots:
    void updateScene();


signals:
    void posClick(double, double);

private:
    Ui::Draw *ui;
};

#endif // DRAW_H
