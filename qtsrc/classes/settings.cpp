#include <QSettings>
#include "settings.h"

Mysetting::Mysetting(QSettings* objwidget)
{
}

Mysetting::~Mysetting(){
}

void Mysetting::mysettingdefault()
{
//	QSettings settings ("./etc/mysettings.ini", QSettings::IniFormat );
//	settings = new QSettings;

	QSettings settings("./etc/mysettings.ini", QSettings::IniFormat );

	settings.setValue( "downloadpath", "/home/acanoe/下载");
//	settings.setValue( "skin", "./etc/qss/abc.qss");
	settings.setValue("uninstallwarn", "YES");
	settings.setValue("installwarn", "YES");
}

void Mysetting::mysettinginit()
{
//	QSettings settings ("./etc/mysettings.ini", QSettings::IniFormat );
	settings.setValue ( "appversion", 1.0);
}

void Mysetting::setdaownloadpath(char *)
{

}
/*
	QList<Login> logins;
	for ( int i = 0; i < 10; ++i )
	{
		Login lgin;
		QString name ( "Name%1");
		lgin.userName = name.arg(i);
		name = "Pass%1";
		lgin.password = name.arg(i);
		logins.push_back ( lgin );
	}

	QSettings settings ("/home/acanoe/qt/test.ini", QSettings::IniFormat );

	settings.beginWriteArray("logins");
	for (int i = 0; i < logins.size(); ++i) {
		settings.setArrayIndex(i);
		settings.setValue("userName", logins.at(i).userName);
		settings.setValue("password", logins.at(i).password);
	}
	settings.endArray();

	settings.beginGroup ( "AnotherGroup");
	settings.setValue ( "test", 10 );
	settings.endGroup ();

	settings.beginGroup ("logins");
	settings.remove ("");
	settings.endGroup ();
	*/

	//	settings = Qsettings("Acanoe","androidmanager");

