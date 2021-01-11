#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QWidget>

#include <QString>

#include <QDebug>

#include "videowidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    //mmedia(0),
    ui(new Ui::MainWindow),
    window(new VideoWidget)
{
    ui->setupUi(this);
    ui->statusBar->showMessage(" Open File to Play "); 
    /*hide the showVideo button*/
    ui->showVideo->setVisible(false);

    minstance = new VlcInstance(VlcCommon::args(),this);
    mplayer = new VlcMediaPlayer(minstance);
    maudio = new VlcAudio(mplayer);
    maudio->setVolume(50);
    mplayer->setVideoWidget(window);

    ui->widgetSeekProgress->setMediaPlayer(mplayer);
    ui->verticalSlider->setValue(50);

    setAcceptDrops(true);

    connect(mplayer,SIGNAL(stateChanged()),this,SLOT(stateUpdate()));
    connect(ui->verticalSlider,SIGNAL(sliderMoved(int)),maudio,SLOT(setVolume(int)));

}

MainWindow::~MainWindow()
{
    window->close();
    delete window;
    delete mplayer;
    delete mmedia;
    delete minstance;
    delete maudio;
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{

    QString file = QFileDialog::getOpenFileName(this,tr("Open File"),
                                               QDir::homePath(),
                                               tr("Music files(*)"));
    if (file.isEmpty())
        return ui->statusBar->showMessage("Failed to load music");

    //uncomment if you want to debug and need fast audio file access
    //but you had to comment the preceeded QFileDialog//

    //QString file = "F:/Music/Dewi Lestari - Malaikat Juga Tahu.mp3";
    //

    ui->statusBar->showMessage(file);
    mmedia = new VlcMedia(file, true, minstance);

    ui->stopButton->setEnabled(true);
    qDebug() << "Got " <<ui->pushButton->isChecked();

    mplayer->openOnly(mmedia);
    startPlay();
}

void MainWindow::on_pushButton_clicked()
{
    //I don't know why
    // the conditional statement is producing
    // "false", so the button control is reversed
    if (ui->pushButton->isChecked()){
        ui->pushButton->setText("Play");
        mplayer->pause();
        ui->pushButton->setChecked(true);
    } else {
        mplayer->resume();
        ui->pushButton->setChecked(false);
        ui->pushButton->setText("Pause");
    }

}

void MainWindow::on_stopButton_clicked()
{
    mplayer->stop();
    ui->stopButton->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->showVideo->setVisible(false);
    ui->ActionLabel->setText("-");
    ui->statusBar->showMessage("No songs loaded");
}



void MainWindow::on_showVideo_clicked()
{
    if(ui->showVideo->isChecked()){
        createVideoWindow();
        ui->showVideo->setText("Hide Video Window");
        ui->showVideo->setChecked(true);
    }else{
        window->close();
        ui->showVideo->setText("Show Video Window");
        ui->showVideo->setChecked(false);
    }
    qDebug() << "shooooow" << ui->showVideo->isChecked();
}

void MainWindow::startPlay()
{
    mplayer->play();

    // Just conditioning for play button
    ui->pushButton->setEnabled(true);
    ui->pushButton->setCheckable(true);
    ui->pushButton->setChecked(false);
    ui->pushButton->setText("Pause");
    //
    // create objects of meta manager
    mmeta = new VlcMetaManager(mmedia);
    ui->ActionLabel->setText(QString("%1 - %2 - %3")
                             .arg(mmeta->artist())
                             .arg(mmeta->title())
                             .arg(mmeta->album())
                             );
    //

    /* show the hidden button */
    ui->showVideo->setVisible(true);
}

void MainWindow::createVideoWindow()
{
    window->resize(320, 240);
    //! [create, resize and show]
    window->setWindowTitle("Video Window");
    window->show();
}

/* accepting drag and drop events */
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QString file;
    foreach (const QUrl &url, event->mimeData()->urls()) {
         file = url.toLocalFile();
        //qDebug() << "Dropped file:" << fileName;
        ui->statusBar->showMessage(file);
    }
    mmedia = new VlcMedia(file, true, minstance);
    ui->stopButton->setEnabled(true);
    //qDebug() << "Got " <<ui->pushButton->isChecked();
    ui->showVideo->setEnabled(true);
    mplayer->openOnly(mmedia);
    startPlay();

}
/* */
void MainWindow::setState(Vlc::State state)
{
    switch(state)
    {
    case Vlc::Stopped:
        ui->pushButton->setText("Play");
        qDebug() << "STopped";
    default:
        break;
    }
}

void MainWindow::stateUpdate()
{
    switch(mmedia->state())
    {
        case Vlc::Playing:
            break;
        case Vlc::Idle:
            break;
        case Vlc::Opening:
            break;
        case Vlc::Buffering:
            break;
        case Vlc::Paused:
            break;
        case Vlc::Stopped:
            break;
        case Vlc::Ended:
            ui->pushButton->setText("Play");
            ui->ActionLabel->setText("No Songs Loaded");
            ui->showVideo->setVisible(false);
            ui->statusBar->showMessage("-");
            break;
        case Vlc::Error:
        default:
            break;
    }

    emit stateChanged(mmedia->state());
}



