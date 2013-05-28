#ifndef SCREENSHOTWIDGET_H
#define SCREENSHOTWIDGET_H

#include <QWidget>
#include "../threads/screenshotthread.h"

namespace Ui {
class ScreenshotWidget;
}

class ScreenshotWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ScreenshotWidget(QWidget *parent = 0);
    ~ScreenshotWidget();
    
private:
    Ui::ScreenshotWidget *ui;
    ThreadScreenshot threadScreenshot;
	QPixmap screenshot;
private slots:
    void takeScreenshot();
    void showScreenshot(QImage, int, int);
};

#endif // SCREENSHOTWIDGET_H
