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
    resize(320, 650);

    QPixmap pix(":/resource/img/temp.jpg");
    int w = ui->framePicture->width();
    int h = ui->framePicture->height();
    ui->profilePicture->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

     // Align the content of the label to the center
    ui->profilePicture->setAlignment(Qt::AlignCenter);
    // Allow the profile picture to expand
    ui->profilePicture->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Add the profilePicture label to the framePicture
    ui->framePicture->setFrameShape(QFrame::StyledPanel);
    ui->framePicture->setMinimumHeight(200);
    ui->framePicture->setLayout(new QVBoxLayout);
    ui->framePicture->layout()->addWidget(ui->profilePicture);

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

