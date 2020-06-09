#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

#include "utils.hpp"


class TileMap : public sf::Drawable, public sf::Transformable
{
private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

public:
    static const sf::Vector2u tileSize;
    static const int levelWidth;
    static const int levelHeight;
    static const int levelSize;

    static std::vector<int> level;

    enum blocks {
        grass = 0,
        dirt = 1,
        sand = 2,
        limestone = 3,
        emerald = 4,
        lapis = 5,
        ruby = 6,
        gold = 7,
        sky1 = 8,
        sky2 = 9,
        sky3 = 10,
        sky4 = 11,
        sky5 = 12,
        corrupt = 13
    };

    TileMap();

    bool load();

    static int getBlockAtPosition(sf::Vector2f v);

    static std::vector<int> generateMap();
};
