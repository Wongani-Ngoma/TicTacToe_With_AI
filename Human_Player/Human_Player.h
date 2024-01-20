#pragma once
#include "Player.h"
#include <string>
#include <stdlib.h>
#include <iostream>

class Human_Player : public Player {
public:
    Human_Player(std::vector<std::vector<char>>& theanalysedBoardPtr) : Player(theanalysedBoardPtr) {}
    void getNextMove() override;
    void setup(char theID) override;

};