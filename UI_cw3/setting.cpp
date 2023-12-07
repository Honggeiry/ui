#include "setting.h"
#include "profile.h"

Profile* p2;
Setting::Setting(QWidget *parent) :
    QDialog(parent)
{
    // Create buttons
    QPushButton *languageButton = new QPushButton("Language", this);
    QPushButton *fontSizeButton = new QPushButton("Change Font Size", this);
    QPushButton *colorThemeButton = new QPushButton("Change Color Theme", this);
    QPushButton *darkMode = new QPushButton("Light Mode", this);
    QPushButton *logoutButton = new QPushButton("Log Out", this);
    QPushButton *deleteAccountButton = new QPushButton("Delete Account", this);
    QPushButton *faqButton = new QPushButton("FAQ", this);
    QPushButton *goBackButton = new QPushButton("Go Back", this);

    // Set the buttons to expand
    QList<QPushButton*> buttons = {languageButton, fontSizeButton, colorThemeButton, darkMode, logoutButton, deleteAccountButton, faqButton};
    foreach(QPushButton* button, buttons) {
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    QString buttonStyle = "QPushButton {"
                          "  background-color: rgb(130, 139, 168);"
                          "  color: white;"
                          "  border-radius: 15px;"
                          "  padding: 10px;"
                          "  border: 5px solid rgb(99, 100, 157);"
                          "}"
                          "QPushButton:pressed {"
                          "  background-color: rgb(120, 138, 249);"
                          "}"
                          "QPushButton:hover {"
                          "  background-color: rgb(62, 76, 139);"
                          "  color: #1BC0FB;"
                          "}";

    // Apply the stylesheet to each button
    languageButton->setStyleSheet(buttonStyle);
    fontSizeButton->setStyleSheet(buttonStyle);
    colorThemeButton->setStyleSheet(buttonStyle);
    darkMode->setStyleSheet(buttonStyle);
    logoutButton->setStyleSheet(buttonStyle);
    deleteAccountButton->setStyleSheet(buttonStyle);
    faqButton->setStyleSheet(buttonStyle);
    goBackButton->setStyleSheet(buttonStyle);

    // Set up main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Create a horizontal layout for the go back button
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(goBackButton, 0, Qt::AlignTop | Qt::AlignLeft);
    topLayout->addStretch();

    // Add the topLayout to the main layout
    mainLayout->addLayout(topLayout);

    // Add the rest of the buttons to the main layout
    foreach(QPushButton* button, buttons) {
        mainLayout->addWidget(button);
    }

    // Set the layout for the main window
    setLayout(mainLayout);

    connect(goBackButton, &QPushButton::clicked, this, &Setting::on_goBackButton_clicked);
    connect(darkMode, &QPushButton::clicked, this, &Setting::on_darkModeButton_clicked);

    // Set a minimum size for the dialog
    // (Use iPhone SE as a reference)
    setMinimumSize(320, 650);
    resize(320, 650);
}

Setting::~Setting() {}

void Setting::on_goBackButton_clicked()
{
    hide();
    p2 = new Profile(this);
    p2->show();
}

void Setting::on_darkModeButton_clicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button)
    {
        if (button->text() == "Dark Mode")
            button->setText("Light Mode");
        else
            button->setText("Dark Mode");
    }
}
