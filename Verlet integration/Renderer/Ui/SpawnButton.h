#pragma once
#include <SFML/Graphics.hpp>

class SpawnButton {
public:
    SpawnButton();
    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    bool isButtonClicked() const;
    void setButtonClicked(bool clicked);
    sf::FloatRect getGlobalBounds() const;

private:
    sf::RectangleShape spawnButton;
    float posX;
    float posY;
    sf::Color spawnColor;
    bool spawnClicked;
};
