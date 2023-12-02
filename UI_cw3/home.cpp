#include "home.h"
#include "ui_home.h"
#include "profile.h"
#include <QTextEdit>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>

Home::Home(QWidget *parent) :
    QDialog(parent)
{
    // Button on the left side of the search line
    QPushButton *addButton = new QPushButton("+", this);

    // Search line edit
    QLineEdit *searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Logo or Search here");

    // Profile button
    QPushButton *profileButton = new QPushButton("My Profile", this);
    connect(profileButton, &QPushButton::clicked, this, &Home::on_profileButton_clicked);

    // Top layout with new button, search, and profile button
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(addButton);
    topLayout->addWidget(searchEdit);
    topLayout->addWidget(profileButton);

    // Player frame placeholder
    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    player->setVideoOutput(videoWidget);
    videoWidget->setMinimumHeight(200);

    // Middle section for video player controls
    playButton = new QPushButton("Pause", this);
    QPushButton *stopButton = new QPushButton("Stop", this);
    timeSlider = new QSlider(Qt::Horizontal, this);
    // Initial range
    timeSlider->setRange(0, 100);

    QString sliderStyle = "QSlider::groove:horizontal {"
                          "  border: 1px solid #999999;"
                          "  height: 8px;"
                          "  background: rgb(99, 100, 157);"
                          "  margin: 2px 0;"
                          "}"

                          "QSlider::handle:horizontal {"
                          "  background: rgb(62, 76, 139);"
                          "  border: 1px solid #1BC0FB;"
                          "  width: 18px;"
                          "  margin: -3px 0;"
                          "  border-radius: 3px;"
                          "}"

                          "QSlider::add-page:horizontal {"
                          "  background: rgb(130, 139, 168);"
                          "}"

                          "QSlider::sub-page:horizontal {"
                          "  background:rgb(120, 138, 249);"
                          "}";

    timeSlider->setStyleSheet(sliderStyle);

    connect(timeSlider, &QSlider::sliderMoved, this, &Home::sliderMoved);
    timeSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    timeLabel = new QLabel("00:00:00", this);
    speedBox = new QComboBox(this);
    speedBox->addItem("0.5x", QVariant(0.5));
    speedBox->addItem("1.0x", QVariant(1.0));
    speedBox->addItem("1.5x", QVariant(1.5));

    // Set "1.0x" as the default selected item
    speedBox->setCurrentIndex(1);

    connect(speedBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changePlaybackSpeed(int)));

    QHBoxLayout *middleLayout = new QHBoxLayout;

    middleLayout->addWidget(timeSlider);
    middleLayout->addWidget(timeLabel);
    middleLayout->addWidget(speedBox);

    // Horizontal layout for volume controls and play stop buttons
    QHBoxLayout *volumeLayout = new QHBoxLayout;
    QLabel *volumeLabel = new QLabel("Volume", this);
    QSlider *volumeSlider = new QSlider(Qt::Horizontal, this);
    // Volume range from 0 to 100
    volumeSlider->setRange(0, 100);
    // Set initial volume to 50%
    volumeSlider->setValue(50);



    volumeSlider->setStyleSheet(sliderStyle);

    volumeLayout->addWidget(playButton);
    volumeLayout->addWidget(stopButton);
    volumeLayout->addWidget(volumeLabel);
    volumeLayout->addWidget(volumeSlider);
    connect(volumeSlider, &QSlider::valueChanged, this, &Home::setVolume);

    // Thumbnails section
    QPushButton *thumb1Button = new QPushButton("Video thumbnail1", this);
    QPushButton *thumb2Button = new QPushButton("Video thumbnail2", this);
    QPushButton *thumb3Button = new QPushButton("Video thumbnail3", this);

    // Set minimum size for thumbnail buttons
    thumb1Button->setMinimumSize(200, 150);
    thumb2Button->setMinimumSize(200, 150);
    thumb3Button->setMinimumSize(200, 150);

    QHBoxLayout *thumbnailLayout = new QHBoxLayout;
    thumbnailLayout->addWidget(thumb1Button);
    thumbnailLayout->addWidget(thumb2Button);
    thumbnailLayout->addWidget(thumb3Button);

    QScrollArea *thumbnailScrollArea = new QScrollArea(this);
    thumbnailScrollArea->setWidgetResizable(true);
    QWidget *thumbnailWidget = new QWidget;
    thumbnailWidget->setLayout(thumbnailLayout);
    thumbnailScrollArea->setWidget(thumbnailWidget);

    // Bottom section for comments
    QVBoxLayout *commentsLayout = new QVBoxLayout;
    QLabel *usernameLabel = new QLabel("Username", this);
    QPushButton *viewComments = new QPushButton("View Comments", this);
    connect(viewComments, &QPushButton::clicked, this, &Home::on_viewComments_clicked);
    commentsLayout->addWidget(usernameLabel);
    commentsLayout->addWidget(viewComments);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(videoWidget);
    mainLayout->addLayout(middleLayout);
    mainLayout->addLayout(volumeLayout);
    mainLayout->addWidget(thumbnailScrollArea);
    mainLayout->addLayout(commentsLayout);


    // Connect the play button to the togglePlayStop slot
    connect(playButton, &QPushButton::clicked, this, &Home::togglePlayStop);
    connect(stopButton, &QPushButton::clicked, this, &Home::stopVideo);

    connect(addButton, &QPushButton::clicked, this, &Home::on_addButton_clicked);


    // Connect media player signals
    connect(player, &QMediaPlayer::durationChanged, this, &Home::durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &Home::positionChanged);

    // Set the layout for the QDialog
    setLayout(mainLayout);

    // Initialize the timer
    notificationTimer = new QTimer(this);
    connect(notificationTimer, &QTimer::timeout, this, &Home::showNotification);
    notificationTimer->setInterval(2000000); // Set the timeout duration
    notificationTimer->start();

    // Set a minimum size for the dialog
    // (Use iPhone SE as a reference)
    setMinimumSize(320, 650);
    resize(320, 650);
}

void Home::on_viewComments_clicked()
{
    if (commentsTextEdit == nullptr)
    {
        // Create the QTextEdit if it doesn't exist
        commentsTextEdit = new QTextEdit(this);
        commentsTextEdit->setPlaceholderText("Type your comments here");
        QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(this->layout());
        layout->addWidget(commentsTextEdit);
    }

    // Toggle visibility of the QTextEdit
    commentsTextEdit->setVisible(!commentsTextEdit->isVisible());
}

void Home::showNotification()
{
    // Create the notification dialog
    QMessageBox notificationDialog(this);
    notificationDialog.setWindowTitle("Notification");
    notificationDialog.setText("Time to upload videos!");

    // Set the size of the dialog
    notificationDialog.setFixedSize(200, 30);

    // Get the geometry of the main window
    QRect mainWindowGeometry = this->geometry();

    // Calculate the position to place the notification above the main window
    int x = mainWindowGeometry.x() + (mainWindowGeometry.width() - notificationDialog.width()) / 2.5;
    int y = mainWindowGeometry.y() - notificationDialog.height() + 35;

    // Move the dialog to the calculated position
    notificationDialog.move(x, y);

    // Show the notification dialog
    notificationDialog.exec();

    // Stop the timer when the user opens another dialog
    notificationTimer->stop();
}

void Home::on_addButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Video"), "", tr("Video Files (*.mp4 *.avi *.mkv)"));
    if (!fileName.isEmpty())
    {
        player->setMedia(QUrl::fromLocalFile(fileName));
        player->play();
        // Set to "Pause" because playback starts immediately
        playButton->setText("Pause");
    }
    else
    {
        // If no file is selected (dialog cancelled), set the button text back to "Continue"
        playButton->setText("Continue");
    }
}


void Home::togglePlayStop()
{
    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
        playButton->setText("Continue");
    } else {
        player->play();
        playButton->setText("Pause");
    }
}

void Home::stopVideo()
{
    // Pause the video playback instead of stopping
    player->pause();
    // Reset the position to the start
    player->setPosition(0);
    playButton->setText("Continue");
    timeSlider->setValue(0);

    updateLabelTime(0);
}



void Home::durationChanged(qint64 duration)
{
    timeSlider->setMaximum(duration);
    updateLabelTime(duration);
}

void Home::positionChanged(qint64 position)
{
    if (!timeSlider->isSliderDown()) {
        timeSlider->setValue(position);
    }
    updateLabelTime(position);
}

void Home::sliderMoved(int position)
{
    player->setPosition(position);
}

void Home::updateLabelTime(qint64 milliseconds)
{
    int seconds = (milliseconds / 1000) % 60;
    int minutes = (milliseconds / (1000 * 60)) % 60;
    int hours = (milliseconds / (1000 * 60 * 60)) % 24;

    QTime time(hours, minutes, seconds);
    timeLabel->setText(time.toString("hh:mm:ss"));
}

void Home::changePlaybackSpeed(int index)
{
    qreal speed = speedBox->itemData(index).toDouble();
    player->setPlaybackRate(speed);
}

void Home::setVolume(int volume)
{
    player->setVolume(volume);
}

Home::~Home(){}

void Home::on_profileButton_clicked()
{
    // Stop the timer when the user opens another dialog
    notificationTimer->stop();
    hide();
    p = new Profile(this);
    p->show();
}