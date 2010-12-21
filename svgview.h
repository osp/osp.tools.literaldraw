#ifndef SVGVIEW_H
#define SVGVIEW_H

#include <QWidget>

namespace Ui {
    class SvgView;
}

class SvgView : public QWidget
{
    Q_OBJECT

public:
    explicit SvgView(QWidget *parent = 0);
    ~SvgView();

public slots:
    void updateSvg(const QString& s);

private:
    Ui::SvgView *ui;
};

#endif // SVGVIEW_H
