#ifndef __PLAYER_H_
#define __PLAYER_H_

#include <QWidget>
#include <QProcess>
#include <QtGui>

QT_BEGIN_NAMESPACE
class QString;
class QPushButton;
class QProcess;
class ManageWindow;
QT_END_NAMESPACE


class Player : public QWidget
{
	Q_OBJECT

public:
	Player(QWidget * parent = 0);
	~Player();


	void play(const QString &fileName);
	void controlCmd(const QString &cmd);

signals:
	void started();
	void error(QProcess::ProcessError);
	void finished(int, QProcess::ExitStatus);
	void readyReadStandardOutput();

protected:
	void resizeEvent(QResizeEvent * event);

private:

	ManageWindow *ui;
	QWidget *renderTarget;
	QProcess *mplayerProcess;
};

#endif // __PLAYER_H_
