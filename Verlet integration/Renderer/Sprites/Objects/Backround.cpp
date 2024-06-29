#include "Backround.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Backround::Backround() :
    background(sf::Vector2f(800.f, 600.f)),
    useTexture(false) {
    background.setFillColor(sf::Color(128, 128, 128));
}

Backround::Backround(float x, float y) :
    background(sf::Vector2f(x, y)),
    useTexture(false) {
    background.setFillColor(sf::Color(128, 128, 128));
}

void Backround::update(float deltaTime) {
    // Nothing Here
}

void Backround::draw(sf::RenderWindow& window) {
    if (useTexture) {
        background.setTexture(&texture);
    }
    else {
        background.setTexture(nullptr);
        background.setFillColor(sf::Color(50, 50, 50));
    }
    window.draw(background);
}
