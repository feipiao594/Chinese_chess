#include "piece.h"
#include "board.h"
#include "algorithms.h"

using Type = Piece::PieceType;

const std::map<Type, wchar_t> Piece::dict = {
    { Type::RED_SHUAI, L'帥' },
    { Type::BLACK_JIANG, L'將' },
    { Type::RED_SHI, L'仕' },
    { Type::BLACK_SHI, L'士' },
    { Type::RED_XIANG, L'相' },
    { Type::BLACK_XIANG, L'象' },
    { Type::RED_MA, L'馬' },
    { Type::BLACK_MA, L'馬' },
    { Type::RED_JU, L'車' },
    { Type::BLACK_JU, L'車' },
    { Type::RED_PAO, L'炮' },
    { Type::BLACK_PAO, L'炮' },
    { Type::RED_BING, L'兵' },
    { Type::BLACK_ZU, L'卒' }
};

const bool Piece::noThreat(int a, int b)const{//mode填true不检查是否被将军
    //return true;
    auto list = Board::getBoard()->find(-1,-1,-1);
    bool flag = false;
    std::pair<Pos, Piece::PieceType> temp;
    for(auto &i:list){
        if(i.first.first==this->x&&i.first.second==this->y){
            for(auto j:list){
                if(j.first.first==a&&j.first.second==b){
                    temp.first.first=j.first.first;
                    temp.first.second=j.first.second;
                    temp.second=j.second;
                    flag = true;
                }
            }
            i.first.first = a;
            i.first.second = b;
        }
    }
    if(flag)list.remove(temp);
    //前面生成了走后的list状态
    if(Algorithms::isCheck(list,side())) return false;//判断走后list状态，棋子所在方是否被将军，若是，则说明有危险输出false
    else return true;
}
