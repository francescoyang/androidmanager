#include "downlist.h"
#include "ui_downlist.h"
#include <QPixmap>
#include <QListWidgetItem>
#include <QIcon>
#include <iostream>

Downloadlist::Downloadlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiDownlist )
{
    ui->setupUi(this);
}

Downloadlist::~Downloadlist()
{
    delete ui;
}

void Downloadlist::refreshdowninfo(int downcount,double speed,int percent,int stat,QString filename)
{
	
//	ui->downstat->setText(stat.toString());
	ui->downname->setText(filename);
	ui->downprogress->setValue(percent);

}
