#include <QSettings>

struct Login {
	QString userName;
	QString password;
};

class Mysetting : public QSettings
{
	Q_OBJECT
	public:
		Mysetting(QSettings*);
		~Mysetting();
		QSettings  settings;

		void mysettinginit();
		void mysettingdefault();
	private:
		QObject* MainWidget;
		void setdaownloadpath(char *);
	private:
};


