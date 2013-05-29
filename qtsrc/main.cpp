#include <QTextCodec>
#include <QSettings>
#include <QDebug>
#include <QApplication>
#include "managewindow.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	system("./bin/adb start-server");

	QStringList args = qApp->arguments();
	if (args.count() > 1)
	{
		/*
		if (args.at(1).endsWith(".apk"))
		{
			App *app = NULL;
			app = FileWidget::getAppInfo(args.at(1));
			appInfo *appInfoDialog = new appInfo(app);
			return appInfoDialog->exec();
		}
		if (args.at(1) == "-install")
		{
			QList<App> appList;
			App *app = NULL;
			for (int i = 2; i < args.count(); i++)
			{
				if (args.at(i).endsWith(".apk"))
				{
					QString fileName = args.at(i);
					app = FileWidget::getAppInfo(fileName);
					if (app != NULL)
						appList.append(*app);
				}
			}
			appDialog *appDialogInstall = new appDialog(appList, appDialog::Install, appDialog::None);
			return appDialogInstall->exec();
		}
		*/
		if (args.at(1) == "-logcat")
		{
			LogcatDialog *logcat = new LogcatDialog;
			return logcat->exec();
		}
	}




	ManageWindow w;
	/*
	   QProcess *phone=new QProcess;
	   phone->start("./bin/adb start-server");
	   phone->waitForFinished(30000);
	   qDebug() << phone->readAll();
	   delete phone;
	   */


	//	addmanager = new DownloadManager;
	/*
	   QStringList urllist;
	   urllist.append("http://cdn.market.hiapk.com/data/upload/marketClient/HiMarket3.6.3_0418190625_1.apk");
	   qDebug() << urllist;

	   DownloadManager manager;
	   manager.append(urllist);
	   */



	w.move ((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);
	w.show();

	return a.exec();
}
