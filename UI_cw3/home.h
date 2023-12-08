#ifndef HOME_H
#define HOME_H

#include <QDialog>
#include "profile.h"

#include <QTextEdit>
#include <QScrollArea>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>
#include <QLabel>
#include <QComboBox>

#include <QMap>

class QTextEdit;
class QTimer;

namespace Ui {
class Home;
}

class Home : public QDialog
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

private slots:
    void on_profileButton_clicked();
    void on_viewComments_clicked();
    void showNotification();
    void on_addButton_clicked();
    void togglePlayStop();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);
    void sliderMoved(int position);
    void updateLabelTime(qint64 milliseconds);
    void changePlaybackSpeed(int index);
    void setVolume(int volume);
    void stopVideo();
    void onThumbnailClicked();
    void updateNowPlayingLabel(const QString &videoName);
    void toggleLikeButton();

private:
    Ui::Home *ui;
    Profile *p;

    QTextEdit *commentsTextEdit;
    QTimer *notificationTimer;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QPushButton *playButton;
    QSlider *timeSlider;
    QLabel *timeLabel;
    QComboBox *speedBox;
    QLabel *nowPlayingLabel;

    QMap<QPushButton*, QString> buttonVideoMap;
    // To keep track of like button state
    bool isLiked = false;
    QPushButton *likeButton;

};

#endif // HOME_H
