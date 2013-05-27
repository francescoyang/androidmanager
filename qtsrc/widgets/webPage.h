#ifndef WEBPAGE_H
#define WEBPAGE_H


//#include "../classes/downloadpthread.h"
//#include "../classes/downloadmanager.h"

#include <QWebPage>
#include <QtNetwork/QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <QTime>
#include <QThread>
#include <QSettings>
//#include "ui_downloaditem.h"
#define MAXLIST 10000

typedef struct __downloadindex{
	int percent;
	int stat;
	double speed;
	QString filename;
}downloadindex_t;

typedef struct __alldownloadinfo{
	int downcount;
	downloadindex_t get_info[MAXLIST];
}alldownloadinfo_t;

#define SUCCESS			1
#define FAILURE			0

#define ADB_INSTALL		1
#define ADB_UNINSTALL	2
#define ADB_DEVICES		3
#define ADB_PUSH		4 
#define ADB_PULL		5
#define ADB_CHECKVERSION	6
#define ADB_SENDMMS			7	






class Downloadthread: public QThread
{
	Q_OBJECT
	public:
		void run();
		QStringList downurllist;
		void startNextDownload(QUrl);
	public:
		QString saveFileName(const QUrl &url);
	private:
		int iteration = 0;
		int downloadsign= 1;
		int beforetime = 0;


		int downcount = -1;
		QString filename;
		int percent;
		int stat;
		double speed;

		qint64 value;
		qint64 maximum;


		QNetworkAccessManager *managertest ;
//		QNetworkReply reply;
		QNetworkRequest *requesttest;


		//		QNetworkReply *currentDownload;
		QNetworkReply *currentDownload[10000];
		QFile output;
		QTime downloadTime;

		QNetworkAccessManager *manager;
		//    TextProgressBar progressBar;


signals:
		void adddownloadurl(int,double,int,int,QString);
		void addstartdownload(int,double,int,int,QString);

		private slots:
		void downloadReadyRead();
		void downloadProgress(qint64, qint64);
		void downloadFinished();

};


class webPage : public QWebPage
{
	Q_OBJECT


	public:
		explicit webPage(QObject *parent = 0);
		Downloadthread *downloadthread[1000];
		QString saveFileName(const QUrl &url);
		alldownloadinfo_t alldownloadinfo;
	private:
		bool m_requestFileName;
		int iteration = 0;
		int downloadsign= 1;
		int beforetime = 0;


		QStringList downurllist;
		int downcount = -1;
		QString filename;
		QString path;
		int percent;
		int stat;
		double speed;

		qint64 value;
		qint64 maximum;
		QList<QString> downloadwait;

		void startNextDownload(QUrl);
		//		QNetworkReply *currentDownload;
		QNetworkReply *currentDownload[10000];
		QFile output;
		QTime downloadTime;

		QNetworkAccessManager *manager[10000];
		//    TextProgressBar progressBar;

		void Downloadthradinit();

signals:
		void loadLink(const QUrl & url);
		void openLink(const QUrl & url);
		void adddownloadurl(int,double,int,int,QString);
		void addstartdownload(int,double,int,int,QString);
		void downloadurlfinished(int,int,QString);

		private slots:
			void handleUnsupportedContent(QNetworkReply *reply); 
		void downloadReadyRead();
		void downloadProgress(qint64, qint64);
		void downloadFinished();


	protected:
		bool acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type);
};

#endif // WEBPAGE_H
