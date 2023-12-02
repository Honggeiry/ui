#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>
#include <QPixmap>
#include "setting.h"

namespace Ui {
class Profile;
}

class Profile : public QDialog
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();

private slots:
    void on_goBackButton_clicked();
    void on_buttonSetting_clicked();

private:
    Ui::Profile *ui;
    Setting *set;
};

#endif // PROFILE_H
