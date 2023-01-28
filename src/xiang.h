#ifndef XIANG_H
#define XIANG_H

#include "piece.h"
#include "board.h"

class Xiang : public Piece
{
private:
    Xiang();
public:
    Xiang(int x, int y, bool side):Piece(x,y,side?(Piece::PieceType::RED_XIANG):(Piece::PieceType::BLACK_XIANG)){}
public:
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces)const{
        return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        auto judge = [&](int a,int b)->void{
            if(a>=1&&a<=9&&b>=1&&b<=10&&isValidMove(a,b))result.push_back(std::make_pair(a,b));
        };
        judge(x-2,y);
        judge(x+2,y);
        judge(x,y+2);
        judge(x,y-2);
        return result;
    }
    virtual const bool isBasicMove(int x, int y) const{
        if(!Board::getBoard()->find(x,y,side()).empty())return false;
        auto judge = [=](int a,int b)->bool{
            if(x-(this->x)==a&&y-(this->y)==b){
                if((Board::getBoard()->find((x+(this->x))/2,(y+(this->y))/2,-1)).empty()){
                     return true;//如果是坐标对且中空，则返回true
                }else return false;
            }else return false;
        };
        if(side()==Board::getBoard()->side()){
            if(y<=5) return judge(2,2)||judge(-2,2)||judge(2,-2)||judge(-2,-2);
            else return false;
        }else{
            if(y>=6) return judge(2,2)||judge(-2,2)||judge(2,-2)||judge(-2,-2);
            else return false;
        }
        return true;
    }
};


#endif // XIANG_H
