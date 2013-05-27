#include "downloadpthread.h"
#include "manager_api.h"
#include <QSettings>
#include <QTextCodec>

void DownloadThread::run()
{
	QString savedir  = "";
	/*
	   web =new webPage(this);
	   QObject::connect(this->web, SIGNAL(adddownloadurl(int,QString)), this, SLOT(adddownloadurl(int,QString)));
	   */
	while(1)
	{
		//		limit ++;
		//		qDebug() << "this->url:" << this->url;

		cmdinfo = refreshinfo();
		if(cmdinfo)
		{
			emit uirefresh(cmdinfo);
		}

		if (this->url == "")
		{
			this->msleep(2000);
			continue;
		} else {
/*
			QStringList urllist;
			urllist.append("http://cdn.market.hiapk.com/data/upload/marketClient/HiMarket3.6.3_0418190625_1.apk");
			qDebug() << urllist;

			DownloadManager manager;
			manager.append(urllist);
			*/
			/*

			   QStringList urllist;
			   urllist.append(url);
			   qDebug() << urllist;

			   urlmanager = new DownloadManager;
			   this->urlmanager->append(urllist);

			   this->msleep(2000);
			   qDebug() << "this url will be NULL";
			   break;
			   */
			this->url = "";
		}
		this->msleep(2000);
	}
}


void DownloadThread::adddownloadurl(int downloadcount,QString url)
{
	qDebug() << "DownloadThread::downloadcount:" << downloadcount << "url:" << url;
	this->url = url;
	this->downloadcount = downloadcount;
}

void DownloadThread::downloadinfo(int count ,QString name,QString size,QString pecent, int speed,int state)
{
	qDebug() << "webPage::downloadfinished";
}
