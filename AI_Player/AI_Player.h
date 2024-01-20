#pragma once
#include "Player.h"
#include "GameAnalyser.h"
#include <time.h>
#include <random>
#include <string.h>

class AI_Player : public Player {
public:
    AI_Player(std::vector<std::vector<char>>& theBoardPtr, GameAnalyser theGameAnalyser) :
        Player(theBoardPtr),
        gameAnalyser(theGameAnalyser) {
        emptyLocations = std::vector<std::vector<int>>(board.size(), std::vector<int>(board[0].size()));

    }
    void getNextMove() override;
    void setup(char theID) override;
private:

    struct InstantWinInfo { //Try to switch the order of this to see size changes (padding)
        bool isPosisble;
        std::vector<int> location;
    };

    void makeRandomMove();
    //Checks if an instant win is possible by putting some marks around the testing board and if it is, it makes that move on the actual analysedBoard
    InstantWinInfo checkForPossibleInstantWin(std::vector<std::vector<char>>& boardToCheck, char possibleWinningMark);
    //Game analyser for ai to use when making moves
    GameAnalyser gameAnalyser;
    //A copy  of the board for us to play with when deciding the move
    std::vector<std::vector<char>> testingBoard;
    //Record all empty locations on the actual game board
    std::vector<std::vector<int>> emptyLocations;
    //When the game has just started, the AI makes a randon move, not a thoghtful one, so we need this to let it know what to do
    bool justStartedGame = true;
};