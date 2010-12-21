#ifndef LITERAL_H
#define LITERAL_H

#include <QWidget>

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

private:
    Ui::Literal *ui;

signals:
    void textChanged();
};

#endif // LITERAL_H
