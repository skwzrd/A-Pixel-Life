#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "utils.hpp"

class Player {

private:

    static const int max_speed_y;

    std::string name;

    std::string textureFile = assetsPath + "entities.png";

    sf::Texture texture;
    sf::Sprite sprite;

    SpriteSheet sSheet;

    float xPos;
    float yPos;
    float w;
    float h;

    sf::Vector2f lastValidPosition;
    HitBox hitbox;

    sf::Vector2f speed;
    float gravity;
    float gravity_accel;


public:
    std::string input;

    Player();
    ~Player();

    void setPosition(float x, float y);
    void setPosition(sf::Vector2f v2f);

    sf::Vector2f getPosition();
    float getX();
    float getY();

    bool validPosition();

    sf::Vector2f getSpeed();
    float getSpeedX();
    float getSpeedY();

    sf::Sprite getSprite();
    void setSpriteLeft();
    void setSpriteRight();
    bool loadTexture();


    void move(float x, float y);
    void jump();

    void update(float sec);
    float getGravityAcceleration(float sec);
    void collisionDetection(float sec);
    void keyboardInput();
    void momentumHandler(float sec);

    int getPos0Block(float leeway = 0);
    int getPos1Block(float leeway = 0);
    int getPos2Block();
    int getPos3Block();
    int getPos4Block(float leeway = 0);
    int getPos5Block(float leeway = 0);

    bool feetInSky(float leeway = 0);

};

