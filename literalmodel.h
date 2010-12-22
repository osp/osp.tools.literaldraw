#ifndef LITERALMODEL_H
#define LITERALMODEL_H

#include <QAbstractTableModel>

class Command;
class LiteralModel : public QAbstractTableModel
{
    Q_OBJECT

	Command * command;
public:
    explicit LiteralModel(Command * c, QObject *parent = 0);

    int columnCount ( const QModelIndex & parent = QModelIndex() ) const{return 2;}
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    Qt::ItemFlags flags ( const QModelIndex & index ) const;

signals:

public slots:

};

#endif // LITERALMODEL_H
