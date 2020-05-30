#pragma once
#include <SFML/Graphics.hpp>
#include "utils.hpp"

const unsigned int WINDOW_W = 720;
const unsigned int WINDOW_H = 720;

const std::string assetsPath = ".\\assets\\";

sf::Vector2f windowCenter() {
    float x_mid = ((float)WINDOW_W) / 2.0;
    float y_mid = ((float)WINDOW_H) / 2.0;
    return sf::Vector2f(x_mid, y_mid);
}


sf::Vector2f defaultCoords(float width, float height) {
    sf::Vector2f v;
    v.x = windowCenter().x - (width / 2);
    v.y = windowCenter().y - (height / 2);
    return v;
}

sf::Vector2f getTopRightFromCenter(sf::Vector2f center, sf::Vector2f size) {
    sf::Vector2f v;
    v.x = center.x - (size.x / 2);
    v.y = center.y - (size.y / 2);
    return v;
}

sf::Vector2f vF_to_vI(sf::Vector2f vf) {
    sf::Vector2f vI((int)vf.x, (int)vf.y);
    return vI;
}


class SpriteSheet {
public:
    float x, y, w, h;

    SpriteSheet() : x(0), y(0), w(0), h(0) {};

    SpriteSheet(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};

    void setCoords(float _x, float _y, float _w, float _h) {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }
};

