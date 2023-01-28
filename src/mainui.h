#ifndef MAINUI_H
#define MAINUI_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>

#include "network.h"

class Cell;
class MainUI : public QDialog
{
    Q_OBJECT

    QVBoxLayout* layout;
    QGridLayout* boardLayout;
    QLabel *h[8 * 10], *v1[9 * 4], *v2[9 * 4], *l[8], *chu, *han;
    Cell* cells[9 * 10];
    QLineEdit* text;
    QLabel* message_area;
signals:
    void setup(Cell**);
    void onMes(QString);
public slots:
    void onFind(const QString opp_name) {
        emit setup(cells);
    }
    void oppmessage(const QString message){
        message_area->setText(QString("对方说:")+message);
    }
    void clickMessage(){
        if(Network::getInstance()->getIfStart()){
            emit onMes(text->text());
        }else{
            message_area->setText(QString("游戏还未开始，不能发送信息哦"));
        }
    };
public:
    MainUI();
};

#endif // MAINUI_H
