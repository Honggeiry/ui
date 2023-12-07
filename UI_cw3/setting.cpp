#include "setting.h"
#include "profile.h"


Profile* p2;
Setting::Setting(QWidget *parent) :
    QDialog(parent),
    isLightMode(false)
{
    // Create buttons
    QPushButton *languageButton = new QPushButton("Language", this);
    QPushButton *fontSizeButton = new QPushButton("Change Font Size", this);
    QPushButton *colorThemeButton = new QPushButton("Change Color Theme", this);
    darkMode = new QPushButton("Light Mode", this);
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
    connect(darkMode, &QPushButton::clicked, this, &Setting::on_lightModeButton_clicked);

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

void Setting::on_lightModeButton_clicked()
{
    // Toggle the mode
    isLightMode = !isLightMode;

    QString buttonStyle;
    QString appStyle;
    if (isLightMode)
    {
        // Use the light mode colour palette
        buttonStyle = "QPushButton {"
                      "  background-color: rgb(180, 189, 218);"
                      "  color: black;"
                      "  border: 5px solid rgb(149, 150, 207);"
                      "}"
                      "QPushButton:pressed {"
                      "  background-color: rgb(170, 188, 255);"
                      "}"
                      "QPushButton:hover {"
                      "  background-color: rgb(112, 126, 189);"
                      "  color: rgb(127, 242, 255);"
                      "}";

        appStyle = "QWidget { background-color: rgb(177, 189, 222); }";
    }
    else
    {
        // Use the original (dark mode) colour palette
        buttonStyle = "QPushButton {"
                      "  background-color: rgb(130, 139, 168);"
                      "  color: white;"
                      "  border: 5px solid rgb(99, 100, 157);"
                      "}"
                      "QPushButton:pressed {"
                      "  background-color: rgb(120, 138, 249);"
                      "}"
                      "QPushButton:hover {"
                      "  background-color: rgb(62, 76, 139);"
                      "  color: #1BC0FB;"
                      "}";

        appStyle = "QWidget { background-color: rgb(127, 139, 172); }";
    }

    // Apply the stylesheet to each button
    foreach (QPushButton* button, this->findChildren<QPushButton*>())
    {
        button->setStyleSheet(buttonStyle);
    }

    qApp->setStyleSheet(appStyle);

    // Update the text of the darkMode button to reflect the current mode
    darkMode->setText(isLightMode ? "Dark Mode" : "Light Mode");
}
