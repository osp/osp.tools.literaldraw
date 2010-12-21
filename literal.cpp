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
