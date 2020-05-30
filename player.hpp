#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "utils.hpp"

class Player {
public:
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

    Player() {
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

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
        xPos = x;
        yPos = y;
    }

    sf::Vector2f getPosition() {
        return sprite.getPosition();
    }

    void move(float x, float y) {
        sprite.move(x, y);
        xPos = sprite.getPosition().x;
        yPos = sprite.getPosition().y;
        
        int hOffset = 0;
        int wOffset = 0;
        if (xPos > WINDOW_W - w + wOffset|| xPos < 0 - wOffset || yPos < 0 - hOffset|| yPos > WINDOW_H - h + hOffset) {
            move(-x, -y);
        }
    }

    bool loadTexture() {
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

};

