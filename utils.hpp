#pragma once
#include <SFML/Graphics.hpp>

const unsigned int WINDOW_W = 720;
const unsigned int WINDOW_H = 720;

const std::string assetsPath = ".\\assets\\";

sf::Vector2f windowCenter();

sf::Vector2f defaultCoords(float width, float height);

sf::Vector2f getTopRightFromCenter(sf::Vector2f center, sf::Vector2f size);

sf::Vector2f vF_to_vI(sf::Vector2f vf);

class SpriteSheet {
public:
    float x, y, w, h;

    SpriteSheet();

    SpriteSheet(int _x, int _y, int _w, int _h);

    void setCoords(float _x, float _y, float _w, float _h);
};

