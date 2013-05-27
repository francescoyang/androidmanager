#ifndef PROCESSPTHREAD_H
#define PROCESSPTHREAD_H
#include <QProcess>
#include <QThread>
#include <QIcon>
#include <QDebug>

#define SUCCESS			1
#define FAILURE			0

#define ADB_INSTALL		1
#define ADB_UNINSTALL	2
#define ADB_DEVICES		3
#define ADB_PUSH		4 
#define ADB_PULL		5
#define ADB_CHECKVERSION	6
#define ADB_SENDMMS			7	


class ProcessThread: public QThread
{
	Q_OBJECT
	public:
		void run();
	private:
		int adbcount = 0;
		int cmdtype  = 0;
		QString adbargv;
		QString output = NULL;
		QStringList CmdList;

		private slots:
			void addadbcmd(int,int,QString);

signals:
		void adbresult(int,int,int);
	protected:
};
#endif
