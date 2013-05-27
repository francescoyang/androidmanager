#include "ftpclient.h"
#include <QListWidgetItem>
#include <QIcon>

Ftpclient::Ftpclient(QObject *parent) :
    QObject(parent)
{
    connected = false;
    initConnection();
}

void Ftpclient::initConnection()
{
    /* FTP连接与登陆 */
    connect(&ftp, SIGNAL(commandStarted(int)), this, SLOT(ftpcommandStarted(int)));
    connect(&ftp, SIGNAL(commandFinished(int,bool)), this, SLOT(ftpcommandFinished(int,bool)));

	/* FTP调用list()时, 自动发出listInfo(QUrlInfo)信号 */
    connect(&ftp, SIGNAL(listInfo(QUrlInfo)), this, SLOT(addToList(QUrlInfo)));
}

void Ftpclient::updateProgressBar(int done, int total)
{
	progressDlg->setValue(done);
	if (done == total)
	{
		file->flush();
		file->close();
		delete file;
		file = NULL;
	}
}

void Ftpclient::downloadFile(const QString &filename)
{
	file = new QFile(filename);
	if (!file->open(QIODevice::ReadWrite))
	{
		qDebug() << "无法打开文件!" << endl;
		return;
	}
	qDebug() << "下载中..." << endl;
	qDebug() << "当前路径为:" << getCurrentPath() << endl;

	ftp.get(filename, file);
}

bool Ftpclient::isDir(const QString &str) const
{
	return this->isDirHash[str];
}

/* 改变目录 */
void Ftpclient::changeDir(const QString &dir)
{
	QString cur;
	int index, flg;

	cur = getCurrentPath().trimmed();
	index = cur.lastIndexOf('/');
	qDebug() << "进入下一步前路径为: " << cur << "最后一个分隔符位置为: " << index << endl;
	if (dir == tr(".."))	/* chanage to parrent */
	{
		if (index > 0)
		{
			cur = cur.left(index);
			setCurrentPath(cur);
			flg = 1;
			qDebug() << "返回到: " << getCurrentPath() << endl;
		}
		else
		{
			cur = "/";
			setCurrentPath(cur);
			flg = 0;
			qDebug() << "返回到: " << getCurrentPath() << endl;
		}
	}
	else
	{
		cur = cur.append("/").append(dir);
		setCurrentPath(cur);
		flg = 2;		/* 返回到更深一层目录 */
		qDebug() << "返回到: " << getCurrentPath() << endl;
	}

	switch(flg)
	{
		case 0:
			ftp.cd(getCurrentPath());	/* 返回到根目录 */
			break;
		case 1:
			ftp.cd(getCurrentPath());	/* 返回上一层 */
			break;
		case 2:
			ftp.cd(dir);				/* 返回到根目录 */
			break;
	}
	ftp.list();
}

void Ftpclient::setCurrentPath(QString &path)
{
	curPath = path;
}

void Ftpclient::ftpConnect()
{
	QString str;

    qDebug() << "验证中..." << endl;
    qDebug() << "host:" << strSrvName << " port:" << strSrvPort << endl;
    qDebug() << "username:" << strUser << " password:" << strPwd << endl;

    qDebug() << strSrvName << endl;
    url = QUrl(strSrvName);
    qDebug() << url << endl;
    qDebug() << url.isValid() << endl;
    if (!url.isValid())
    {
        qDebug() << "请输入合法的FTP地址!";
        return;
    }

    /* 当前路径为空 */
	str = "";
    setCurrentPath(str);
    connectId = ftp.connectToHost(strSrvName, strSrvPort.toInt());
    loginId = ftp.login(strUser, strPwd);
}

/* 把目录加到列表中 */
void Ftpclient::addToList(const QUrlInfo &urlInfo)
{
	isDirHash[urlInfo.name()] = urlInfo.isDir();
    emit cmdAddToList(urlInfo);
}

void Ftpclient::ftpcommandStarted(int id)
{
    if (id == connectId)
    {
        qDebug() << "FTP连接中..." << endl;
    }
    else if (id == loginId)
    {
        connected = false;
        qDebug() << "FTP登陆中..." << endl;
    }
    else if (id == closeId)
    {
        qDebug() << "FTP退出中..." << endl;
    }
}

/* FTP主机的最简字符串 */
QString Ftpclient::getUrlStr(const QUrl &url)
{
	QString str;
	int index;

	str = url.toString().trimmed();
	index = str.lastIndexOf("/");
	if (index >= 0 && index < str.length())
	{
		str = str.left(index);
	}

	return str;
}

void Ftpclient::ftpcommandFinished(int id, bool error)
{
	QString str;

    if (error)
    {
        return;
    }

    if (id == connectId)
    {
        qDebug() << "FTP已连接!" << endl;
    }
    else if (id == loginId)
    {
        qDebug() << "FTP已登陆!" << endl;
        connected = true;
		ftp.list();

		/**
		 * @brief	url后面的最简形式， 方便获取路径
		 * 如：		"ftp.ntu.edu.tw/" --> "ftp.ntu.edu.tw"
		 */
		
		curPath = "";
        setCurrentPath(curPath);	/* 当前FTP所列的路径为 str */
		str = getCurrentPath();
        qDebug() << "目前的路径:" << getCurrentPath();
    }
    else if (id == closeId)
    {
        qDebug() << "FTP已退出!" << endl;
        connected = false;
    }
}

void Ftpclient::ftpLogout()
{
    if (connected == true)
    {
        closeId = ftp.close();
        connected = false;
    }
}

Ftpclient::~Ftpclient()
{
}
