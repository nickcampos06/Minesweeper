#include "board.h"

// == BOARD CLASS == //

// GAMEPLAY FUNCTIONS HELPERS //
void Board::RevealAllMines() {
    for (unsigned int coords = 0; coords < _mine_positions.size(); ++coords) {
        Tile* current_tile = _board[_mine_positions[coords][0]][_mine_positions[coords][1]];
        if (current_tile->IsFlagged()) {
           current_tile->ToggleTileFlag();
        }
        current_tile->ForceRevealTile();
    }
}
void Board::AutoFlagMines() {
    for (unsigned int i = 0; i < _mine_positions.size(); ++i) {
        Tile* bomb_tile = _board[_mine_positions[i][0]][_mine_positions[i][1]];
        if (!bomb_tile->IsFlagged()) {
            RightClickOnBoard(_mine_positions[i][0], _mine_positions[i][1]);
        }
    }
}


// GAMEPLAY FUNCTIONS //
void Board::LeftClickOnBoard(unsigned int row, unsigned int column) {
    _board[row][column]->RevealTile();
    if (_board[row][column]->IsDetonated()) {
        _game_status = 1;
    }
}
void Board::RightClickOnBoard(unsigned int row, unsigned int column) {
    if(_board[row][column]->ToggleTileFlag()) {
        _mine_count -= 1;
    }
    else {
        _mine_count += 1;
    }
}
void Board::CheckTilesCleared() {
    int covered_mines = 0;
    for (unsigned int i = 0; i < _board_height; i++) {
        for (unsigned int j = 0; j < _board_width; j++) {
            Tile* current_tile = _board[i][j];
            if (!current_tile->IsRevealed() && !current_tile->IsMine()) {
                covered_mines += 1;
            }
        }
    }
    if (covered_mines == 0) {
        _game_status = 2;
    }
}
void Board::WinLossTileUpdates() {
    if (_game_status == 1) {
        RevealAllMines();
    }
    else if (_game_status == 2) {
        AutoFlagMines();
    }
    else {
        CheckTilesCleared();
    }

}

// ACCESSORS //
unsigned int Board::GetWindowWidth() {
    return _window_width;
}
unsigned int Board::GetWindowHeight() {
    return _window_height;
}
unsigned int Board::GetBoardWidth() {
    return _board_width;
}
unsigned int Board::GetBoardHeight() {
    return _board_height;
}
int Board::GetMineCount() {
    return _mine_count;
}
unsigned int Board::GetGameStatus() {
    return _game_status;
}

// CONSTRUCTORS //
Board::Board() {
    GrabConfigData();

    GenerateTiles();
    GenerateMines();

    SetAdjacentTiles();
    CountAdjacentMines();

    _game_status = 0;
}
Board::Board(string& file_name) {
    GrabConfigData();

    GenerateTiles();
    LoadTiles(file_name);

    SetAdjacentTiles();
    CountAdjacentMines();

    _game_status = 0;
    _mine_count = _mine_positions.size();
}

// DESTRUCTOR //
Board::~Board() {
    for(unsigned int row = 0; row < _board_height; ++row) {
        for (unsigned int column = 0; column < _board_width; ++column) {
            delete _board[row][column];
        }
    }
}

// CONSTRUCTOR HELPERS //
void Board::GrabConfigData() {
    fstream config_file("boards/config.cfg");

    string width;
    getline(config_file, width);
    _board_width = stoi(width);
    _window_width = _board_width * 32;

    string height;
    getline(config_file, height);
    _board_height = stoi(height);
    _window_height = (_board_height * 32) + 100;

    string mine_count;
    getline(config_file, mine_count);
    _mine_count = stoi(mine_count);
}
void Board::GenerateTiles() {
    for (unsigned int row = 0; row < _board_height; ++row) {
        vector<Tile*> vector_row;
        _board.push_back(vector_row);
        for (unsigned int column = 0; column < _board_width; ++column) {
            _board[row].push_back(new Tile());
        }
    }
}
void Board::GenerateMines() {
    // this loop will generate the mines within the board
    for (unsigned int i = 0; i < _mine_count; ++i) {
        unsigned int mine_row = Random::Int(0, _board_height - 1);
        unsigned int mine_column = Random::Int(0, _board_width - 1);

        // ensure we don't make a tile a mine twice
        while (_board[mine_row][mine_column]->IsMine()) {
            mine_row = Random::Int(0, _board_height - 1);
            mine_column = Random::Int(0, _board_width - 1);
        }

        _board[mine_row][mine_column]->MakeTileMine();

        vector<unsigned int> temp_coords;
        _mine_positions.push_back(temp_coords);
        _mine_positions[i].push_back(mine_row);
        _mine_positions[i].push_back(mine_column);

    }
}
void Board::LoadTiles(string& file_name) {
    fstream tile_file(file_name);
    for (unsigned int i = 0; i < _board_height; ++i) {
        string file_row;
        getline(tile_file, file_row);
        istringstream row_stream(file_row);

        for (unsigned int j = 0; j < _board_width; ++j) {
            unsigned char tile_is_bomb;
            tile_is_bomb = row_stream.get();

            if (tile_is_bomb == '1') {
                _board[i][j]->MakeTileMine();
                vector<unsigned int> temp_coords;
                temp_coords.push_back(i);
                temp_coords.push_back(j);
                _mine_positions.push_back(temp_coords);
            }
        }
    }
}
void Board::SetAdjacentTiles() {
    for(int row = 0; row < _board_height; ++row) {
        for(int column = 0; column < _board_width; ++ column) {
            for (int i = -1; i <= 1; ++i) { // seeks through adjacent tiles top to bottom
                for (int j = -1; j <= 1; ++j) { // seeks through adjacent tiles left to right


                    if (i == 0 && j == 0) {
                        continue;
                    } // make sure a tile doesn't count itself as adjacent

                    int adjacent_row = row + i; // find the adjacent tile's row
                    int adjacent_column = column + j;  // find the adjacent tile's column

                    // make sure adjacent row is within the board, otherwise set it to null
                    if (adjacent_row < 0 || adjacent_column < 0 || adjacent_row > _board_height - 1 || adjacent_column > _board_width - 1) {
                        _board[row][column]->AddAdjacentMine(nullptr);
                    }

                    else {
                        _board[row][column]->AddAdjacentMine((_board[adjacent_row][adjacent_column]));
                    } // assuming all is well, make tile aware of adjacent tile

                }
            }
        }
    }
}
void Board::CountAdjacentMines() {
    for (unsigned int i = 0; i < _mine_positions.size(); ++i) {
        for (unsigned int j = 0; j < 8; ++j) {
            Tile *bomb_tile = _board[_mine_positions[i][0]][_mine_positions[i][1]];
            if (bomb_tile->AccessAdjacentMine(j) == nullptr) {
                continue;
            }
            else {
                bomb_tile->AccessAdjacentMine(j)->IncrementAdjacentMineCount();
            }
        }
    }
}

// VISUAL OUTPUT //
void Board::RenderBoard(sf::RenderWindow& window, bool debug) {
    for (unsigned int row = 0; row < _board_height; ++row) {
        for (unsigned int column = 0; column < _board_width; ++column) {
            _board[row][column]->RenderTile(window, row, column, debug);
        }
    }
}


// == TILE CLASS == //

// CONSTRUCTORS //
Board::Tile::Tile() {
    _is_mine = false;
    _is_flagged = false;
    _is_revealed = false;
    _adjacent_mine_count = 0;
}

// ACCESSORS //
bool Board::Tile::IsMine() const{
    return _is_mine;
}
bool Board::Tile::IsDetonated() const {
    if (_is_mine && _is_revealed) {
        return true;
    }
    else {
        return false;
    }
}
bool Board::Tile::IsRevealed() const {
    return _is_revealed;
}
bool Board::Tile::IsFlagged() const {
    return _is_flagged;
}
Board::Tile* Board::Tile::AccessAdjacentMine(unsigned int index) {
    return _adjacent_mines[index];
}

// MODIFIERS //
void Board::Tile::MakeTileMine() {
    _is_mine = true;
}
void Board::Tile::AddAdjacentMine(Board::Tile* tile_pointer) {
    _adjacent_mines.push_back(tile_pointer);
}
void Board::Tile::IncrementAdjacentMineCount() {
    _adjacent_mine_count += 1;
}

// GAMEPLAY FUNCTIONS //
void Board::Tile::RevealTile() {
    if (!_is_flagged && !_is_revealed) {
        if (_adjacent_mine_count > 0) {
            _is_revealed = true;
        }
        else {
            _is_revealed = true;
            for (unsigned int i = 0; i < _adjacent_mines.size(); ++i) {
                if (_adjacent_mines[i] == nullptr) {
                    continue;
                }
                _adjacent_mines[i]->RevealTile();
            }
        }
    }
}
void Board::Tile::ForceRevealTile() {
    _is_revealed = true;
}
bool Board::Tile::ToggleTileFlag() {
    if (_is_flagged) {
      _is_flagged = false;
      return false;
    }
    else {
        _is_flagged = true;
        return true;
    }
}

// VISUAL OUTPUT //
void Board::Tile::RenderTile(sf::RenderWindow &window, unsigned int row, unsigned int col, bool debug) {
    if (_is_revealed) {
        sf::Sprite tile_appearance(TextureManager::GetTexture("tile_revealed"));
        tile_appearance.setPosition(col * 32, row * 32);
        window.draw(tile_appearance);
        if (_is_mine) {
            sf::Sprite tile_addon(TextureManager::GetTexture("mine"));
            tile_addon.setPosition(col * 32, row * 32);
            window.draw(tile_addon);
        }
        else if (_adjacent_mine_count > 0) {
            string file_name = "number_" + to_string(_adjacent_mine_count);
            sf::Sprite tile_addon(TextureManager::GetTexture(file_name));
            tile_addon.setPosition(col * 32, row * 32);
            window.draw(tile_addon);
        }
    }
    else {
        sf::Sprite tile_appearance(TextureManager::GetTexture("tile_hidden"));
        tile_appearance.setPosition(col * 32, row * 32);
        window.draw(tile_appearance);
        if (_is_flagged) {
            sf::Sprite tile_addon(TextureManager::GetTexture("flag"));
            tile_addon.setPosition(col * 32, row * 32);
            window.draw(tile_addon);
        }
        if (debug && _is_mine) {
            sf::Sprite tile_addon(TextureManager::GetTexture("mine"));
            tile_addon.setPosition(col * 32, row * 32);
            window.draw(tile_addon);
        }
    }
}