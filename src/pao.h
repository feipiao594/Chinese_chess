#ifndef PAO_H
#define PAO_H

#include "piece.h"
#include "board.h"

class Pao : public Piece
{
private:
    Pao();
public:
    Pao(int x, int y, bool side):Piece(x,y,side?(Piece::PieceType::RED_PAO):(Piece::PieceType::BLACK_PAO)){}
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
        if(mx==(this->x)){
            if(my>this->y){
                int j = 0;
                for(int i=((this->y)+1);i<=my-1;i++){
                    if(!notExistAtPos(mx,i)) j++;
                }
                if(j==0||j>1)return false;
                else return true;
            }else if(my<this->y){
            int j = 0;
            for(int i=my+1;i<=((this->y)-1);i++){
                if(!notExistAtPos(mx,i)) j++;
            }
                if(j==0||j>1)return false;
                else return true;
            }
        }else if(my==(this->y)){
            if(mx>this->x){
                int j = 0;
                for(int i=((this->x)+1);i<=mx-1;i++){
                    if(!notExistAtPos(i,my)) j++;
                }
                if(j==0||j>1)return false;
                else return true;
            }else if(mx<this->x){
                int j = 0;
                for(int i=mx+1;i<=((this->x)-1);i++){
                    if(!notExistAtPos(i,my)) j++;
                }
                if(j==0||j>1)return false;
                else return true;
            }
        }else return false;
    }
    virtual const std::list<Pos> getPossibleMoves() const{
        std::list<Pos> result;
        for(int j=1;j<=9;j++){
            if(isValidMove(j,y)){
                result.push_back(std::make_pair(j,y));
            }
        }
        for(int j=1;j<=10;j++){
            if(isValidMove(x,j)){
                result.push_back(std::make_pair(x,j));
            }
        }
        return result;
    }
    virtual const bool isBasicMove(int x, int y) const{
        if(!Board::getBoard()->find(x,y,side()).empty())return false;
        if(x==(this->x)||y==(this->y)){
            if((Board::getBoard()->find(x,y,((Board::getBoard()->side())?0:1))).empty()){
                if(x==(this->x)){
                    if(y>this->y){
                        for(int i=((this->y)+1);i<=y-1;i++){
                            if(!((Board::getBoard()->find(x,i,-1)).empty())) return false;
                        }
                    }else if(y<this->y){
                        for(int i=y+1;i<=((this->y)-1);i++){
                            if(!((Board::getBoard()->find(x,i,-1)).empty())) return false;
                        }
                    }
                }else if(y==(this->y)){
                    if(x>this->x){
                        for(int i=((this->x)+1);i<=x-1;i++){
                            if(!((Board::getBoard()->find(i,y,-1)).empty())) return false;
                        }
                    }else if(x<this->x){
                        for(int i=x+1;i<=((this->x)-1);i++){
                            if(!((Board::getBoard()->find(i,y,-1)).empty())) return false;
                        }
                    }
                }
            }else{
                if(x==(this->x)){
                    if(y>this->y){
                        int j = 0;
                        for(int i=((this->y)+1);i<=y-1;i++){
                            if(!((Board::getBoard()->find(x,i,-1)).empty())) j++;
                        }
                        if(j==0||j>1)return false;
                        else return true;
                    }else if(y<this->y){
                        int j = 0;
                        for(int i=y+1;i<=((this->y)-1);i++){
                            if(!((Board::getBoard()->find(x,i,-1)).empty())) j++;
                        }
                        if(j==0||j>1)return false;
                        else return true;
                    }
                }else if(y==(this->y)){
                    if(x>this->x){
                        int j = 0;
                        for(int i=((this->x)+1);i<=x-1;i++){
                            if(!((Board::getBoard()->find(i,y,-1)).empty())) j++;
                        }
                        if(j==0||j>1)return false;
                        else return true;
                    }else if(x<this->x){
                        int j = 0;
                        for(int i=x+1;i<=((this->x)-1);i++){
                            if(!((Board::getBoard()->find(i,y,-1)).empty())) j++;
                        }
                        if(j==0||j>1)return false;
                        else return true;
                    }
                }
            }
            return true;
        }else return false;
    }
};

#endif // PAO_H
