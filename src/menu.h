#pragma once
#include "board.h"
#include "TextureManager.h"
struct Menu {
    static void RenderMenu(Board*, sf::RenderWindow& window);
    unsigned int ClickedSetting(sf::Vector2i);
};