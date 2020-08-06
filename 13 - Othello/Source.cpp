#include <iostream>
#include <vector>

typedef std::vector<std::vector<char>> OthelloBoardState;


bool IsValidMove(char player, int x, int y, const OthelloBoardState& grid)
{
    // Size of the game board
    const unsigned int SIZE = 8;
    // Determine the opponents playing piece
    const char opp = (player == 'B') ? 'W' : 'B';

    // The space must be empty
    if (grid[y][x] != ' ')
        return false;
    

    // Horizontal and vertical
    for (size_t i = 0; i < 8; i++)
    {
        // Check if there is a valid index in each direction
        bool xpos = (x + (int)i < SIZE-2);
        bool xneg = (x - (int)i > 1);
        bool ypos = (y + (int)i < SIZE-2);
        bool yneg = (y - (int)i > 1);

        // If all directions are invalid, exit the loop
        if (!xpos && !xneg && !ypos && !yneg)
            break;


        // Check if there is an opponent, then a player after it
        if (ypos && grid[y+i][x] == opp && grid[y+i+1][x] == player)
            return true;
        if (yneg && grid[y-i][x] == opp && grid[y-i-1][x] == player)
            return true;
        if (xpos && grid[y][x+i] == opp && grid[y][x+i+1] == player)
            return true;
        if (xneg && grid[y][x-i] == opp && grid[y][x-i-1] == player)
            return true;
    }

    // Diagnals
    for (size_t i = 0; i < 8; i++)
    {
        // Check if there is a valid index in each direction
        bool ppos = (x - (int)i > 1 && y + (int)i < SIZE-2);        //pos gradient, pos direction
        bool pneg = (x + (int)i < SIZE-2 && y - (int)i > 1);        //pos gradient, neg direction
        bool npos = (x + (int)i < SIZE-2 && y + (int)i < SIZE-2);   //neg gradient, pos direction
        bool nneg = (x - (int)i > 1 && y - (int)i > 1);             //neg gradient, neg direction
        
        // If all directions are invalid, exit the loop
        if (!ppos && !pneg && !npos && !nneg)
            break;


        // Check if there is an opponent, then a player after it
        if (ppos && grid[y+i][x-i] == opp && grid[y+i+1][x-i-1] == player)
            return true;
        if (pneg && grid[y-i][x+i] == opp && grid[y-i-1][x+i+1] == player)
            return true;
        if (npos && grid[y+i][x+i] == opp && grid[y+i+1][x+i+1] == player)
            return true;
        if (nneg && grid[y-i][x-i] == opp && grid[y-i-1][x-i-1] == player)
            return true;
    }


    // There was no valid move found
    return false;
}


OthelloBoardState MakeMove(char player, int x, int y, OthelloBoardState grid)
{
    // if the move was not valid, just return the origional...
    if (IsValidMove(player, x, y, grid) == false)
        return grid;
    // TODO: This is optionan, but gitve it a go if you have time ;)
    // update 'grid' so that the approprate tiles have been flipped.
    return grid;
}

int main(int argc, char** argv)
{
    OthelloBoardState state1 =
    {//   0    1    2    3    4    5    6    7
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 0
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 1
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 2
        {' ', ' ', ' ', 'W', 'B', ' ', ' ', ' '}, // 3
        {' ', ' ', ' ', 'B', 'W', ' ', ' ', ' '}, // 4
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 5
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 6
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}  // 7
    };
    auto ShouldBe = [](auto result, auto expected) {
        std::cout << (result == expected ? "\033[32m [PASS]" : "\033[31m [FAIL]") << "\033[0m" << std::endl;
    };
    ShouldBe(IsValidMove('B', 5, 4, state1), true); // true
    ShouldBe(IsValidMove('B', 2, 4, state1), false); // false
    ShouldBe(IsValidMove('B', 3, 2, state1), true); // true
    ShouldBe(IsValidMove('B', 3, 5, state1), false); // false
    ShouldBe(IsValidMove('B', 5, 5, state1), false); // false
    ShouldBe(IsValidMove('W', 5, 4, state1), false); // false
    ShouldBe(IsValidMove('W', 2, 4, state1), true); // true
    ShouldBe(IsValidMove('W', 3, 2, state1), false); // false
    ShouldBe(IsValidMove('W', 3, 5, state1), true); // true
    ShouldBe(IsValidMove('W', 5, 5, state1), false); // false
    OthelloBoardState state2 =
    {//   0    1    2    3    4    5    6    7
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 0
        {' ', ' ', 'B', ' ', ' ', ' ', ' ', ' '}, // 1
        {' ', ' ', 'B', 'W', ' ', ' ', ' ', ' '}, // 2
        {' ', ' ', 'B', 'W', 'B', ' ', ' ', ' '}, // 3
        {' ', ' ', 'W', 'W', 'W', ' ', ' ', ' '}, // 4
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 5
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 6
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}  // 7
    };
    ShouldBe(IsValidMove('B', 2, 5, state2), true); // true
    ShouldBe(IsValidMove('B', 3, 5, state2), false); // false
    ShouldBe(IsValidMove('B', 4, 5, state2), true); // true
    ShouldBe(IsValidMove('B', 3, 1, state2), false); // false
    ShouldBe(IsValidMove('B', 4, 2, state2), true); // true
    ShouldBe(IsValidMove('B', 4, 1, state2), true); // true

    ShouldBe(IsValidMove('W', 2, 5, state2), false); // false
    ShouldBe(IsValidMove('W', 2, 0, state2), true); // true
    ShouldBe(IsValidMove('W', 3, 1, state2), false); // false
    return 0;
}