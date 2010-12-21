#include "svgview.h"
#include "ui_svgview.h"

SvgView::SvgView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SvgView)
{
    ui->setupUi(this);
}

SvgView::~SvgView()
{
    delete ui;
}


void SvgView::updateSvg(const QString &s)
{
	ui->textBrowser->setPlainText(s);
}
