#include "webPage.h"

#include <QCoreApplication>
#include <QStringList>
#include <stdio.h>
#include <QDebug>
#include <QFileInfo>

#include <QtCore/QMetaEnum>
#include <QtCore/QSettings>

#include <QtGui/QDesktopServices>
#include <QtGui/QFileDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QFileIconProvider>

#include <QtCore/QDebug>

#include <QtWebKit/QWebSettings>











webPage::webPage(QObject *parent) :
	QWebPage(parent)
{
	connect(this, SIGNAL(unsupportedContent(QNetworkReply *)),
			this, SLOT(handleUnsupportedContent(QNetworkReply *)));
	this->setForwardUnsupportedContent(true);
	Downloadthradinit();
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
	//	connect(this, SIGNAL(adddownloadurl(int,double,int,int,QString)), downloadthread , SLOT(adddownloadurl(int,double,int,int,QString)));
}


void webPage::handleUnsupportedContent(QNetworkReply *reply)
{
	//	downloadcount ++;
	if (!reply || reply->url().isEmpty())
		return;
	QVariant header = reply->header(QNetworkRequest::ContentLengthHeader);
	bool ok;
	int size = header.toInt(&ok);
	if (ok && size == 0)
		return;

/*
	downloadthread[downcount] = new Downloadthread;
	downloadthread[downcount]->downurllist.append(reply->url().toString());
	downloadthread[downcount]->start();
	*/
/*
	downcount ++;
	downloadthread[downcount]->startNextDownload(QUrl::fromEncoded(downloadthread[downcount]->downurllist.takeFirst().toLocal8Bit())); 
	*/
	/*
	if(downloadsign)
	{
		//		qDebug() << downurllist.size();
		downloadsign = 0;
	} else
	{
		return;
	}
	*/
	qDebug() << "webPage::handleUnsupportedContent downurllist.append";
	downurllist.append(reply->url().toString());
	if(downloadsign)
	{
		//		qDebug() << downurllist.size();
		downloadsign = 0;
		startNextDownload(QUrl::fromEncoded(downurllist.takeFirst().toLocal8Bit())); 
	}
}


QString webPage::saveFileName(const QUrl &url)
{
	QString path = url.path();
	basename = QFileInfo(path).fileName();

	if (basename.isEmpty())
		basename = "download";
//	QString home = QDir::homePath();
	/*
	QString home = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
	home += "download";
	if(QDir::exists("home"))
	{
		basename += home;
	} else {
		QDir::mkdir(home);
		basename += home;
	}
*/
	savedir = "/home/acanoe/download/";
	savefile = savedir  + basename;

	if (QFile::exists(savefile)) {
		// already exists, don't overwrite
		int i = 0;
		basename += '.';
		while (QFile::exists(savedir + basename + QString::number(i)))
			++i;

		basename += QString::number(i);
	}else{

	}

	return savedir + basename;
}


void webPage::startNextDownload(QUrl url)
{

	qDebug() << "url" <<url ;

	filename = saveFileName(url);
	/*
	path = "/home/acanoe/download/";
	QString save = "";
	save = path + filename;
	*/

	qDebug() << "filename" << filename;
	output.setFileName(filename);

	if (!output.open(QIODevice::WriteOnly)) {
		fprintf(stderr, "Problem opening save file '%s' for download '%s': %s\n",
				qPrintable(filename), url.toEncoded().constData(),
				qPrintable(output.errorString()));

		return;                 // skip this download
	}
	downcount ++;
	emit addstartdownload(downcount,speed,percent,stat,basename);

	QNetworkRequest request(url);
	manager[downcount] = new QNetworkAccessManager;

	currentDownload[downcount] = manager[downcount]->get(request);

	connect(currentDownload[downcount], SIGNAL(readyRead()),
			SLOT(downloadReadyRead()));
	connect(currentDownload[downcount], SIGNAL(downloadProgress(qint64,qint64)),
			SLOT(downloadProgress(qint64,qint64)));
	connect(currentDownload[downcount], SIGNAL(finished()),
			SLOT(downloadFinished()));

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
	emit adddownloadurl(downcount,speed,percent,stat,basename);
}

void webPage::downloadReadyRead()
{
	output.write(currentDownload[downcount]->readAll());
}

void webPage::downloadFinished()
{
	output.close();
	qDebug() << "downloadFinished" << "downcount = "  << downcount;


	emit adddownloadurl(downcount,speed,100,stat,basename);
	emit downloadurlfinished(downcount,ADB_INSTALL,0,savedir + basename); 
	beforetime = 0;

	if(downurllist.size())
	{
		startNextDownload(QUrl::fromEncoded(downurllist.takeFirst().toLocal8Bit())); 
		qDebug() << "download next url";
	}else {
		downloadsign = 1;
	}
}
