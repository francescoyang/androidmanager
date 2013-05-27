#include <QDebug>
#include "mms_dialog.h"
#include "ui_mms_dialog.h"

MMS_Dialog::MMS_Dialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MMS_Dialog)
{
	ui->setupUi(this);
	this->setWindowTitle("发送 短信");
	get_data();
}

MMS_Dialog::~MMS_Dialog()
{
	delete ui;
}

void MMS_Dialog::get_data()
{

//	connect(this->mms_dialog, SIGNAL(clicked()),this, SLOT(get_message()));

	connect(ui->Btn_send, SIGNAL(clicked()), this, SLOT(dialog_accept()));
}
void MMS_Dialog::dialog_accept()
{
	mmsnumber = ui->Tedt_number->toPlainText();
	mmsdata	= ui->Tedt_data->toPlainText();
	emit mmsdlg_accept();
	this->accept();
}

void MMS_Dialog::setnumber(QString number)
{
	ui->Tedt_number->setText(number);
}
