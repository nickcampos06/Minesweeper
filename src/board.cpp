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
    GrabConfigData();

    GenerateTiles();
    LoadTiles(file_name);

    SetAdjacentTiles();
    CountAdjacentMines();
}

// DESTRUCTOR //
Board::~Board() {
    for(unsigned int row = 0; row < _board.size(); ++row) {
        for (unsigned int column = 0; column < _board[row].size(); ++column) {
            delete _board[row][column];
        }
    }
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
        vector<Tile*> vector_row;
        _board.push_back(vector_row);
        for (unsigned int column = 0; column < _width; ++column) {
            _board[row].push_back(new Tile());
        }
    }
}
void Board::GenerateMines() {
    // this loop will generate the mines within the board
    for (unsigned int i = 0; i < _mine_count; ++i) {
        unsigned int mine_row = Random::Int(0, _height - 1);
        unsigned int mine_column = Random::Int(0, _width - 1);

        // ensure we don't make a tile a mine twice
        while (_board[mine_row][mine_column]->_is_mine) {
            mine_row = Random::Int(0, _height - 1);
            mine_column = Random::Int(0, _width - 1);
        }

        _board[mine_row][mine_column]->_is_mine = true;

        vector<unsigned int> temp_coords;
        _mine_positions.push_back(temp_coords);
        _mine_positions[i].push_back(mine_row);
        _mine_positions[i].push_back(mine_column);

    }
}

void Board::LoadTiles(string& file_name) {
    fstream tile_file(file_name);
    for (unsigned int i = 0; i < _height; ++i) {
        string file_row;
        getline(tile_file, file_row);
        istringstream row_stream(file_row);

        for (unsigned int j = 0; j < _width; ++j) {
            unsigned char tile_is_bomb;
            tile_is_bomb = row_stream.get();

            if (tile_is_bomb == '1') {
                _board[i][j]->_is_mine = true;
                vector<unsigned int> temp_coords;
                temp_coords.push_back(i);
                temp_coords.push_back(j);
                _mine_positions.push_back(temp_coords);
            }
        }
    }
}
void Board::SetAdjacentTiles() {
    for(int row = 0; row < _board.size(); ++row) {
        for(int column = 0; column < _board[row].size(); ++ column) {
            for (int i = -1; i <= 1; ++i) { // seeks through adjacent tiles top to bottom
                for (int j = -1; j <= 1; ++j) { // seeks through adjacent tiles left to right


                    if (i == 0 && j == 0) {
                        continue;
                    } // make sure a tile doesn't count itself as adjacent

                    int adjacent_row = row + i; // find the adjacent tile's row
                    int adjacent_column = column + j;  // find the adjacent tile's column

                    // make sure adjacent row is within the board, otherwise set it to null
                    if (adjacent_row < 0 || adjacent_column < 0 || adjacent_row > _height - 1 || adjacent_column > _width -1) {
                        _board[row][column]->_adjacent_mines.push_back(nullptr);
                    }

                    else {
                        _board[row][column]->_adjacent_mines.push_back((_board[adjacent_row][adjacent_column]));
                    } // assuming all is well, make tile aware of adjacent tile

                }
            }
        }
    }
}

void Board::CountAdjacentMines() {
    for (unsigned int i = 0; i < _mine_positions.size(); ++i) {
        for (unsigned int j = 0; j < _board[_mine_positions[i][0]][_mine_positions[i][1]]->_adjacent_mines.size(); ++j) {
            Tile* bomb_tile = _board[_mine_positions[i][0]][_mine_positions[i][1]];
            if (bomb_tile->_adjacent_mines[j] == nullptr) {
                continue;
            }
            else {
                bomb_tile->_adjacent_mines[j]->_adjacent_mine_count += 1;
            }
        }
    }
}

// CONSOLE OUTPUT //
void Board::PrintBoard(bool debug) {
    for (unsigned int row = 0; row < _board.size(); ++row) {
        for (unsigned int column = 0; column < _board[row].size(); ++column) {
            _board[row][column]->PrintTile(debug);
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
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
void Board::Tile::PrintTile(bool debug) {
    if (debug) {
        if (_is_mine) {
            cout << "B";
        }
        else {
            cout << _adjacent_mine_count;
        }
    }
    else {
        cout << _tile_status;
    }
}