#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <VLCQtWidgets/WidgetVideo.h>

class VideoWidget : public VlcWidgetVideo
{
    Q_OBJECT

public:
    VideoWidget(QWidget *parent = 0);
    ~VideoWidget();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // VIDEOWIDGET_H
