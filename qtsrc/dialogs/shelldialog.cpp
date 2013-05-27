#include "shelldialog.h"
#include "ui_shelldialog.h"

ShellDialog::ShellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShellDialog)
{
    ui->setupUi(this);
	this->setWindowTitle("android shell");

	shellWidget = new ShellWidget(ui->QW_shell);
	shellWidget->setFixedSize(650,480);
}

ShellDialog::~ShellDialog()
{
    delete ui;
}
