#include "screenshotwidget.h"
#include "ui_screenshotwidget.h"

ScreenshotWidget::ScreenshotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenshotWidget)
{
    ui->setupUi(this);
	takeScreenshot();
}

ScreenshotWidget::~ScreenshotWidget()
{
    delete ui;
}


void ScreenshotWidget::takeScreenshot()
{
    threadScreenshot.widthScreen = this->ui->QLb_screens->width();
    threadScreenshot.heightScreen = this->ui->QLb_screens->height();
    threadScreenshot.start();
    connect(&threadScreenshot, SIGNAL(gotScreenshot(QImage, int, int)), this, SLOT(showScreenshot(QImage, int, int)));
}


void ScreenshotWidget::showScreenshot(QImage image, int width, int height)
{
    QSize scaledSize = QSize(width, height);
    scaledSize.scale(this->size(), Qt::KeepAspectRatio);
    this->screenshot = QPixmap::fromImage(image, Qt::AutoColor);
    this->ui->QLb_screens->setPixmap(this->screenshot.scaled(this->ui->QLb_screens->size(),
                                                             Qt::KeepAspectRatio,
                                                             Qt::SmoothTransformation));
    disconnect(this, SLOT(showScreenshot(QImage,int,int)));
}
