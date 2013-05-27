#ifndef FTPCLIENTWINDOW_H
#define FTPCLIENTWINDOW_H

#include <QString>
#include <QUrlInfo>
#include <QHash>
#include <QtGui>
#include "ftpclient.h"

class QListWidgetItem;

namespace Ui {
class FtpClientWindow;
}

class FtpClientWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit FtpClientWindow(QWidget *parent = 0);
    ~FtpClientWindow();
    void configWidget();    /* 初始化控件的属性 */
    void initConnection();
	QString getCurrentPath() const;
	bool isDir(const QString &str) const;

signals:

private slots:
    void ftpHostChanged();
    void ftpPortChanged();
    void ftpUserChanged();
    void ftpPwdChanged();
    void ftpConnect();
    void mainWindowQuit();
    void addToList(const QUrlInfo &urlInfo);
    void DoubleClicked(QListWidgetItem *item);
    void downLoadFile(const QString &filename);
    void callDownload();
	void switchDownloadBtn(QListWidgetItem *item);
	void changeToParrent();
    
private:
	void clearMemory(QList<QListWidgetItem*> &listItemCtn);

private:
    Ui::FtpClientWindow *ui;
    Ftpclient ftpclient;
	QList<QListWidgetItem*> listItemCtn;
};

#endif // FTPCLIENTWINDOW_H
