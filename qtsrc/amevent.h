#ifndef JPEVENT_H
#define JPEVENT_H

#include <QObject>
#include <QEvent>
#include <QApplication>

#define SOFT_INIT 1
#define MONITOR_USB 2
#define START_DAEMON 0

const QEvent::Type AMEVENT_USBEVENT = (QEvent::Type)3001;
const QEvent::Type AMEVENT_INITEVENT = (QEvent::Type)3002;
const QEvent::Type AMEVENT_DAEMON= (QEvent::Type)3003;
const QEvent::Type AMEVENT_TEST= (QEvent::Type)3004;
const QEvent::Type AMEVENT_UNINSTALL= (QEvent::Type)3005;
const QEvent::Type AMEVENT_INSTALL= (QEvent::Type)3006;
const QEvent::Type AMEVENT_EXIT= (QEvent::Type)3007;
const QEvent::Type AMEVENT_SENDMMS= (QEvent::Type)3008;
const QEvent::Type AMEVENT_REFRESH= (QEvent::Type)3009;

class AMEvent : public QEvent
{
public:
	AMEvent(QEvent::Type, int);
	~AMEvent();

	int msg() const;

private:
	int ret;
};

#endif

