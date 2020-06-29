#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "utils.hpp"
#include "hitbox.hpp"

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
    //HitBox hitbox;

    sf::Vector2f speed;
    float gravity;
    float gravity_accel;

    HitBox hitbox;


public:
    std::string input;
    bool displayHitBox;

    Player();
    ~Player();

    HitBox getHitBox();

    void setPosition(float x, float y);
    void setPosition(sf::Vector2f v2f);

    sf::Vector2f getPosition();
    sf::Vector2i getPositionInt();
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
    sf::RectangleShape getHitBoxShape();
    float getGravityAcceleration(float sec);
    void collisionDetection(float sec);
    void keyboardInput();
    void momentumHandler(float sec);

};

