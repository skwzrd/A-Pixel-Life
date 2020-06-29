#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "hitbox.hpp"
#include "tilemap.hpp"


// This outlines the hitbox N (6) points
// assumes hitbox entities are 1 block wide and 2 blocks high for now
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


HitBox::HitBox()
{
}

HitBox::~HitBox()
{
}

HitBox::HitBox(float _xPos, float _yPos, float _w, float _h, int _points)
    : xPos(_xPos), yPos(_yPos), w(_w), h(_h), points(_points)
{
}

// given a number that corresponds to a point on an entity,
// return what kind of block is at that point's position
std::string HitBox::getBlockNameAtPositionN(int n, float margin) {

    sf::Vector2f pos = getPositionN(n);
    int block_num = TileMap::getBlockAtPosition(pos);
    std::string block_string = TileMap::block_map.at(block_num);
    return block_string;
}

int HitBox::getBlockAtPositionN(int n, float margin) {

    sf::Vector2f pos = getPositionN(n, margin);
    int block_num = TileMap::getBlockAtPosition(pos);
    return block_num;
}

sf::Vector2f HitBox::getPositionN(int n, float margin) {
    sf::Vector2f pos;

    switch (n) {
        case 0:
            pos = sf::Vector2f(xPos, yPos + margin);
            break;
        case 1:
            pos = sf::Vector2f(xPos + w, yPos + margin);
            break;
        case 2:
            pos = sf::Vector2f(xPos, yPos + h / 2);
            break;
        case 3:
            pos = sf::Vector2f(xPos + w, yPos + h / 2);
            break;
        case 4:
            pos = sf::Vector2f(xPos, yPos + h + margin);
            break;
        case 5:
            pos = sf::Vector2f(xPos + w, yPos + h + margin);
            break;
        default:
            throw;
            std::cout << "Error getting block." << std::endl;
    }
    return pos;
}


bool HitBox::validPosition()
{
    for (int i = 0; i < points; i++) {
        float margin = 0.0;
        if(i==0 || i==1)
        {
            margin = .5;
        }
        if (getBlockAtPositionN(i, margin) < TileMap::blocks::sky1) {
            return false;
        }
    }
    return true;
}

bool HitBox::feetInSky()
{
    for (int i = 4; i < points; i++) {
        int block = getBlockAtPositionN(i, 0.5);
        if (! TileMap::blockIsSky(block) ){
            return false;
        }
    }
    return true;
}

sf::RectangleShape HitBox::getShape()
{
    sf::RectangleShape box = sf::RectangleShape(sf::Vector2f(w, h));
    box.setPosition(xPos, yPos);
    return box;
}

void HitBox::update(float _xPos, float _yPos) {
    xPos = _xPos;
    yPos = _yPos;
}
