#ifndef DOWNLOADLIST 
#define DOWNLOADLIST 

#include <QString>
#include <QUrlInfo>
#include <QHash>
#include <QtGui>

class QListWidgetItem;

namespace Ui {
class UiDownlist;
}

class Downloadlist: public QWidget
{
    Q_OBJECT
    
public:
    explicit Downloadlist(QWidget *parent = 0);
    ~Downloadlist();
    Ui::UiDownlist *ui;
signals:

private slots:
		void refreshdowninfo(int,double,int,int,QString);
   
private:

private:
};

#endif // FTPCLIENTWINDOW_H
