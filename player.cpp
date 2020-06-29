#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "player.hpp"
#include "utils.hpp"
#include "tilemap.hpp"
#include "hitbox.hpp"
#include "utils.hpp"

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

    input = "";
    displayHitBox = false;

    hitbox = HitBox::HitBox(xPos, yPos, w, h, 6);
}

Player::~Player() {}


HitBox Player::getHitBox() {
    return hitbox;
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

sf::Vector2i Player::getPositionInt() {
    return vF_to_vI(sprite.getPosition());
}

sf::Sprite Player::getSprite() {
    return sprite;
}


bool Player::validPosition()
{
    return hitbox.validPosition();
}

void Player::move(float x, float y)
{
    sprite.move(x, y);
    xPos = sprite.getPosition().x;
    yPos = sprite.getPosition().y;
     
    int hOffset = 0;
    hitbox.update(sprite.getPosition().x, sprite.getPosition().y);
    int wOffset = 0;
    if (getX() > WINDOW_W - w + wOffset || getX() < 0 - wOffset || getY() < 0 - hOffset || getY() > WINDOW_H - h + hOffset) {
        move(-x, -y);
    }

    if ( Player::validPosition())
    {
        lastValidPosition = getPosition();
    }
    else
    {
        setPosition(lastValidPosition);
    }
    hitbox.update(sprite.getPosition().x, sprite.getPosition().y);
}

void Player::jump()
{
    // we can jump if we're on the ground
    if (! hitbox.feetInSky())
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
    if (hitbox.feetInSky())
    {
        move(0.f, gravity_accel);
    }
}

void Player::momentumHandler(float sec)
{
    float gravity_accel = getGravityAcceleration(sec);

    // momentum
    if (hitbox.feetInSky())
    {
        speed.y += gravity_accel;
    }
    move(0, speed.y);

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

sf::RectangleShape Player::getHitBoxShape() {
    return hitbox.getShape();
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
