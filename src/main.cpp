#include <iostream>
#include <vector>
#include <string>


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

    void movePlayer(Movement move)
    {
        switch (move)
        {
        case Movement::UP:
            if(isValidPlayerXY(px, py - 1))
                updatePlayer(px, py - 1);
            break;
        
        case Movement::RIGHT:
            if(isValidPlayerXY(px + 1, py))
                updatePlayer(px + 1, py);
            break;
        
        case Movement::DOWN:
            if(isValidPlayerXY(px, py + 1))
                updatePlayer(px, py + 1);
            break;
        
        case Movement::LEFT:
            if(isValidPlayerXY(px - 1, py))
                updatePlayer(px - 1, py);
            break;
        
        default:
            break;
        }
    }
};




int main(int argc, char const *argv[])
{
    std::cout << "hola sokoban" << std::endl;
    std::cout << "--------------" << std::endl;
    
    Board b(board1, 2, 2);
    b.draw();

    b.movePlayer(Movement::DOWN);
    b.draw();

    b.movePlayer(Movement::RIGHT);
    b.draw();
    
    return 0;
}
