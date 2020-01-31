#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include<bits/stdc++.h> 

enum Movement {
    UP,
    RIGHT,
    DOWN,
    LEFT
};


class Board
{
private:
    /* data */
    std::vector<std::string> state;
    int px;
    int py;
    int frame;
    std::vector<std::array<int,2>> boxes;
    std::vector<std::array<int,2>> goals;

    bool updatePlayer(int new_x, int new_y);

public:
    //                              layout      ancho alto
    Board(std::vector<std::string> init_state, int x, int y);
    void initPlayer(int x, int y);
    void setState(std::vector<std::string> new_state);
    std::vector<std::string> getState();
    void draw();
    bool isValidPlayerXY(int x, int y);
    bool isCellFree(int x, int y);
    bool isCellGoal(int x, int y);
    bool isCellBox(int x, int y);
    void movePlayer(Movement move);
    void addBox(int x, int y);
    void addGoal(int x, int y);
    bool checkGoals();
    void updateBoxes();
    void updateGoals();
    
};
#endif