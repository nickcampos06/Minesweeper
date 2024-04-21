#include <iostream>
#include <SFML/Graphics.hpp>
#include "board.h"
#include "menu.h"

Board* CreateNewBoard(Board*);
Board* LoadTestBoard(Board*, unsigned int);


int main() {
    string test = "../../boards/testboard1.brd";
    auto* CurrentBoard = new Board(test);
    sf::RenderWindow window(sf::VideoMode(CurrentBoard->GetWindowWidth(), CurrentBoard->GetWindowHeight()), "Minesweeper");

    bool debug = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (mousePosition.y < (CurrentBoard->GetWindowHeight() - 100)) {
                        unsigned int row = mousePosition.y / 32;
                        unsigned int col = mousePosition.x / 32;
                        CurrentBoard->LeftClickOnBoard(row, col);

                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    if (mousePosition.y < (CurrentBoard->GetWindowHeight() - 100)) {
                        unsigned int row = mousePosition.y / 32;
                        unsigned int col = mousePosition.x / 32;
                        CurrentBoard->RightClickOnBoard(row, col);
                    }
                }
            }
        }
        window.clear();
        Menu::RenderMenu(CurrentBoard, window);
        CurrentBoard->WinLossTileUpdates();
        CurrentBoard->RenderBoard(window, debug);
        window.display();

    }

    delete CurrentBoard;
    return 0;
}

Board* CreateNewBoard(Board* current_board) {
    delete current_board;
    return new Board();
}
Board* LoadTestBoard(Board* current_board, unsigned int test_number) {
    delete current_board;
    string file_name;
    if (test_number == 1) {
        file_name = "../../boards/testboard1.brd";
    }
    else if (test_number == 2) {
        file_name = "../../boards/testboard2.brd";
    }
    else if (test_number == 3) {
        file_name = "../../boards/testboard3.brd";
    }
    return new Board(file_name);
}