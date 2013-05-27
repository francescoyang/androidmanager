/************************************************************************************************************
Copyright(C) 2008 Hailing Zhao.
This widget may be used under the terms of the GNU General Public License versions 3.0 as published by the 
Free Software Foundation and appearing in the file LICENSE.GPL included in the packaging of this file. 
Please review the following information to ensure GNU General Public Licensing requirements will be met: 
<http://www.gnu.org/licenses/>.
**************************************************************************************************************/

#include <QtGui>
#include <QDir>
#include <QStringList>
#include "picturelistmodel.h"

PictureListModel::PictureListModel(QObject *parent)
	: QAbstractListModel(parent)
{

}

QVariant PictureListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == Qt::DecorationRole)
		return QIcon(pixmaps.value(index.row()).scaled(80, 60,
				Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
	else if (role == Qt::DisplayRole)
	{
		QString filename = pictureFiles.at(index.row());
		if (filename.length() > 10)
		{
			filename.remove(9, filename.length()-9);
			filename.append("...");
		}
		return filename;
	}
	else if (role == Qt::UserRole)
		return pixmaps.value(index.row());

	return QVariant();
}

void PictureListModel::addPictures(QString directory)
{
	// clear
	if (pixmaps.size() != 0)
	{
		beginRemoveRows(QModelIndex(), 0, pixmaps.size()-1);
		pixmaps.clear();
		pictureFiles.clear();
		endRemoveRows();
	}

	// get directory file list
	QDir dir(directory, "", QDir::Name|QDir::IgnoreCase, QDir::Files|QDir::NoDotAndDotDot );
	QStringList fileList = dir.entryList();
	uint count = dir.count();

	for (uint i = 0; i < count; i++)
	{
		QString filename = dir.path() + "/" + fileList.at(i);
		QPixmap pixmap(filename);
		if (!pixmap.isNull())
		{
			int row = pixmaps.size();
			beginInsertRows(QModelIndex(), row, row);
			pixmaps.insert(row, pixmap);
			pictureFiles.insert(row, fileList.at(i));
			endInsertRows();
		}
	}
}

bool PictureListModel::removeRows(int row, int count, const QModelIndex &parent)
{
	if (parent.isValid())
		return false;

	if (row >= pixmaps.size() || row + count <= 0)
		return false;

	int beginRow = qMax(0, row);
	int endRow = qMin(row + count - 1, pixmaps.size() - 1);

	beginRemoveRows(parent, beginRow, endRow);

	while(beginRow <= endRow)
	{
		pixmaps.removeAt(beginRow);
		pictureFiles.removeAt(beginRow);
		++beginRow;
	}

	endRemoveRows();
	return true;
}

int PictureListModel::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	else
		return pixmaps.size();
}
