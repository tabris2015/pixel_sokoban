#define OLC_PGE_APPLICATION
#include <iostream>
#include "olcPixelGameEngine.h"
#include "board.h"


std::vector<std::string> board1 = {
    "PPPPPPPPPPPPPPP",
    "PLLLPLLLLPPLLLP",
    "PLLLLLLLLLPLLLP",
    "PLLLLLLLLPPLLLP",
    "PPLPPLLLLLLLLLP",
    "PLLLPLLLLPPLLLP",
    "PLLLPLLLLLLLLLP",
    "PPPPPPPPPPPPPPP"};

// Override base class with your custom functionality
class Sokoban : public olc::PixelGameEngine
{
private:
    // tablero
    Board board;

    void DrawBoard()
    {
        for(int row = 0; row < board.getState().size(); row++)
        {
            for(int col = 0; col < board.getState()[0].size(); col++)
            {
                olc::Pixel color;
                switch (board.getState()[row][col])
                {
                case 'P':
                    color = olc::DARK_GREY;
                    break;
                case 'L':
                    color = olc::VERY_DARK_MAGENTA;
                    break;
                case 'C':
                    color = olc::BLUE;
                    break;
                case 'O':
                    color = olc::GREEN;
                    break;
                case 'J':
                    color = olc::DARK_RED;
                    break;
                default:
                    break;
                }
                Draw(col, row, color);
            }
        }
    }
public:
    Sokoban(std::vector<std::string> layout, int x, int y): board(layout, x, y)
    {
        board.draw();
        sAppName = "Sokoban";
    }

public:
    bool OnUserCreate() override
    {
        // Called once at the start, so create things here
        board.addBox(4, 2);
        board.addBox(6, 5);
        
        board.addGoal(2, 1);
        board.addGoal(6, 12);
        DrawBoard();
        return true;
    }
    bool OnUserUpdate(float fElapsedTime) override
    {
        if(GetKey(olc::Key::LEFT).bPressed)
        {
            board.movePlayer(Movement::LEFT);
        }
        else if(GetKey(olc::Key::RIGHT).bPressed)
        {
            board.movePlayer(Movement::RIGHT);
        }
        else if(GetKey(olc::Key::UP).bPressed)
        {
            board.movePlayer(Movement::UP);
        }
        else if(GetKey(olc::Key::DOWN).bPressed)
        {
            board.movePlayer(Movement::DOWN);
        }

        DrawBoard();
        return true;
    }
};

int main(int argc, char const *argv[])
{
    std::cout << "hola sokoban" << std::endl;
    std::cout << "--------------" << std::endl;

    Sokoban demo(board1, 2, 3);
    if (demo.Construct(board1[0].size(), board1.size(), 60, 60))
        demo.Start();
    return 0;
}
