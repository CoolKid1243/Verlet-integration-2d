#include "PlayButton.h"
#include <iostream>
#include <SFML/Graphics.hpp>

PlayButton::PlayButton() :
    playButton(sf::Vector2f(200.f, 65.f)),
    posX(5.f),
    posY(5.f),
    playColor(sf::Color::White),
    playClicked(false) {

    playButton.setPosition(posX, posY);
    playButton.setFillColor(playColor);
}

void PlayButton::handleEvent(const sf::Event& event, const sf::RenderWindow& window, std::vector<Circle>& circles) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

        if (playButton.getGlobalBounds().contains(worldMousePos)) {
            // Toggle button state
            playClicked = !playClicked;

            if (playClicked) {
                playColor = sf::Color::Red;
                std::cout << "PlayButton enabled" << std::endl;
            }
            else {
                playColor = sf::Color::White;
                std::cout << "PlayButton disabled" << std::endl;
            }

            playButton.setFillColor(playColor);
        }
    }
}

void PlayButton::draw(sf::RenderWindow& window) {
    window.draw(playButton);
}

bool PlayButton::isButtonClicked() const {
    return playClicked;
}

sf::FloatRect PlayButton::getGlobalBounds() const {
    return playButton.getGlobalBounds();
}
