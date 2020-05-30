#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <windows.h> // sleep()

#include "player.hpp"
#include "utils.hpp"
#include "map.hpp"
#include "game.hpp"



void inputLoop(Game& game, Player& theo) {
    // movement
    // up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        theo.move(0, -theo.speed*1.5);
    }
    // left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        theo.move(-theo.speed, 0);
    }
    // down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        theo.move(0, theo.speed*1.5);
    }
    // right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        theo.move(theo.speed, 0);
    }

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

        }
    }

}



int main()
{
    Game game;

    // create the window
    std::shared_ptr<sf::RenderWindow> window = game.window;
    window->setFramerateLimit(50);


    Player& theo = game.getPlayer();
    TileMap& map = game.getMap();

    sf::Clock clock;
    float sec = 0;

    // run the program as long as the window is open
    while (window->isOpen())
    {

        window->clear(sf::Color::Black);

        sec = clock.restart().asSeconds();
        

        window->draw(map);
        window->draw(theo.sprite);


        game.centerViewAt(vF_to_vI(theo.getPosition()));

        inputLoop(game, theo);

        eventLoop(game, theo);
        
        game.displayDebug();


        window->display();

        Sleep(10);
    }

    return 0;
}