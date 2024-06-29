#include "SpawnButton.h"
#include <iostream>
#include <SFML/Graphics.hpp>

SpawnButton::SpawnButton() :
    spawnButton(sf::Vector2f(200.f, 65.f)),
    posX(215.f),
    posY(5.f),
    spawnColor(sf::Color::White),
    spawnClicked(false) {

   spawnButton.setPosition(posX, posY);
   spawnButton.setFillColor(spawnColor);
}

void SpawnButton::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

        if (spawnButton.getGlobalBounds().contains(worldMousePos)) {
            spawnClicked = !spawnClicked;

            if (spawnClicked) {
                spawnColor = sf::Color::Red;
                std::cout << "SpawnButton enabled" << std::endl;
            }
            else {
                spawnColor = sf::Color::White;
                std::cout << "SpawnButton disabled" << std::endl;
            }

            spawnButton.setFillColor(spawnColor);
        }
    }
}

void SpawnButton::draw(sf::RenderWindow& window) {
    window.draw(spawnButton);
}

bool SpawnButton::isButtonClicked() const {
    return spawnClicked;
}

sf::FloatRect SpawnButton::getGlobalBounds() const {
    return spawnButton.getGlobalBounds();
}
