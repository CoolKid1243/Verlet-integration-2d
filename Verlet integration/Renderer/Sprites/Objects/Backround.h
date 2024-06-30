#pragma once

#include <SFML/Graphics.hpp>

class Backround {
public:
    Backround();
    Backround(float x, float y);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape background;
    sf::Texture texture;
    bool useTexture;
};