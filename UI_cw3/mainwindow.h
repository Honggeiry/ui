#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QMediaPlaylist>
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void showLoginWindow();
    ~MainWindow();

signals:
    void openLoginWindow();

private slots:
    void on_login_clicked();

public slots:
    void showWindow();

private:
    Ui::MainWindow *ui;
    QVideoWidget *videoWidget;
    QMediaPlayer *mediaPlayer;


    Login *l;
};
#endif // MAINWINDOW_H
