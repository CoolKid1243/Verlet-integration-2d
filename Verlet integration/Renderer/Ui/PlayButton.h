#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Circle.h"

class PlayButton {
public:
    PlayButton();
    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window, std::vector<Circle>& circles);
    bool isButtonClicked() const;
    void setButtonClicked(bool clicked);
    sf::FloatRect getGlobalBounds() const;
    bool playClicked;

private:
    sf::RectangleShape playButton;
    float posX;
    float posY;
    sf::Color playColor;
};
