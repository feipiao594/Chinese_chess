#include "loginui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto w = new LoginUI;
    w->show();
    return a.exec();
}
