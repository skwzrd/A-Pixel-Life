#pragma once
#include <SFML/Graphics.hpp>

const unsigned int WINDOW_W = 720;
const unsigned int WINDOW_H = 720;

const std::string assetsPath = ".\\assets\\";

sf::Vector2f windowCenter();

sf::Vector2f defaultCoords(float width, float height);

sf::Vector2f getTopRightFromCenter(sf::Vector2f center, sf::Vector2f size);

sf::Vector2i vF_to_vI(sf::Vector2f vf);

class SpriteSheet {
private:
    float x, y, w, h;
public:
    sf::IntRect intRectY;
    sf::IntRect intRectYReflected;

    bool yReflected = false;

    SpriteSheet();

    SpriteSheet(int _x, int _y, int _w, int _h);

    void setCoords(float _x, float _y, float _w, float _h);

    void updateIntRectYReflected();
    void updateIntRectY();

    float getX();
    float getY();
    float getW();
    float getH();
};

