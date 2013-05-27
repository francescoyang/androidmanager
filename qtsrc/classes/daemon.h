#ifndef JPTIMER_H
#define JPTIMER_H

#include "classes/downloadpthread.h"
#include <QObject>
#include <QEvent>
#include <QApplication>
#include <QCoreApplication>
#include <QMainWindow>

#include "../amevent.h"
#include "../connectionthread.h"
#define ADD_USB		1
#define REMOVE_USB	0

#define DISCONNECTED 0
#define DEVICE 1
#define RECOVERY 2
#define FASTBOOT 3

typedef struct tag_timerdata{
	int cmd;
	char time[16];
	int status;
}timerdata_t;

class Daemon : public QObject
{
	Q_OBJECT
	public:
		Daemon(QWidget*); 
		~Daemon();
		void Downloadthradinit();

	private:

		void post_refresh(int cmd);
		void post_daemon(int cmd);

		void recv_daemoninit();
//		void recv_daemon(int);

		void Connecttestinit();	
		int checkapp();
	private:
		//MainThread object
		//	ManageWindow* MainWidget;
		QObject* MainWidget;
		timerdata_t timerdata;
		ConnectThread  *connecttest;
		DownloadThread *downloadthread;

		QString serialNumber;
		unsigned int timercount;
		int FINDDEVICE  = 0;
		int MUTEX	= 0;
		private slots:
			void slotConnectionChanged(int,QString);
			void recv_uirefresh(int);

	protected:
		void customEvent(QEvent*);

};

#endif
