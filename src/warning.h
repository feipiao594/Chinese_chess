#ifndef WARNING_H
#define WARNING_H

#include <QMessageBox>

class WarningWindow : public QMessageBox {
public:
    WarningWindow(QString what) {
        setAttribute(Qt::WA_DeleteOnClose);
        setText(what);
    }

    void popup() {
        show();
    }
};
//弹窗模块
class Warning {
    WarningWindow* window;
public:
    Warning(QString what) : window(new WarningWindow(what)) {}

    void process() {
        window->popup();
    }
};

#endif // WARNING_H
