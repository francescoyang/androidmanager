#ifndef SHELLDIALOG_H
#define SHELLDIALOG_H

#include <QDialog>
#include "widgets/shellwidget.h"

namespace Ui {
class ShellDialog;
}

class ShellDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ShellDialog(QWidget *parent = 0);
    ~ShellDialog();

	ShellWidget *shellWidget;
    
private:
    Ui::ShellDialog *ui;
};

#endif // SHELLDIALOG_H
