#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <windows.h> // only for sleep()

#include "player.hpp"
#include "utils.hpp"
#include "map.hpp"
#include "game.hpp"


int main()
{
    Game game;
    std::shared_ptr<sf::RenderWindow> window = game.window;
    window->setFramerateLimit(50);

    TileMap& map = game.getMap();
    Player& theo = game.getPlayer();

    sf::Clock gameClock;
    sf::Clock clock;
    float sec = 0;

    // run the program as long as the window is open
    while (window->isOpen())
    {
        window->clear(sf::Color::Black);
        sec = clock.restart().asSeconds();
        

        window->draw(map);
        window->draw(theo.getSprite());
        game.centerViewAt(vF_to_vI(theo.getPosition()));


        eventLoop(game, theo);
        game.displayDebug();

        theo.update(sec);

        window->display();
        Sleep(10);
    }

    return 0;
}