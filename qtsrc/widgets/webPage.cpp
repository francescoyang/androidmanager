#include "webPage.h"

#include <QCoreApplication>
#include <QStringList>
#include <stdio.h>
#include <QDebug>
#include <QFileInfo>

void Downloadthread::run()
{
}

webPage::webPage(QObject *parent) :
	QWebPage(parent)
{
	connect(this, SIGNAL(unsupportedContent(QNetworkReply *)),
			this, SLOT(handleUnsupportedContent(QNetworkReply *)));
	this->setForwardUnsupportedContent(true);


	//	connect(this,SIGNAL(loadLink(QUrl)),this,SLOT(urlChanged(const QUrl &)));
}

bool webPage::acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type){

	if(type==0){//如果是用户点击
		if(frame!=mainFrame()){ //如果不是在本窗口的连接
			qDebug() << "openlink"  << request.url();
			emit openLink(request.url());//发送打开新连接信号
		}else{
			qDebug() << "loadLink"  << request.url();
			emit loadLink(request.url());//发送点击连接信号
		}

	}
	return QWebPage::acceptNavigationRequest(frame, request, type);
}

void webPage::Downloadthradinit()
{
	/*
	   downloadthread = new DownloadThread;
	   downloadthread->start();
	//	connect(downloadthread, SIGNAL(uirefresh(int)), this, SLOT(recv_uirefresh(int)));
	connect(this, SIGNAL(adddownloadurl(int,double,int,int,QString)), downloadthread , SLOT(adddownloadurl(int,double,int,int,QString)));
	*/
}


void webPage::handleUnsupportedContent(QNetworkReply *reply)
{
	qDebug() << "handleUnsupportedContent   -----------" << &reply;
	//	downloadcount ++;
	if (!reply || reply->url().isEmpty())
		return;
	QVariant header = reply->header(QNetworkRequest::ContentLengthHeader);
	bool ok;
	int size = header.toInt(&ok);
	if (ok && size == 0)
		return;
	urllist.append(reply->url().toString());
	if(downloadsign)
	{
		//		qDebug() << urllist.size();
		startNextDownload(QUrl::fromEncoded(urllist.takeFirst().toLocal8Bit()));
		downloadsign = 0;
	} else
	{
		return;
	}
	//	startNextDownload(reply->url());
}


QString webPage::saveFileName(const QUrl &url)
{
	QString path = url.path();
	QString basename = QFileInfo(path).fileName();

	if (basename.isEmpty())
		basename = "download";

	if (QFile::exists(basename)) {
		// already exists, don't overwrite
		int i = 0;
		basename += '.';
		while (QFile::exists(basename + QString::number(i)))
			++i;

		basename += QString::number(i);
	}

	return basename;
}


void webPage::startNextDownload(QUrl url)
{

	qDebug() << "url" <<url ;

	filename = saveFileName(url);
	QString path = "/home/acanoe/download/";
	QString save = "";
	save = path + filename;

	qDebug() << "filename" << filename;
	output.setFileName(save);

	if (!output.open(QIODevice::WriteOnly)) {
		fprintf(stderr, "Problem opening save file '%s' for download '%s': %s\n",
				qPrintable(filename), url.toEncoded().constData(),
				qPrintable(output.errorString()));

		return;                 // skip this download
	}
	downcount ++;
	emit addstartdownload(downcount,speed,percent,stat,filename);

	QNetworkRequest request(url);

	currentDownload[downcount] = manager.get(request);

	connect(currentDownload[downcount], SIGNAL(readyRead()),
			SLOT(downloadReadyRead()));
	connect(currentDownload[downcount], SIGNAL(downloadProgress(qint64,qint64)),
			SLOT(downloadProgress(qint64,qint64)));
	connect(currentDownload[downcount], SIGNAL(finished()),
			SLOT(downloadFinished()));

	/*
	   currentDownload[downcount] = manager.get(request);

	   connect(currentDownload, SIGNAL(readyRead()),
	   SLOT(downloadReadyRead()));
	   connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
	   SLOT(downloadProgress(qint64,qint64)));
	   connect(currentDownload, SIGNAL(finished()),
	   SLOT(downloadFinished()));
	   */

	// prepare the output
	printf("Downloading %s...\n", url.toEncoded().constData());
	downloadTime.start();
}

void webPage::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{

	// calculate the download speed
	speed = bytesReceived * 1000.0 / downloadTime.elapsed();
	if (downloadTime.elapsed() - beforetime < 1000)
	{
		return;
	}

	beforetime = downloadTime.elapsed();
	qDebug() << "download time: " <<  downloadTime.elapsed()  << " beforetime " <<beforetime ;
	QString unit;
	if (speed < 1024) {
		unit = "bytes/sec";
	} else if (speed < 1024*1024) {
		speed /= 1024;
		unit = "kB/s";
	} else {
		speed /= 1024*1024;
		unit = "MB/s";
	}

	++iteration;

	if (bytesTotal> 0) {
		// we know the maximum
		// draw a progress bar
		percent = bytesReceived * 100 / bytesTotal;
	}
	//        int hashes = percent / 2;
	qDebug() << "speed: " << speed << " " << unit << "percent " << percent;
	emit adddownloadurl(downcount,speed,percent,stat,filename);
}

void webPage::downloadReadyRead()
{
	output.write(currentDownload[downcount]->readAll());
}
/*
   void webPage::downloadlist()
   {

   }
   */


void webPage::downloadFinished()
{
	output.close();
	qDebug() << "downloadFinished" << "downcount = "  << downcount;

	emit adddownloadurl(downcount,speed,100,stat,filename);
	beforetime = 0;
	downloadsign = 1;
	if(urllist.size())
	{
		qDebug() << "download next url";
		startNextDownload(QUrl::fromEncoded(urllist.takeFirst().toLocal8Bit()));
	}

	//	QString url =	//	qDebug() << url;
	/*
	   if(!urllist.isEmpty())
	   {
	   }
	   */
}
