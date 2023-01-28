#ifndef MA_H
#define MA_H

#include "piece.h"
#include "board.h"

class Ma : public Piece
{
private:
    Ma();
public:
    Ma(int x, int y, bool side):Piece(x,y,side?(Piece::PieceType::RED_MA):(Piece::PieceType::BLACK_MA)){}
public:
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces)const{
        if(Board::getBoard()->isChecked(side()))return false;
        int mx,my;
        for(auto &i:pieces){
                if(i.second==(side()?Piece::PieceType::BLACK_JIANG:Piece::PieceType::RED_SHUAI)){
                    mx = i.first.first;
                    my = i.first.second;
                    break;
                }
            }
        auto notExistAtPos = [=](int a,int b)->bool{
            for(auto [pos,type]:pieces){
                if(pos.first==a&&pos.second==b)return false;
            }
            return true;
        };
        auto judge = [=](int a,int b)->bool{
            if(mx-x==a&&my-y==b){
                if(notExistAtPos(a/2+x,b/2+y)){
                     return true;//如果是坐标对且空，则不绊脚返回true
                }else return false;
            }else return false;
        };
        return judge(1,2)||judge(1,-2)||judge(-1,2)||judge(-1,-2)||judge(2,1)||judge(2,-1)||judge(-2,1)||judge(-2,-1);
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        auto judge = [&](int a,int b)->void{
            if(a>=1&&a<=9&&b>=1&&b<=10&&isValidMove(a,b))result.push_back(std::make_pair(a,b));
        };
        judge(x-1,y-2);
        judge(x+1,y-2);
        judge(x-1,y+2);
        judge(x+1,y+2);
        judge(x-2,y-1);
        judge(x+2,y-1);
        judge(x-2,y+1);
        judge(x+2,y+1);
        return result;
    }
    virtual const bool isBasicMove(int x, int y) const{
        if(!Board::getBoard()->find(x,y,side()).empty())return false;
        auto judge = [=](int a,int b)->bool{
            if(x-(this->x)==a&&y-(this->y)==b){
                if(Board::getBoard()->find(a/2+this->x,b/2+this->y,-1).empty()){
                     return true;//如果是坐标对且空，则不绊脚返回true
                }else return false;
            }else return false;
        };
        return judge(1,2)||judge(1,-2)||judge(-1,2)||judge(-1,-2)||judge(2,1)||judge(2,-1)||judge(-2,1)||judge(-2,-1);
    }
};


#endif // MA_H
