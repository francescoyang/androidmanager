/************************************************************************************************************
Copyright(C) 2008 Hailing Zhao.
This widget may be used under the terms of the GNU General Public License versions 3.0 as published by the 
Free Software Foundation and appearing in the file LICENSE.GPL included in the packaging of this file. 
Please review the following information to ensure GNU General Public Licensing requirements will be met: 
<http://www.gnu.org/licenses/>.
**************************************************************************************************************/

#include <QAbstractListModel>
#include <QStringList>
#include <QPixmap>

#ifndef PICTURELISTMODEL_H_
#define PICTURELISTMODEL_H_
class PictureListModel : public QAbstractListModel
{
	Q_OBJECT;
public:
	PictureListModel(QObject *parent = 0);

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	bool removeRows(int row, int count, const QModelIndex &parent);
	int rowCount(const QModelIndex &parent) const;

	void addPictures(const QString directory);

private:
	QList<QPixmap> pixmaps;
	QStringList pictureFiles;
};

#endif /* PICTURELISTMODEL_H_ */
