#ifndef SHI_H
#define SHI_H

#include "piece.h"
#include "board.h"

class Shi : public Piece
{
private:
    Shi();
public:
    Shi(int x, int y, bool side):Piece(x,y,side?(Piece::PieceType::RED_SHI):(Piece::PieceType::BLACK_SHI)){}
public:
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces)const{
        return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        auto judge = [&](int a,int b)->void{
            if(a>=1&&a<=9&&b>=1&&b<=10&&isValidMove(a,b))result.push_back(std::make_pair(a,b));
        };
        judge(x-1,y-1);
        judge(x+1,y+1);
        judge(x-1,y+1);
        judge(x+1,y-1);
        return result;
    }
    virtual const bool isBasicMove(int x, int y) const{
        if(!Board::getBoard()->find(x,y,side()).empty())return false;
        auto judge = [=](int a,int b)->bool{
            if(x-(this->x)==a&&y-(this->y)==b)return true;
            else return false;
        };
        if(side()==Board::getBoard()->side()){
            if(x>=4&&y>=1&&x<=6&&y<=3) return judge(1,1)||judge(-1,1)||judge(1,-1)||judge(-1,-1);
            else return false;
        }else{
            if(x>=4&&y>=8&&x<=6&&y<=10) return judge(1,1)||judge(-1,1)||judge(1,-1)||judge(-1,-1);
            else return false;
        }
        return true;
    }
};

#endif // SHI_H
