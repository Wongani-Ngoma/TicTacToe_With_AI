#pragma once
#include <iostream>
#include <vector>
#include <string>

class Player {
public:
    Player(std::vector<std::vector<char>>& theBoardPtr) : board(theBoardPtr) {}
    virtual void getNextMove() = 0;
    virtual void setup(char theID) = 0;
    std::string& getNameRef() { return name; }

protected:
    std::string name;
    char id;
    std::vector<std::vector<char>>& board;
};