#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "utils.hpp"

class Player {

private:
    std::string name;

    std::string textureFile = assetsPath + "entities.png";

    sf::Texture texture;
    sf::Sprite sprite;

    SpriteSheet sSheet;

    float xPos;
    float yPos;
    float w;
    float h;

    float speed;

public:

    Player();

    void setPosition(float x, float y);

    float getX();
    float getY();
    float getSpeed();
    sf::Sprite getSprite();

    sf::Vector2f getPosition();

    void move(float x, float y);

    bool loadTexture();

    void update();

    int getRightFootBlock();
    int getLeftFootBlock();
    int getRightHeadBlock();
    int getLeftHeadBlock();

};

