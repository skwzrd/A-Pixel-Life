#pragma once
#include <SFML/Graphics.hpp>

#include "utils.hpp"
#include "game.hpp"
#include "tilemap.hpp"
#include "player.hpp"


Game::Game() {
    bdisplayDebug = false;
    playerSet = false;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 5;

    // create the window
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_W, WINDOW_H), "2d Pixels", sf::Style::Default, settings);
    window->setFramerateLimit(50);

    view = std::make_shared<sf::View>(sf::FloatRect(0.f, 0.f, 300.f, 300.f));
    centerViewAt(windowCenter());

    if (!debugFont.loadFromFile(assetsPath + "debugFont.ttf"))
    {
        std::cout << "Could not find the debug font file." << std::endl;
        return;
    }
    debugText.setFont(debugFont);
    debugText.setCharacterSize(10);
    debugText.setOutlineColor(sf::Color::White);
    debugText.setFillColor(sf::Color::Black);
    debugText.setOutlineThickness(1);
}

Game::~Game() {}

void Game::centerViewAt(sf::Vector2f v2f) {
    view->setCenter(v2f);
    window->setView(*view);
}

void Game::displayDebug() {
    if (bdisplayDebug)
    {
        std::string data = "";
        data.append("Debug info:\n");
        if (playerSet)
        {
            data.append("xPos: " + std::to_string(player.getX()) + " yPos: " + std::to_string(player.getY()) + "\n");
            data.append("Vx: " + std::to_string(player.getSpeedX()) + " Vy: " + std::to_string(player.getSpeedY()) + "\n");
            for (int i = 0; i < 6; i++) {
                data.append("Pos " + std::to_string(i) + ": " + player.getHitBox().getBlockNameAtPositionN(i, 0.5) + "\n");
            }
            data.append("\n\nKeys pressed: " + player.input + "\n");
        }
        debugText.setString(data);
        sf::Vector2f textPos = getTopRightFromCenter(view->getCenter(), view->getSize());
        debugText.setPosition(textPos);

        window->draw(debugText);

        bdisplayDebug = true;
    }

    if (player.displayHitBox) {
        window->draw(player.getHitBoxShape());
        player.displayHitBox = true;
    }
}


Player& Game::getPlayer() {
    playerSet = true;
    return player;
}

TileMap& Game::getMap() {
    return map;
}


void eventLoop(Game& game, Player& theo) {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (game.window->pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            game.window->close();
        }

        if (event.type == sf::Event::KeyPressed) {
            // debug info text overlay
            if (event.key.code == sf::Keyboard::R)
            {
                // show debug display
                if (!game.bdisplayDebug) {
                    std::cout << "Displaying debug" << std::endl;
                    game.bdisplayDebug = true;
                }
                // hide debug display
                else {
                    std::cout << "Hiding debug" << std::endl;
                    game.bdisplayDebug = false;
                }
            }
            if (event.key.code == sf::Keyboard::H) {
                // display player hitbox
                // show debug display
                if (!game.player.displayHitBox) {
                    std::cout << "Displaying hitbox" << std::endl;
                    game.player.displayHitBox = true;
                }
                // hide debug display
                else {
                    std::cout << "Hiding hitbox" << std::endl;
                    game.player.displayHitBox = false;
                }
            }
        }
    }
}
