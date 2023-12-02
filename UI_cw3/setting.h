#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private slots:
    void on_goBackButton_clicked();

private:
    Ui::Setting *ui;
};

#endif // SETTING_H
