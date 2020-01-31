#include "board.h"

Board::Board(std::vector<std::string> init_state, int x, int y)
    : state(init_state), frame(0)
{
    initPlayer(x, y);
    state[y][x] = 'J';
}

bool Board::updatePlayer(int new_x, int new_y)
{
    char next_cell = state[new_y][new_x];
    if (next_cell == 'L' || next_cell == 'J' || next_cell == 'O')
    {
        state[new_y][new_x] = 'J';
        state[py][px] = 'L';
        px = new_x;
        py = new_y;
        return true;
    }
    return false;
}

void Board::initPlayer(int x, int y)
{
    if (!isValidPlayerXY(x, y))
    {
        std::cout << "posicion inicial del jugador Invalida" << std::endl;
        return;
    }

    px = x;
    py = y;
    updatePlayer(px, py);
}
void Board::setState(std::vector<std::string> new_state)
{
    state = new_state;
}
std::vector<std::string> Board::getState()
{
    return state;
}
void Board::draw()
{
    std::cout << "----" << frame << "----" << std::endl;
    for (auto &row : state)
        std::cout << row << std::endl;

    std::cout << "-----------" << std::endl;
    frame++;
}
bool Board::isValidPlayerXY(int x, int y)
{
    if (x < 0 || y < 0 || x > (state[y].size() - 1) || y > (state.size() - 1))
        return false;
    return state[y][x] == 'L' || state[y][x] == 'J';
}
bool Board::isCellFree(int x, int y)
{
    if (x < 0 || y < 0 || x > (state[y].size() - 1) || y > (state.size() - 1))
        return false;
    return state[y][x] == 'L';
}
bool Board::isCellGoal(int x, int y)
{
    if (x < 0 || y < 0 || x > (state[y].size() - 1) || y > (state.size() - 1))
        return false;
    return state[y][x] == 'O';
}
bool Board::isCellBox(int x, int y)
{
    if (x < 0 || y < 0 || x > (state[y].size() - 1) || y > (state.size() - 1))
        return false;
    return state[y][x] == 'C';
}
void Board::movePlayer(Movement move)
{
    int next_x = px;
    int next_y = py;
    switch (move)
    {
    case Movement::UP:
        next_x = px;
        next_y = py - 1;

        if (isValidPlayerXY(next_x, next_y) || isCellGoal(next_x, next_y))
            updatePlayer(next_x, next_y);
        else if (isCellBox(next_x, next_y))
        {
            // se puede empujar la caja
            if (isCellFree(next_x, next_y - 1) || isCellGoal(next_x, next_y - 1))
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
        updateGoals();
        break;

    case Movement::RIGHT:
        next_x = px + 1;
        next_y = py;
        
        if (isValidPlayerXY(next_x, next_y) || isCellGoal(next_x, next_y))
            updatePlayer(next_x, next_y);
        else if (isCellBox(next_x, next_y))
        {
            // se puede empujar la caja
            if (isCellFree(next_x + 1, next_y) || isCellGoal(next_x + 1, next_y))
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

updateGoals();
        break;

    case Movement::DOWN:
        next_x = px;
        next_y = py + 1;
        
        if (isValidPlayerXY(next_x, next_y) || isCellGoal(next_x, next_y))
            updatePlayer(next_x, next_y);
        else if (isCellBox(next_x, next_y))
        {
            // se puede empujar la caja
            if (isCellFree(next_x, next_y + 1) || isCellGoal(next_x, next_y + 1))
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

updateGoals();
        break;

    case Movement::LEFT:
        next_x = px - 1;
        next_y = py;
        
        if (isValidPlayerXY(next_x, next_y) || isCellGoal(next_x, next_y))
            updatePlayer(next_x, next_y);
        else if (isCellBox(next_x, next_y))
        {
            // se puede empujar la caja
            if (isCellFree(next_x - 1, next_y) || isCellGoal(next_x - 1, next_y))
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
        updateGoals();
        break;

    default:
        break;
    }

    std::cout << (checkGoals() ? "ganaste!" : "todavia no") << std::endl;
}
void Board::addBox(int x, int y)
{
    if (isCellFree(x, y))
    {
        boxes.push_back({x, y});
    }
    updateBoxes();
}
void Board::addGoal(int x, int y)
{
    if (isCellFree(x, y))
    {
        goals.push_back({x, y});
    }

    for (auto &goal : goals)
        state[goal[1]][goal[0]] = 'O';
}
bool Board::checkGoals()
{
    if (boxes.size() != goals.size())
        return false;

    for (int i = 0; i < goals.size(); i++)
    {
        if (goals[i] != boxes[i])
            return false;
    }

    return true;
}
void Board::updateBoxes()
{
    for (auto &row : state)
    {
        for (auto &cell : row)
        {
            if (cell == 'C')
                cell = 'L';
        }
    }

    for (auto &box : boxes)
        state[box[1]][box[0]] = 'C';
}

void Board::updateGoals()
{
    for (auto &row : state)
    {
        for (auto &cell : row)
        {
            if (cell == 'O')
                cell = 'L';
        }
    }

    for (auto &goal : goals)
        state[goal[1]][goal[0]] = 'O';
}