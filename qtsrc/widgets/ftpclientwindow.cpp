#include "ftpclientwindow.h"
#include "ui_ftpclientwindow.h"
#include <QPixmap>
#include <QListWidgetItem>
#include <QIcon>
#include <iostream>

FtpClientWindow::FtpClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FtpClientWindow)
{
    ui->setupUi(this);
    ui->listWidget->clear();
    ui->listWidget->setEnabled(true);

    const QIcon icon = QIcon(":/images/cdtoparent.png");
    ui->upwardBtn->setIcon(icon);

    configWidget();     /* 初始化控件的属性 */
    initConnection();   /* 初始化信号与槽 */
}

/* 初始化信号与槽 */
void FtpClientWindow::initConnection()
{
    /* FTP主机、端口、用户名、密码 */
    connect(ui->ftpHostLE, SIGNAL(editingFinished()), this, SLOT(ftpHostChanged()));
    connect(ui->ftpPortLE, SIGNAL(editingFinished()), this, SLOT(ftpPortChanged()));
    connect(ui->usernameLE, SIGNAL(editingFinished()), this, SLOT(ftpUserChanged()));
    connect(ui->passwordLE, SIGNAL(editingFinished()), this, SLOT(ftpPwdChanged()));

    /* 退出 */
//    connect(ui->exitBtn, SIGNAL(clicked()), this, SLOT(mainWindowQuit()));

    /* FTP登陆 */
    connect(ui->linkBtn, SIGNAL(clicked()), this, SLOT(ftpConnect()));

    /* 接收列表项 */
    connect(&ftpclient, SIGNAL(cmdAddToList(QUrlInfo)), this, SLOT(addToList(QUrlInfo)));

    /* 文件或文件夹被双击 */
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(DoubleClicked(QListWidgetItem*)));

    /* 下载按钮 */
    connect(ui->downloadBtn, SIGNAL(clicked()), this, SLOT(callDownload()));
	/* 状态转换 */
	connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), 
			this, SLOT(switchDownloadBtn(QListWidgetItem*)));
	/* 返回到上级目录 */
	connect(ui->upwardBtn, SIGNAL(clicked()), this, SLOT(changeToParrent()));
}

/* 返回上一级目录 */
void FtpClientWindow::changeToParrent()
{
	clearMemory(listItemCtn);
	ui->listWidget->clear();
	listItemCtn.clear();
	ftpclient.changeDir("..");
}

void FtpClientWindow::clearMemory(QList<QListWidgetItem*> &listItemCtn)
{
	QListWidgetItem *item;
	QList<QListWidgetItem*>::iterator it;
	
	it = listItemCtn.begin();
	while (it != listItemCtn.end())
	{
		item = *it;
		if (item != NULL)
		{
			delete item;
			item = NULL;
		}
		++it;
	}
	static int a = 0;
	qDebug() << "delete times: " << ++a << endl;
}

bool FtpClientWindow::isDir(const QString &str) const
{
	return (ftpclient.isDir(str));
}

/* 初始化控件的属性 */
void FtpClientWindow::configWidget()
{
    ui->passwordLE->setEchoMode(QLineEdit::Password);

//    ui->ftpHostLE->setText("192.168.1.204");
    ui->ftpHostLE->setText("127.0.0.1");
    ui->ftpPortLE->setText("2222");
    ui->usernameLE->setText("a");
    ui->passwordLE->setText("a");
}

void FtpClientWindow::switchDownloadBtn(QListWidgetItem *item)
{
	QString filename;

	filename = item->text();
	if (this->isDir(filename))
	{
		ui->downloadBtn->setEnabled(false);
	}
	else
	{
		ui->downloadBtn->setEnabled(true);
	}
}
/* 下载选中的文件 */
void FtpClientWindow::callDownload()
{
	QString str;

	str = ui->listWidget->currentItem()->text();	/* filename */
	if (isDir(str) == false)
	{
		downLoadFile(str);
	}
}

/* 通在ftpclient下载文件filename */
void FtpClientWindow::downLoadFile(const QString &filename)
{
	ftpclient.downloadFile(filename);
}

/* 文件或文件夹被双击 */
void FtpClientWindow::DoubleClicked(QListWidgetItem *item)
{
	QString dir, filename, str;

	str = item->text();
	if (isDir(str))
	{
		dir = str;
		/* 清除列表前释放内存 */
		clearMemory(listItemCtn);
		ui->listWidget->clear();	/* 清除当前的列表, 以便显示新的 */
		listItemCtn.clear();
		ftpclient.changeDir(dir);
	}
	else
	{
		filename = str;
		downLoadFile(filename);
	}
}

/**
 * @brief	FTP调用list()时, 自动发出listInfo(QUrlInfo)信号
 *
 * @param	urlInfo	: 发送过来的Url信息
 */
void FtpClientWindow::addToList(const QUrlInfo &urlInfo)
{
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);

    item->setText(urlInfo.name().toLatin1());	/* 在listWidget中显示的名字 */  // toLatin1  转换中文乱码
//	qDebug() << urlInfo.name().toLatin1();
    const QIcon icon = QIcon(urlInfo.isDir() ? "/home/acanoe/qt/androidmanager/qtsrc/image/dir.png" : "/home/acanoe/qt/androidmanager/qtsrc/image/file.png");
	listItemCtn.append(item);

    item->setIcon(icon);
    ui->listWidget->addItem(item);
}

void FtpClientWindow::mainWindowQuit()
{
    ftpclient.ftpLogout();
//    close();
}

/* 连接FTP */
void FtpClientWindow::ftpConnect()
{

    ftpclient.ftpLogout();
    ftpHostChanged();
    ftpPortChanged();
    ftpUserChanged();
    ftpPwdChanged();
    ftpclient.ftpConnect(); /* FTP登陆 */
}

void FtpClientWindow::ftpHostChanged()
{
    ftpclient.setServerName(ui->ftpHostLE->text());
}

void FtpClientWindow::ftpPortChanged()
{
    ftpclient.setServerPort(ui->ftpPortLE->text());
}

void FtpClientWindow::ftpUserChanged()
{
    ftpclient.setUserName(ui->usernameLE->text());
}

void FtpClientWindow::ftpPwdChanged()
{
    ftpclient.setPwd(ui->passwordLE->text());
}


FtpClientWindow::~FtpClientWindow()
{
    delete ui;
}
