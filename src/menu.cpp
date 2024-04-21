#include "menu.h"


void Menu::RenderMenu(Board* board, sf::RenderWindow& window) {
    if (board->GetGameStatus() == 0) {
        sf::Sprite reset_button(TextureManager::GetTexture("face_happy"));
        reset_button.setPosition(board->GetWindowWidth() / 2 - 30, board->GetWindowHeight() - 100);
        window.draw(reset_button);
    } else if (board->GetGameStatus() == 1) {
        sf::Sprite reset_button(TextureManager::GetTexture("face_lose"));
        reset_button.setPosition(board->GetWindowWidth() / 2 - 30, board->GetWindowHeight() - 100);
        window.draw(reset_button);
    } else if (board->GetGameStatus() == 2) {
        sf::Sprite reset_button(TextureManager::GetTexture("face_win"));
        reset_button.setPosition(board->GetWindowWidth() / 2 - 30, board->GetWindowHeight() - 100);
        window.draw(reset_button);
    }

    sf::Sprite debug_button(TextureManager::GetTexture("debug"));
    debug_button.setPosition(board->GetWindowWidth() - 256, board->GetWindowHeight() - 100);
    window.draw(debug_button);

    sf::Sprite test_1_button(TextureManager::GetTexture("test_1"));
    test_1_button.setPosition(board->GetWindowWidth() - 192, board->GetWindowHeight() - 100);
    window.draw(test_1_button);

    sf::Sprite test_2_button(TextureManager::GetTexture("test_2"));
    test_2_button.setPosition(board->GetWindowWidth() - 128, board->GetWindowHeight() - 100);
    window.draw(test_2_button);

    sf::Sprite test_3_button(TextureManager::GetTexture("test_3"));
    test_3_button.setPosition(board->GetWindowWidth() - 64, board->GetWindowHeight() - 100);
    window.draw(test_3_button);

    sf::Sprite first_digit(TextureManager::GetTexture("digits"));
    sf::Sprite second_digit(TextureManager::GetTexture("digits"));
    sf::Sprite third_digit(TextureManager::GetTexture("digits"));

    if (board->GetMineCount() >= 0) {
        unsigned int x_offset = (board->GetMineCount() / 100) * 21;
        first_digit.setTextureRect(sf::IntRect(x_offset, 0, 21, 32));

        x_offset = (board->GetMineCount() / 10) * 21;
        second_digit.setTextureRect(sf::IntRect(x_offset, 0, 21, 32));

        x_offset = (board->GetMineCount() % 10) * 21;
        third_digit.setTextureRect(sf::IntRect(x_offset, 0, 21, 32));
    }
    else if (board->GetMineCount() < 0) {
        if (abs(board->GetMineCount()) < 10) {
            first_digit.setTextureRect(sf::IntRect(-21, 0, 21, 32));
            second_digit.setTextureRect(sf::IntRect(210, 0, 21, 32 ));
            unsigned int x_offset = abs(board->GetMineCount()) * 21;
            third_digit.setTextureRect(sf::IntRect(x_offset, 0, 21, 32));
        }
        else if (abs(board->GetMineCount()) >= 10) {
            first_digit.setTextureRect(sf::IntRect(210, 0, 21, 32));
            unsigned int x_offset = (abs(board->GetMineCount()) / 10) * 21;
            second_digit.setTextureRect(sf::IntRect(x_offset, 0, 21, 32));
            x_offset = (abs(board->GetMineCount()) % 10) * 21;
            third_digit.setTextureRect(sf::IntRect(x_offset, 0, 21, 32));
        }
    }
    first_digit.setPosition(64, board->GetWindowHeight() - 100);
    window.draw(first_digit);

    second_digit.setPosition(85, board->GetWindowHeight() - 100);
    window.draw(second_digit);

    third_digit.setPosition(106, board->GetWindowHeight() - 100);
    window.draw(third_digit);
}

unsigned int ClickedSetting(sf::Vector2i mouse_click_position) {
    return 0;
}