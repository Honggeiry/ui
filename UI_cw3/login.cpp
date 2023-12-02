#include "login.h"

Login::Login(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Login");

    // Style the Login interface with Qt Style Sheets
    QString appStyle =
        "QPushButton {"
        "    font-size: 18px;"
        "    background-color: #5cb85c;"
        "    color: white;"
        "    border-radius: 5px;"
        "    padding: 6px;"
        "    margin: 2px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #449d44;"
        "}"
        "QFrame {"
        "    background-color: #333;"
        "    padding: 10px;"
        "}"
        "QLabel {"
        "    color: #d3d3d3;"
        "    font-weight: bold;"
        "}"
        "QLineEdit {"
        "    border: 2px solid #a9a9a9;"
        "    border-radius: 4px;"
        "    padding: 5px;"
        "    background: white;"
        "    color: black;"
        "}"
        "QLineEdit:focus {"
        "    border-color: #00bfff;"
        "}";
    setStyleSheet(appStyle);

    // Create a grid layout for the username and password fields
    QGridLayout *gridLayout = new QGridLayout;

    // QLineEdit widgets for username and password
    QLineEdit *usernameLineEdit = new QLineEdit;
    QLineEdit *passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    // Add widgets to the grid layout
    gridLayout->addWidget(new QLabel("Username"), 0, 0);
    gridLayout->addWidget(usernameLineEdit, 0, 1);
    gridLayout->addWidget(new QLabel("Password"), 1, 0);
    gridLayout->addWidget(passwordLineEdit, 1, 1);

    // Create the main layout for the login dialog
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(gridLayout);

    // Create the frame to hold the buttons
    QFrame *frame = new QFrame(this);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    // Create the buttons
    QPushButton *loginButton = new QPushButton("Login", frame);
    QPushButton *resetButton = new QPushButton("Reset", frame);

    // Create the layout for the frame
    QHBoxLayout *frameLayout = new QHBoxLayout(frame);
    frameLayout->addWidget(loginButton, 1);
    frameLayout->addWidget(resetButton, 1);

    // Add the buttons frame to the main layout without allowing vertical stretching
    mainLayout->addWidget(frame, 0);

    // Set the layout on the dialog
    setLayout(mainLayout);

    // Set the size policy to allow horizontal stretching but fixed vertical size
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Connect the login button's clicked signal to the slot
    connect(loginButton, &QPushButton::clicked, this, &Login::on_loginButton_clicked);

    resize(320, 650);
}

Login::~Login(){}

void Login::on_loginButton_clicked()
{
    close();
    h = new Home(nullptr);
    h->show();
}
