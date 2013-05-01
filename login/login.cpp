#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QByteArray>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QStackedWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include "login.h"
#include "user.h"
#include "passwordmanager.h"

LoginPanel::LoginPanel(QWidget* parent) : QWidget(parent) {
    setFixedSize(400,200);
    m_nameLine = new QLineEdit(this);
    m_nameLine->setMaximumWidth(300);
    m_passLine = new QLineEdit(this);
    connect (m_passLine, SIGNAL(returnPressed()),
             this, SLOT(ok()));
    m_passLine->setMaximumWidth(300);
    m_passLine->setEchoMode(QLineEdit::Password);

    QLabel* nameLabel = new QLabel("NAME: ", this);
    QLabel* passLabel = new QLabel("PASSWORD: ", this);
    QWidget* m_nameWidget = new QWidget(this);
    QWidget* m_passWidget = new QWidget(this);
    QHBoxLayout* nameLayout = new QHBoxLayout(m_nameWidget);
    QHBoxLayout* passLayout = new QHBoxLayout(m_passWidget);
    nameLayout->addWidget(nameLabel);
    nameLayout->addSpacing(80);
    nameLayout->addWidget(m_nameLine);
    passLayout->addWidget(passLabel);
    passLayout->addSpacing(50);
    passLayout->addWidget(m_passLine);
    delete layout();
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addSpacing(20);
    m_mainLayout->addWidget(m_nameWidget);
    m_mainLayout->addWidget(m_passWidget);
    
    // m_buttonLayout = new QHBoxLayout;
    m_buttons = new QWidget(this);
    QHBoxLayout* hbox = new QHBoxLayout(m_buttons);
    
    m_Ok = new QPushButton("Sign In", this);
    m_Cancel = new QPushButton("Cancel", this);
    connect (m_Ok, SIGNAL(clicked()), this, SLOT(ok()));
    connect (m_Cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    hbox->addStretch(1);
    hbox->addWidget(m_Ok);
    hbox->addWidget(m_Cancel);
    m_mainLayout->addWidget(m_buttons);
    
}

void LoginPanel::cancel() {
    setVisible(false);   
}

void LoginPanel::ok() {
    emit login(m_nameLine->text(), m_passLine->text());
}

void RegisterPanel::ok() {
    if (m_passLine->text() != m_passVerifyLine->text()) {
        QMessageBox::critical(this, "Register Panel", "Passwords do not match");
    }
    else emit newUser(m_nameLine->text(), m_passLine->text());
}
        
RegisterPanel::RegisterPanel(QWidget* parent)  :
    LoginPanel(parent) {
    m_Ok->setText("Register");
    m_passVerifyLine = new QLineEdit(this);
    m_passVerifyLine->setMaximumWidth(300);
    m_passVerifyLine->setEchoMode(QLineEdit::Password);
    disconnect(m_passLine, SIGNAL(returnPressed()), this, SLOT(ok()));
    
    connect(m_passVerifyLine, SIGNAL(returnPressed()), this, SLOT(ok()));
    connect(m_passLine, SIGNAL(returnPressed()), 
            m_passVerifyLine, SIGNAL(setFocus())); 
    m_verifyWidget = new QWidget(this);
    QHBoxLayout* verifyLayout = new QHBoxLayout(m_verifyWidget);
    
    verifyLayout->addWidget(new QLabel("Pass Verify:", this));
    verifyLayout->addSpacing(10);
    verifyLayout->addWidget(m_passVerifyLine);
    
    // Re-add all widgets so that the tab order is correct.
    //  m_mainLayout->removeWidget(m_buttons);
    m_mainLayout->addWidget(m_verifyWidget);
    m_mainLayout->addWidget(m_buttons);
    
    // fix tab order
    setTabOrder(m_passLine, m_passVerifyLine);
    setTabOrder(m_passVerifyLine, m_Ok);
}


void LoginScreen::login(QString name, QString pw) {
    if (m_PasswordManager->checkPassword(name, pw)) {
        setWindowTitle(QString("Welcome %1").arg(name));
        m_User->setName(name);
        m_Login->setEnabled(false);
        m_Logout->setEnabled(true);
        m_Register->setEnabled(false);
    }
    else QMessageBox::critical(this, "LoginScreen", "Username or Password invalid. ");
}

void LoginScreen::addUser(QString name, QString pw) {
    if (m_PasswordManager->addUser(name, pw)) {
        QMessageBox::information(this, "LoginScreen", "User registered. Please check your e-mail for add'l information (TBR) and login. ");
    }
    else {
        QMessageBox::critical(this, "LoginScreen", "Username already exists, please choose another.");
    }
}

void LoginScreen::showLoginPanel() {
    m_Login->setEnabled(true);
    m_Logout->setEnabled(false);
    m_Register->setEnabled(true);   
    m_CentralWidget->setCurrentWidget(m_LoginPanel);
    m_LoginPanel->setVisible(true);
    setWindowTitle("Please Login");
}

void LoginScreen::showRegisterPanel() {
    m_CentralWidget->setCurrentWidget(m_RegisterPanel);
    m_RegisterPanel->setVisible(true);
    setWindowTitle("Please choose a username and password");
    // TODO
}

LoginScreen::LoginScreen() {
    m_User = new User(this);
    m_Login = createAction("login", "Log&in");
    m_Logout = createAction("logout", "Log&out");
    m_Register = createAction("register", "&Register");
    m_Register->setWhatsThis("Create a new User");
    QMenu* userMenu = new QMenu("&User", this);
    userMenu->addAction(m_Login);
    userMenu->addAction(m_Register);
    userMenu->addAction(m_Logout);
    menuBar()->addMenu(userMenu);
    connect (m_Login, SIGNAL(triggered()), this, SLOT(showLoginPanel()));
    connect (m_Register, SIGNAL(triggered()), this, SLOT(showRegisterPanel()));
    connect (m_Logout, SIGNAL(triggered()), this, SLOT(logout()));
    m_Logout->setEnabled(false);
    
    m_LoginPanel = new LoginPanel(this);
    connect (m_LoginPanel, SIGNAL(login(QString, QString)), 
             this, SLOT(login(QString, QString)));
    m_RegisterPanel = new RegisterPanel(this);
    connect (m_RegisterPanel, SIGNAL(newUser(QString, QString)),
             this, SLOT(addUser(QString, QString))); 
    m_CentralWidget = new QStackedWidget(this);
    m_CentralWidget->addWidget(m_LoginPanel);
    m_CentralWidget->addWidget(m_RegisterPanel);
    setCentralWidget(m_CentralWidget);

    m_PasswordManager = new PasswordManager();
    m_PasswordManager->setParent(this);
    
    move(400, 400);
    resize(400, 230);
    showLoginPanel();

}
void LoginScreen::logout() {
    qDebug() << "Logout" ;
    showLoginPanel();
}

bool LoginScreen::eventFilter(QObject* o, QEvent* e) {
    if (e->type() == QEvent::KeyPress ) {
        QKeyEvent* k = static_cast<QKeyEvent*>(e);
        int key = k->key();
        /*        if (key == Qt::Key_Return) {
        // do same thing as ok()
        return true;
        } */
        if (key == Qt::Key_Escape) {
            qApp->exit(0);
        }
    }

    return QMainWindow::eventFilter(o, e);
}

QAction* LoginScreen::createAction(QString name, QString text) {
    QAction* retval = new QAction(text, this);
    retval->setObjectName(name);
    return retval;
}

int main(int argc, char* argv[]) {
    QApplication app (argc, argv);
    LoginScreen login;
    login.show();
    return app.exec();
}
