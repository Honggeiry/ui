#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "home.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

// Signal to show the main window
signals:
    void showMainWindow();

private slots:
    void on_loginButton_clicked();

private:
    Ui::Login *ui;
    Home *h;
};

#endif // LOGIN_H
