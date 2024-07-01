#pragma once

#include <SFML/Graphics.hpp>

class Background {
public:
    Background();
    Background(float x, float y);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape background;
    sf::Texture texture;
    bool useTexture;
};