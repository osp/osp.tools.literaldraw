#include "literal.h"
#include "ui_literal.h"

Literal::Literal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Literal)
{
    ui->setupUi(this);

    connect(ui->literalEdit, SIGNAL(textChanged()), this, SIGNAL(textChanged()));
}

Literal::~Literal()
{
    delete ui;
}

QString Literal::text()
{
	return ui->literalEdit->toPlainText();
}


void Literal::insertPoint(double x, double y)
{
	QString s(" %1 %2 ");
	ui->literalEdit->insertPlainText(s.arg(x, 0, 'f', 2).arg(y, 0, 'f', 2));
}
