#ifndef JIANG_SHUAI_H
#define JIANG_SHUAI_H

#include "piece.h"
#include "board.h"

class Jiang_Shuai : public Piece
{
private:
    Jiang_Shuai();
public:
    Jiang_Shuai(int x, int y, bool side):Piece(x,y,side?(Piece::PieceType::RED_SHUAI):(Piece::PieceType::BLACK_JIANG)){}
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
        if(mx==x){
            if(my>y){
                for(int i=y+1;i<=my-1;i++){
                    if(!notExistAtPos(mx,i)) return false;
                }
                return true;
            }else if(my<y){
                for(int i=my+1;i<=y-1;i++){
                    if(!notExistAtPos(mx,i)) return false;
                }
                return true;
            }
        }else return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        for(int i=4;i<=6;i++){
            for(int j=1;j<=3;j++){
                if(isValidMove(i,j)){
                    result.push_back(std::make_pair(i,j));
                }
            }
        }
        return result;
    }
    virtual const bool isBasicMove(int x, int y) const{
        if(!Board::getBoard()->find(x,y,side()).empty())return false;
        if(side()==Board::getBoard()->side()){
            if(x>=4&&y>=1&&x<=6&&y<=3){
                if(((x-(this->x))==0)&&((y-(this->y))==1)) return true;
                else if(((x-(this->x))==0)&&((y-(this->y))==-1)) return true;
                else if(((x-(this->x))==-1)&&((y-(this->y))==0)) return true;
                else if(((x-(this->x))==1)&&((y-(this->y))==0)) return true;
                else return false;
            }else if(Board::getBoard()->find(x,y,-1).front().second==(Board::getBoard()->side()?Piece::PieceType::BLACK_JIANG:Piece::PieceType::RED_SHUAI)){
                if(x==this->x){
                    for(int i=((this->y)+1);i<=y-1;i++){
                        if(!((Board::getBoard()->find(x,i,-1)).empty())) return false;
                    }
                    return true;
                }else return false;
            }else{
                return false;
            }
        }else{
            if(x>=4&&y>=8&&x<=6&&y<=10){
                if(((x-(this->x))==0)&&((y-(this->y))==1)) return true;
                else if(((x-(this->x))==0)&&((y-(this->y))==-1)) return true;
                else if(((x-(this->x))==-1)&&((y-(this->y))==0)) return true;
                else if(((x-(this->x))==1)&&((y-(this->y))==0)) return true;
                else return false;
            }else if(Board::getBoard()->find(x,y,-1).front().second==(Board::getBoard()->side()?Piece::PieceType::RED_SHUAI:Piece::PieceType::BLACK_JIANG)){
                if(x==this->x){
                    for(int i=((this->y)-1);i>=y+1;i--){
                        if(!((Board::getBoard()->find(x,i,-1)).empty())) return false;
                    }
                    return true;
                }else return false;
            }else{
                return false;
            }
        }
    }
};

#endif // JIANG_SHUAI_H
