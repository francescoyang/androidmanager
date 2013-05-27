#include <QObject>
#include <QEvent>
#include <QApplication>
#include <QMainWindow>
#include <QCoreApplication>

#include "amevent.h"

//class Backthread : public QObject
class Backthread : public QObject
{
	Q_OBJECT
public:
	Backthread(QWidget*);
	~Backthread();

private:
	void post_softinit(int);
	void post_usbevent(int);
	void post_uninsatll(int);
	void post_insatll(int);
	void post_sendmms(int);

	void recv_softinit(int);
	void recv_usbevent(int);
	void recv_uninstall(int);
	void recv_install(int);
	void recv_exit(int);
	void recv_sendmms(int);
	void recv_refresh(int);



private:
//MainThread object
	QObject* MainWidget;

//linux api
	FILE* logfp;

protected:
	void customEvent(QEvent*);

};
