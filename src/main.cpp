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

struct Player
{
    int x;
    int y;
};




std::vector<std::string> board1 = {
    "PPPPP",
    "PLLLP",
    "PLLLP",
    "PLLLP",
    "PPPPP"
};

class Board
{
private:
    std::vector<std::string> state;
    int px;
    int py;
    int frame = 0;
    std::vector<std::array<int,2>> boxes;
    std::vector<std::array<int,2>> goals;

    bool updatePlayer(int new_x, int new_y)
    {
        if(state[new_y][new_x] == 'L' || state[new_y][new_x] == 'J')
        {
            state[new_y][new_x] = 'J';
            state[py][px] = 'L';
            px = new_x;
            py = new_y;
            return true;
        }
        return false;
    };
public:
    Board(std::vector<std::string> init_state, int x, int y)
    :
    state(init_state)
    {
        initPlayer(x, y);
    };

    void initPlayer(int x, int y)
    {
        if(!isValidPlayerXY(x, y)) 
        {
            std::cout << "posicion inicial del jugador Invalida" << std::endl;
            return;
        }

        px = x;
        py = y;
        updatePlayer(px, py);
    };

    void setState(std::vector<std::string> new_state)
    {
        state = new_state;
    };

    std::vector<std::string> getState()
    {
        return state;
    };

    void draw()
    {
        std::cout << "----" << frame << "----" << std::endl;
        for(auto& row: state)
            std::cout << row << std::endl;
        
        std::cout << "-----------" << std::endl;
        frame++;
    };

    bool isValidPlayerXY(int x, int y)
    {
        if(x < 0 || y < 0 || x > (state[y].size() - 1) || y > (state.size() - 1)) 
            return false;
        return state[y][x] == 'L' || state[y][x] == 'J';
    };

    bool isCellFree(int x, int y)
    {
        if(x < 0 || y < 0 || x > (state[y].size() - 1) || y > (state.size() - 1)) 
            return false;
        return state[y][x] == 'L';
    };
    bool isCellGoal(int x, int y)
    {
        if(x < 0 || y < 0 || x > (state[y].size() - 1) || y > (state.size() - 1)) 
            return false;
        return state[y][x] == 'O';
    };
    bool isCellBox(int x, int y)
    {
        if(x < 0 || y < 0 || x > (state[y].size() - 1) || y > (state.size() - 1)) 
            return false;
        return state[y][x] == 'C';
    };

    void movePlayer(Movement move)
    {
        int next_x = px;
        int next_y = py;
        switch (move)
        {
        case Movement::UP:
            next_x = px;
            next_y = py - 1;
            
            if(isValidPlayerXY(next_x, next_y))
                updatePlayer(next_x, next_y);
            else if(isCellBox(next_x, next_y))
            {
                // se puede empujar la caja
                if(isCellFree(next_x,next_y - 1) || isCellGoal(next_x, next_y -1))
                {
                    // mover la caja
                    // -- encontrar en indice de la caja en el vector boxes
                    std::array<int, 2> box_pos = {next_x, next_y};
                    auto it = std::find(boxes.begin(), boxes.end(), box_pos);
                    (*it)[1] = (*it)[1] - 1;
                    updateBoxes();
                    // mover el jugador
                    updatePlayer(next_x, next_y);
                }   
                // no se empujar la caja
            }
            break;
        
        case Movement::RIGHT:
            next_x = px + 1;
            next_y = py;
            if(isValidPlayerXY(next_x, next_y))
                updatePlayer(next_x, next_y);
            else if(isCellBox(next_x, next_y))
            {
                // se puede empujar la caja
                if(isCellFree(next_x + 1,next_y) || isCellGoal(next_x + 1, next_y))
                {
                    // mover la caja
                    // -- encontrar en indice de la caja en el vector boxes
                    std::array<int, 2> box_pos = {next_x, next_y};
                    auto it = std::find(boxes.begin(), boxes.end(), box_pos);
                    (*it)[0] = (*it)[0] + 1;
                    updateBoxes();
                    // mover el jugador
                    updatePlayer(next_x, next_y);
                }   
                // no se empujar la caja
            }
            
            break;
        
        case Movement::DOWN:
            next_x = px;
            next_y = py + 1;
            if(isValidPlayerXY(next_x, next_y))
                updatePlayer(next_x, next_y);
            else if(isCellBox(next_x, next_y))
            {
                // se puede empujar la caja
                if(isCellFree(next_x,next_y + 1) || isCellGoal(next_x, next_y + 1))
                {
                    // mover la caja
                    // -- encontrar en indice de la caja en el vector boxes
                    std::array<int, 2> box_pos = {next_x, next_y};
                    auto it = std::find(boxes.begin(), boxes.end(), box_pos);
                    (*it)[1] = (*it)[1] + 1;
                    updateBoxes();
                    // mover el jugador
                    updatePlayer(next_x, next_y);
                }   
                // no se empujar la caja
            }
            
            break;
        
        case Movement::LEFT:
            next_x = px - 1;
            next_y = py;
            if(isValidPlayerXY(next_x, next_y))
                updatePlayer(next_x, next_y);
            else if(isCellBox(next_x, next_y))
            {
                // se puede empujar la caja
                if(isCellFree(next_x - 1,next_y) || isCellGoal(next_x - 1, next_y))
                {
                    // mover la caja
                    // -- encontrar en indice de la caja en el vector boxes
                    std::array<int, 2> box_pos = {next_x, next_y};
                    auto it = std::find(boxes.begin(), boxes.end(), box_pos);
                    (*it)[0] = (*it)[0] - 1;
                    updateBoxes();
                    // mover el jugador
                    updatePlayer(next_x, next_y);
                }   
                // no se empujar la caja
            }
            break;
        
        default:
            break;
        }

        std::cout << (checkGoals() ? "ganaste!" : "todavia no") << std::endl;
    };

    void addBox(int x, int y)
    {
        if(isCellFree(x, y))
        {
            boxes.push_back({x,y});
        }
        updateBoxes();
    };

    void addGoal(int x, int y)
    {
        if(isCellFree(x, y))
        {
            goals.push_back({x,y});
        }
        
        for(auto& goal: goals)
            state[goal[1]][goal[0]] = 'O';
    };

    bool checkGoals()
    {
        if(boxes.size() != goals.size())
            return false;
        
        for(int i = 0; i < goals.size(); i++)
        {
            if(goals[i] != boxes[i])
                return false;
        }

        return true;
    }
    void updateBoxes()
    {
        for(auto& row: state)
        {
            for(auto& cell: row)
            {
                if(cell == 'C')
                    cell = 'L';
            }
        }

        for(auto& box: boxes)
            state[box[1]][box[0]] = 'C';
    };
};




int main(int argc, char const *argv[])
{
    std::cout << "hola sokoban" << std::endl;
    std::cout << "--------------" << std::endl;
    
    Board b(board1, 2, 3);
    b.addBox(2,2);
    b.addGoal(2,1);
    b.draw();

    b.movePlayer(Movement::LEFT);
    b.draw();

    b.movePlayer(Movement::RIGHT);
    b.draw();

    b.movePlayer(Movement::UP);
    b.draw();

    b.movePlayer(Movement::RIGHT);
    b.draw();
    
    return 0;
}
