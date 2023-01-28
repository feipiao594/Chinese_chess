#ifndef DIALOGUI_H
#define DIALOGUI_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class DialogUI : public QDialog {
    Q_OBJECT

    QVBoxLayout* layout;
    QPushButton *start, *exit;
    QLabel* pending;
private slots:
    void onStart();
    void onExit() {
        ::exit(0);
    }
    void onFind(const QString opp_name);
    void onWin(bool side);
    void onFailure(const QString message) {
        pending->setText(message);
        show();
    }
public:
    DialogUI();
};

#endif // DIALOGUI_H
