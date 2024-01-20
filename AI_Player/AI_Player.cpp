#include "AI_Player.h"
#include <fstream>

AI_Player::InstantWinInfo AI_Player::checkForPossibleInstantWin(std::vector<std::vector<char>>& boardToCheck, char possibleWinningMark) {
    for (int i = 0; i < emptyLocations.size(); i++) {
        for (int e = 0; e < emptyLocations[0].size(); e++) {
            if (emptyLocations[i][e] == 1) {
                boardToCheck[i][e] = possibleWinningMark; //Putting the mark on the testing analysedBoard
                if (gameAnalyser.analyseIfSomeoneHasWon(boardToCheck) != 0) {
                    boardToCheck[i][e] = '~';
                    return { true, {i, e} };
                }
                boardToCheck[i][e] = '~';

            }
        }
    }
    return { false, { 0, 0 } };
}

void AI_Player::getNextMove() {

    if (justStartedGame) {
        makeRandomMove();
        justStartedGame = false;
        return;
    }
    //Make the testing analysedBoard to be an exact copy of the actual analysedBoard, that's why i've used a nested for loop
    testingBoard = std::vector<std::vector<char>>(board.size(), std::vector<char>(board[0].size()));
    for (int i = 0; i < board.size(); i++) {
        for (int e = 0; e < board[i].size(); e++) {
            testingBoard[i][e] = board[i][e];
        }
    }
    //Record all empty locations on the analysedBoard
    for (int i = 0; i < board.size(); i++) {
        for (int e = 0; e < board[0].size(); e++) {
            emptyLocations[i][e] = (board[i][e] == '~' ? 1 : 0);
        }
    }
    //Create possible instant win information
    AI_Player::InstantWinInfo iwi = checkForPossibleInstantWin(testingBoard, id);
    //Enemy id
    char oppoenntID = (id == 'X' ? 'O' : 'X');

    if (iwi.isPosisble == true) { //We've basically won the game now
        board[iwi.location[0]][iwi.location[1]] = id;
        return;
    }

    //Playing defensive, blocking the other player's chances of success
    // 
    //First defence is simple, just check for an instant win opportunity for the opponent and block it
    iwi = checkForPossibleInstantWin(testingBoard, oppoenntID);
    if (iwi.isPosisble == true) {
        board[iwi.location[0]][iwi.location[1]] = id;
        return;
    }
    //This next defence blocks a possible move by the opponent that will lead to an opportunity for an instant win
    for (int i = 0; i < emptyLocations.size(); i++) {
        for (int e = 0; e < emptyLocations[0].size(); e++) {
            if (emptyLocations[i][e] == 1) {
                testingBoard[i][e] = oppoenntID;
                emptyLocations[i][e] = 0; //So that checkInstant win doesent deal with wrong intel
                iwi = checkForPossibleInstantWin(testingBoard, oppoenntID);
                if (iwi.isPosisble == true) {//We exlicitly set the mark to the enemies's mark, so no need to test the winningMark
                    board[i][e] = id; //Place our AI's mark there so opponent doesent have a chance to win there
                    return;
                }
                testingBoard[i][e] = '~';
                emptyLocations[i][e] = 1;
            }
        }
    }

    //Time to think a little bit more, lets assume there was our mark somewhere on the analysedBoard
    for (int i = 0; i < emptyLocations.size(); i++) {
        for (int e = 0; e < emptyLocations[0].size(); e++) {
            if (emptyLocations[i][e] == 1) { //We only execute this on empty locations
                testingBoard[i][e] = id;
                emptyLocations[i][e] = 0;
                iwi = checkForPossibleInstantWin(testingBoard, id); //Update instant win info
                if (iwi.isPosisble == true) { //If this is true, it means the instant win was a result of the mark we put earlier
                    board[i][e] = id; //We'll just make that move
                    return;
                }
                testingBoard[i][e] = '~';
                emptyLocations[i][e] = 1;
            }
        }
    }

    //No offensive or defensive move to make, lets just do a random move
    makeRandomMove();

}

//Chooses a random locationfroma all the free space remaining and makes a move there
//Dont fuck with this one it works perfectly
void AI_Player::makeRandomMove() {
    srand(((unsigned int)time(0)));

    //Update empty locations
    for (int i = 0; i < board.size(); i++) {
        for (int e = 0; e < board[0].size(); e++) {
            emptyLocations[i][e] = (board[i][e] == '~' ? 1 : 0);
        }
    }
    int numOfPosLoc = 0;
    std::vector<std::vector<int>> possibleLocations;
    for (int i = 0; i < emptyLocations.size(); i++) {
        for (int e = 0; e < emptyLocations[0].size(); e++) {
            if (emptyLocations[i][e] == 1) { //Location is empty
                possibleLocations.push_back({ i, e });
                numOfPosLoc++;
            }
        }
    }
    //No need to worry about division by zero, if numOfPosLoc is 0, the game is over(DRAW) so this method shouuldnt even be called
    int randLoc = rand() % numOfPosLoc;
    board[possibleLocations[randLoc][0]][possibleLocations[randLoc][1]] = id;
}

void AI_Player::setup(char theID) {
    srand((unsigned int)time(NULL));
    id = theID;

    int numOfLines = 0;
    std::ifstream ifs;
    ifs.open("Names.txt");
    
    if (ifs.is_open()) {
        while (std::getline(ifs, name)) numOfLines++;
        int randNum = (rand() % (numOfLines + 1)) + 1;
        ifs.clear(); //So that the end of file indicator is set to false
        ifs.seekg(0, std::ios::beg); //Set file stream at the begining
        for (int i = 0; i < randNum; i++) {
            std::getline(ifs, name);
        }
        
    }
    else {
        std::cout << "Error opening AI names file, using Joe...\n";
        name = "Joe";
    }
    ifs.close();
    std::cout << "You'll be playing against me, " << name << "\n";
}