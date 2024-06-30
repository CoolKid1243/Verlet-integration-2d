#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Circle.h"

class LinkButton {
public:
    LinkButton();
    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window, std::vector<Circle>& circles);
    bool isButtonClicked() const;
    sf::FloatRect getGlobalBounds() const;

private:
    sf::RectangleShape linkButton;
    float posX;
    float posY;
    sf::Color linkColor;
    bool linkClicked;
};