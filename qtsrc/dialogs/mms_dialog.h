#ifndef MMS_DIALOG_H
#define MMS_DIALOG_H

#include <QDialog>

namespace Ui {
	class MMS_Dialog;
}

class MMS_Dialog : public QDialog
{
	Q_OBJECT

	public:
		explicit MMS_Dialog(QWidget *parent = 0);
		~MMS_Dialog();
		Ui::MMS_Dialog *ui;

		void setnumber(QString);

		QString mmsnumber;
		QString mmsdata;
	private:
		void get_data();
	signals:
		void mmsdlg_accept();
	private slots:
		void dialog_accept();
};

#endif // MMS_DIALOG_H
