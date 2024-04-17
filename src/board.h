#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "random.h"
using namespace std;

class Board {

    class Tile {
        bool _is_mine; // true or false
        bool _is_revealed;
        bool _is_flagged;
        unsigned int _adjacent_mine_count; // number 1 - 8
        vector<Tile*> _adjacent_mines; // [0] = up -> moves clockwise
    public:
        // CONSTRUCTORS //
        Tile();

        // ACCESSORS //
        bool IsMine() const;
        Tile* AccessAdjacentMine(unsigned int);

        // MODIFIERS //
        void MakeTileMine();
        void AddAdjacentMine(Tile*);
        void IncrementAdjacentMineCount();

        // GAMEPLAY FUNCTIONS //
        void RevealTile();
        void ToggleTileFlag();

        // CONSOLE OUTPUT //
        void PrintTile(bool debug =  false) const;

    };

    vector<vector<unsigned int>> _mine_positions;
    vector<vector<Tile*>> _board;

    unsigned int _width;
    unsigned int _height;
    unsigned int _mine_count;

    // CONSTRUCTOR HELPERS //
    void GrabConfigData(); // loads config data such as width and height
    void GenerateTiles(); // generates a board with desired width and height
    void GenerateMines(); // randomly generates mine positions
    void LoadTiles(string& file_name); // loads tiles from preset file into board
    void SetAdjacentTiles(); // makes every tile aware of its direct neighbors
    void CountAdjacentMines(); // makes mines alert neighboring tiles of its presence

public:
    // GAMEPLAY FUNCTIONS //
    void LeftClickOnBoard(unsigned int, unsigned int);
    void RightClickOnBoard(unsigned int, unsigned int);

    // CONSTRUCTORS //
    Board();
    Board(string& file_name);

    // DESTRUCTOR //
    ~Board();

    // CONSOLE OUTPUT //
    void PrintBoard(bool debug = false) const;

};