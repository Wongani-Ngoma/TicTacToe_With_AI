#include <iostream>
#include <string>
#include <vector>
#include "AI_Player.h"
#include "Human_Player.h"
#include "GameAnalyser.h"

enum GameState { X_WON, O_WON, DRAW, NOT_OVER };

//Function prototypes
void setupGame();
void setupPlayers();
void gameLoop();
void printResults();
GameState getGameState();
void setupBoard();
void printBoard();

//Players' data
std::string playerName;
char myID;

Player* player1;
Player* player2;

//Game data
GameState gameState = NOT_OVER;
std::vector<std::vector<char>> gameBoard;
const int boardRows = 5;
const int boardColumns = 5;
const int numOfMarksToWin = 4;
GameAnalyser gameAnalyser(numOfMarksToWin, boardRows, boardColumns);

int main() {
    setupGame();
    gameLoop();
    printResults();
    system("pause");
    return 0;
}

void setupGame() {
    setupBoard();
    setupPlayers();
}

void setupPlayers() {

    std::string decision;
    int decisionInt;

    std::cout << "================\nTIC-TAC-TOE\n================\n";
    std::cout << "Select type of match\n1: Human vs Human\n2: Human vs AI\n3: AI vs Human\n4: AI vs AI\n -- ";
    std::cin >> decision;
    decisionInt = std::stoi(decision);
    switch (decisionInt) {
    case 1:
        player1 = new Human_Player(gameBoard);
        player2 = new Human_Player(gameBoard);
        std::cout << "Player 1 setup\n";
        player1->setup('X');
        std::cout << "Player 2 setup\n";
        player2->setup('O');
        break;
    case 2:
        player1 = new Human_Player(gameBoard);
        std::cout << "Player 1 setup\n";
        player1->setup('X');
        player2 = new AI_Player(gameBoard, gameAnalyser);
        std::cout << "Player 2 setup\n";
        player2->setup('O');
        break;
    case 3:
        player1 = new AI_Player(gameBoard, gameAnalyser);
        std::cout << "Player 1 setup\n";
        player1->setup('X');
        player2 = new Human_Player(gameBoard);
        std::cout << "Player 2 setup\n";
        player2->setup('O');
        break;
    case 4:
        player1 = new AI_Player(gameBoard, gameAnalyser);
        std::cout << "Player 1 setup\n";
        player1->setup('X');
        player2 = new AI_Player(gameBoard, gameAnalyser);
        std::cout << "Player 2 setup\n";
        player2->setup('O');
        break;
    default:
        std::cout << "Please choose a valid choice\n";
        break;
    }

}

void gameLoop() {
    char row_char, col_char = ' ';
    int row, col = 0;
    while (true) {
        player1->getNextMove();

        printBoard();

        if (getGameState() != NOT_OVER) break;

        player2->getNextMove();

        printBoard();

        if (getGameState() != NOT_OVER) break;
    }

}

void setupBoard() {
    gameBoard = std::vector<std::vector<char>>(boardRows, std::vector<char>(boardColumns));
    for (std::vector<char>& row : gameBoard) {
        for (char& cell : row) {
            cell = '~';
        }
    }
}

GameState getGameState() {
    char result = gameAnalyser.analyseIfSomeoneHasWon(gameBoard);
    if (result != 0) { //Someone won
        gameState = (result == 'X' ? X_WON : O_WON);
        return gameState;
    }
    bool isFull = true; //Lets assume the gameBoard it's full, if we spot a '~', this will get set to false
    for (int i = 0; i < boardRows; i++) {
        for (int e = 0; e < boardColumns; e++) {
            if (gameBoard[i][e] == '~') {
                isFull = false;
            }
        }
    }
    if (isFull) gameState = DRAW;
    return gameState;
    gameState = NOT_OVER;
    return gameState;
}

void printBoard() {
    system("cls");
    //First row
    std::cout << "|";
    for (int i = 0; i < boardColumns; i++) {
        std::cout << gameBoard[0][i] << "|";
    }
    std::cout << "\n";
    for (int i = 0; i < boardColumns; i++) {
        std::cout << "--";
    }
    std::cout << "-";
    std::cout << "\n";

    //Print all middle rows
    for (int i = 1; i < boardRows - 1; i++) {
        std::cout << "|";
        for (int e = 0; e < boardColumns; e++) {
            std::cout << gameBoard[i][e] << "|";
        }
        std::cout << "\n";
        for (int i = 0; i < boardColumns; i++) {
            std::cout << "--";
        }
        std::cout << "-";
        std::cout << "\n";
    }

    //Last row
    std::cout << "|";
    for (int i = 0; i < boardColumns; i++) {
        std::cout << gameBoard[boardRows - 1][i] << "|";
    }
    std::cout << "\n";
    for (int i = 0; i < boardColumns; i++) {
        std::cout << "--";
    }
    std::cout << "-";
    std::cout << "\n";
}

void printResults() {
    if (gameState == X_WON) std::cout << "---------- X won ----------\n";
    if (gameState == O_WON) std::cout << "---------- O won ----------\n";
    if (gameState == DRAW) std::cout << "---------- Draw! ----------\n";
}