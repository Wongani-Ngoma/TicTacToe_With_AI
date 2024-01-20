#pragma once
#include <vector>
class GameAnalyser {
public:
    GameAnalyser(int theNumOfMarksToWin,
        const int theanalysedBoardRows, const int theanalysedBoardColumns)
        : numOfMarksToWin(theNumOfMarksToWin)
        , analysedBoardRows(theanalysedBoardRows)
        , analysedBoardColumns(theanalysedBoardColumns) {}
    bool isPartOfFullHoriLineRight(int row, int col, std::vector<std::vector<char>>& analysedBoard) const;
    bool isPartOfFullHoriLineLeft(int row, int col, std::vector<std::vector<char>>& analysedBoard) const;
    bool isPartOfFullVertLineDown(int row, int col, std::vector<std::vector<char>>& analysedBoard) const;
    bool isPartOfFullVertLineUp(int row, int col, std::vector<std::vector<char>>& analysedBoard) const;
    bool isPartOfFullForwardDiagLineLeft(int row, int col, std::vector<std::vector<char>>& analysedBoard) const;
    bool isPartOfFullBackwardDiagLineLeft(int row, int col, std::vector<std::vector<char>>& analysedBoard) const;
    bool isPartOfFullForwardDiagLineRight(int row, int col, std::vector<std::vector<char>>& analysedBoard) const;
    bool isPartOfFullBackwardDiagLineRight(int row, int col, std::vector<std::vector<char>>& analysedBoard) const;

    void setNumberOfMarksToWin(int newNumberOfMarksToWin);
    bool analyseIfMarkHasWon(int row, int col, std::vector<std::vector<char>>& analysedBoard) const;
    char analyseIfSomeoneHasWon(std::vector<std::vector<char>>& analysedBoard) const;

private:

    int numOfMarksToWin;
    const int analysedBoardRows;
    const int analysedBoardColumns;
};

