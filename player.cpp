#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "player.hpp"
#include "utils.hpp"
#include "map.hpp"


const int Player::max_speed_y = 2;

Player::Player() {
    name = "Theodore";

    sSheet = SpriteSheet(0.f, 0.f, 16.f, 32.f);

    // how fast keys move player in x-dir
    speed = sf::Vector2f(1.5, 0);
    // increase to make player fall faster
    gravity = 1.1;

    if (!loadTexture()) {
        return;
    }

    w = sSheet.getW();
    h = sSheet.getH();

    sf::Vector2f scale = sprite.getScale();
    if (scale != sf::Vector2f(1.f, 1.f)) {
        w *= scale.x;
        h *= scale.y;
    }

    sf::Vector2f dc = defaultCoords(w, h);
    setPosition(dc.x, dc.y);
    lastValidPosition = sf::Vector2f(dc.x, dc.y);

    // This outlines the hitbox points on Player
    // 
    // 0       1
    //     0
    //  /--|--\
    //  |  |  |
    // 2   |   3
    //    / \  
    //   /   \
    // _/     \_
    // 4       5
    
    // trying composition rather than inheritance
    hitbox = HitBox(xPos, yPos, w, h);
    input = "";
}

Player::~Player() {}

// 0
int Player::getPos0Block(float leeway)
{
    sf::Vector2f pos = sf::Vector2f(xPos, yPos + leeway);
    return TileMap::getBlockAtPosition(pos);
}

// 1
int Player::getPos1Block(float leeway)
{
    sf::Vector2f pos = sf::Vector2f(xPos + w, yPos + leeway);
    return TileMap::getBlockAtPosition(pos);
}

// 2
int Player::getPos2Block()
{
    sf::Vector2f pos = sf::Vector2f(xPos, yPos + h / 2);
    return TileMap::getBlockAtPosition(pos);
}

// 3
int Player::getPos3Block()
{
    sf::Vector2f pos = sf::Vector2f(xPos + w, yPos + h / 2);
    return TileMap::getBlockAtPosition(pos);
}

// 4
int Player::getPos4Block(float leeway)
{
    sf::Vector2f pos = sf::Vector2f(xPos, yPos + h + leeway);
    return TileMap::getBlockAtPosition(pos);
}

// 5
int Player::getPos5Block(float leeway)
{
    sf::Vector2f pos = sf::Vector2f(xPos + w, yPos + h + leeway);
    return TileMap::getBlockAtPosition(pos);
}


void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    xPos = x;
    yPos = y;
}

void Player::setPosition(sf::Vector2f v2f)
{
    setPosition(v2f.x, v2f.y);
}

float Player::getX() {
    return sprite.getPosition().x;
}

float Player::getY() {
    return sprite.getPosition().y;
}

sf::Vector2f Player::getSpeed() {
    return speed;
}

float Player::getSpeedX() {
    return speed.x;
}

float Player::getSpeedY() {
    return speed.y;
}

sf::Vector2f Player::getPosition() {
    return sprite.getPosition();
}

sf::Sprite Player::getSprite() {
    return sprite;
}

bool Player::validPosition()
{
    float leeway = 0.5;
    if (   getPos0Block(leeway) >= TileMap::blocks::sky1
        && getPos1Block(leeway) >= TileMap::blocks::sky1
        && getPos2Block() >= TileMap::blocks::sky1
        && getPos3Block() >= TileMap::blocks::sky1
        && getPos4Block() >= TileMap::blocks::sky1
        && getPos5Block() >= TileMap::blocks::sky1
        )
    {
        return true;
    }
    return false;
}

void Player::move(float x, float y)
{
    sprite.move(x, y);
    xPos = sprite.getPosition().x;
    yPos = sprite.getPosition().y;

    int hOffset = 0;
    int wOffset = 0;
    if (getX() > WINDOW_W - w + wOffset || getX() < 0 - wOffset || getY() < 0 - hOffset || getY() > WINDOW_H - h + hOffset) {
        move(-x, -y);
    }

    if (validPosition())
    {
        lastValidPosition = getPosition();
    }
    else
    {
        setPosition(lastValidPosition);
    }
}

bool Player::feetInSky(float leeway)
{
    if (getPos4Block(leeway) >= TileMap::blocks::sky1
        && getPos5Block(leeway) >= TileMap::blocks::sky1)
    {
        return true;
    }
    return false;
}

void Player::jump()
{
    // if on ground, we can jump
    // we need some leeway though because if we go into onto or
    // into a tile that is not sky, we will not be able to jump
    float leeway = 0.5f;
    if (!feetInSky(leeway))
    {
        speed.y = -max_speed_y * 1.5;
    }
}


bool Player::loadTexture() {
    // load the texture file
    if (!texture.loadFromFile(textureFile)) {
        std::cout << "Error reading texture from " << textureFile << "\n\n";
        return false;
    }
    sprite.setTexture(texture);
    texture.setSmooth(true);
    sprite.setTextureRect(sSheet.intRectY);
    return true;
}

void Player::keyboardInput()
{
    input = "";
    // movement from user
    // up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        move(0, -getSpeedY() * 1.5);
        input += "W ";
    }
    // left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        setSpriteLeft();
        move(-getSpeedX(), 0);
        input += "A ";
    }
    // down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        // power downwards
        //move(0, getSpeedY() * 1.5);
        move(0, 0);
        input += "S ";
    }
    // right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        setSpriteRight();
        move(getSpeedX(), 0);
        input += "D ";
    }
    // jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        input += "[SPACE] ";
        jump();
    }
}

float Player::getGravityAcceleration(float sec)
{
    float gravity_accel = (5 * gravity * sec);
    return gravity_accel;
}

void Player::collisionDetection(float sec)
{
    float gravity_accel = getGravityAcceleration(sec);

    // movement from game mechanics
    // fall down
    if (feetInSky())
    {
        move(0.f, gravity_accel);
    }
}

void Player::momentumHandler(float sec)
{
    float gravity_accel = getGravityAcceleration(sec);

    // momentum
    if (feetInSky())
    {
        speed.y += gravity_accel;
        move(0, speed.y);
    }

    if (speed.y > max_speed_y)
    {
        speed.y = max_speed_y;
    }
    if (speed.y < -max_speed_y)
    {
        speed.y = -max_speed_y;
    }
}

void Player::update(float sec)
{
    collisionDetection(sec);
    keyboardInput();
    momentumHandler(sec);
    
}


void Player::setSpriteLeft()
{
    if (!sSheet.yReflected) {
        sprite.setTextureRect(sSheet.intRectYReflected);
        sSheet.yReflected = true;
    }
}

void Player::setSpriteRight()
{
    if (sSheet.yReflected) {
        sprite.setTextureRect(sSheet.intRectY);
        sSheet.yReflected = false;
    }
}
