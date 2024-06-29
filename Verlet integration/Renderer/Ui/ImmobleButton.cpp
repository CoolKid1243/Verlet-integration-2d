#include "ImmobleButton.h"
#include <iostream>
#include <SFML/Graphics.hpp>

ImmobleButton::ImmobleButton() :
    immobleButton(sf::Vector2f(100.f, 45.f)),
    posX(265.f),
    posY(85.f),
    immobleColor(sf::Color::White),
    immobleClicked(false) {

    immobleButton.setPosition(posX, posY);
    immobleButton.setFillColor(immobleColor);
}

void ImmobleButton::handleEvent(const sf::Event& event, const sf::RenderWindow& window, std::vector<Circle>& circles) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

        if (immobleButton.getGlobalBounds().contains(worldMousePos)) {
            // Toggle button state
            immobleClicked = !immobleClicked;

            if (immobleClicked) {
                immobleColor = sf::Color::Red;
                std::cout << "ImmobleButton enabled" << std::endl;
            }
            else {
                immobleColor = sf::Color::White;
                std::cout << "ImmobleButton disabled" << std::endl;
            }

            immobleButton.setFillColor(immobleColor);
        }
    }
}

void ImmobleButton::draw(sf::RenderWindow& window) {
    window.draw(immobleButton);
}

bool ImmobleButton::isButtonClicked() const {
    return immobleClicked;
}

sf::FloatRect ImmobleButton::getGlobalBounds() const {
    return immobleButton.getGlobalBounds();
}
