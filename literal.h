#ifndef LITERAL_H
#define LITERAL_H

#include <QWidget>

class LiteralModel;

namespace Ui {
	class Literal;
}

class Literal : public QWidget
{
	Q_OBJECT
public:
	explicit Literal(QWidget *parent = 0);
	~Literal();

	QString text();
	void setModel(LiteralModel * m);

private:
	Ui::Literal *ui;

public slots:
	void insertPoint(double x, double y);
	void updateNamesView();

signals:
	void textChanged();
};

#endif // LITERAL_H
