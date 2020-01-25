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
    Player player;
    int frame = 0;

    bool updatePlayer(int new_x, int new_y)
    {
        if(state[new_y][new_x] == 'L')
        {
            state[player.y][player.x] == 'L';
            state[new_y][new_x] = 'J';
            player.x = new_x;
            player.y = new_y;
            return true;
        }
        return false;
    };
public:
    Board(std::vector<std::string> init_state, Player i_player)
    :
    state(init_state)
    {
        initPlayer(i_player);
    };

    void initPlayer(Player new_player)
    {
        if(!isValidPlayerXY(new_player.x, new_player.y)) 
        {
            std::cout << "posicion inicial del jugador Invalida" << std::endl;
            return;
        }

        player = new_player;
        updatePlayer(player.x, player.y);
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
        if(x < 0 || y < 0 || x > (state[y].size() - 1) || 1 > (state.size() - 1)) 
            return false;
        return state[y][x] == 'L' || state[y][x] == 'J';
    };

    void movePlayer(Movement move)
    {
        switch (move)
        {
        case Movement::UP:
            if(isValidPlayerXY(player.x, player.y - 1))
                updatePlayer(player.x, player.y - 1);
            break;
        
        case Movement::RIGHT:
            if(isValidPlayerXY(player.x + 1, player.y))
                updatePlayer(player.x + 1, player.y);
            break;
        
        case Movement::DOWN:
            if(isValidPlayerXY(player.x, player.y + 1))
                updatePlayer(player.x, player.y + 1);
            break;
        
        case Movement::LEFT:
            if(isValidPlayerXY(player.x - 1, player.y))
                updatePlayer(player.x - 1, player.y);
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
    
    Board b(board1, {2,2});
    b.draw();

    b.movePlayer(Movement::DOWN);
    b.draw();

    b.movePlayer(Movement::RIGHT);
    b.draw();
    
    return 0;
}
