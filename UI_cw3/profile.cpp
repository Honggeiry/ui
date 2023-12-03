#include "profile.h"
#include "ui_profile.h"
#include "home.h"
#include "setting.h"

Home* h2;
Profile::Profile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);

    setWindowTitle("Profile");

    // Set the initial size of the dialog
    // (Use iphone SE as a reference)
    setMinimumSize(320, 650);
    resize(320, 650);

    QPixmap pix(":/resource/img/temp.jpg");
    int w = ui->framePicture->width();
    int h = ui->framePicture->height();
    ui->profilePicture->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));


    QVBoxLayout *layout = new QVBoxLayout;
    ui->framePicture->setLayout(layout);

     // Align the content of the label to the center
    ui->profilePicture->setAlignment(Qt::AlignCenter);

    layout->addWidget(ui->profilePicture);

}

Profile::~Profile()
{
    delete ui;
}

void Profile::on_goBackButton_clicked()
{
    hide();
    h2 = new Home(this);
    h2->show();
}


void Profile::on_buttonSetting_clicked()
{
    hide();
    set = new Setting(this);
    set->show();
}

