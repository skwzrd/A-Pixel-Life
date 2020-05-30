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

    Game() {
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

    void centerViewAt(sf::Vector2f v2f) {
        view->setCenter(v2f);
        window->setView(*view);
    }

    void displayDebug() {
        if (bdisplayDebug)
        {
            std::string data = "";
            data.append("Debug info:\n");
            if (playerSet)
            {
                data.append("xPos: " + std::to_string((int)player.xPos) + " yPos: " + std::to_string((int)player.yPos) + "\n");
            }
            debugText.setString(data);
            sf::Vector2f textPos = getTopRightFromCenter(view->getCenter(), view->getSize());
            debugText.setPosition(textPos);
            window->draw(debugText);
            
            bdisplayDebug = true;
        }
    }


    Player& getPlayer(){
        playerSet = true;
        return player;
    }

    TileMap& getMap() {
        // load up graphics
        if (!map.load()) {
            std::cout << "Failed to load map!" << std::endl;
        }
        return map;
    }
};
