#include "Human_Player.h"

void Human_Player::getNextMove()
{
    while (true) {
        char row_char, col_char = ' ';
        int row, col = 0;
        std::cout << "-" << name << "'s turn!\n--Enter row: ";
        std::cin >> row_char;
        row = row_char - 48; //Simple conversion to int
        if (row < 1 || row > board.size()) {
            std::cout << "Please enter a valid row number\n";
            continue;
        }
        std::cout << "--Enter column: ";
        std::cin >> col_char;
        col = col_char - 48; //Simple conversion to int
        if (col < 1 || col > board[0].size()) {
            std::cout << "Please enter a valid column number\n";
            continue;
        }
        if (board[row - 1][col - 1] != '~') {
            std::cout << "That place already contains a mark, try again\n";
            continue;
        }
        board[row - 1][col - 1] = id;
        break;
    }
    return;
}

void Human_Player::setup(char theID) {
    id = theID;
    std::cout << "Enter name: ";
    //std::getline(std::cin, name);
    std::cin >> name;
}