#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>


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

public slots:
    void updateScene();

private:
    Ui::Draw *ui;
};

#endif // DRAW_H
