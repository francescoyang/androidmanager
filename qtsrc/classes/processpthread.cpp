#include "processpthread.h"

void ProcessThread::run()
{
	QProcess *phone=new QProcess(this);
	QString adbpath = "./bin/adb";
	QString command;
	QString outputLines;
	/*
	phone->start("./bin/adb start-server");
	phone->waitForFinished(30000);
	qDebug() << phone->readAll();

	*/
	while(1)
	{
		switch(cmdtype)
		{
			case ADB_UNINSTALL:
				command = adbpath + " shell pm uninstall -k " + adbargv;
				qDebug()<<"Phone::getFileList() - "<< command;
				phone->start(command);
				phone->waitForFinished(-1);
				outputLines=phone->readAll();
				if (outputLines.contains("Success"))
				{
					phone->terminate();
					emit adbresult(cmdtype,adbcount,SUCCESS);
				}else{
					emit adbresult(cmdtype,adbcount,FAILURE);
				}
				cmdtype = 0;
				break;

			case ADB_INSTALL:
				command = adbpath + " install -r " + adbargv;
				qDebug()<<"Phone::getFileList() - "<< command;
				phone->start(command);

				phone->waitForFinished(-1);
				outputLines=phone->readAll();
				if (outputLines.contains("Success"))
				{
					phone->terminate();
					emit adbresult(cmdtype, adbcount,SUCCESS);
				}else{
					emit adbresult(cmdtype, adbcount,FAILURE);
				}

				cmdtype = 0;
				break;
			default:
				cmdtype = 0;
				break;
		}
		this->msleep(2000);
	}
}

void ProcessThread::addadbcmd(int cmdtype,int adbcount ,QString cmd)
{
	qDebug() << "ProcessThread::addadbcmd:" << cmdtype << "cmd:" << cmd;
	this->cmdtype	= cmdtype;
	this->adbcount	= adbcount;
	this->adbargv	= cmd;
}
