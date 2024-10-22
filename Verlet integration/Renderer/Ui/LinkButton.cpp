#include "LinkButton.h"
#include <iostream>
#include <SFML/Graphics.hpp>

LinkButton::LinkButton() :
    linkButton(sf::Vector2f(200.f, 65.f)),
    posX(425.f),
    posY(5.f),
    linkColor(sf::Color::White),
    linkClicked(false) {

    linkButton.setPosition(posX, posY);
    linkButton.setFillColor(linkColor);
}

void LinkButton::handleEvent(const sf::Event& event, const sf::RenderWindow& window, std::vector<Circle>& circles) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

        if (linkButton.getGlobalBounds().contains(worldMousePos)) {
            linkClicked = !linkClicked;

            if (linkClicked) {
                linkColor = sf::Color::Red;
                std::cout << "linkButton enabled" << std::endl;
            }
            else {
                linkColor = sf::Color::White;
                std::cout << "linkButton disabled" << std::endl;
            }

            linkButton.setFillColor(linkColor);
        }
        else {
            if (linkClicked) {
                for (auto& circle : circles) {
                    if (circle.getGlobalBounds().contains(worldMousePos)) {
                        circle.toggleSelection();
                    }
                }

                int selectedCount = 0;
                for (auto& circle : circles) {
                    if (circle.isSelected()) {
                        selectedCount++;
                    }
                }

                if (selectedCount == 2) {
                    for (auto& circle : circles) {
                        if (circle.isSelected()) {
                            circle.setColor(sf::Color::Green);
                        }
                    }
                    Circle::createSpringForceBetweenSelectedCircles(circles);

                    // Unselect the circles after linking them
                    for (auto& circle : circles) {
                        if (circle.isSelected()) {
                            circle.toggleSelection();
                        }
                    }

                    linkClicked = false;
                    linkColor = sf::Color::White;
                    linkButton.setFillColor(linkColor);
                    std::cout << "linkButton disabled after linking circles" << std::endl;
                }
            }
        }
    }
}

void LinkButton::draw(sf::RenderWindow& window) {
    window.draw(linkButton);
}

bool LinkButton::isButtonClicked() const {
    return linkClicked;
}

sf::FloatRect LinkButton::getGlobalBounds() const {
    return linkButton.getGlobalBounds();
}
