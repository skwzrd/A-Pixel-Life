#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

#include "utils.hpp"
#include "tilemap.hpp"


const sf::Vector2u TileMap::tileSize = sf::Vector2u(16, 16);
const int TileMap::levelWidth = (WINDOW_W / TileMap::tileSize.x);
const int TileMap::levelHeight = (WINDOW_H / TileMap::tileSize.y);
const int TileMap::levelSize = TileMap::levelWidth * TileMap::levelHeight;
std::vector<int> TileMap::level = TileMap::generateMap();

const std::map<int, std::string> TileMap::block_map = {
    {0, "grass"},
    {1, "dirt"},
    {2, "sand"},
    {3, "limestone"},
    {4, "emerald"},
    {5, "lapis"},
    {6, "ruby"},
    {7, "gold"},
    {8, "sky1"},
    {9, "sky2"},
    {10, "sky3"},
    {11, "sky4"},
    {12, "sky5"},
    {13, "corrupt"}
};

TileMap::TileMap()
{
    if (!load()) {
        std::cout << "Failed to load map!" << std::endl;
    }
}

TileMap::~TileMap() {};

int TileMap::randomSky()
{
    // 5 sky blocks, starting at 8
    return rand() % 5 + 8;
}


int TileMap::randomGround()
{
    int num = rand() % 100;
    int blockNum = blocks::corrupt;
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
    return blockNum;
}

std::vector<int> TileMap::generateMap()
{
    std::vector<int> level;
    // all the blocks that are to be sky
    //         half the map     remove left over half row    plus one for 1 index
    int sky = (levelSize / 2) + (levelWidth / 2) + 1;
    for (int i = 0; i < levelSize; i++)
    {
        int blockNum = blocks::corrupt;
        if (i < sky)
        {
            blockNum = randomSky();
        }
        else if (i >= sky && i < sky + levelWidth)
        {
            blockNum = blocks::grass;
        }
        else
        {
            blockNum = randomGround();
        }
        level.push_back(blockNum);
    }

    // I want a crater in the center of the map for collision detection testing
    // let's just hard code one for now...
    int crater[] = {
        1052, 1053, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061,
        1094, 1095, 1096, 1097, 1098, 1099, 1100, 1101, 1102, 1103, 1104,
        1137, 1138, 1139, 1140, 1141, 1142, 1143, 1144, 1145, 1146, 1147, 1148,
        1179, 1180, 1181, 1182, 1183, 1184, 1185, 1186, 1187, 1188, 1189, 1190, 1191, 1192,
        1225, 1226, 1227, 1228, 1229, 1230, 1231, 1232, 1233, 1234, 1235, 1236,
    };
    for (int i = 0; i < sizeof(crater)/sizeof(crater[0]); i++)
    {
        level[crater[i]] = randomSky();
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


bool TileMap::blockIsSky(int block) {
    if (block >= TileMap::blocks::sky1) {
        return true;
    }
    return false;
}

int TileMap::getBlockAtPosition(sf::Vector2f v)
{   
    int block_x = (int)(v.x / tileSize.x);
    int block_y = (int)(v.y / tileSize.y);
    int vertex_index = block_x + (block_y * levelWidth);

    int block = level[vertex_index];

    return block;
}

