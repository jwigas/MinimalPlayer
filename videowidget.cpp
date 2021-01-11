#include "videowidget.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include "mainwindow.h"

VideoWidget::VideoWidget(QWidget *parent)
    : VlcWidgetVideo(parent)
{
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setPalette(p);

    setAttribute(Qt::WA_OpaquePaintEvent);
}

VideoWidget::~VideoWidget()
{
}

void VideoWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape ) {
        setWindowState(windowState() & ~Qt::WindowFullScreen);
        event->accept();
    }else {
        VlcWidgetVideo::keyPressEvent(event);
    }
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(windowState() != Qt::WindowFullScreen)
        setWindowState(windowState() | Qt::WindowFullScreen);
    else
        setWindowState(windowState() & ~Qt::WindowFullScreen);
    event->accept();
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    VlcWidgetVideo::mousePressEvent(event);
}
