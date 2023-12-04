//
// Created by eddi on 23. 12. 4.
//

#include <iostream>
#include "BoardManager.h"

BoardManager &BoardManager::getInstance(std::shared_ptr<BoardController> _boardController) {
    static BoardManager boardManager;
    boardManager.boardController = _boardController;
    return boardManager;
}
// 추후 UI랑 위치를 바꾸는게 좋아보임
void BoardManager::startBoard() {

    std::cout << "게시판 시작!" << std::endl;

    boardList = boardController->boardList();
    nextUid = boardList[boardList.size()-1].getBoardUID()+1;


}

void BoardManager::printBoardList() {
    std::cout << "가즈아ㅏㅏㅏ\n\n\n" << std::endl;
    int count = boardList.size();
    for(int i = 0; i < count ; i++){
        boardList[i].printBoardInfo();
    }
}

unsigned int BoardManager::getNextUid(){
    return nextUid;
}

std::vector<Board> BoardManager::getBoardList() {
    return boardList;
}


