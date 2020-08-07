#include "Application.h"
#include "raylib.h"
#include <map>

Application::Application()
{
}

Application::~Application()
{
}


void Application::Run()
{
    InitWindow(m_tileSize * 8, m_tileSize * 8, "Othello");
    Load();
    while (!WindowShouldClose())
    {
        Update(GetFrameTime());
        Draw();
    }
    Unload();
    CloseWindow();
}


void Application::Load()
{
    m_board =
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
}

void Application::Unload()
{
}


void Application::Update(float dt)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        int mouseXIndex = GetMouseX() / m_tileSize;
        int mouseYIndex = GetMouseY() / m_tileSize;
        if (mouseXIndex >= 0 && mouseXIndex < 8 && mouseYIndex >= 0 && mouseYIndex < 8)
        {
            if (IsValidMove(m_player, mouseXIndex, mouseYIndex, m_board))
            {
                m_board = MakeMove(m_player, mouseXIndex, mouseYIndex, m_board);
                // swap to next player
                m_player = m_player == 'B' ? 'W' : 'B';
                if (AnyValidMoves(m_player, m_board) == false)
                {
                    // swap back
                    m_player = m_player == 'B' ? 'W' : 'B';
                    // check again - 
                    if (AnyValidMoves(m_player, m_board) == false)
                    {
                        CheckWinState();
                    }
                }
            }
        }
    }
}

void Application::Draw()
{
    Color bgColor = { 34, 34, 34, 255 };
    Color tileColor = { 0, 144, 103, 255 };
    Color tileHoverColor = { 10, 154, 113, 255 };
    Color whitePieceColor = { 244, 253, 250, 255 };
    Color blackPieceColor = { 19, 26, 24, 255 };
    int mouseXIndex = GetMouseX() / m_tileSize;
    int mouseYIndex = GetMouseY() / m_tileSize;
    BeginDrawing();
    ClearBackground(bgColor);
    // draw chekcered background
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            float xp = x * m_tileSize;
            float yp = y * m_tileSize;
            float hs = m_tileSize * 0.5f;
            Color tCol = x == mouseXIndex && y == mouseYIndex ? tileHoverColor : tileColor;
            DrawRectangle(xp, yp, m_tileSize - 1, m_tileSize - 1, tCol);
            if (m_board[y][x] != ' ')
            {
                Color pieceCol = m_board[y][x] == 'B' ? blackPieceColor : whitePieceColor;
                DrawCircle(xp + hs, yp + hs, hs - 10, pieceCol);
            }
            if (IsValidMove(m_player, x, y, m_board))
            {
                DrawCircle(xp + hs, yp + hs, 5, blackPieceColor);
                DrawCircleLines(xp + hs, yp + hs, 5, whitePieceColor);
            }
        }
    }
    if (m_endGameMessage != "")
    {
        // m_endGameMessage = "Black Wins";
        int sw = GetScreenHeight();
        int sh = GetScreenHeight();
        DrawRectangle(0, sh * 0.5f - 100, sh, 200, { 0, 0, 0, 196 });
        auto textSize = MeasureText(m_endGameMessage.c_str(), 32);
        DrawText(m_endGameMessage.c_str(), sw * 0.5f - textSize * 0.5f, sh * 0.5f, 32, RAYWHITE);
        textSize = MeasureText("Space to play again", 24);
        DrawText("Space to play again", sw * 0.5f - textSize * 0.5f, sh * 0.5f + 42, 24, GRAY);
    }
    EndDrawing();
}


bool Application::IsValidMove(char player, int x, int y, const OthelloBoardState& grid)
{
    // Size of the game board
    const unsigned int SIZE = 8;
    // Determine the opponents playing piece
    const char opp = (player == 'B') ? 'W' : 'B';

    // The space must be empty
    if (grid[y][x] != ' ')
        return false;


    // It must be in range, and it must have an opponent as the first cell in that direction
    bool xpos = (x+1 < SIZE-1 && grid[y][x+1] == opp);
    bool xneg = (x-1 > 0 && grid[y][x-1] == opp);
    bool ypos = (y+1 < SIZE-1 && grid[y+1][x] == opp);
    bool yneg = (y-1 > 0 && grid[y-1][x] == opp);
    // Horizontal and vertical
    for (size_t i = 1; i < SIZE; i++)
    {
        // Check if there is a valid index in each direction
        if (xpos)
            xpos = (x+(int)i < SIZE-1);
        if (xneg)
            xneg = (x-(int)i > 0);
        if (ypos)
            ypos = (y+(int)i < SIZE-1);
        if (yneg)
            yneg = (y-(int)i > 0);

        // If all directions are invalid, exit the loop
        if (!xpos && !xneg && !ypos && !yneg)
            break;
        

        // If there is a player next, this is valid
        if (xpos && grid[y][x+i] == player)
            return true;
        else if (xpos && grid[y][x+i] == ' ') // If the cell is empty, this direction is invalid
            xpos = false;
        // If its an opponent, then xpos stays true

        if (xneg && grid[y][x-i] == player)
            return true;
        else if (xneg && grid[y][x-i] == ' ')
            xneg = false;

        if (ypos && grid[y+i][x] == player)
            return true;
        else if (ypos && grid[y+i][x] == ' ')
            ypos = false;

        if (yneg && grid[y-i][x] == player)
            return true;
        else if (yneg && grid[y-i][x] == ' ')
            yneg = false;
    }


    // It must be in range, and it must have an opponent as the first cell in that direction
    bool ppos = ((x-1 > 0 && y+1 < SIZE-1) && grid[y+1][x-1] == opp);
    bool pneg = ((x+1 < SIZE-1 && y-1 > 0) && grid[y-1][x+1] == opp);
    bool npos = ((x+1 < SIZE-1 && y+1 < SIZE-1) && grid[y+1][x+1] == opp);
    bool nneg = ((x-1 > 0 && y-1 > 0) && grid[y-1][x-1] == opp);
    // Diagnals
    for (size_t i = 1; i < SIZE; i++)
    {
        // Check if there is a valid index in each direction
        if (ppos)
            ppos = (x-(int)i > 0 && y+(int)i < SIZE-1);        //pos gradient, pos direction
        if (pneg)
            pneg = (x+(int)i < SIZE-1 && y-(int)i > 0);        //pos gradient, neg direction
        if (npos)
            npos = (x+(int)i < SIZE-1 && y+(int)i < SIZE-1);   //neg gradient, pos direction
        if (nneg)
            nneg = (x-(int)i > 0 && y-(int)i > 0);             //neg gradient, neg direction

        // If all directions are invalid, exit the loop
        if (!ppos && !pneg && !npos && !nneg)
            break;


        // If there is a player next, this is valid
        if (ppos && grid[y+i][x-i] == player)
            return true;
        else if (ppos && grid[y+i][x-i] == ' ') // If the cell is empty, this direction is invalid
            ppos = false;
        // If its an opponent, then ppos stays true

        if (pneg && grid[y-i][x+i] == player)
            return true;
        else if (pneg && grid[y-i][x+i] == ' ')
            pneg = false;

        if (npos && grid[y+i][x+i] == player)
            return true;
        else if (npos && grid[y+i][x+i] == ' ')
            npos = false;

        if (nneg && grid[y-i][x-i] == player)
            return true;
        else if (nneg && grid[y-i][x-i] == ' ')
            nneg = false;
    }


    // There was no valid move found
    return false;
}

OthelloBoardState Application::MakeMove(char player, int x, int y, OthelloBoardState grid)
{
    // Size of the game board
    const unsigned int SIZE = 8;
    // Determine the opponents playing piece
    const char opp = (player == 'B') ? 'W' : 'B';

    // Map each direction to know what cells to flip
    std::map<const char*, bool> dirMap;
    // Set the selected cell to the player
    grid[y][x] = player;


    // It must be in range, and it must have an opponent as the first cell in that direction
    bool xpos = (x+1 < SIZE-1 && grid[y][x+1] == opp);
    bool xneg = (x-1 > 0 && grid[y][x-1] == opp);
    bool ypos = (y+1 < SIZE-1 && grid[y+1][x] == opp);
    bool yneg = (y-1 > 0 && grid[y-1][x] == opp);
    // Horizontal and vertical
    for (size_t i = 1; i < SIZE; i++)
    {
        // Check if there is a valid index in each direction
        if (xpos)
            xpos = (x + (int)i < SIZE - 1);
        if (xneg)
            xneg = (x - (int)i > 0);
        if (ypos)
            ypos = (y + (int)i < SIZE - 1);
        if (yneg)
            yneg = (y - (int)i > 0);

        // If all directions are invalid, exit the loop
        if (!xpos && !xneg && !ypos && !yneg)
            break;


        // If there is a player next, this is a valid direction
        if (xpos && grid[y][x + i] == player)
            dirMap["EE"] = true;
        if (xpos && grid[y][x + i] != opp) // Stop looking when its not an opponent
            xpos = false;

        if (xneg && grid[y][x - i] == player)
            dirMap["WW"] = true;
        if (xneg && grid[y][x - i] != opp)
            xneg = false;
        
        if (ypos && grid[y + i][x] == player)
            dirMap["NN"] = true;
        if (ypos && grid[y + i][x] != opp)
            ypos = false;

        if (yneg && grid[y - i][x] == player)
            dirMap["SS"] = true;
        if (yneg && grid[y - i][x] != opp)
            yneg = false;
    }

    // It must be in range, and it must have an opponent as the first cell in that direction
    bool ppos = ((x-1 > 0 && y+1 < SIZE-1) && grid[y+1][x-1] == opp);
    bool pneg = ((x+1 < SIZE-1 && y-1 > 0) && grid[y-1][x+1] == opp);
    bool npos = ((x+1 < SIZE-1 && y+1 < SIZE-1) && grid[y+1][x+1] == opp);
    bool nneg = ((x-1 > 0 && y-1 > 0) && grid[y-1][x-1] == opp);
    // Diagnals
    for (size_t i = 1; i < SIZE; i++)
    {
        // Check if there is a valid index in each direction
        if (ppos)
            ppos = (x - (int)i > 0 && y + (int)i < SIZE - 1);        //pos gradient, pos direction
        if (pneg)
            pneg = (x + (int)i < SIZE - 1 && y - (int)i > 0);        //pos gradient, neg direction
        if (npos)
            npos = (x + (int)i < SIZE - 1 && y + (int)i < SIZE - 1);   //neg gradient, pos direction
        if (nneg)
            nneg = (x - (int)i > 0 && y - (int)i > 0);             //neg gradient, neg direction

        // If all directions are invalid, exit the loop
        if (!ppos && !pneg && !npos && !nneg)
            break;


        // If there is a player next, this is a valid direction
        if (ppos && grid[y + i][x - i] == player)
            dirMap["NW"] = true;
        if (ppos && grid[y + i][x - i] != opp) // Stop looking when its not an opponent
            ppos = false;

        if (pneg && grid[y - i][x + i] == player)
            dirMap["SE"] = true;
        if (pneg && grid[y - i][x + i] != opp)
            pneg = false;

        if (npos && grid[y + i][x + i] == player)
            dirMap["NE"] = true;
        if (npos && grid[y + i][x + i] != opp)
            npos = false;

        if (nneg && grid[y - i][x - i] == player)
            dirMap["SW"] = true;
        if (nneg && grid[y - i][x - i] != opp)
            nneg = false;
    }


    // Update game board
    for (int i = 1; i < SIZE; i++)
    {
        // Horizontal and vertical
        if (dirMap["NN"])
        {
            if (grid[y + i][x] == opp)
                grid[y + i][x] = player;
            else
                dirMap["NN"] = false;
        }
        if (dirMap["SS"])
        {
            if (grid[y - i][x] == opp)
                grid[y - i][x] = player;
            else
                dirMap["SS"] = false;
        }
        if (dirMap["EE"])
        {
            if (grid[y][x + i] == opp)
                grid[y][x + i] = player;
            else
                dirMap["EE"] = false;
        }
        if (dirMap["WW"])
        {
            if (grid[y][x - i] == opp)
                grid[y][x - i] = player;
            else
                dirMap["WW"] = false;
        }

        // Diagnals
        if (dirMap["NW"])
        {
            if (grid[y + i][x - i] == opp)
                grid[y + i][x - i] = player;
            else
                dirMap["NW"] = false;
        }
        if (dirMap["NE"])
        {
            if (grid[y + i][x + i] == opp)
                grid[y + i][x + i] = player;
            else
                dirMap["NE"] = false;
        }
        if (dirMap["SW"])
        {
            if (grid[y - i][x - i] == opp)
                grid[y - i][x - i] = player;
            else
                dirMap["SW"] = false;
        }
        if (dirMap["SE"])
        {
            if (grid[y - i][x + i] == opp)
                grid[y - i][x + i] = player;
            else
                dirMap["SE"] = false;
        }
    }

    // Return the new game board
    return grid;
}


bool Application::AnyValidMoves(char player, const OthelloBoardState& grid)
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (IsValidMove(player, x, y, grid))
                return true;
        }
    }
    return false;
}

void Application::CheckWinState()
{
    int numBlack = 0;
    int numWhite = 0;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (m_board[y][x] == 'W') numWhite++;
            if (m_board[y][x] == 'B') numBlack++;
        }
    }
    if (numBlack > numWhite) m_endGameMessage = "Black Wins";
    else if (numWhite > numBlack) m_endGameMessage = "White Wins";
    else m_endGameMessage = "Draw";
}