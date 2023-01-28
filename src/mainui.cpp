#include "mainui.h"

#include "cell.h"
#include "dialogui.h"

//添加board.h
#include "network.h"
#include "board.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

MainUI::MainUI() : QDialog(),
    layout(new QVBoxLayout), boardLayout(new QGridLayout),
    chu(new QLabel("楚河")), han(new QLabel("汉界"))
{
    auto count = 0;
    for (auto& i : h) {
        i = new QLabel("---");
        boardLayout->addWidget(i, count / 8 * 2, count % 8 * 2 + 1, Qt::AlignCenter);
        count++;
    }
    count = 0;
    for (auto& i : v1) {
        i = new QLabel("|");
        boardLayout->addWidget(i, count / 9 * 2 + 1, count % 9 * 2, Qt::AlignCenter);
        count++;
    }
    boardLayout->addWidget(chu, 9, 0, 1, 8, Qt::AlignCenter);
    boardLayout->addWidget(han, 9, 10, 1, 8, Qt::AlignCenter);
    for (auto& i : v2) {
        i = new QLabel("|");
        boardLayout->addWidget(i, count / 9 * 2 + 3, count % 9 * 2, Qt::AlignCenter);
        count++;
    }
    count = 0;
    for (auto& i : cells) {
        i = new Cell(count% 9 + 1, 10 - count / 9);
        boardLayout->addWidget(i, count / 9 * 2, count % 9 * 2);
        count++;
    }
    l[0] = new QLabel("\\");
    boardLayout->addWidget(l[0], 1, 7, Qt::AlignCenter);
    l[1] = new QLabel("/");
    boardLayout->addWidget(l[1], 1, 9, Qt::AlignCenter);
    l[2] = new QLabel("/");
    boardLayout->addWidget(l[2], 3, 7, Qt::AlignCenter);
    l[3] = new QLabel("\\");
    boardLayout->addWidget(l[3], 3, 9, Qt::AlignCenter);
    l[0] = new QLabel("\\");
    boardLayout->addWidget(l[0], 15, 7, Qt::AlignCenter);
    l[1] = new QLabel("/");
    boardLayout->addWidget(l[1], 15, 9, Qt::AlignCenter);
    l[6] = new QLabel("/");
    boardLayout->addWidget(l[6], 17, 7, Qt::AlignCenter);
    l[7] = new QLabel("\\");
    boardLayout->addWidget(l[7], 17, 9, Qt::AlignCenter);

    layout->addLayout(boardLayout);

    //Message Area UI:

    message_area = new QLabel;
    QHBoxLayout* send_area = new QHBoxLayout;
    text = new QLineEdit;
    QPushButton* button = new QPushButton("发送");
    send_area->addWidget(text);
    text->setMinimumWidth(0.5 * width());
    text->setMaximumWidth(0.7 * width());
    send_area->addWidget(button, Qt::AlignRight);
    button->setMaximumWidth(0.2 * width());
    layout->addWidget(message_area);
    layout->addLayout(send_area);

    setLayout(layout);

    //Add your own code here:
    /////////////////////////
    connect(this,&MainUI::onMes,Network::getInstance(),&Network::sendMessage);
    connect(button,&QPushButton::clicked,this,&MainUI::clickMessage);
    connect(Network::getInstance(),&Network::findOK,this,&MainUI::onFind);
    connect(this,&MainUI::setup,Board::getBoard(),&Board::onSetup);
    connect(Network::getInstance(),&Network::message,this,&MainUI::oppmessage);
    /////////////////////////
    show();
    auto popup = new DialogUI;
    popup->show();
}
