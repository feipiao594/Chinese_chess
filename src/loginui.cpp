#include "loginui.h"
#include "network.h"
#include "mainui.h"

#include <QDir>
#include <QMessageBox>

LoginUI::LoginUI()
    : layout(new QFormLayout), buttonLayout(new QHBoxLayout),
      user(new QLabel("用户名")), passwd(new QLabel("密码")),
      userTxt(new QLineEdit), passwdTxt(new QLineEdit),
      login(new QPushButton("登录")), signup(new QPushButton("注册"))
{
    setAttribute(Qt::WA_DeleteOnClose);
    setLayout(layout);
    layout->addRow(user, userTxt);
    layout->addRow(passwd, passwdTxt);
    buttonLayout->addWidget(login);
    buttonLayout->addWidget(signup);
    layout->addRow(buttonLayout);

    userTxt->setMaxLength(20);
    passwdTxt->setEchoMode(QLineEdit::Password);

    try {
    //Add your own code here:
    /////////////////////////
    connect(login,&QPushButton::clicked,this,&LoginUI::onLogin);
    connect(signup,&QPushButton::clicked,this,&LoginUI::onSignup);
    connect(Network::getInstance(),&Network::loginOK,this,&LoginUI::loginSuccess);
    connect(Network::getInstance(),&Network::signupOK,this,&LoginUI::signupSuccess);
    connect(Network::getInstance(),&Network::failure,this,&LoginUI::onFailure);
    /////////////////////////
    } catch(Exception e) {
        e.process();
    }
}

void LoginUI::onLogin() {
    Network::getInstance()->login(userTxt->text(), passwdTxt->text());
}

void LoginUI::onSignup() {
    Network::getInstance()->signup(userTxt->text(), passwdTxt->text());
}

void LoginUI::loginSuccess() {
    this->disconnect();
    hide();
    MainUI* ui = new MainUI;
    //ui->show();
    close();
}

void LoginUI::signupSuccess() {
    QMessageBox* nov = new QMessageBox;
    nov->setText(tr("注册成功！"));
    nov->show();
}

void LoginUI::onFailure(const QString message) {
    QMessageBox* nov = new QMessageBox;
    nov->setText(message);
    nov->show();
}
