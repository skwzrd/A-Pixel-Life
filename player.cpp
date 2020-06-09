#include <SFML/Graphics.hpp>
#include <iostream>

#include "player.hpp"
#include "utils.hpp"
#include "map.hpp"

Player::Player() {
    name = "Theodore";

    sSheet.setCoords(0.f, 0.f, 16.f, 32.f);

    speed = 1.5;

    if (!loadTexture()) {
        return;
    }

    w = sSheet.w;
    h = sSheet.h;

    sf::Vector2f scale = sprite.getScale();
    if (scale != sf::Vector2f(1.f, 1.f)) {
        w *= scale.x;
        h *= scale.y;
    }

    sf::Vector2f dc = defaultCoords(w, h);
    setPosition(dc.x, dc.y);
}

int Player::getRightFootBlock()
{
    sf::Vector2f pos = this->getPosition();
    pos.x += w;
    pos.y += h;
    return TileMap::getBlockAtPosition(pos);
}

int Player::getLeftFootBlock()
{
    sf::Vector2f pos = this->getPosition();
    pos.y += h;
    return TileMap::getBlockAtPosition(pos);
}

int Player::getRightHeadBlock()
{
    sf::Vector2f pos = this->getPosition();
    pos.x += w;
    return TileMap::getBlockAtPosition(pos);
}

int Player::getLeftHeadBlock()
{
    sf::Vector2f pos = this->getPosition();
    return TileMap::getBlockAtPosition(pos);
}

void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    xPos = x;
    yPos = y;
}

float Player::getX() {
    return sprite.getPosition().x;
}

float Player::getY() {
    return sprite.getPosition().y;
}

float Player::getSpeed() {
    return speed;
}

sf::Vector2f Player::getPosition() {
    return sprite.getPosition();
}

sf::Sprite Player::getSprite() {
    return sprite;
}


void Player::move(float x, float y) {
    sprite.move(x, y);

    int hOffset = 0;
    int wOffset = 0;
    if (getX() > WINDOW_W - w + wOffset || getX() < 0 - wOffset || getY() < 0 - hOffset || getY() > WINDOW_H - h + hOffset) {
        move(-x, -y);
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
    sf::IntRect r(sSheet.x, sSheet.y, sSheet.w, sSheet.h);
    sprite.setTextureRect(r);
    return true;
}



void Player::update() {
    // if player is in the air
    // fall down until something is hit
}
