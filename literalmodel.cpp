#include "literalmodel.h"
#include "command.h"

LiteralModel::LiteralModel(Command * c, QObject *parent) :
    QAbstractTableModel(parent),
    command(c)
{
}


int LiteralModel::rowCount(const QModelIndex &parent) const
{
	if(parent.isValid())
		return 0;
	return command->getAliases().count();
}


QVariant LiteralModel::data(const QModelIndex &index, int role) const
{
	if(!index.isValid())
		return QVariant();

	QList<QString> keys(command->getAliases().keys());
	QList<QString> values(command->getAliases().values());
	if(role == Qt::DisplayRole || role == Qt::EditRole)
	{
		if(index.column() == 0)
			return keys.at(index.row());
		else
			return values.at(index.row());
	}

	return QVariant();
}


bool LiteralModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(!index.isValid())
		return false;
	QList<QString> values(command->getAliases().values());
	QString v(values.at(index.row()));

	command->setAlias(v, value.toString());
	return true;
}


Qt::ItemFlags LiteralModel::flags(const QModelIndex &index) const
{
	if(!index.isValid())
		return Qt::NoItemFlags;
	if(index.column() == 1)
		return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;

	return Qt::ItemIsEnabled;
}
