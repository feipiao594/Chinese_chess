#ifndef BING_ZU_H
#define BING_ZU_H

#include "piece.h"
#include "board.h"

class Bing_Zu : public Piece
{
private:
    Bing_Zu();
public:
    Bing_Zu(int x, int y, bool side):Piece(x,y,side?(Piece::PieceType::RED_BING):(Piece::PieceType::BLACK_ZU)){}
public:
    virtual bool isThreat(const std::list<std::pair<Pos, Piece::PieceType>>& pieces)const{//可以攻击将
        if(Board::getBoard()->isChecked(side()))return false;
        int mx,my;
        for(auto &i:pieces){
                if(i.second==(side()?Piece::PieceType::BLACK_JIANG:Piece::PieceType::RED_SHUAI)){
                    mx = i.first.first;
                    my = i.first.second;
                    break;
                }
            }
        auto judge = [=](int a,int b)->bool{
            if(mx-x==a&&my-y==b) return true;
            else return false;
        };
        if(side()==Board::getBoard()->side()){
            return judge(0,1)||judge(-1,0)||judge(1,0);
        }else{
            return judge(0,-1)||judge(-1,0)||judge(1,0);
        }
        return true;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        auto judge = [&](int a,int b)->void{
            if(a>=1&&a<=9&&b>=1&&b<=10&&isValidMove(a,b))result.push_back(std::make_pair(a,b));
        };
        judge(x-1,y);
        judge(x+1,y);
        judge(x,y+1);
        judge(x,y-1);
        return result;
    }
    virtual const bool isBasicMove(int x, int y) const{
        //return true;
        if(!Board::getBoard()->find(x,y,side()).empty())return false;
        auto judge = [=](int a,int b)->bool{
            if(x-(this->x)==a&&y-(this->y)==b) return true;
            else return false;
        };
        if(side()==Board::getBoard()->side()){
            if(y<=5) return judge(0,1);
            else if(y>=6) return judge(0,1)||judge(-1,0)||judge(1,0);
        }else{
            if(y>=6) return judge(0,-1);
            else if(y<=5) return judge(0,-1)||judge(-1,0)||judge(1,0);
        }
        return true;
    }
};

#endif // BING_ZU_H
