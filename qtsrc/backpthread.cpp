#include <time.h>
#include "backpthread.h"
#include "amevent.h"
#include "manager_api.h"
#include "pthread_api.h"
#include "typestruct_api.h"

allappinfo_t backappinfo;

AMEvent::AMEvent(QEvent::Type etype,int re) :
	QEvent(etype),ret(re)
{
	
}

AMEvent::~AMEvent(){

}

int AMEvent::msg() const{
	return ret;
}


//-------------------------------------------


Backthread::Backthread(QWidget* objwidget) :
	MainWidget((QObject*)objwidget)
{
}

Backthread::~Backthread(){
}

/*
void Backthread::post_exit(int res){
	AMEvent* event_exit= new AMEvent(AMEVENT_EXIT,res);
	QApplication::postEvent(MainWidget,event_exit);
}
*/
void Backthread::post_softinit(int res){
	AMEvent* event_softinit = new AMEvent(AMEVENT_INITEVENT ,res);
	QApplication::postEvent(MainWidget,event_softinit);
}

void Backthread::post_usbevent(int res){
	AMEvent* event_devinit = new AMEvent(AMEVENT_USBEVENT ,res);
	QApplication::postEvent(MainWidget,event_devinit);
}

void Backthread::post_uninsatll(int res){
	AMEvent* event_uninstall= new AMEvent(AMEVENT_UNINSTALL,res);
	QApplication::postEvent(MainWidget,event_uninstall);
}

void Backthread::post_insatll(int res){
	AMEvent* event_install= new AMEvent(AMEVENT_INSTALL,res);
	QApplication::postEvent(MainWidget,event_install);
}

void Backthread::post_sendmms(int res){
	AMEvent* event_sendmms= new AMEvent(AMEVENT_INSTALL,res);
	QApplication::postEvent(MainWidget,event_sendmms);
}
void Backthread::recv_install(int cmd)
{
	printf("recv_install\n");
	toinstallapp();
	post_insatll(1);
}
void Backthread::recv_sendmms(int cmd)
{
	tosendmms();
}
void Backthread::recv_uninstall(int cmd)
{
	getappinfo(&backappinfo);

	printf("will be uninstall %s\n",backappinfo.get_info[cmd].apppackname);
	if(app_uninstall(backappinfo.get_info[cmd].apppackname))
	{
		post_uninsatll(1);
	}else {
		post_uninsatll(0);
	}
}
void Backthread::recv_exit(int cmd)
{
	system_exit();
}
void Backthread::recv_softinit(int cmd)
{
	tmpclean();
//	usb_thread_init();
}

void Backthread::recv_refresh(int cmd)
{
	regetinfo(cmd);
}

void Backthread::recv_usbevent(int cmd){
//	post_usb(USB_ADD);
}
void Backthread::customEvent(QEvent* e){
	AMEvent* jpe = dynamic_cast<AMEvent*>(e);
	switch (jpe->type()){

		case AMEVENT_REFRESH:
			recv_refresh(jpe->msg());
			break;
		case AMEVENT_INSTALL:
			recv_install(jpe->msg());
			break;

		case AMEVENT_SENDMMS:
			recv_sendmms(jpe->msg());
			break; 

		case AMEVENT_UNINSTALL:
			recv_uninstall(jpe->msg());
			break;
		case AMEVENT_INITEVENT:
			recv_softinit(jpe->msg());
			break;
		case AMEVENT_EXIT:
			recv_exit(jpe->msg());
			break;
		case AMEVENT_USBEVENT:
			recv_usbevent(jpe->msg());
			break;
		default:
			break;
	}
	return;
}
