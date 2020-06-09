#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "utils.hpp"
#include "map.hpp"


const sf::Vector2u TileMap::tileSize = sf::Vector2u(16, 16);
const int TileMap::levelWidth = (WINDOW_W / TileMap::tileSize.x);
const int TileMap::levelHeight = (WINDOW_H / TileMap::tileSize.y);
const int TileMap::levelSize = TileMap::levelWidth * TileMap::levelHeight;
std::vector<int> TileMap::level = TileMap::generateMap();

TileMap::TileMap()
{
    if (!load()) {
        std::cout << "Failed to load map!" << std::endl;
    }
}


std::vector<int> TileMap::generateMap()
{
    std::vector<int> level;
    //         half the map      plus a bit more     remove left over half row
    int sky = ((levelSize / 2) + (2 * levelWidth)) - (levelWidth / 2);
    for (int i = 0; i < levelSize; i++)
    {
        int blockNum = blocks::corrupt;
        if (i < sky)
        {
            // 5 sky blocks, starting at 8
            blockNum = rand() % 5 + 8;
        }
        else if (i >= sky && i < sky + levelWidth)
        {
            blockNum = blocks::grass;
        }
        else
        {
            int num = rand() % 100;

            // probabilities
            if (num < 40) {
                blockNum = blocks::dirt;
            }
            else if (num < 75) {
                blockNum = blocks::limestone;
            }
            else if (num < 85) {
                blockNum = blocks::sand;
            }
            else if (num < 88) {
                blockNum = blocks::emerald;
            }
            else if (num < 93) {
                blockNum = blocks::lapis;
            }
            else if (num < 96) {
                blockNum = blocks::ruby;
            }
            else {
                blockNum = blocks::gold;
            }
        }
        level.push_back(blockNum);
    }
    return level;
}


bool TileMap::load()
{
    const std::string tileSet = ".\\assets\\map.png";
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileSet))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(levelSize * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < levelWidth; ++i)
        for (unsigned int j = 0; j < levelHeight; ++j)
        {
            // get the current tile number
            int tileNumber = level[i + j * levelWidth];

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * levelWidth) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}

int TileMap::getBlockAtPosition(sf::Vector2f v)
{   
    int block_x = (int)(v.x / tileSize.x);
    int block_y = (int)(v.y / tileSize.y);
    int vertex_index = block_x + (block_y * levelWidth);

    int block = level[vertex_index];

    return block;
}

