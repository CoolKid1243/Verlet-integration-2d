#include "Circle.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Circle::Circle(float x, float y, bool immobleState) :
    circle(15.f),
    physics(x, y, 15.f),
    immoble(immobleState),
    immoblePosX(x),
    immoblePosY(y),
    useTexture(false),
    selected(false) {

    if (useTexture) {
        std::string imagePath = "D:/All Game Stuff And Softwhere/VS Games/Verlet integration 2d/Verlet integration/Renderer/Sprites/Textures/AwesomeFace.png";

        if (!texture.loadFromFile(imagePath)) {
            std::cerr << "Error loading png" << std::endl;
            useTexture = false;
        }
    }

    circle.setPosition(physics.getPosition());
    if (immoble) {
        circleColor = sf::Color::Yellow;
    }
    else {
        circleColor = sf::Color::White;
    }
    circle.setFillColor(circleColor);
}

void Circle::update(float deltaTime, bool paused, std::vector<Circle>& circles) {
    if (!immoble && !paused) {
        physics.applyGravity(0.3f, deltaTime);
        physics.applyFriction(0.7f);
        physics.update(deltaTime, getPhysicsPointers(circles));
    }

    circle.setPosition(physics.getPosition() - sf::Vector2f(circle.getRadius(), circle.getRadius()));

    if (immoble) {
        sf::Vector2f immobilePosition(immoblePosX, immoblePosY);
        physics.setPosition(immobilePosition);
        circle.setPosition(immobilePosition - sf::Vector2f(circle.getRadius(), circle.getRadius()));
    }
}

void Circle::draw(sf::RenderWindow& window) {
    if (useTexture) {
        circle.setTexture(&texture);
    }
    else {
        circle.setTexture(nullptr);
    }
    window.draw(circle);
}

void Circle::setImmoble(bool immoble) {
    this->immoble = immoble;
    if (immoble) {
        circleColor = sf::Color::Yellow;
    }
    else {
        circleColor = sf::Color::White;
    }
    circle.setFillColor(circleColor);
}

void Circle::toggleSelection() {
    selected = !selected;
}

bool Circle::isSelected() const {
    return selected;
}

void Circle::setColor(const sf::Color& color) {
    circleColor = color;
    circle.setFillColor(circleColor);
}

sf::FloatRect Circle::getGlobalBounds() const {
    return circle.getGlobalBounds();
}

std::vector<VerletPhysics*> Circle::getPhysicsPointers(std::vector<Circle>& circles) {
    std::vector<VerletPhysics*> physicsPointers;
    for (auto& circle : circles) {
        physicsPointers.push_back(&circle.physics);
    }
    return physicsPointers;
}
