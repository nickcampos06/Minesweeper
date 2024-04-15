#include "board.h"

// == BOARD CLASS == //

// CONSTRUCTORS //
Board::Board() {
    GrabConfigData();

    GenerateTiles();
    GenerateMines();

    SetAdjacentTiles();
    CountAdjacentMines();
}
Board::Board(string& file_name) {
    GenerateTiles();

    LoadTiles(file_name);

    SetAdjacentTiles();
}

// CONSTRUCTOR HELPERS //
void Board::GrabConfigData() {
    fstream config_file("../../boards/config.cfg");

    string width;
    getline(config_file, width);
    _width = stoi(width);

    string height;
    getline(config_file, height);
    _height = stoi(height);

    string mine_count;
    getline(config_file, mine_count);
    _mine_count = stoi(mine_count);
}
void Board::GenerateTiles() {
    for (unsigned int row = 0; row < _height; ++row) {
        vector<Tile> vector_row;
        _board.push_back(vector_row);
        for (unsigned int column = 0; column < _width; ++column) {
            _board[row].push_back(Tile());
        }
    }
}
void Board::GenerateMines() {

}

void Board::LoadTiles(string& file_name) {

}

void Board::SetAdjacentTiles() {

}
void Board::CountAdjacentMines() {

}

// CONSOLE OUTPUT //
void Board::PrintBoard() {
    for (unsigned int row = 0; row < _board.size(); ++row) {
        for (unsigned int column = 0; column < _board[row].size(); ++column) {
            _board[row][column].PrintTile();
            cout << " ";
        }
        cout << endl;
    }
}

// == TILE CLASS == //

// CONSTRUCTORS //
Board::Tile::Tile() {
    _is_mine = false;
    _adjacent_mine_count = 0;
    _tile_status = 'c';

}

// ACTIVE GAME FUNCTIONS //
void Board::Tile::RevealTile(bool is_spreading) {

}

// CONSOLE OUTPUT //
void Board::Tile::PrintTile() {
    cout << _tile_status;
}