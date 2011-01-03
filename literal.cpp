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

void Literal::setText(const QString &text)
{
	ui->literalEdit->setPlainText(text);
	emit textChanged();
}


void Literal::insertPoint(double x, double y)
{
	QPointF p(x,y);
	QString transStr(Command::getInstance()->getAliases().value(QString("transform")));
	QStringList tl(ui->literalEdit->toPlainText().split(QChar('\n'), QString::SkipEmptyParts));
	foreach(QString s, tl)
	{
		QStringList vars(s.simplified().split(" ", QString::SkipEmptyParts));
		if(vars.first() == transStr
		   && vars.count() == 7)
		{
			QTransform t(vars.at(1).toDouble(), vars.at(2).toDouble(),
				     vars.at(3).toDouble(), vars.at(4).toDouble(),
				     vars.at(5).toDouble(), vars.at(6).toDouble());

			p = t.inverted().map(p);
		}
	}
	QString s(" %1 %2 ");
	ui->literalEdit->insertPlainText(s.arg(p.x(), 0, 'f', 2).arg(p.y(), 0, 'f', 2));
}


void Literal::updateNamesView()
{
	ui->table->reset();
}
