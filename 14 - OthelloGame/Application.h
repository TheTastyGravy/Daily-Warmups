#pragma once
#include <vector>
#include <string>

typedef std::vector<std::vector<char>> OthelloBoardState;


class Application
{
public:

    Application();
    ~Application();

    void Run();

    void Load();
    void Unload();
    void Update(float dt);
    void Draw();

    bool IsValidMove(char player, int x, int y, const OthelloBoardState& grid);
    OthelloBoardState MakeMove(char player, int x, int y, OthelloBoardState grid);
    bool AnyValidMoves(char player, const OthelloBoardState& grid);
    void CheckWinState();

protected:
    int m_tileSize = 64;
    OthelloBoardState m_board;

    char m_player = 'B';

    std::string m_endGameMessage = "";
};