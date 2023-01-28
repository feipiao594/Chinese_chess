#ifndef BOARD_H
#define BOARD_H

#include "cell.h"

#include <QObject>
#include <functional>
#include <mutex>
#include <utility>

/* BOARD Layout
 * 对手：
 * 10   +-+-+-+-+-+-+-+-+
 *      | | | |\|/| | | |
 * 9    +-+-+-+-+-+-+-+-+
 *      | | | |/|\| | | |
 * 8    +-+-+-+-+-+-+-+-+
 *      | | | | | | | | |
 * 7    +-+-+-+-+-+-+-+-+
 *      | | | | | | | | |
 * 6    +-+-+-+-+-+-+-+-+
 *        楚河      汉界
 * 5    +-+-+-+-+-+-+-+-+
 *      | | | | | | | | |
 * 4    +-+-+-+-+-+-+-+-+
 *      | | | | | | | | |
 * 3    +-+-+-+-+-+-+-+-+
 *      | | | |\|/| | | |
 * 2    +-+-+-+-+-+-+-+-+
 *      | | | |/|\| | | |
 * 1    +-+-+-+-+-+-+-+-+
 *      1 2 3 4 5 6 7 8 9
 * 我方：
*/
class Board : public QObject
{
    Q_OBJECT

    using Constructor = std::function<const std::shared_ptr<Piece>(int, int, bool)>;    //工厂函数类型
public:
    //获取全局单例对象
    static inline const Board* getBoard() {
        static Board const* singleton = nullptr;    //全局单例
        if (!singleton)
            singleton = new Board;
        return singleton;
    }
private:
    bool checked[2] = { false, false };        //将军状态
    bool your_turn = false;     //你的回合
    bool moved = false;         //是否走棋
    mutable bool SIDE;          //哪一方？
    std::mutex lock;
public:
    inline bool isChecked(bool side = Board::getBoard()->SIDE) const {
        return checked[side];
    }
    inline const bool isYourTurn() const {
        return your_turn;
    }
    inline const bool isMoved() const {
        return moved;
    }
    inline const bool side() const {
        return SIDE;
    }
private:
    std::map<Pos, std::shared_ptr<Piece> > pieces;
    std::map<Pos, Cell*> cells;

    Board();
    void setPieces(const std::map<Piece::PieceType, Constructor> &);
    void move(const Pos from, const Pos to);
    void judgeStatus(); //走棋后对局势评估（输赢和当前是否处于将军状态）
public:
    const std::list<std::pair<Pos, Piece::PieceType>> find(int x = -1, int y = -1, int side = -1) const;
signals:
    void win(bool side);
    void MySideMove(const Pos from,const Pos to);
public slots:
    void onSetup(Cell**);
    void onClick();
    void onMove(const Pos from, const Pos to);  //对方走棋
public:
    ~Board() {}

    friend class Algorithms;
    friend class Network;
};
#endif // BOARD_H
