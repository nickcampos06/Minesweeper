#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "random.h"
#include "TextureManager.h"
using namespace std;

class Board {

    class Tile {
        bool _is_mine; // true or false
        bool _is_revealed;
        bool _is_flagged;
        unsigned int _adjacent_mine_count; // number 1 - 8
        vector<Tile*> _adjacent_mines;
    public:
        // CONSTRUCTORS //
        Tile();

        // ACCESSORS //
        bool IsMine() const;
        bool IsDetonated() const;
        bool IsRevealed() const;
        bool IsFlagged() const;
        Tile* AccessAdjacentMine(unsigned int);

        // MODIFIERS //
        void MakeTileMine();
        void AddAdjacentMine(Tile*);
        void IncrementAdjacentMineCount();

        // GAMEPLAY FUNCTIONS //
        void RevealTile();
        void ForceRevealTile();
        bool ToggleTileFlag();

        // VISUAL OUTPUT //
        void RenderTile(sf::RenderWindow&, unsigned int, unsigned int, bool);

        // CONSOLE OUTPUT //
        void PrintTile(bool debug =  false) const;

    };

    vector<vector<unsigned int>> _mine_positions;
    vector<vector<Tile*>> _board;

    unsigned int _game_status; // 0 = game_active ; 1 = loss ; 2 = win

    unsigned int _board_width;
    unsigned int _board_height;
    int _mine_count;

    unsigned int _window_width;
    unsigned int _window_height;

    // CONSTRUCTOR HELPERS //
    void GrabConfigData(); // loads config data such as width and height
    void GenerateTiles(); // generates a board with desired width and height
    void GenerateMines(); // randomly generates mine positions
    void LoadTiles(string& file_name); // loads tiles from preset file into board
    void SetAdjacentTiles(); // makes every tile aware of its direct neighbors
    void CountAdjacentMines(); // makes mines alert neighboring tiles of its presence

    // GAMEPLAY FUNCTIONS HELPERS //
    void RevealAllTiles();
    void AutoFlagMines();
    void CheckTilesCleared();
public:
    // GAMEPLAY FUNCTIONS //
    void LeftClickOnBoard(unsigned int, unsigned int);
    void RightClickOnBoard(unsigned int, unsigned int);
    void WinLossTileUpdates();

    // ACCESSORS //
    unsigned int GetWindowWidth();
    unsigned int GetWindowHeight();
    unsigned int GetBoardWidth();
    unsigned int GetBoardHeight();
    unsigned int GetGameStatus();
    int GetMineCount();

    // CONSTRUCTORS //
    Board();
    Board(string& file_name);

    // DESTRUCTOR //
    ~Board();

    // VISUAL OUTPUT //
    void RenderBoard(sf::RenderWindow&, bool);

    // CONSOLE OUTPUT //
    void PrintBoard(bool debug = false) const;

};