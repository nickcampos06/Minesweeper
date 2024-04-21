#pragma once
#include "board.h"
#include "TextureManager.h"
struct Menu {
    static void RenderMenu(Board*, sf::RenderWindow& window);
    static unsigned int ClickedSetting(Board*, sf::Vector2i);
};