#include <iostream>
#include "board.h"
#include "menu.h"

int main() {
    Board ActiveBoard;
    ActiveBoard.PrintBoard();
    ActiveBoard.PrintBoard(true);

    string board_file = "../../boards/testboard2.brd";
    Board FileBoard(board_file);
    FileBoard.PrintBoard();
    FileBoard.PrintBoard(true);


}

// [1][0] [1][1] [0][1] [-1][1] [-1][0] [-1][-1] [0][-1] [1][-1]
// [1][1] TR [1][0] T [1][-1] TL [0][1] MR [0][-1] ML [-1][1] BR [-1][0] B [-1][-1] BL