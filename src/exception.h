#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QMessageBox>

class ExceptionWindow : public QMessageBox {
    int err_code;
public:
    ExceptionWindow(QString what, int code) : err_code(code) {
        setAttribute(Qt::WA_DeleteOnClose);
        setText(what);
    }

    void popup() {
        show();
    }

    ~ExceptionWindow() {
        exit(err_code);
    }
};
//Fatal
class Exception {
    ExceptionWindow* window;
public:
    Exception(QString what, int code) : window(new ExceptionWindow(what, code)) {}

    void process() {
        window->popup();
    }
};

#endif // EXCEPTION_H
