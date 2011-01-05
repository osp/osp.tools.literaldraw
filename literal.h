#ifndef LITERAL_H
#define LITERAL_H

#include <QWidget>
#include <QStringList>

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
	QStringList lines();
	int currentLine();
	void setText(const QString& text);
	void setModel(LiteralModel * m);

private:
	Ui::Literal *ui;

public slots:
	void insertPoint(double x, double y);
	void updateNamesView();

signals:
	void textChanged();
	void posChanged();
};

#endif // LITERAL_H
