#include <iostream>
#include "board.h"
#include "menu.h"

int main() {
    Board ActiveBoard;
    ActiveBoard.PrintBoard();
    ActiveBoard.PrintBoard(true);

    string board_file = "../../boards/recursion_test.brd";
    Board FileBoard(board_file);
    FileBoard.PrintBoard(true);

    FileBoard.RightClickOnBoard(5, 20);
    FileBoard.LeftClickOnBoard(9, 22);
    FileBoard.LeftClickOnBoard(2, 2);
    FileBoard.PrintBoard();

}