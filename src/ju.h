#ifndef JU_H
#define JU_H

#include "piece.h"
#include "board.h"

class Ju : public Piece
{
private:
    Ju();
public:
    Ju(int x, int y, bool side):Piece(x,y,side?(Piece::PieceType::RED_JU):(Piece::PieceType::BLACK_JU)){}
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
                if(pos.first==a&&pos.second==b)return false;//如果存在坐标相等的，就返回false
            }
            return true;//empty则输出true
        };
        if(mx==(this->x)){
            if(my>this->y){
                for(int i=((this->y)+1);i<=my-1;i++){
                    if(!notExistAtPos(mx,i)) return false;
                }
                return true;
            }else if(my<this->y){
                for(int i=my+1;i<=((this->y)-1);i++){
                    if(!notExistAtPos(mx,i)) return false;
                }
                return true;
            }
        }else if(my==(this->y)){
            if(mx>this->x){
                for(int i=((this->x)+1);i<=mx-1;i++){
                    if(!notExistAtPos(i,my)) return false;
                }
                return true;
            }else if(mx<this->x){
                for(int i=mx+1;i<=((this->x)-1);i++){
                    if(!notExistAtPos(i,my)) return false;
                }
                return true;
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
        if(x==(this->x)){
            if(y>this->y){
                for(int i=((this->y)+1);i<=y-1;i++){
                    if(!((Board::getBoard()->find(x,i,-1)).empty())) return false;
                }
                return true;
            }else if(y<this->y){
                for(int i=y+1;i<=((this->y)-1);i++){
                    if(!((Board::getBoard()->find(x,i,-1)).empty())) return false;
                }
                return true;
            }
        }else if(y==(this->y)){
            if(x>this->x){
                for(int i=((this->x)+1);i<=x-1;i++){
                    if(!((Board::getBoard()->find(i,y,-1)).empty())) return false;
                }
                return true;
            }else if(x<this->x){
                for(int i=x+1;i<=((this->x)-1);i++){
                    if(!((Board::getBoard()->find(i,y,-1)).empty())) return false;
                }
                return true;
            }
        }else return false;
    }
};

#endif // JU_H
