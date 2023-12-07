#include "home.h"
#include "profile.h"
#include <QTextEdit>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QLineEdit>

Home::Home(QWidget *parent) :
    QDialog(parent),
    commentsTextEdit(nullptr)
{
    // Button on the left side of the search line
    QPushButton *addButton = new QPushButton("Upload", this);

    // Search line edit
    QLineEdit *searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Search here...");

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
    videoWidget->setMinimumHeight(300);

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
                          "  background: rgb(130, 139, 168);"
                          "  border: 1px solid #1BC0FB;"
                          "  width: 18px;"
                          "  margin: -3px 0;"
                          "  border-radius: 3px;"
                          "}"

                          "QSlider::add-page:horizontal {"
                          "  background: rgb(99, 100, 157);"
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
    speedBox->setMinimumWidth(80);

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

    // Horizontal layout for current playing video's name
    QHBoxLayout *nameLayout = new QHBoxLayout;

    nowPlayingLabel = new QLabel("Now Playing: ", this);
    nameLayout->addWidget(nowPlayingLabel);

    volumeSlider->setStyleSheet(sliderStyle);

    volumeLayout->addWidget(playButton);
    volumeLayout->addWidget(stopButton);
    volumeLayout->addWidget(volumeLabel);
    volumeLayout->addWidget(volumeSlider);
    connect(volumeSlider, &QSlider::valueChanged, this, &Home::setVolume);

    // Thumbnails section
    QPushButton *thumb1Button = new QPushButton("", this);
    QPushButton *thumb2Button = new QPushButton("", this);
    QPushButton *thumb3Button = new QPushButton("", this);

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

    QString scrollbarStyle = R"(
    QScrollArea {
        border: 2px solid rgb(99, 100, 157);
        border-radius: 4px;
    }
    QScrollBar:vertical, QScrollBar:horizontal {
        background: rgb(99, 100, 157);
    }
    QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
        background: rgb(166, 175, 200);
        border: 1px solid #1BC0FB;
        border-radius: 3px;
    }
    )";

    thumbnailScrollArea->setStyleSheet(scrollbarStyle);

    // Initialize the button to video map
    buttonVideoMap[thumb1Button] = "qrc:/resource/video/thumbtest1.mp4";
    buttonVideoMap[thumb2Button] = "qrc:/resource/video/thumbtest2.mp4";
    buttonVideoMap[thumb3Button] = "qrc:/resource/video/thumbtest3.mp4";

    // Set thumbnails for buttons
    thumb1Button->setIcon(QIcon(":/resource/img/thumbtest1.jpg"));
    // Set the icon size to match the button size
    thumb1Button->setIconSize(QSize(250, 250));
    // Remove border and background from the button
    QString thumbBtnStyle = "QPushButton { border: none; border-radius: 3px}";
    thumb1Button->setStyleSheet(thumbBtnStyle);

    thumb2Button->setIcon(QIcon(":/resource/img/thumbtest2.jpg"));
    thumb2Button->setIconSize(QSize(250, 250));
    thumb2Button->setStyleSheet(thumbBtnStyle);

    thumb3Button->setIcon(QIcon(":/resource/img/thumbtest3.jpg"));
    thumb3Button->setIconSize(QSize(250, 250));
    thumb3Button->setStyleSheet(thumbBtnStyle);


    // Connect thumbnail buttons to slot
    connect(thumb1Button, &QPushButton::clicked, this, &Home::onThumbnailClicked);
    connect(thumb2Button, &QPushButton::clicked, this, &Home::onThumbnailClicked);
    connect(thumb3Button, &QPushButton::clicked, this, &Home::onThumbnailClicked);

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
    mainLayout->addLayout(nameLayout);
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
    // Set the timeout duration
//    notificationTimer->setInterval(2000000);
    notificationTimer->setInterval(5000);
    notificationTimer->start();

    // Set a minimum size for the dialog
    // (Use iPhone SE as a reference)
    setMinimumSize(320, 650);
    resize(320, 650);

    QString appStyle =
        "QPushButton {"
        "  background-color: rgb(130, 139, 168);"
        "  color: white;"
        "  border-radius: 15px;"
        "  padding: 5px;"
        "  border: 3px solid rgb(99, 100, 157);"
        "}"
        "QPushButton:pressed {"
        "  background-color: rgb(120, 138, 249);"
        "}"
        "QPushButton:hover {"
        "  background-color: rgb(62, 76, 139);"
        "  color: #1BC0FB;"
        "}"
        "QLabel {"
        "  color: #d3d3d3;"
        "  font-weight: bold;"
        "}"
        "QLineEdit {"
        "  border: 2px solid rgb(99, 100, 157);"
        "  border-radius: 4px;"
        "  background: white;"
        "  color: black;"
        "}"
        "QTextEdit {"
        "  background-color: rgb(240, 240, 240);"
        "  color: rgb(60, 60, 60);"
        "  border: 2px solid rgb(200, 200, 200);"
        "  border-radius: 5px;"
        "  padding: 5px;"
        "  font-family: 'Arial';"
        "  font-size: 12pt;"
        "}"
        "QTextEdit:focus {"
        "  border: 2px solid rgb(100, 149, 237);"
        "}"
        "QLineEdit:focus {"
        "  border-color: rgb(62, 76, 139);"
        "}"
        "QComboBox {"
        "  border: 2px solid rgb(100, 100, 150);"
        "  border-radius: 5px;"
        "  background-color: rgb(255, 255, 255);"
        "  color: rgb(50, 50, 50);"
        "}"
        "QComboBox QAbstractItemView {"
        "  border: 2px solid darkgray;"
        "  selection-background-color: lightgray;"
        "}";
    profileButton->setStyleSheet("QPushButton {margin: 3px 0 0 3px;}");
    setStyleSheet(appStyle);
}

//void Home::on_viewComments_clicked()
//{
//    if (commentsTextEdit == nullptr)
//    {
//        // Create the QTextEdit if it doesn't exist
//        commentsTextEdit = new QTextEdit(this);
//        commentsTextEdit->setPlaceholderText("Type your comments here");
//        QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(this->layout());
//        layout->addWidget(commentsTextEdit);


//    }

//    // Toggle visibility of the QTextEdit
//    commentsTextEdit->setVisible(!commentsTextEdit->isVisible());

//}

void Home::on_viewComments_clicked()
{
    if (commentsTextEdit == nullptr)
    {
        // Create the QTextEdit if it doesn't exist and initially set it to not visible
        commentsTextEdit = new QTextEdit(this);
        commentsTextEdit->setPlaceholderText("Type your comments here");
        QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(this->layout());
        layout->addWidget(commentsTextEdit);
         // Initial visibility is set to false
        commentsTextEdit->setVisible(false);
        // Ensure the videoWidget has the correct initial minimum height
        videoWidget->setMinimumHeight(300);
    }

    // Toggle visibility of the QTextEdit
    bool isVisible = commentsTextEdit->isVisible();
    commentsTextEdit->setVisible(!isVisible);

    // Adjust the minimum height of the videoWidget based on the visibility of the comments
    if (isVisible)
    {
        // Set back to original minimum height
        videoWidget->setMinimumHeight(300);
    }
    else
    {
        // Set to smaller size when comments are visible
        videoWidget->setMinimumHeight(200);
    }
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
        QFileInfo fileInfo(fileName);
        updateNowPlayingLabel(fileInfo.fileName());
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

// Slot for handling thumbnail click
void Home::onThumbnailClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());

    QString videoPath = buttonVideoMap[clickedButton];

    QFileInfo fileInfo(videoPath);
    updateNowPlayingLabel(fileInfo.fileName());

    player->setMedia(QUrl(videoPath));
    player->play();

    playButton->setText("Pause");

}

void Home::updateNowPlayingLabel(const QString &videoName) {
    nowPlayingLabel->setText("Now Playing: " + videoName);
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
