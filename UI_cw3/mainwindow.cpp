#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include <QMenuBar>

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

    QPixmap pix(":/resource/img/logo.jpg");
    ui->logo->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QVBoxLayout *layout = new QVBoxLayout;

    // Align the content of the label to the center
    ui->logo->setAlignment(Qt::AlignCenter);

    layout->addWidget(ui->logo);

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
    videoLayout->addLayout(layout);
    videoLayout->addWidget(videoWidget);

    // Set up a container for the video widget
    QWidget *videoContainer = new QWidget;
    videoContainer->setLayout(videoLayout);
    videoContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    videoContainer->setStyleSheet("QWidget { "
                                  "border-radius: 15px; "
                                  "background-color: rgb(99, 100, 157); "
                                  "}");

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
