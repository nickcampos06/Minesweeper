#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "random.h"
using namespace std;

class Board {

    struct Tile {
        // == VARIABLES == //

        bool _is_mine; // true or false
        unsigned int _adjacent_mine_count; // number 1 - 8
        vector<Tile*> _adjacent_mines; // [0] = up -> moves clockwise
        unsigned char _tile_status; // r = revealed ; c = covered ; f = flagged ; d = detonated ; B = bomb DEBUG ONLY

        // == FUNCTIONS == //

        // ACTIVE GAME FUNCTIONS //
        void RevealTile(bool is_spreading = false);
        void ToggleTileFlag();

        // CONSTRUCTORS //
        Tile();

        // CONSOLE OUTPUT //
        void PrintTile(bool debug =  false);

    };

    vector<vector<unsigned int>> _mine_positions;
    vector<vector<Tile*>> _board;

    unsigned int _width;
    unsigned int _height;
    unsigned int _mine_count;

    // CONSTRUCTOR HELPERS //
    void GrabConfigData();
    void GenerateTiles(); // generates a board with desired width and height
    void GenerateMines(); // randomly generates mine positions

    void LoadTiles(string& file_name); // loads tiles from preset file into board

    void SetAdjacentTiles(); // makes every tile aware of its direct neighbors
    void CountAdjacentMines(); // makes mines alert neighboring tiles of its presence

public:
    // CONSTRUCTORS //
    Board();
    Board(string& file_name);

    // DESTRUCTOR //
    ~Board();

    // CONSOLE OUTPUT //
    void PrintBoard(bool debug = false);

};