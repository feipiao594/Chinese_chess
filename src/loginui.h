#ifndef LOGINUI_H
#define LOGINUI_H

#include <QDialog>
#include <QButtonGroup>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class LoginUI : public QDialog
{
    Q_OBJECT
private:
    QFormLayout* layout;
    QHBoxLayout* buttonLayout;
    QLabel *user, *passwd;
    QLineEdit *userTxt, *passwdTxt;
    QPushButton *login, *signup;
public:
    LoginUI();
public slots:
    void onLogin();
    void onSignup();
    void loginSuccess();
    void onFailure(const QString);
    void signupSuccess();
};

#endif // LOGINUI_H
