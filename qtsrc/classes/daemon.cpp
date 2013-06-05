#include <stdio.h>
#include <QDebug>
#include "daemon.h"
#include "pthread_api.h"
#include "manager_api.h"

Daemon::Daemon(QWidget* objwidget) :
	MainWidget((QObject*)objwidget)
{
}

Daemon::~Daemon(){
}

void Daemon::post_refresh(int cmd){
	AMEvent* event_refresh= new AMEvent(AMEVENT_REFRESH,cmd);
	QApplication::postEvent(MainWidget,event_refresh);
}

void Daemon::post_daemon(int cmd){
	AMEvent* event_devinit = new AMEvent(AMEVENT_DAEMON,cmd);
	QApplication::postEvent(MainWidget,event_devinit);
}
void Daemon:: recv_daemoninit()
{
	Connecttestinit();	
	Downloadthradinit();
}

void Daemon::Downloadthradinit()
{
	downloadthread = new DownloadThread;
	downloadthread->start();
	connect(downloadthread, SIGNAL(uirefresh(int)), this, SLOT(recv_uirefresh(int)));
}
void Daemon::Connecttestinit()
{
	connecttest = new ConnectThread;
	connecttest->start();
	connect(connecttest, SIGNAL(connectionChanged(int,QString)), this, SLOT(slotConnectionChanged(int,QString)));
}

void Daemon::recv_uirefresh(int cmd)
{
	qDebug() << "Daemon::recv_uirefresh ::::::::::" << cmd;
	post_refresh(cmd);
}

int Daemon::checkapp()
{
	QProcess *phone=new QProcess;
	QString outputLines;

	phone->start("./bin/adb shell ls /data/app/ | grep com.acanoe.phonemanager");
	phone->waitForFinished(30000);
	outputLines = phone->readAll();
	if (outputLines.contains("com.acanoe.phonemanager"))
	{
		qDebug() << "app version correct" << outputLines;
		outputLines = "";
		return 1;
	}else {
		qDebug() << outputLines;
		phone->start("./bin/adb  install ./bin/phonemanager.apk");
		phone->waitForFinished(30000);
		c_delay(2);
		outputLines = phone->readAll();
		if (outputLines.contains("Success"))
		{
			c_delay(2);
			qDebug() << outputLines;
			outputLines = "";
			return 1;
		} else {
			qDebug() << outputLines;
			outputLines = "";
			return 0;
		}
		outputLines = "";
		return 1; 
	}

}

void Daemon::slotConnectionChanged(int state,QString serialNumber)
{
	int i = 0;
	switch(state)
	{
		case DISCONNECTED:
			printf("disconnected \n");
			//			this->serialNumber.clear();
			break;
		case DEVICE:
			qDebug() << "The DEVICE is = " << state << serialNumber;
			MUTEX = 1;
			post_daemon(FIND);
			if(checkapp() >= 1)
			{
				qDebug() << "start create main thread";
				main_thread_init();
				for(i = 0; i < 100; i++)
				{
					post_daemon(WAITDATA);
					if(waitdata())
					{
						FINDDEVICE = 0;
						post_daemon(DATA_READY);
						break;
					}
					c_delay(1);
				}
			} else {
				qDebug() << "install clent fair";
				//	post_daemon(INSTALLAPP);
			}
			break;
		case RECOVERY:
			qDebug() << "The RECOVERY is = " << state << serialNumber;
			break;
		case FASTBOOT:
			c_delay(1);
			if(MUTEX  && (serialNumber =="" || serialNumber == "????????????"))
			{
				MUTEX = 0;
				printf("REMOVE_USB\n");
				allpthread_exit();
				post_daemon(REMOVE_USB);
				/*
				if(!find_devices()){
					printf("you remove a android device\n");
				}
				*/
			}
			break;
		default:
			break;
	}
}
void Daemon::customEvent(QEvent* e){
	AMEvent* ame = dynamic_cast<AMEvent*>(e);
	switch (ame->type()){
		case AMEVENT_DAEMON:
			recv_daemoninit();
			break;
		default:
			break;
	}
}
