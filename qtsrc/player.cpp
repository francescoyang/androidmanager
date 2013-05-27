#include <QtGui>
#include "player.h"

Player::Player(QWidget * parent)
	: QWidget(parent)
{

	renderTarget = new QWidget(this);
	renderTarget->setStyleSheet(
			"background-image: url(:/home/acanoe/qt/androidmanage/qtsrc/image/background.jpg)"
			);
	renderTarget->setAttribute(Qt::WA_OpaquePaintEvent);

//    ui->W_P->setAttribute(Qt::WA_OpaquePaintEvent);

	mplayerProcess = new QProcess(this);
	connect(mplayerProcess, SIGNAL(started()), this, SIGNAL(started()));
	connect(mplayerProcess, SIGNAL(error(QProcess::ProcessError)), this, SIGNAL(error(QProcess::ProcessError)));
	connect(mplayerProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SIGNAL(finished(int, QProcess::ExitStatus)));
	connect(mplayerProcess, SIGNAL(readyReadStandardOutput()), this, SIGNAL(readyReadStandardOutput()));
	

}

Player::~Player()
{}
	
void Player::play(const QString &fileName)
{
	QStringList args;
	args << tr("-slave");
	args << "-quiet";
	args << "-zoom";
    args << tr("-wid") << QString::number(renderTarget->winId());
	args << fileName;
	mplayerProcess->start(tr("/usr/bin/mplayer"), args);
//	emit started();
}

void Player::controlCmd(const QString &cmd)
{
	mplayerProcess->write(cmd.toLatin1());
}

void Player::resizeEvent(QResizeEvent * event)
{
	renderTarget->resize(event->size());
}
