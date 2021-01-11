#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDropEvent>
#include <QUrl>
#include <QMimeData>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/MetaManager.h>
#include <VLCQtWidgets/WidgetVideo.h>
#include <VLCQtWidgets/WidgetVolumeSlider.h>
#include <VLCQtCore/Audio.h>

namespace Ui {
class MainWindow;
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;
class VlcMetaManager;
class VlcWidgetVideo;
class VlcAudio;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void stateChanged(const Vlc::State &);

private slots:
    void on_actionOpen_triggered();

    void on_pushButton_clicked();

    void on_stopButton_clicked();

    void on_showVideo_clicked();

    void startPlay();

    void createVideoWindow();

    void dragEnterEvent(QDragEnterEvent *event);

    void dropEvent(QDropEvent *event);

    void setState(Vlc::State state);

    void stateUpdate();


private:
    Ui::MainWindow *ui;

    VlcMedia *mmedia;
    VlcInstance *minstance;
    VlcMediaPlayer *mplayer;
    VlcMetaManager *mmeta;
    VlcAudio *maudio;

    VlcWidgetVideo  *window;
};

#endif // MAINWINDOW_H
