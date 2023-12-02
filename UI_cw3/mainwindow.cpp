#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"

MainWindow::~MainWindow()
{
    delete ui;
    delete mediaPlayer;
    delete videoWidget;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set the initial size of the dialog
    // (Use iphone SE as a reference)
    resize(320, 650);

    // Set up the video widget and media player
    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);

    // Make video fill the space available while maintaining aspect ratio
    videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);

    // Set up the media player
    QUrl mediaUrl("qrc:/resource/video/cloud.mp4");
    mediaPlayer->setMedia(QMediaContent(mediaUrl));
    mediaPlayer->setVideoOutput(videoWidget);

    // Create a playlist and set it to loop
    QMediaPlaylist *playlist = new QMediaPlaylist(mediaPlayer);
    playlist->addMedia(QMediaContent(mediaUrl));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    mediaPlayer->setPlaylist(playlist);

    // Layout for video widget
    QVBoxLayout *videoLayout = new QVBoxLayout;
    videoLayout->addWidget(videoWidget);

    // Set up a container for the video widget
    QWidget *videoContainer = new QWidget;
    videoContainer->setLayout(videoLayout);
    videoContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Set up the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(videoContainer, 1);
    mainLayout->addWidget(ui->groupButton, 0);

    // Set the central widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Start playing the video
    mediaPlayer->play();
}

void MainWindow::on_login_clicked()
{
    mediaPlayer->stop();
    close();
    l = new Login(this);
    l->show();
}
