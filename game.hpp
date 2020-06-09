#pragma once
#include <SFML/Graphics.hpp>

#include "utils.hpp"
#include "player.hpp"
#include "map.hpp"


class Game {
public:
    bool bdisplayDebug; // sf::Text bool to display player coords, speed, cursor on <type> block, etc.

    std::shared_ptr<sf::RenderWindow> window = nullptr;
    std::shared_ptr<sf::View> view = nullptr;

    sf::Font debugFont;
    sf::Text debugText;

    Player player;
    TileMap map;

    bool playerSet;

    Game();

    void centerViewAt(sf::Vector2f v2f);
    void displayDebug();

    Player& getPlayer();

    TileMap& getMap();
};


void inputLoop(Player& theo);
void eventLoop(Game& game, Player& theo);
