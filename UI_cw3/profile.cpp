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

    QHBoxLayout *ppLayout = new QHBoxLayout;

    // Create spacers to push the button to the center
    QSpacerItem *horizontalSpacerLeft = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *horizontalSpacerRight = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    // Add the spacers and button to the layout
    ppLayout->addItem(horizontalSpacerLeft);
    ppLayout->addWidget(ui->changePP);
    ppLayout->addItem(horizontalSpacerRight);

    ui->changePP->setStyleSheet("QPushButton {"
                                "  background-color: rgb(62, 76, 139);"
                                "  border-radius: 10px;"
                                "}");

    layout->addLayout(ppLayout);
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

