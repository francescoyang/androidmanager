#include <QtGui>
#include <QFileDialog>
#include <QSettings>

#include "managewindow.h"
#include "player.h"
#include "ui_managewindow.h"

ManageWindow::ManageWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::ManageWindow)
{
	ui->setupUi(this);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

#if 0
	setStyleSheet(
			"QPushButton{border:groove gray;border-radius:10px;padding:2px 4px;}"
			"QPushButton{ color: white;}"
			/*"QPushButton{background-color:pink; color: white;}"*/
			"QPushButton:hover{background-color:green;}"
			"QPushButton:pressed{background:qlineargradient(x1:0,y1:0.5,x2:1,y2:0.5,"
			"stop:0 green,stop:0.5 cyan stop: 1 darkcyan)}");
#endif

	Makeconnect();
	CurrentWidget(CONNECT);
	//	ClassTestInit();
	UiToolInit();
	Mysettingsinit();

	ProcessThreadInit();
	BackQthreadInit();
	DaemonQthreadInit();
}


ManageWindow::~ManageWindow()
{
	delete ui;
}



void ManageWindow::UiToolInit()
{

	/*
	   QSettings settings;
	   QString sdk;

	   settings->setValue("sdkPath", "/home/acanoe/android_tool/android-sdk-linux/platform-tools/");

	   this->settingsWidget = new SettingsWidget(ui->P_Music);
	   this->fileWidget = new FileWidget(ui->P_Storage, this->settingsWidget);
	   this->appWidget = new AppWidget(ui->P_Test);
	   */

	setFixedSize(1020,700);
	setIcon();
	this->setWindowTitle("android manager 杨小军 自由软件");
	ui->Lab_info->setStyleSheet("font-size:22px;");

	/*
	   ui->centralWidget->setWindowOpacity(0.7);
	   ui->W_kouzhan->setWindowOpacity(0.7);
	   ui->P_Connect->setWindowOpacity(0.7);
	   */
	Animationinit();
	Refreshlabinit();
	//SetWordCode();
	LoadImage();
	LoadVideo();
	LoadMusic();
	LoadConnect();
	LoadApp();
	LoadMms();
	LoadSettings();
	LoadWebview();
	LoadBook();
	LoadDownloadlist();
	LoadFtpfilelist();
	LoadQmenu();




	video_player();
	//	slotTrans(90);
	//	Qssinit(1);
	connectinit();

}

void ManageWindow::connectinit()
{
	refreshsign.book = 1;
	refreshsign.mms	= 1;
	refreshsign.app	= 1;
	refreshsign.image= 1;
	refreshsign.video= 1;
	refreshsign.music= 1;

	ui->Pb_mem->setRange(0, 100);
	ui->Pb_mem->setValue(0);

	ui->Pb_sd->setRange(0, 100);
	ui->Pb_sd->setValue(0);

	m_anim->start();
	refresh_anim->stop();
	setui_clean();


	//	delete 	page;	
}

void ManageWindow::setIcon()
{
	setWindowIcon(QIcon(QLatin1String("./qtsrc/image/heart.svg")));
}

void ManageWindow::Refreshlabinit()
{
	ui->Lab_refresh->setHidden(true);
	refresh_anim = new Animation(ui->Lab_refresh, "pos");
	refresh_anim->setPathType((Animation::PathType)1);  // circle
	refresh_anim->setEasingCurve(QEasingCurve::Linear);
	/*
	   refresh_anim->setStartValue(QPointF(0, 0));
	   refresh_anim->setEndValue(QPointF(200, 200));  // circle
	   */

	refresh_anim->setStartValue(QPointF(450, 250));
	refresh_anim->setEndValue(QPointF(650, 450));
	refresh_anim->setDuration(1000);
	refresh_anim->setLoopCount(-1); // forever
}

void ManageWindow::Animationinit()
{
	m_anim = new Animation(ui->Lab_test, "pos");
	m_anim->setPathType((Animation::PathType)1);
	m_anim->setEasingCurve(QEasingCurve::Linear);
	/*
	   m_anim->setStartValue(QPointF(0, 0));
	   m_anim->setEndValue(QPointF(200, 200));  // circle
	   */

	m_anim->setStartValue(QPointF(0, 290));
	m_anim->setEndValue(QPointF(950, 290));
	m_anim->setDuration(3000);
	m_anim->setLoopCount(-1); // forever
	m_anim->start();
}
void ManageWindow::Qssinit(int argc)     //透明度
{
	//初始化样式，酷黑
	QFile file("./etc/qss/abc.qss");
	file.open(QFile::ReadOnly);
	styleSheet = QLatin1String(file.readAll());
	//	qDebug() << styleSheet;
	this->setStyleSheet(styleSheet);
	dlg->setStyleSheet(styleSheet);
	file.close();

}

//void ManageWindow::slotappclasschange(QString StyleString)     //透明度

void ManageWindow::slotappclasschange(int Appclass)     
{
	setui_appclass(Appclass);
}



void ManageWindow::StyleChange(int StyleString,QDialog *dialogsheet)     //透明度
{
	//	QFile file0("./etc/qss/abc.qss");
	QFile file0("./etc/qss/style0.qss");
	QFile file1("./etc/qss/style1.qss");
	QFile file2("./etc/qss/style2.qss");
	QFile file3("./etc/qss/style3.qss");
	QFile file4("./etc/qss/style4.qss");
	QFile file5("./etc/qss/style5.qss");

	switch(StyleString)
	{
		case 0:
			file0.open(QFile::ReadOnly);
			styleSheet = QLatin1String(file0.readAll());
			dialogsheet->setStyleSheet(styleSheet);
			file0.close();
			settings->setValue( "skin", 0);
			break;
		case 1:
			file1.open(QFile::ReadOnly);
			styleSheet = QLatin1String(file1.readAll());
			dialogsheet->setStyleSheet(styleSheet);
			file1.close();
			settings->setValue( "skin", 1);
			break;
		case 2:

			file2.open(QFile::ReadOnly);
			styleSheet = QLatin1String(file2.readAll());
			dialogsheet->setStyleSheet(styleSheet);
			file2.close();
			settings->setValue( "skin", 2);
			break;
		case 3:
			file3.open(QFile::ReadOnly);
			styleSheet = QLatin1String(file3.readAll());
			dialogsheet->setStyleSheet(styleSheet);
			file3.close();
			settings->setValue( "skin", 3);
			break;
		case 4:
			file4.open(QFile::ReadOnly);
			styleSheet = QLatin1String(file4.readAll());
			dialogsheet->setStyleSheet(styleSheet);
			file4.close();
			settings->setValue( "skin", 4);
			break;
		case 5:
			file5.open(QFile::ReadOnly);
			styleSheet = QLatin1String(file5.readAll());
			dialogsheet->setStyleSheet(styleSheet);
			file5.close();
			settings->setValue( "skin", 5);
			break;
		default:
			break;
	}
}

void ManageWindow::slotStyleChange(int StyleString)     //透明度
{
	//	QFile file0("./etc/qss/abc.qss");
	QFile file0("./etc/qss/style0.qss");
	QFile file1("./etc/qss/style1.qss");
	QFile file2("./etc/qss/style2.qss");
	QFile file3("./etc/qss/style3.qss");
	QFile file4("./etc/qss/style4.qss");
	QFile file5("./etc/qss/style5.qss");

	switch(StyleString)
	{
		case 0:
			file0.open(QFile::ReadOnly);
			styleSheet = QLatin1String(file0.readAll());
			this->setStyleSheet(styleSheet);
			dlg->setStyleSheet(styleSheet);
			file0.close();
			settings->setValue( "skin", 0);
			break;
		case 1:
			file1.open(QFile::ReadOnly);
			styleSheet = QLatin1String(file1.readAll());
			this->setStyleSheet(styleSheet);
			dlg->setStyleSheet(styleSheet);
			file1.close();
			settings->setValue( "skin", 1);
			break;
		case 2:

			file2.open(QFile::ReadOnly);
			styleSheet = QLatin1String(file2.readAll());
			this->setStyleSheet(styleSheet);
			dlg->setStyleSheet(styleSheet);
			file2.close();
			settings->setValue( "skin", 2);
			break;
		case 3:
			file3.open(QFile::ReadOnly);
			styleSheet = QLatin1String(file3.readAll());
			this->setStyleSheet(styleSheet);
			dlg->setStyleSheet(styleSheet);
			file3.close();
			settings->setValue( "skin", 3);
			break;
		case 4:
			file4.open(QFile::ReadOnly);
			styleSheet = QLatin1String(file4.readAll());
			this->setStyleSheet(styleSheet);
			dlg->setStyleSheet(styleSheet);
			file4.close();
			settings->setValue( "skin", 4);
			break;
		case 5:
			file5.open(QFile::ReadOnly);
			styleSheet = QLatin1String(file5.readAll());
			this->setStyleSheet(styleSheet);
			dlg->setStyleSheet(styleSheet);
			file5.close();
			settings->setValue( "skin", 5);
			break;
		default:
			break;
	}
}
void ManageWindow::slotTrans(int value)     //透明度
{
	settings->setValue( "opacity", value);
	qreal opacity = qreal(value)/100.0;
	this->setWindowOpacity(opacity);
	//	ui->stackedWidget->setWindowOpacity(opacity);
	//	emit senopacity(opacity);
}
void ManageWindow::LoadImage()
{

	ui->imagelist->setViewMode(QListView::IconMode);
	ui->imagelist->setIconSize(QSize(80,60));
	ui->imagelist->setResizeMode(QListView::Adjust);
	listModel = new PictureListModel(this);
	ui->imagelist->setModel(listModel);
	listModel->addPictures("/home/acanoe/图片");
	connect(ui->imagelist->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)),
			this, SLOT(listItemChanged(QModelIndex, QModelIndex)));
	/*
	   label = new QLabel(ui->imagelist);
	   label->setScaledContents(true);

	   showPicture(listModel->index(0));
	   */
}
void ManageWindow::listItemChanged(const QModelIndex &current, const QModelIndex &previous)
{
	qDebug() << current;
}


void ManageWindow::showPicture(const QModelIndex &index)
{
	if (!index.isValid())
		return;

	QPixmap pixmap = listModel->data(index, Qt::UserRole).value<QPixmap>();
	label->setPixmap(pixmap);
	label->adjustSize();
	ui->imagelist->setCurrentIndex(index);
}
void ManageWindow::LoadVideo()
{
}
void ManageWindow::LoadMusic()
{
}
void ManageWindow::LoadConnect()
{
}
void ManageWindow::LoadBook()
{
	Book_table = new QTableWidget(ui->W_Book);
	Book_table->setGeometry(0,0,680,668);
	Book_table->setFrameShape(QFrame::NoFrame);  //无边框
	Book_table->setAutoScroll(false);
	Book_table->setShowGrid(false); //设置不显示格子线
	Book_table->setColumnCount(2);  //  hang count 
	Book_table->setMouseTracking(true);
	Book_table->verticalHeader()->setDefaultSectionSize(30);
	Book_table->setSelectionMode(QAbstractItemView::SingleSelection); 
	Book_table->setSelectionBehavior(QAbstractItemView::SelectRows); 
	//	Book_table->setFont(15);   
	Book_table->setColumnWidth(0,175);
	Book_table->setColumnWidth(1,370);
	//	Book_table->setColumnWidth(2,80);
	Book_table->verticalHeader()->setVisible(false);   
	Book_table->horizontalHeader()->setVisible(true); 
	Book_table->setEditTriggers ( QAbstractItemView::NoEditTriggers );
	Book_table->setAlternatingRowColors(true);  //奇偶行底色不同

	QStringList labels;
	labels << tr("姓名") << tr("号码");
	Book_table->setHorizontalHeaderLabels(labels);

	connect(Book_table,SIGNAL(cellClicked(int,int)),this,SLOT(Book_clicked(int,int)));
}

void ManageWindow::goto_helpdev()
{
	QMessageBox::about(this, tr("捐助 软件开发者"), tr(
				"android manager"
				"<p>"
				"<p><p><p>对android manager 后续开发进行捐助"
				"<p>支付宝捐助"
				"<p><a href=\"weibo.com/imcanoe\">weibo.com/imcanoe</a>."
				"<p>androidmanager by 杨小军 2013/5/24 "
				));

}

void ManageWindow::slotAboutApplication()
{
	QMessageBox::about(this, tr("关于 Androidmanager"), tr(
				"android manager"
				"<p>"
				"<p><p><p>android manager 是一款  android 手机管理软件"
				"<p>目前可运行环境为ubuntu 等已安装有qt4 库的Linux 操作系统"
				"<p>androidmanger 是一款自由软件，遵循GNU GPL协议"
				"<p>任何个人和组织都可以对源码进行自由的传播和修改。"
				"<p>版本：			1.0<p>"
				"<p>问题及建议？"
				"<p>欢迎联系我:	 <a href = https://mail.google.com >imcanoe@gmail.com</a>"
				"<p>博客:	 <a href = http://blog.csdn.net/ACanoe >blog.csdn.net/ACanoe</a>"
				"<p>关注新浪微博了解最新更新："
				"<a href = http://weibo.com/acanoe >weibo.com/acanoe</a>"
				"<p>androidmanager by 杨小军 2013/5/24 "
				));
	// "<p>QtWebKit is based on the Open Source WebKit Project developed at <a href=\"http://webkit.org/\">http://webkit.org/</a>."
	//        ).arg(QCoreApplication::applicationVersion()));
}

void ManageWindow::LoadQmenu()
{

	QMenu *connect= menuBar()->addMenu(tr("&选项"));
	connect->addAction(tr("&首页"), this, SLOT(goto_connect()));
	connect->addAction(tr("&任务列表"), this, SLOT(goto_manager()));

	QMenu *tools= menuBar()->addMenu(tr("&工具箱"));
	tools->addAction(tr("&Logcat"), this, SLOT(goto_logcat()));
	tools->addAction(tr("&Android 终端"), this, SLOT(goto_shell()));
	tools->addAction(tr("&Android 刷机"), this, SLOT(goto_refreshsystem()));

	QMenu *menusettings= menuBar()->addMenu(tr("&设置"));
	menusettings->addAction(tr("&软件设置"), this, SLOT(goto_settings()));


	QMenu *helpMenu = menuBar()->addMenu(tr("&帮助"));
	helpMenu->addAction(tr("关于 &Qt"), qApp, SLOT(aboutQt()));
	helpMenu->addAction(tr("关于 &Androidmanager"), this, SLOT(slotAboutApplication()));
	helpMenu->addAction(tr("捐助 &软件开发者"), this, SLOT(goto_helpdev()));
	helpMenu->addAction(tr("&注册使用"), this, SLOT(goto_helpdev()));
}
void ManageWindow::LoadFtpfilelist()
{
	ftpfilelist = new FtpClientWindow(ui->P_Storage); 
}

void ManageWindow::LoadDownloadlist()
{
	Downloadlist_table = new QTableWidget(ui->downloadlist_widget);
	Downloadlist_table->setGeometry(0,0,800,668);
	Downloadlist_table->setFrameShape(QFrame::NoFrame);  //璁剧疆杈规
	Downloadlist_table->setAutoScroll(false);
	Downloadlist_table->setShowGrid(false);
	Downloadlist_table->setColumnCount(1);
	Downloadlist_table->setMouseTracking(true);
	Downloadlist_table->verticalHeader()->setDefaultSectionSize(48);
	Downloadlist_table->setSelectionMode(QAbstractItemView::SingleSelection); 
	Downloadlist_table->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行
	//	Downloadlist_table->setFont(15);   
	Downloadlist_table->setColumnWidth(0,800);

	//	Downloadlist_table->setColumnWidth(1,370);
	//	Downloadlist_table->setColumnWidth(2,80);

	Downloadlist_table->verticalHeader()->setVisible(false);   
	Downloadlist_table->horizontalHeader()->setVisible(true); 
	Downloadlist_table->setEditTriggers ( QAbstractItemView::NoEditTriggers ); // 不能进行编辑
	Downloadlist_table->setAlternatingRowColors(true);  //奇偶行底色不同

	Downloadlist_table->horizontalHeader()->setFixedHeight(33); //修改表头合适的高度
	Downloadlist_table->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:lightblue; \
			color: black;padding-left: 4px;border: 1px solid #6c6c6c;}"); //设置表头字体，颜色，模式

		Downloadlist_table->setRowCount(0);

	QStringList labels;
	labels << tr("任务列表");
	Downloadlist_table->setHorizontalHeaderLabels(labels);
	/*

	   ui->Cmbx_appclass->addItem("系统应用");
	   ui->Cmbx_appclass->addItem("第三方应用");
	   ui->Cmbx_appclass->setMaxVisibleItems(10);  // 设置最大显示下列项 超过要使用滚动条拖拉
	   ui->Cmbx_appclass->setMaxCount(5); //设置最大下拉项 超过将不显示
	   */
	//	connect(ui->Cmbx_downlist,SIGNAL(currentIndexChanged(int)),this,SLOT(slotappclasschange(int)));
	connect(Downloadlist_table,SIGNAL(cellClicked(int,int)),this,SLOT(Download_clicked(int,int)));

}

void ManageWindow::LoadApp()
{
	App_table = new QTableWidget(ui->app_widget);
	App_table->setGeometry(0,0,800,635);
	App_table->setFrameShape(QFrame::NoFrame);  //璁剧疆杈规
	App_table->setAutoScroll(false);
	App_table->setShowGrid(false);
	App_table->setColumnCount(4);
	App_table->setMouseTracking(true);
	App_table->verticalHeader()->setDefaultSectionSize(30);
	App_table->setSelectionMode(QAbstractItemView::SingleSelection); 
	App_table->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行
	//	App_table->setFont(15);   
	App_table->setColumnWidth(0,175);
	App_table->setColumnWidth(1,370);
	App_table->setColumnWidth(2,80);
	App_table->setColumnWidth(3,80);
	App_table->verticalHeader()->setVisible(false);   
	App_table->horizontalHeader()->setVisible(true); 
	App_table->setEditTriggers ( QAbstractItemView::NoEditTriggers ); // 不能进行编辑
	App_table->setAlternatingRowColors(true);  //奇偶行底色不同

	//	App_table->horizontalHeader()->resizeSection(0,150);//修改表头第一列的宽度为150
	App_table->horizontalHeader()->setFixedHeight(30); //修改表头合适的高度
	App_table->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:lightblue; \
			color: black;padding-left: 4px;border: 1px solid #6c6c6c;}"); //设置表头字体，颜色，模式


		QStringList labels;
	labels << tr("名称") << tr("版本")  << tr("大小") << tr("位置");
	App_table->setHorizontalHeaderLabels(labels);
/*
	QPalette pal;
	pal.setColor(QPalette::Base, QColor(255, 0, 0));
	pal.setColor(QPalette::AlternateBase, QColor(0, 255, 0));
	App_table->setPalette(pal);
	*/

	ui->Cmbx_appclass->addItem("系统应用");
	ui->Cmbx_appclass->addItem("第三方应用");
	ui->Cmbx_appclass->setMaxVisibleItems(10);  // 设置最大显示下列项 超过要使用滚动条拖拉
	ui->Cmbx_appclass->setMaxCount(5); //设置最大下拉项 超过将不显示

	connect(ui->Cmbx_appclass,SIGNAL(currentIndexChanged(int)),this,SLOT(slotappclasschange(int)));


	connect(App_table,SIGNAL(cellClicked(int,int)),this,SLOT(App_clicked(int,int)));

}

void ManageWindow::Download_clicked(int x,int y)
{
	DOWNLOADSIGN  = x;
}

void ManageWindow::App_clicked(int x,int y)
{
	APPSIGN = appindex[APPINDEX][x];
	printf("x = %d, y = %d\n",x,y);
}


void ManageWindow::Book_clicked(int x,int y)
{
	BOOKSIGN = x;
	printf("x = %d, y = %d\n",x,y);
}

void ManageWindow::LoadSettings()
{

	ui->pellucidity->setRange(70,100);
	ui->pellucidity->setValue(100);
	connect(ui->pellucidity,SIGNAL(valueChanged(int)),this,SLOT(slotTrans(int)));

	ui->skinstyle->addItem("黄-绿");
	ui->skinstyle->addItem("绿-青");
	ui->skinstyle->addItem("青");
	ui->skinstyle->addItem("青-蓝");
	ui->skinstyle->addItem("蓝-紫");
	ui->skinstyle->addItem("紫");
	connect(ui->skinstyle,SIGNAL(currentIndexChanged(int)),this,SLOT(slotStyleChange(int)));

}



void ManageWindow::setui_downloadlist(int row)
{
	//	Downloadlist_table->setRowCount(uiappinfo.count + 1);
	//	for (int i = 0; i <= 50; i++) {
	downname[row] = new QLabel(&UiDownlist[row]);
	downname[row]->setGeometry(QRect(0, 0, 111, 31));

	downprogress[row] = new QProgressBar(&UiDownlist[row]);
	downprogress[row]->setGeometry(QRect(134, 10, 532, 15));
	downprogress[row]->setStyleSheet(QString::fromUtf8(""));
	downprogress[row]->setValue(24);

	downstat[row] = new QLabel(&UiDownlist[row]);
	downstat[row]->setGeometry(QRect(710, 0, 71, 31));


	Downloadlist_table->insertRow(row);
	Downloadlist_item[row][0] = new QTableWidgetItem;
	Downloadlist_table->setItem(row,0,Downloadlist_item[row][0]);
	Downloadlist_table->setCellWidget(row, 0, &UiDownlist[row]);

	/*
	   QWidget *widget_test = new QWidget;

	   QProgressBar *pushButton_test= new QProgressBar(widget_test);
	   */

	/*
	   Downloadlist_item[i][0]->setText(QString(uiappinfo.get_info[i].appname));
	   Downloadlist_item[i][1]->setText(QString(uiappinfo.get_info[i].appversion));
	   Downloadlist_item[i][2]->setText(QString(uiappinfo.get_info[i].appsize));
	   */
	//	}

}


void ManageWindow::goto_setdownloadpath()
{
	QString downloadpath;

	/*
	   QFileDialog *chosedir= new QFileDialog(this);
	   StyleChange(settings->value( "skin",1).toInt(),chosedir);
	   downloadpath=chosedir->getExistingDirectory(NULL,QObject::tr("选择一个下载保存目录"),"/");
	   */

	downloadpath=QFileDialog::getExistingDirectory(NULL,QObject::tr("选择一个下载保存目录"),"/");
	qDebug() << downloadpath;

	if (downloadpath.isEmpty())
		return;


	ui->Lab_dirpath->setText(downloadpath);
	settings->setValue("downloadpath", downloadpath);

}
void ManageWindow::LoadMms()
{
	Mms_table = new QTableWidget(ui->mms_widget);
	Mms_table->setGeometry(0,0,800,668);
	Mms_table->setFrameShape(QFrame::NoFrame);  
	Mms_table->setAutoScroll(false);
	Mms_table->setShowGrid(false);
	Mms_table->setColumnCount(3);
	Mms_table->setMouseTracking(true);
	Mms_table->verticalHeader()->setDefaultSectionSize(48);
	Mms_table->setSelectionMode(QAbstractItemView::SingleSelection); 
	Mms_table->setSelectionBehavior(QAbstractItemView::SelectRows); 
	//	Mms_table->setFont(15);   
	Mms_table->setColumnWidth(0,100);
	Mms_table->setColumnWidth(1,540);
	Mms_table->setColumnWidth(2,140);
	Mms_table->verticalHeader()->setVisible(false);     
	Mms_table->horizontalHeader()->setVisible(true);  
	Mms_table->setEditTriggers ( QAbstractItemView::NoEditTriggers );
	Mms_table->setAlternatingRowColors(true);  //奇偶行底色不同

	QStringList labels;
	labels << tr("号码") << tr("内容")  << tr("时间");
	Mms_table->setHorizontalHeaderLabels(labels);


	//	Mms_table->setRowCount(50);

	connect(Mms_table,SIGNAL(cellClicked(int,int)),this,SLOT(Mms_clicked(int,int)));
}


void ManageWindow::Mms_clicked(int a, int b)
{
	MMSSIGN = a;
}

void ManageWindow::ClassTestInit()
{
	/*
	   test= new class_test(this);
	   QThread* testpthread= new QThread;
	   DaemonThread->moveToThread(testpthread);
	   testpthread->start(QThread::IdlePriority);               
	   post_test(1);
	   */
}

void ManageWindow::Mysettingsinit()
{
	settings = new QSettings;
	//	settings("./etc/mysettings->ini", QSettings::IniFormat );
	settingsargv.skin = settings->value( "skin",1).toInt();
	settingsargv.opacity = settings->value( "opacity", 100).toInt();
	settingsargv.downloadpath = settings->value( "downloadpath", "/home/acanoe/下载").toString();

	ui->skinstyle->setCurrentIndex(settingsargv.skin);
	slotStyleChange(settingsargv.skin);
	slotTrans(settingsargv.opacity);
	ui->Lab_dirpath->setText(settingsargv.downloadpath);

	//	mysettings = new Mysetting;
	/*
	   mysettings->mysettingdefault();
	   mysettings->mysettinginit();
	   */


	/*
	   mysettings = new Mysettings;
	   connect(this,SIGNAL(settingsargc(QString,QString)),this,SLOT(settingsargc(QString,QString)));
	   connect(mysettings,SIGNAL(getsettings(QString,QString)),this,SLOT(getsettings(QString,QString)));
	   */
}

void ManageWindow::ProcessThreadInit()
{
	adbthread = new ProcessThread;
	connect(adbthread,SIGNAL(adbresult(int,int,int)),this,SLOT(adbresult(int,int,int)));
	connect(this,SIGNAL(addadbcmd(int,int,QString)),adbthread,SLOT(addadbcmd(int,int,QString)));
	adbthread->start();
}

void ManageWindow::adbresult(int resulttype ,int adbcount,int result)
{
	switch(resulttype)
	{
		case ADB_UNINSTALL:
			if(result)
			{
				qDebug() << "Unistall : " << adbcount  << " Success";
				post_refresh(CMD_APP);
				dlg->accept();
			} else {
				qDebug() << "Unistall : " << adbcount  << " Failure";
				dlg->accept();
			}
			break;
		case ADB_INSTALL:
			if(result)
			{
				qDebug() << "Istall : " << adbcount  << " Success";
				post_refresh(CMD_APP);
				downstat[adbcount]->setText("安装成功");
				dlg->accept();
			} else {
				qDebug() << "Istall : " << adbcount  << " Failure";
				downstat[adbcount]->setText("安装失败");
				dlg->accept();
			}
			break;
		default:
			break;
	}

}
void ManageWindow::DaemonQthreadInit()
{

	DaemonThread = new Daemon(this);
	QThread* daemon_thread = new QThread;
	DaemonThread->moveToThread(daemon_thread);
	daemon_thread->start(QThread::IdlePriority);               
	post_daemon(START_DAEMON);
}
void ManageWindow::BackQthreadInit()
{
	BackThread = new Backthread(this);
	QThread* thread = new QThread;
	BackThread->moveToThread(thread);
	thread->start();
	post_softinit(SOFT_INIT);
}

void ManageWindow::post_install(int cmd){
	AMEvent* event_install= new AMEvent(AMEVENT_INSTALL,cmd);
	QApplication::postEvent(BackThread,event_install);
}

void ManageWindow::post_sendmms(int cmd){
	AMEvent* event_sendmms= new AMEvent(AMEVENT_SENDMMS,cmd);
	QApplication::postEvent(BackThread,event_sendmms);
}

void ManageWindow::post_uninstall(int cmd){
	AMEvent* event_uninstall= new AMEvent(AMEVENT_UNINSTALL,cmd);
	QApplication::postEvent(BackThread,event_uninstall);
}
void ManageWindow::post_exit(int cmd){
	AMEvent* event_exit= new AMEvent(AMEVENT_EXIT,cmd);
	QApplication::postEvent(BackThread,event_exit);
}
void ManageWindow::post_softinit(int cmd){
	AMEvent* event_softinit= new AMEvent(AMEVENT_INITEVENT,cmd);
	QApplication::postEvent(BackThread,event_softinit);
}



void ManageWindow::Makeconnect()
{
	/*
	   connect(this,SIGNAL(btn_connect_sig()),this,SLOT(FindDevice()));
	   connect(ui->Btn_360, SIGNAL(clicked()),this, SLOT(goto_360()));
	   connect(ui->Btn_wdj, SIGNAL(clicked()),this, SLOT(goto_wdj()));
	   connect(ui->Btn_jf, SIGNAL(clicked()),this, SLOT(goto_jf()));
	   connect(ui->Btn_manager, SIGNAL(clicked()),this, SLOT(goto_manager()));
	   connect(ui->Btn_settings, SIGNAL(clicked()),this, SLOT(goto_settings()));
	   */

	connect(ui->Btn_app, SIGNAL(clicked()),this, SLOT(btn_app_clicked()));
	connect(ui->Btn_book, SIGNAL(clicked()),this, SLOT(btn_book_clicked()));
	connect(ui->Btn_image, SIGNAL(clicked()),this, SLOT(goto_imagelist()));
	connect(ui->Btn_app, SIGNAL(clicked()),this, SLOT(goto_applist()));
	connect(ui->Btn_uninstall, SIGNAL(clicked()),this, SLOT(goto_uninstall()));
	connect(ui->Btn_install, SIGNAL(clicked()),this, SLOT(goto_install()));
	connect(ui->Btn_sendmms, SIGNAL(clicked()),this, SLOT(goto_sendmms()));
	connect(ui->Btn_changedir, SIGNAL(clicked()),this, SLOT(goto_setdownloadpath()));
	connect(ui->Btn_book, SIGNAL(clicked()),this, SLOT(goto_book()));
	connect(ui->Btn_storage, SIGNAL(clicked()),this, SLOT(goto_storage()));
	connect(ui->Btn_booksendmms, SIGNAL(clicked()),this, SLOT(goto_booksendmms()));
	connect(ui->Btn_call, SIGNAL(clicked()),this, SLOT(goto_call()));
	connect(ui->Btn_mmsrefresh, SIGNAL(clicked()),this, SLOT(goto_mmsrefresh()));
	connect(ui->Btn_detail, SIGNAL(clicked()),this, SLOT(goto_mmsdetail()));
	connect(ui->Btn_appstore, SIGNAL(clicked()),this, SLOT(goto_appstore()));


	/*    connect(this,SIGNAL(AppInstall()),this,SLOT(c_finddevice()));
		  connect(this,SIGNAL(AppUninstall()),this,SLOT(c_finddevice()));
		  connect(this,SIGNAL(FilePush()),this,SLOT(c_finddevice()));
		  connect(this,SIGNAL(FilePull()),this,SLOT(c_finddevice()));
		  */
}

void ManageWindow::Menuaction(int P_NUM)
{
	qDebug() << P_NUM;
	CurrentWidget(P_NUM);
}
void ManageWindow::CurrentWidget(int P_NUM)
{
	switch(P_NUM)
	{
		case MENU:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Menu);
			break;
		case BOOK:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Book);
			break;
		case CONNECT:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Connect);
			break;
		case IMAGE:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Image);
			break;
		case VIDEO:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Video);
			break;
		case MUSIC:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Music);
			break;
		case MASSIGE:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Massige);
			break;
		case WEBVIEW:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Web);
			break;
		case  APP:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_App);
			break;
		case  SETTINGS:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Settings);
			break;
		case  TEST:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Test);
			break;
		case  STORAGE:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Storage);
			break;
		case  DOWNLOADLIST:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Downloadlist);
			break;
		case  MMS:
			ui->stackedWidget->QStackedWidget::setCurrentWidget(ui->P_Mms);
			break;
		default:
			break;
	}

}

void ManageWindow::post_monitorusb(int cmd){
	AMEvent* event_monitorusb = new AMEvent(AMEVENT_USBEVENT,cmd);
	QApplication::postEvent(BackThread,event_monitorusb);
}

void ManageWindow::post_refresh(int cmd){
	AMEvent* event_refresh= new AMEvent(AMEVENT_REFRESH,cmd);
	QApplication::postEvent(BackThread,event_refresh);
}

void ManageWindow::post_daemon(int cmd){
	AMEvent* event_daemon = new AMEvent(AMEVENT_DAEMON,cmd);
	QApplication::postEvent(DaemonThread ,event_daemon);
}

void ManageWindow::post_test(int cmd){
}

void ManageWindow::goto_mmsdetail()
{
	if(MMSSIGN  >= 0)
	{
		QMessageBox::about(this, tr("短信详情"),QString(uimmsinfo.get_info[MMSSIGN].mmsnumber) +
				"<p>" + 	QString(uimmsinfo.get_info[MMSSIGN].mmsbody) + "<p>" + QString(uimmsinfo.get_info[MMSSIGN].mmsdate));
	}

}

void ManageWindow::goto_mmsrefresh()
{
	post_refresh(CMD_MMS);
}

void ManageWindow::goto_call()
{
}

void ManageWindow::goto_booksendmms()
{
	if(BOOKSIGN >= 0)
	{
		mms_dialog = new MMS_Dialog;
		StyleChange(settings->value( "skin",1).toInt(),mms_dialog);
		mms_dialog->show();
		connect(this->mms_dialog, SIGNAL(mmsdlg_accept()),this, SLOT(get_message()));
		mms_dialog->setnumber(QString(uibookinfo.get_info[BOOKSIGN].booknumber));


		//		Book_item[i][0]->setText(QString(uibookinfo.get_info[i].bookname));
		//		Book_item[i][1]->setText();

	}

}
void ManageWindow::goto_manager()
{
	CurrentWidget(DOWNLOADLIST);
}
void ManageWindow::goto_storage()
{
	CurrentWidget(STORAGE);
}
void ManageWindow::goto_book()
{
	if(refreshsign.book)
	{
		ui->Lab_refresh->setHidden(false);
		refresh_anim->start();
		post_refresh(CMD_BOOK);
		refreshsign.book= 0;
	}

	CurrentWidget(BOOK);
}
void ManageWindow::goto_appstore()
{
	CurrentWidget(WEBVIEW);
}

void ManageWindow::goto_wdj()
{
	ui->Webview->load(QUrl("http://www.wandoujia.com/apps"));
}

void ManageWindow::goto_logcat()
{
	logcat = new LogcatDialog;
	StyleChange(settings->value( "skin",1).toInt(),logcat);
	logcat->show();
}
void ManageWindow::goto_settings()
{
	CurrentWidget(SETTINGS);
}

void ManageWindow::get_message()
{
	qDebug() << "mms_dialog->mmsnumber" << mms_dialog->mmsnumber;
	qDebug() << "mms_dialog->mmsdata" <<  mms_dialog->mmsdata;

	if((mms_dialog->mmsnumber != "") && (mms_dialog->mmsdata != ""))
	{
		QByteArray byte_list = mms_dialog->mmsnumber.toLatin1();
		char *char_mmsnumber= byte_list.data();


		QByteArray by_list = mms_dialog->mmsdata.toUtf8();
		char *char_mmsdata= by_list.data();
		setmessageinfo(char_mmsnumber,char_mmsdata);
		post_refresh(CMD_SENDMMS);
	}
	else {
		return;
	}
}

void ManageWindow::goto_sendmms()
{
	if(MMSSIGN  >= 0)
	{

		mms_dialog = new MMS_Dialog;
		StyleChange(settings->value( "skin",1).toInt(),mms_dialog);
		mms_dialog->show();

		mms_dialog->setnumber(QString(uimmsinfo.get_info[MMSSIGN].mmsnumber));
		connect(this->mms_dialog, SIGNAL(mmsdlg_accept()),this, SLOT(get_message()));
	}
	/*
	   QString str;
	   str = ui->Mms_no->toPlainText();
	//	qDebug() << "the Mms_no is:" << str;	

	QString list = str;
	QByteArray byte_list = list.toLatin1();
	char *char_list = byte_list.data();



	QString strinfo;
	strinfo = ui->Mms_info->toPlainText();

	QString listinfo = strinfo;
	QByteArray byte_mmsinfo = listinfo.toUtf8();

	char *char_mmsinfo = byte_mmsinfo.data();
	setsendmmsinfo(char_list,char_mmsinfo);
	//	qDebug() << "the Mms_info is:" << strinfo;	
	post_sendmms(1);
	*/
}
void ManageWindow::goto_install()
{
	QString name = "acanoe";
	QString age = "ui.h";
	QFileDialog *fd = new QFileDialog(this);
	fd->setWindowTitle("选择一个apk 安装文件");
	StyleChange(settings->value( "skin",1).toInt(),fd);
	fd->setGeometry(200,200,600,400);
	fd->setFilter(tr("apk Files(*.apk)"));

	if (fd->exec()==QFileDialog::Accepted)// ok
	{
		QTextStream cout(stdout, QIODevice::WriteOnly);

		QStringList slist=fd->selectedFiles();
		QString list = slist[0];
		/*
		   QByteArray byte_list = list.toLatin1();
		   char *char_list = byte_list.data();

		   setinstallapp(char_list);
		   */
		emit addadbcmd(ADB_INSTALL,adbcount,list);

		//		post_install(1);
	} else
	{
	}
	delete fd;
}




void ManageWindow::goto_uninstall()
{
	if(APPSIGN >= 0)
	{
		char tmpbuf[150] = { 0 };
		//	QDialog *dlg = new QDialog;
		dialogUi = new Ui::dialog;
		dialogUi->setupUi(dlg);
		//	dlg->exec();
		//		dlg.move ((QApplication::desktop()->width() - dlg.width())/2,(QApplication::desktop()->height() - dlg.height())/2);
		dlg->setWindowTitle("卸载 应用");
		dlg->show();
		memset(tmpbuf,0,150);


		dialogUi->L_uninstallinfo->setText("");
		sprintf(tmpbuf,"确认卸载 : %s",uiappinfo.get_info[APPSIGN].appname);
		printf("APPSIGN = %d\n",APPSIGN);
		dialogUi->L_uninstallinfo->setText(tmpbuf);

		connect(dialogUi->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
		connect(dialogUi->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
		connect(dialogUi->checkBox,SIGNAL(stateChanged(int)),this,SLOT(valuechange(int)));
	}
}

void ManageWindow::recv_refresh(int res)
{
	switch(res)
	{
		case CMD_APP:
			qDebug() << "refresh APP";
			ui->Lab_refresh->setHidden(true);
			refresh_anim->stop();
			//			setui_appinfo();
			setui_appclass(APPINDEX);
			ui->Cmbx_appclass->setCurrentIndex(APPINDEX);
			break;
		case CMD_BOOK:
			refresh_anim->stop();
			ui->Lab_refresh->setHidden(true);
			qDebug() << "refresh BOOK";
			setui_bookinfo();
			break;
		case CMD_STORAGE:
			qDebug() << "refresh STORAGE";
			setui_storageinfo();
			break;
		case CMD_MMS:
			ui->Lab_refresh->setHidden(true);
			refresh_anim->stop();
			qDebug() << "refresh MMS";
			setui_mmsinfo();
			break;
		default:
			break;
	}
}

void ManageWindow::recv_install(int res)
{
}

void ManageWindow::recv_sendmms(int res)
{
}
void ManageWindow::recv_uninstall(int res)
{
	if(res)
	{
		dialogUi ->L_uninstallinfo->setText("卸载成功");
		dlg->accept();
		setui_appclass(APPINDEX);
//		setui_appinfo();
	} else{
		dialogUi->L_uninstallinfo->setText("卸载失败");
	}
	//	delete  dlg;
}


//void Ui::dialog::accept()
void ManageWindow::valuechange(int value)
{
	printf("checkBox value = %d\n",value);
}

void ManageWindow::reject()
{
	dlg->reject();
}

void ManageWindow::accept()
{
	if(APPSIGN >= 0)
	{
		emit addadbcmd(ADB_UNINSTALL,adbcount,QString(uiappinfo.get_info[APPSIGN ].apppackname));
	}
	//		post_uninstall(APPSIGN);
	/*
	   QProcess *phone=new QProcess(this);

	   QString command;
	   QString outputLines;

	   command = "./bin/adb shell pm uninstall -k " + QString(uiappinfo.get_info[APPSIGN ].apppackname);

	   qDebug()<<"Phone::getFileList() - "<<command;

	   phone->start(command);

	   phone->waitForFinished(-1);
	   outputLines=phone->readAll();
	   if (outputLines.contains("Success"))
	   {
	   phone->terminate();
	   delete phone;
	   post_refresh(CMD_APP);
	   }
	//		qDebug()<<"Phone::getFileList() - "<<outputLines;
	*/
	//	sprintf(endcmd,"%s %s","./bin/adb shell pm uninstall -k",argv);

	/*
	   if(app_uninstall(uiappinfo.get_info[cmd].apppackname))
	   {
	   post_uninsatll(1);
	   }else {
	   post_uninsatll(0);
	   }
	   */

}
void ManageWindow::goto_applist()
{
	if(refreshsign.app)
	{
		ui->Lab_refresh->setHidden(false);
		refresh_anim->start();
		post_refresh(CMD_APP);
		refreshsign.app = 0;
	}
	CurrentWidget(APP);
}
void ManageWindow::goto_imagelist()
{
	CurrentWidget(IMAGE);
}
void ManageWindow::goto_jf()
{
	ui->Webview->load(QUrl("http://apk.hiapk.com/"));
}
void ManageWindow::btn_app_clicked()
{

}
void ManageWindow::btn_book_clicked()
{

}


void ManageWindow::goto_refreshsystem()
{

}
void ManageWindow::goto_shell()
{
	shelldialog = new ShellDialog();
	StyleChange(settings->value( "skin",1).toInt(),shelldialog);
	shelldialog->show();
}

void  ManageWindow::goto_connect()
{
	CurrentWidget(MENU);
}


void  ManageWindow::on_Btn_video_clicked()
{
	CurrentWidget(VIDEO);

}
void  ManageWindow::on_Btn_music_clicked()
{
	CurrentWidget(MUSIC);


}
void  ManageWindow::on_Btn_massage_clicked()
{
	if(refreshsign.mms)
	{
		ui->Lab_refresh->setHidden(false);
		refresh_anim->start();
		post_refresh(CMD_MMS);
		refreshsign.mms= 0;
	}

	CurrentWidget(MMS);
}
void  ManageWindow::on_Btn_app_clicked()
{
}
void  ManageWindow::on_Btn_book_clicked()
{
}

void ManageWindow::recv_softinit(int res)
{
}


void ManageWindow::recv_monitorusb(int res){
}

void ManageWindow::recv_daemon(int cmd){
	switch(cmd)
	{
		case FIND:
			ui->Lab_info->setText("发现设备");
			break;
		case INSTALLAPP:
			ui->Lab_info->setText("安装客户端");
			break;
		case KONG_USB:
			ui->Lab_info->setText("请链接手机");
			CurrentWidget(CONNECT);
			break;
		case REMOVE_USB:
			connectinit();
			ui->Lab_info->setText("请链接手机");
			CurrentWidget(CONNECT);
			break;
		case WAITDATA:
			ui->Lab_info->setText("正在获取数据");
			break;
		case DATA_READY:
			m_anim->stop();
			CurrentWidget(MENU);
			break;
		default:
			m_anim->start();
			CurrentWidget(CONNECT);
			break;
	}

}

void ManageWindow::recv_test(int res){
}
void ManageWindow::customEvent(QEvent* e){
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
		case AMEVENT_USBEVENT:
			recv_monitorusb(jpe->msg());
			break;
		case AMEVENT_DAEMON:
			recv_daemon(jpe->msg());
			break;
		case AMEVENT_EXIT:
			//			recv_exit(jpe->msg());
			break;
		case AMEVENT_TEST:
			recv_test(jpe->msg());
			break;
		default:
			break;
	}
	return;
}

void ManageWindow::setui_bookinfo()
{
	getbookinfo(&uibookinfo);
	Book_table->setRowCount(0);

	printf("uibookinfo.count = %d\n",uibookinfo.count);

	Book_table->setRowCount(uibookinfo.count + 1);
	for (int i = 0; i <= uibookinfo.count; i++) {
		for (int j = 0; j < 2; j++) {
			Book_item[i][j] = new QTableWidgetItem;
			Book_table->setItem(i,j,Book_item[i][j]);
		}
		Book_item[i][0]->setText(QString(uibookinfo.get_info[i].bookname));
		Book_item[i][1]->setText(QString(uibookinfo.get_info[i].booknumber));
		//		printf("%s,%s\n",uibookinfo.get_info[i].bookname,uibookinfo.get_info[i].booknumber);
		//		Book_item[i][2]->setText(QString(uibookinfo.get_info[i].bookdate));
	}
}


void ManageWindow::setui_mmsinfo()
{
	memset(&uimmsinfo,0,sizeof(allmmsinfo_t));
	getmmsinfo(&uimmsinfo);
	Mms_table->setRowCount(0);

	Mms_table->clearContents();
	//	Mms_table->clear();
	printf("uimmsinfo.count = %d\n",uimmsinfo.count);
	Mms_table->setRowCount(uimmsinfo.count + 1);
	for (int i = 0; i <= uimmsinfo.count; i++) {
		for (int j = 0; j < 3; j++) {
			Mms_item[i][j] = new QTableWidgetItem;
			Mms_table->setItem(i,j,Mms_item[i][j]);
		}
		Mms_item[i][0]->setText(QString(uimmsinfo.get_info[i].mmsnumber));
		Mms_item[i][1]->setText(QString(uimmsinfo.get_info[i].mmsbody));
		Mms_item[i][2]->setText(QString(uimmsinfo.get_info[i].mmsdate));
	}
}


void ManageWindow::setui_appclass(int Appclass)     
{

	refreshsign.app = 0;
	getappinfo(&uiappinfo);

	//	if(StyleString=="系统应用")
	switch(Appclass)
	{
		case 0:
			testapp = -1;
			qDebug() << "系统应用";
			APPINDEX = 0;
			App_table->setRowCount(0);

			App_table->clearContents();
			App_table->setRowCount(0);
			for (int i = 0; i <= uiappinfo.count; i++) {
				if(!uiappinfo.get_info[i].appattribute)
				{

					testapp++;
					App_table->insertRow(testapp);

					/*
					   QComboBox *comBox = new QComboBox(); 
					   comBox->addItem("F"); 
					   comBox->addItem("M"); 
					   Book_table->setCellWidget(0,2,comBox);
					   */


					for (int j = 0; j < 3; j++) {
						App_item[testapp][j] = new QTableWidgetItem;
						App_table->setItem(testapp,j,App_item[testapp][j]);
					}
					appindex[0][testapp] = i;

					/*
					   QProgressBar *pushButton_test= new QProgressBar;
					   App_table->setCellWidget(testapp, 0, pushButton_test);
					   */

					App_item[testapp][0]->setText(QString(uiappinfo.get_info[i].appname));
					App_item[testapp][1]->setText(QString(uiappinfo.get_info[i].appversion));
					App_item[testapp][2]->setText(QString(uiappinfo.get_info[i].appsize));
				}
			}

			break;
		case 1:

			testapp = -1;
			qDebug() << "第三方应用";

			APPINDEX = 1;
			App_table->clearContents();
			App_table->setRowCount(0);
			//		App_table->removeRow(0);
			//		App_table->setRowCount(uiappinfo.count + 1);
			for (int i = 0; i <= uiappinfo.count; i++) {
				if(uiappinfo.get_info[i].appattribute)
				{
					testapp++;
					App_table->insertRow(testapp);
					for (int j = 0; j < 3; j++) {
						App_item[testapp][j] = new QTableWidgetItem;
						App_table->setItem(testapp,j,App_item[testapp][j]);
					}

					appindex[1][testapp] = i;
					App_item[testapp][0]->setText(QString(uiappinfo.get_info[i].appname));
					App_item[testapp][1]->setText(QString(uiappinfo.get_info[i].appversion));
					App_item[testapp][2]->setText(QString(uiappinfo.get_info[i].appsize));
					//				printf("uiappinfo.get_info[i].appname = %s\n",uiappinfo.get_info[i].appname);
				}
			}
			break;
		default:
			break;
	}
}


// add app

void ManageWindow::setui_clean()
{
	Mms_table->setRowCount(0);
	Book_table->setRowCount(0);
	App_table->setRowCount(0);

	memset(&uimmsinfo,0,sizeof(allmmsinfo_t));
	memset(&uibookinfo,0,sizeof(allbookinfo_t));
	memset(&uiappinfo,0,sizeof(allappinfo_t));
	printf("qt clean ui done\n");

}
void ManageWindow::setui_appinfo()
{
	refreshsign.app = 0;
	getappinfo(&uiappinfo);
	App_table->setRowCount(0);

	App_table->clearContents();
	App_table->setRowCount(uiappinfo.count + 1);
	for (int i = 0; i <= uiappinfo.count; i++) {
		for (int j = 0; j < 3; j++) {
			App_item[i][j] = new QTableWidgetItem;
			App_table->setItem(i,j,App_item[i][j]);

		}	
		App_item[i][0]->setText(QString(uiappinfo.get_info[i].appname));
		App_item[i][1]->setText(QString(uiappinfo.get_info[i].appversion));
		App_item[i][2]->setText(QString(uiappinfo.get_info[i].appsize));
	}
}


// end app


// add player
void ManageWindow::video_player()
{

	openFileButton = new QPushButton();
	//	connect(ui->Btn_opv, SIGNAL(clicked()), this, SLOT(slotOpenFile()));

	playButton = new QPushButton();
	playButton = new QPushButton();
	connect(playButton, SIGNAL(clicked()), this, SLOT(slotPlay()));

	stopButton = new QPushButton();
	connect(stopButton, SIGNAL(clicked()), this, SLOT(slotStop()));

	stepButton = new QPushButton();
	backwardButton = new QPushButton();
	muteButton = new QPushButton();

	buttonLayout = new QHBoxLayout();

	buttonLayout->addWidget(openFileButton);

	buttonLayout->addStretch(1);
	buttonLayout->addWidget(backwardButton);
	buttonLayout->addWidget(playButton);
	buttonLayout->addWidget(stopButton);
	buttonLayout->addWidget(stepButton);
	buttonLayout->addWidget(muteButton);

	/*
	   player = new Player(ui->W_video);


	   player->setGeometry(QRect(0, 0, 600, 400));

	   player->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	   connect(player, SIGNAL(started()), this, SLOT(slotStarted()));
	   connect(player, SIGNAL(error(QProcess::ProcessError)), this, SLOT(slotError(QProcess::ProcessError)));
	   connect(player, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slotFinished(int, QProcess::ExitStatus)));
	   connect(player, SIGNAL(readyReadStandardOutput()), this, SLOT(slotBackMessage()));
	   */

}

void ManageWindow::slotOpenFile()
{
	/*
	   currentFileName = QFileDialog::getOpenFileName(this, tr("打开媒体文件"), tr(""), 
	   tr("Video files(*.rmvb *.rm *.avi *.wmv *.mkv *.asf *.3gp *.mov *.mp4 *.ogv)"));
	   if( !currentFileName.isEmpty() )
	   {
	   qDebug() << "start play";
	   player->play(currentFileName);
	   }
	   */
}

void ManageWindow::slotPlay()
{
	if( currentFileName.isEmpty() )
	{
		slotOpenFile();
		playButton->setIcon(QIcon(":/images/pause.png"));
	}
	else
	{
		player->controlCmd("pause\n");	
	}
}

void ManageWindow::slotStop()
{
	player->controlCmd("quit\n");
	currentFileName = "";
}

void ManageWindow::setui_storageinfo()
{
	float tmp =0;
	float sdsize = 0;
	float sdavail = 0;
	float memorysize = 0;
	float memoryavail = 0;

	getstorageinfo(&uistorageinfo);


	QString sdSize =	uistorageinfo.sdSize;
	QString sdAvail =	uistorageinfo.sdAvail;
	QString memorySize =	uistorageinfo.memorySize;
	QString memoryAvail =	uistorageinfo.memoryAvail;
	if(sdSize.contains("GB"))
	{
		sdSize.remove("GB");
		tmp = sdSize.toFloat();
		sdsize = tmp*1024;
	} else if(sdSize.contains("MB"))
	{
		sdSize.remove("MB");
		sdsize = sdSize.toFloat();
	}

	if(sdAvail.contains("GB"))
	{
		sdAvail.remove("GB");
		tmp = sdAvail.toFloat();
		sdavail = tmp * 1024;

	} else if(sdAvail.contains("MB"))
	{
		sdAvail.remove("MB");
		sdavail = sdAvail.toFloat();

	}

	if(memorySize.contains("GB"))
	{
		memorySize.remove("GB");
		tmp = memorySize.toFloat();
		memorysize = tmp * 1024;

	} else if(memorySize.contains("MB"))
	{
		memorySize.remove("MB");
		memorysize = memorySize.toFloat();

	}

	if(memoryAvail.contains("GB"))
	{

		memoryAvail.remove("GB");
		tmp = memoryAvail.toFloat();
		memoryavail = tmp * 1024;

	} else if(memoryAvail.contains("MB"))
	{
		memoryAvail.remove("MB");
		memoryavail = memoryAvail.toFloat();

	}

	printf("%f,%f,%f,%f,%f\n",sdsize,sdavail,memorysize,memoryavail ,(memorysize - memoryavail)/memorysize);
	//	qDebug << "" << sdsize;// << sdavail << memorysize << memoryavail;

	ui->Pb_sd ->setValue(((sdsize - sdavail)/sdsize)*100);

	ui->Pb_mem->setValue(((memorysize - memoryavail)/memorysize)*100);
	qDebug() << "refresh storage ui over";
}

void ManageWindow::slotStep()
{
}

void ManageWindow::slotBackward()
{
}

void ManageWindow::slotMute(bool /*status*/)
{
}

void ManageWindow::slotStarted()
{
	qDebug() << "lplayer started++++++++++++";
}

void ManageWindow::slotError(QProcess::ProcessError /*error*/)
{
}

void ManageWindow::slotFinished(int /*exitCode*/, QProcess::ExitStatus /*exitStatus*/)
{
	qDebug() << "lplayer finished++++++++++++";
	player->play(currentFileName);
}

void ManageWindow::slotBackMessage()
{
}
// end player


void ManageWindow::LoadWebview()
{
	urlAddr = new QLineEdit;

	//	view = new QWebView;	
	//	view->load(QUrl("http://www.google.cn"));

	/*

	   QHBoxLayout *topLayout = new QHBoxLayout(ui->Webview);
	   topLayout->addWidget(goBack);
	   topLayout->addWidget(goForward);
	   topLayout->addWidget(pageReload);
	   topLayout->addWidget(pageStop);
	   topLayout->addWidget(urlAddr);
	   topLayout->setSpacing(0);

	   QVBoxLayout *mainLayout = new QVBoxLayout(ui->Webview);
	   mainLayout->addLayout(topLayout);
	   mainLayout->addWidget(ui->Webview);
	   mainLayout->setContentsMargins(0,0,0,0);
	   */
	page =new webPage(this);
	ui->Webview->setPage(page);
	ui->Cmbx_otherstore->addItem("豌豆荚应用");
	ui->Cmbx_otherstore->addItem("豌豆荚游戏");
	ui->Cmbx_otherstore->addItem("安卓市场");
	

	connect(this->page, SIGNAL(adddownloadurl(int,double,int,int,QString)), this, SLOT(adddownloadurl(int,double,int,int,QString)));
	connect(this->page, SIGNAL(addstartdownload(int,double,int,int,QString)), this, SLOT(addstartdownload(int,double,int,int,QString)));
	connect(this->page, SIGNAL(downloadurlfinished(int,int,int,QString)), this, SLOT(addadbcmdslot(int,int,int,QString)));

	connect(ui->Btn_back, SIGNAL(clicked()), ui->Webview, SLOT(back()));
	connect(ui->Btn_forward, SIGNAL(clicked()), ui->Webview, SLOT(forward()));
	connect(ui->Btn_reload, SIGNAL(clicked()), ui->Webview, SLOT(reload()));


	ui->Webview->load(QUrl("http://apk.hiapk.com/"));
	//	ui->Webview->load(QUrl("http://www.wandoujia.com/apps"));
	/*	

		connect(urlAddr, SIGNAL(returnPressed()), this, SLOT(loadUrlAddr()));

		connect(ui->Webview, SIGNAL(urlChanged(const QUrl &)), this, SLOT(displayUrlAddr(const QUrl &)));
		connect(ui->Webview, SIGNAL(titleChanged(const QString &)), this, SLOT(showTitle(const QString &)));
		*/
}
void ManageWindow::addadbcmdslot(int downcount,int adb_type, int adb_count, QString adb_list)
{

	downstat[downcount]->setText("正在安装");
	qDebug() << "ready install " << adb_list;
	emit addadbcmd(adb_type,downcount,adb_list);
}
void ManageWindow::addstartdownload(int downcount,double speed,int percent,int stat,QString filename)
{
	qDebug() << "ManageWindow::addstartdownload" << downcount;
	download_info[downcount].speed = speed;
	download_info[downcount].stat = stat;
	download_info[downcount].percent = percent;
	download_info[downcount].filename = filename;

	connect(this, SIGNAL(refreshdowninfo(int,double,int,int,QString)), &downloadlist[downcount], SLOT(refreshdowninfo(int,double,int,int,QString)));

	setui_downloadlist(downcount);
	downstat[downcount]->setText("正在下载");
	downname[downcount]->setText(filename);
	//	emit refreshdowninfo(downcount,speed,percent,stat,filename); 
	//	&downloadlist[downcount].ui->downname->setText(filename);
}



void ManageWindow::adddownloadurl(int downcount,double speed,int percent,int stat,QString filename)
{
	qDebug() << "ManageWindow::adddownloadurl" << downcount;
	download_info[downcount].speed = speed;
	download_info[downcount].stat = stat;
	download_info[downcount].percent = percent;
	download_info[downcount].filename = filename;

	connect(this, SIGNAL(refreshdowninfo(int,double,int,int,QString)), &downloadlist[downcount], SLOT(refreshdowninfo(int,double,int,int,QString)));

	downprogress[downcount]->setValue(percent);
	//	emit refreshdowninfo(downcount,speed,percent,stat,filename); 
	//	UiDownlist[downcount].downname->setTest(filename);

	//	&downloadlist[downcount]->ui->downname->setText(filename);
	/*
	   downloadlist[downcount].ui->downstat->setText(stat.toString());
	   this.downloadlist[downcount].ui->downprogress->setValue(percent);
	   */
}

void ManageWindow::loadUrlAddr()
{
	ui->Webview->load(QUrl(urlAddr->text()));
}

void ManageWindow::displayUrlAddr(const QUrl &url)
{
	qDebug() <<  url.toString();
	qDebug() <<  "urlChanged";
	urlAddr->setText(url.toString());
}

void ManageWindow::showTitle(const QString &title)
{
	this->setWindowTitle(title);
}


void ManageWindow::closeEvent(QCloseEvent *event)
{
	printf(" process exit\n");
	post_exit(1);
}
