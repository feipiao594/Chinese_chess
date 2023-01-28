#ifndef CELL_H
#define CELL_H

#include "piece.h"

#include <QPushButton>
#include <QTimer>

class Cell : public QPushButton {
    Q_OBJECT

    static Cell *chosen;
private:
    inline void delayedFade() {
        QTimer::singleShot(500, this, &Cell::fade);
    }
    inline void setBackground(const QColor& color) {
        QPalette style(palette());
        style.setColor(QPalette::Button, color);
        setPalette(style);
    }
    inline void setTextColor(const QColor& color) {
        QPalette style(palette());
        style.setColor(QPalette::ButtonText, color);
        setPalette(style);
    }
private slots:
    void fade() {
        if (text() == "+")
            setBackground(Qt::white);
        else
            setBackground(Qt::black);
    }
public:
    const int x, y;
    Cell(int x, int y);

    inline void change(Piece const* piece = nullptr) {
        if (!piece) {
            setText("+");
            fade();
            setTextColor(Qt::black);
            return;
        }
        setText(QString(piece->text()));
        setBackground(Qt::black);
        if (piece->side())
            setTextColor(Qt::red);
        else
            setTextColor(Qt::white);
    }
    inline void select() {
        if (chosen)
            chosen->fade();
        setBackground(Qt::blue);
        chosen = this;
    }
    inline void wrongMove() {
        setBackground(Qt::red);
        delayedFade();
    }
    inline void fineMove() {
        setBackground(Qt::green);
        //qDebug()<<"test finemove";
        delayedFade();
        chosen->fade();
        chosen = nullptr;
    }
};

#endif // CELL_H
