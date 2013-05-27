#ifndef DOWNLOADPTHREAD_H 
#define DOWNLOADPTHREAD_H 

#include <QProcess>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QImage>
#include <QTcpSocket>
#include <QThread>
#include <QIcon>
#include <QDebug>
#include <QDateTime>
#include <QTextCodec>
//#include "../widgets/webPage.h"
#include "../classes/downloadmanager.h"

#define DISCONNECTED 0
#define DEVICE 1
#define RECOVERY 2
#define FASTBOOT 3

#define READDOWNLOAD 0
#define DOWNLOADING  1 
#define DOWNLOADED	 2
#define CANCEL		 3
#define INSTALLING   4
#define INSTALLED    5


class DownloadThread: public QThread
{
	Q_OBJECT
	public:
		QList<QString> downloadlist;
		void run();
	private:

		int	cmdinfo = 0;
		int limit	= 0;
		int downloadcount = 0; 
		QString url = "";

//		webPage *web;
//		DownloadManager *urlmanager[5];
		DownloadManager *urlmanager;

		QStringList arguments;
signals:
		void uirefresh(int);
		private slots:

			void downloadinfo(int,QString,QString,QString, int,int);
		void adddownloadurl(int,QString);
	protected:
};

#endif

