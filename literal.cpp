#include "literal.h"
#include "ui_literal.h"
#include <QPointF>
#include <QTransform>
#include <QStringList>

#include "command.h"
#include "literalmodel.h"

Literal::Literal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Literal)
{
    ui->setupUi(this);
    connect(ui->literalEdit, SIGNAL(textChanged()), this, SIGNAL(textChanged()));
    connect(ui->literalEdit, SIGNAL(cursorPositionChanged()), this, SIGNAL(posChanged()));
}

Literal::~Literal()
{
    delete ui;
}

void Literal::setModel(LiteralModel *m)
{
	ui->table->setModel(m);
}

QString Literal::text()
{
	return ui->literalEdit->toPlainText();
}

QStringList Literal::lines()
{
	return ui->literalEdit->toPlainText().split(QChar('\n'));
}

int Literal::currentLine()
{
	QStringList l(ui->literalEdit->toPlainText().split(QChar('\n')));
	int ccounter(0);
	int lcounter(0);
	int c(ui->literalEdit->textCursor().position());
	foreach(const QString& s, l)
	{
		foreach(const QChar& ch, s)
		{
			if(c == ccounter)
				return lcounter;
			++ccounter;
		}
		++lcounter;
		++ccounter; // newline character
	}
	return -1;
}

void Literal::setText(const QString &text)
{
	ui->literalEdit->setPlainText(text);
	emit textChanged();
}


void Literal::insertPoint(double x, double y)
{
	QPointF p(x,y);
	QList<QTransform> trans(Command::getInstance()->getTrans());
	foreach(QTransform t, trans)
	{
		p = t.inverted().map(p);
	}
	QString s(" %1 %2 ");
	ui->literalEdit->insertPlainText(s.arg(p.x(), 0, 'f', 2).arg(p.y(), 0, 'f', 2));
}


void Literal::updateNamesView()
{
	ui->table->reset();
}
