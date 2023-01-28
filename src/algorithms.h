#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "board.h"
#include "bing_zu.h"
#include "pao.h"
#include "ju.h"
#include "ma.h"
#include "shi.h"
#include "xiang.h"
#include "jiang_shuai.h"


//工具类
class Algorithms {
public:
    //判断僵局(无子可走)
    static bool isStalemate(bool side) {
        auto pieces = Board::getBoard()->find();
        auto result = Board::getBoard()->find(-1, -1, side);
        for (const auto& [pos, type] : result) {
            auto piece = Board::getBoard()->pieces.at(pos);
            //qDebug()<<pos<<" "<<piece->getPossibleMoves();
            if (!piece->getPossibleMoves().empty())
                return false;
        }
        return true;
    }

    //Piece::noThreat和Algorithms::isCheck的推荐辅助函数，目测输入整个棋盘pair，输出side一方是否*被*将军
    static inline bool isCheck(const std::list<std::pair<Pos, Piece::PieceType>>& pieces, bool side) {
        auto createPiece = [=](Pos p,Piece::PieceType type)->std::shared_ptr<Piece>{
            switch(removeSide(type)){
            case Piece::PieceType::BING_ZU:{
                return std::make_shared<Bing_Zu>(p.first,p.second,!side);
            }break;
            case Piece::PieceType::JIANG_SHUAI:{
                return std::make_shared<Jiang_Shuai>(p.first,p.second,!side);
            }break;
            case Piece::PieceType::PAO:{
                return std::make_shared<Pao>(p.first,p.second,!side);
            }break;
            case Piece::PieceType::JU:{
                return std::make_shared<Ju>(p.first,p.second,!side);
            }break;
            case Piece::PieceType::SHI:{
                return std::make_shared<Shi>(p.first,p.second,!side);
            }break;
            case Piece::PieceType::XIANG:{
                return std::make_shared<Xiang>(p.first,p.second,!side);
            }break;
            case Piece::PieceType::MA:{
                return std::make_shared<Ma>(p.first,p.second,!side);
            }break;
            }
        };
        for(auto i:pieces){
            //qDebug()<<i.first<<" "<<(int)i.second;
            if(getSide(i.second)==!side){
                std::shared_ptr<Piece> temp = createPiece(i.first,i.second);
                //qDebug()<<i.first<<" "<<temp->isThreat(pieces);
                if(temp->isThreat(pieces))return true;
            }
        }
        return false;
    }

    static const bool isCheck(bool side) {
        //Add your own code below
        //////////////////////////
        auto list=Board::getBoard()->find(-1,-1,-1);
        if(isCheck(list,side))return true;
        //////////////////////////
        return false;
    }
};

#endif // ALGORITHMS_H
