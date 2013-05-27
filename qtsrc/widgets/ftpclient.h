#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QString>
#include <QHash>
#include <QProgressDialog>

class Ftpclient : public QObject
{
    Q_OBJECT
public:
    explicit Ftpclient(QObject *parent = 0);
    virtual ~Ftpclient();
    void ftpConnect();
    void ftpLogout();
    void initConnection();
    void setServerName(const QString &server) { strSrvName = server; }
    void setServerPort(const QString &port) { strSrvPort = port; }
    void setUserName(const QString &userName) { strUser = userName; }
    void setPwd(const QString &pwd) { strPwd = pwd; }
    void setCurrentPath(QString &path);
    QString getCurrentPath() const { return curPath; }
    QString getUrlStr(const QUrl &url);
	bool isDir(const QString &str) const;
	void downloadFile(const QString &filename);
    
signals:
    void cmdAddToList(const QUrlInfo &urlInfo);
	void currentPathChanged(const QString &path);
    
public slots:
    void ftpcommandStarted(int id);
    void ftpcommandFinished(int id, bool error);
    void addToList(const QUrlInfo &urlInfo);
    void changeDir(const QString &dir);
    void updateProgressBar(int done, int total);

private:
    QFtp ftp;
    QUrl url;
    bool connected;
    QFile *file;
    QProgressDialog *progressDlg;

    /* 服务器、端口、用户名和密码 */
    QString strSrvName, strSrvPort, strUser, strPwd;
    /* 当前路径 */
    QString curPath;
	/* 记录是文件还是路径 */
	QHash<QString, bool> isDirHash;
    int connectId, loginId, closeId;
};

#endif // FTPCLIENT_H
