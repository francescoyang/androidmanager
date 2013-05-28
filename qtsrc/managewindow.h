#ifndef MANAGEWINDOW_H
#define MANAGEWINDOW_H

#include <QWidget>
#include <QtGui>
#include <QThread>
#include <QMainWindow>
#include <QProcess>
#include <QTableWidget>
#include <QCloseEvent>
#include <string.h>
#include <QDesktopServices>


#include "ui_dialog.h"
#include "animation.h"

#include "amevent.h"

#include "dialogs/mms_dialog.h"
#include "dialogs/logcatdialog.h"
#include "dialogs/shelldialog.h"

#include "classes/downloadmanager.h"
#include "classes/processpthread.h"
#include "classes/daemon.h"

#include "widgets/webPage.h"
#include "widgets/ftpclientwindow.h"
#include "widgets/downlist.h"

#include "backpthread.h"

#include "picturelistmodel.h"
#include "manager_api.h"
#include "pthread_api.h"
#include "typestruct_api.h"


//#include "classes/settings.h"


#define MENU			1
#define CONNECT			2
#define VIDEO			3
#define MUSIC			4
#define MASSIGE			5
#define WEBVIEW			6	
#define MMS				7
#define IMAGE			8
#define APP				9	
#define	SETTINGS		10 
#define	BOOK			11 
#define	STORAGE			12
#define	DOWNLOADLIST	13
#define	TEST			18
#define MAXLIST			1000




class QString;
class QPushButton;
class QProcess;
class QHBoxLayout;

class Player;

typedef struct __refreshsign{
	int book = 1;
	int mms	= 1;
	int app	= 1;
	int image= 1;
	int video= 1;
	int music= 1;
}refreshsign_t;

typedef struct __settingsargv{
	int skin = 1;
	int opacity = 0;
	QString downloadpath;
}settingsargv_t;

namespace Ui {
	class ManageWindow;
}

class ManageWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit ManageWindow(QWidget *parent = 0);
		~ManageWindow();

		allappinfo_t uiappinfo;
		allmmsinfo_t uimmsinfo;
		allbookinfo_t uibookinfo;
		storageinfo_t uistorageinfo;
		DownloadManager *addmanager;

	private:

		QLabel *downname[1000];
		QProgressBar *downprogress[1000];
		QLabel *downstat[1000];
		QWidget UiDownlist[1000];

		Ui::ManageWindow *ui;
		Ui::dialog *dialogUi; 

		MMS_Dialog *mms_dialog;
		Animation *m_anim;
		Animation *refresh_anim;

		webPage *page;
		FtpClientWindow *ftpfilelist;
		Downloadlist  downloadlist[1000];	

		QDialog *dlg = new QDialog;
		LogcatDialog *logcat;

		Backthread* BackThread;
		Daemon* DaemonThread;
		ProcessThread *adbthread;
		ShellDialog *shelldialog;
		//		Mysetting *mysettings;

		refreshsign_t refreshsign;
		settingsargv_t settingsargv;

		QSettings * settings;
		deviceslist_t m_devices;
		QString styleSheet;

		// add image ui
		PictureListModel *listModel;

		// add app ui

		QTableWidget* Downloadlist_table;
		QTableWidgetItem *Downloadlist_item[300][3];

		QTableWidget* App_table;
		QTableWidgetItem *App_item[300][3];

		// add mms ui
		QTableWidget* Mms_table;
		QTableWidgetItem *Mms_item[500][3];


		// add book ui
		QTableWidget* Book_table;
		QTableWidgetItem *Book_item[1000][3];

		// add player
		Player *player;
		QHBoxLayout *buttonLayout;
		QPushButton *openFileButton;
		QPushButton *playButton;
		QPushButton *stopButton;
		QPushButton *stepButton;
		QPushButton *backwardButton;
		QPushButton *muteButton;
		QString currentFileName;
		// end player


		//add web
		QLineEdit *urlAddr;
		QPushButton *goBack;
		QPushButton *goForward;
		QPushButton *pageReload;
		QPushButton *pageStop;
		// end web


	private:

		typedef struct __downloadindex{
			int percent;
			int stat;
			double speed;
			QString filename;
		}downloadindex_t;

		downloadindex_t download_info[MAXLIST];



		//		allappinfo_t uiappinfo;
		char APPSIGN = -1;
		char DOWNLOADSIGN = -1;
		char APPINDEX = 0;
		char BOOKSIGN = -1;
		char MMSSIGN = -1;

		int adbcount = 0;
		int testapp;
		int appindex[4][100];

		QString mmsnumber;
		QString mmsdata;

	private:

		// Load UI
		void LoadMms();
		void LoadConnect();
		void LoadApp();
		void LoadMusic();
		void LoadVideo();
		void LoadImage();
		void LoadSettings();
		void LoadWebview();
		void LoadBook();
		void LoadDownloadlist();
		void LoadFtpfilelist();
		void LoadQmenu();
		void setIcon();
		void Mysettingsinit();
		void ProcessThreadInit();
		void DaemonQthreadInit();
		void ProcessQthreadinit();
		void BackQthreadInit();
		void ClassTestInit();
		void UiToolInit();
		void Animationinit();
		void connectinit();
		void Refreshlabinit();
		void Qssinit(int argc);

		void post_uninstall(int);
		void post_install(int);
		void post_softinit(int);
		void post_exit(int);
		void post_monitorusb(int);
		void post_daemon(int);
		void post_test(int);
		void post_sendmms(int);
		void post_refresh(int);

		void recv_test(int res);
		void recv_daemon(int cmd);
		void recv_softinit(int res);
		void recv_uninstall(int res);
		void recv_sendmms(int res);
		void recv_install(int res);
		void recv_monitorusb(int res);
		void recv_refresh(int res);

		void customEvent(QEvent* e);
		void SoftInit();
		void Makeconnect();
		void CurrentWidget(int P_NUM);

		// add player

		void video_player();
		// end player

		QLabel* label;
		void showPicture(const QModelIndex &index);


		private slots:
			void adbresult(int,int,int);	
		void Menuaction(int);
		void slotAboutApplication();
		void on_Btn_video_clicked();
		void on_Btn_music_clicked();
		void on_Btn_massage_clicked();
		void on_Btn_app_clicked();
		void on_Btn_book_clicked();
		void goto_connect();
		void goto_appstore();
		void goto_book();
		void goto_manager();
		void goto_storage();
		void goto_wdj();
		void goto_imagelist();
		void goto_applist();
		void goto_jf();
		void goto_uninstall();
		void goto_install();
		void goto_logcat();
		void goto_settings();
		void goto_setdownloadpath();
		void goto_sendmms();
		void goto_booksendmms();
		void goto_call();
		void goto_shell();
		void goto_refreshsystem();
		void goto_helpdev();
		void goto_mmsrefresh();
		void goto_mmsdetail();

		void get_message();

		void listItemChanged(const QModelIndex &current, const QModelIndex &previous);

		void btn_app_clicked();
		void btn_book_clicked();

		void setui_appinfo();
		void setui_appclass(int);
		void setui_downloadlist(int);
		void setui_mmsinfo();
		void setui_bookinfo();
		void setui_storageinfo();
		void setui_clean();

		void Mms_clicked(int,int);
		void App_clicked(int,int);
		void Book_clicked(int,int);
		void Download_clicked(int x,int y);

		void slotTrans(int value);
		void slotStyleChange(int StyleString);
		void StyleChange(int StyleString,QDialog *test);
		//		void slotappclasschange(QString StyleString);
		void slotappclasschange(int);
		void valuechange(int);
		void reject();
		void accept();
		// add player
		void slotPlay(); 		// 播放
		void slotStop(); 		// 停止
		void slotStep(); 		// 步进
		void slotBackward(); 	// 后退
		void slotMute(bool status); // 静音
		void slotOpenFile();
		void slotStarted();
		void slotError(QProcess::ProcessError error);
		void slotFinished(int exitCode, QProcess::ExitStatus exitStatus);
		void slotBackMessage();
		void adddownloadurl(int,double,int,int,QString);
		void addstartdownload(int,double,int,int,QString);


		// add web
		void loadUrlAddr();
		void displayUrlAddr(const QUrl &);
		void showTitle(const QString &);
		void addadbcmdslot(int,int,int,QString);


signals:
		void addadbcmd(int,int,QString);
		void refreshdowninfo(int,double,int,int,QString);

	protected:
		void closeEvent(QCloseEvent *event);
		//bool acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type);
};

#endif // MANAGEWINDOW_H
