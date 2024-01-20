#include "GameAnalyser.h"

//Returns true only when the positions right of analysedBoard[row][col] if they have the same mark as analysedBoard[row][col] itself
bool GameAnalyser::isPartOfFullHoriLineRight(int row, int col, std::vector<std::vector<char>>& analysedBoard)  const {
    if (analysedBoard[row][col] == '~') return false;

    for (int i = col + 1; i <= col + (numOfMarksToWin - 1); i++) {
        if (analysedBoard[row][i] != analysedBoard[row][col]) return false;
    }
    return true;
}

bool GameAnalyser::isPartOfFullHoriLineLeft(int row, int col, std::vector<std::vector<char>>& analysedBoard)  const {
    if (analysedBoard[row][col] == '~') return false;

    for (int i = col - 1; i >= col - (numOfMarksToWin - 1); i--) {
        if (analysedBoard[row][i] != analysedBoard[row][col]) return false;
    }
    return true;
}

bool GameAnalyser::isPartOfFullVertLineDown(int row, int col, std::vector<std::vector<char>>& analysedBoard) const {
    if (analysedBoard[row][col] == '~') return false;

    for (int i = row + 1; i <= row + (numOfMarksToWin - 1); i++) {
        if (analysedBoard[i][col] != analysedBoard[row][col]) return false;
    }
    return true;
}

bool GameAnalyser::isPartOfFullVertLineUp(int row, int col, std::vector<std::vector<char>>& analysedBoard) const {
    if (analysedBoard[row][col] == '~') return false;

    for (int i = row - 1; i >= row - (numOfMarksToWin - 1); i--) {
        if (analysedBoard[i][col] != analysedBoard[row][col]) return false;
    }
    return true;

}

bool GameAnalyser::isPartOfFullForwardDiagLineLeft(int row, int col, std::vector<std::vector<char>>& analysedBoard) const {
    if (analysedBoard[row][col] == '~') return false;

    for (int i = 1; i <= numOfMarksToWin - 1; i++) {
        if (analysedBoard[row + i][col - i] != analysedBoard[row][col]) return false;
    }
    return true;
}

bool GameAnalyser::isPartOfFullBackwardDiagLineLeft(int row, int col, std::vector<std::vector<char>>& analysedBoard) const {
    if (analysedBoard[row][col] == '~') return false;

    for (int i = 1; i <= numOfMarksToWin - 1; i++) {
        if (analysedBoard[row - i][col - i] != analysedBoard[row][col]) return false;
    }
    return true;
}

bool GameAnalyser::isPartOfFullForwardDiagLineRight(int row, int col, std::vector<std::vector<char>>& analysedBoard) const {
    if (analysedBoard[row][col] == '~') return false;

    for (int i = 1; i <= numOfMarksToWin - 1; i++) {
        if (analysedBoard[row - i][col + i] != analysedBoard[row][col]) return false;
    }
    return true;
}

bool GameAnalyser::isPartOfFullBackwardDiagLineRight(int row, int col, std::vector<std::vector<char>>& analysedBoard) const {
    if (analysedBoard[row][col] == '~') return false;

    for (int i = 1; i <= numOfMarksToWin - 1; i++) {
        if (analysedBoard[row + i][col + i] != analysedBoard[row][col]) return false;
    }
    return true;
}

void GameAnalyser::setNumberOfMarksToWin(int newNumberOfMarksToWin) {
    numOfMarksToWin = newNumberOfMarksToWin;
}

//Ever seen trash code such as this?
bool GameAnalyser::analyseIfMarkHasWon(int row, int col, std::vector<std::vector<char>>& analysedBoard)  const {
    if (col <= (analysedBoardColumns - numOfMarksToWin)) {
        if (isPartOfFullHoriLineRight(row, col, analysedBoard)) return true;
    }

    if (col >= (numOfMarksToWin - 1)) {
        if (isPartOfFullHoriLineLeft(row, col, analysedBoard)) return true;
    }

    if (row <= (analysedBoardRows - numOfMarksToWin)) {
        if (isPartOfFullVertLineDown(row, col, analysedBoard)) return true;
    }

    if (row >= (numOfMarksToWin - 1)) {
        if (isPartOfFullVertLineUp(row, col, analysedBoard)) return true;
    }

    if ((row >= (numOfMarksToWin - 1)) && (col >= (numOfMarksToWin - 1))) {
        if (isPartOfFullBackwardDiagLineLeft(row, col, analysedBoard)) return true;
    }

    if ((row >= (numOfMarksToWin - 1) && col <= (analysedBoardColumns - numOfMarksToWin))) {
        if (isPartOfFullForwardDiagLineRight(row, col, analysedBoard)) return true;
    }

    if ((row <= (analysedBoardRows - numOfMarksToWin)) && (col <= (analysedBoardColumns - numOfMarksToWin))) {
        if (isPartOfFullBackwardDiagLineRight(row, col, analysedBoard)) return true;
    }

    if ((row <= (analysedBoardRows - numOfMarksToWin) && (col >= (numOfMarksToWin - 1)))) {
        if (isPartOfFullForwardDiagLineLeft(row, col, analysedBoard)) return true;
    }

    return false;
}

//This simply returns true if some a mark(any) has won
char GameAnalyser::analyseIfSomeoneHasWon(std::vector<std::vector<char>>& analysedBoard)  const {
    for (int i = 0; i < analysedBoard.size(); i++) {
        for (int e = 0; e < analysedBoard[0].size(); e++) {
            if (analyseIfMarkHasWon(i, e, analysedBoard)) return analysedBoard[i][e];
        }
    }
    return 0;
}
