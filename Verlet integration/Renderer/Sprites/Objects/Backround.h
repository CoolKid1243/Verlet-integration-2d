#ifndef BACKROUND_H
#define BACKROUND_H

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

#endif // BACKROUND_H
