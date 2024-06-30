#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Circle.h"

class ImmobleButton {
public:
    ImmobleButton();
    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window, std::vector<Circle>& circles);
    bool isButtonClicked() const;
    sf::FloatRect getGlobalBounds() const;

private:
    sf::RectangleShape immobleButton;
    float posX;
    float posY;
    sf::Color immobleColor;
    bool immobleClicked;
};
