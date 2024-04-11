#include <vector>
using namespace std;

struct Tile {
    // == VARIABLES == //
    bool _is_mine; // true or false
    unsigned char _adjacent_mine_count; // number 1 - 8
    unsigned char _mine_status; // r = revealed ; c = covered ; f = flagged ; d = detonated ; B = bomb DEBUG ONLY
    vector<Tile*> _adjacent_mines; // [0] = up ; [1] = right ; [2] = down ; [3] = left

    // == FUNCTIONS == //
    // ACTIVE GAME FUNCTIONS
    void RevealTile();
    void ToggleTileFlag();
    // CONSTRUCTORS
    Tile(bool is_mine);

};