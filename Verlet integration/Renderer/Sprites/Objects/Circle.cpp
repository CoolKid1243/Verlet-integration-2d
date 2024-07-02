#include "Circle.h"
#include <iostream>
#include <SFML/Graphics.hpp>

std::vector<Circle*> Circle::selectedCircles;

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
    if (selected) {
        selectedCircles.push_back(this);
    }
    else {
        selectedCircles.erase(std::remove(selectedCircles.begin(), selectedCircles.end(), this), selectedCircles.end());
    }
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

std::vector<Circle*> Circle::getSelectedCircles() {
    return selectedCircles;
}

void Circle::createSpringForceBetweenSelectedCircles(std::vector<Circle>& circles) {
    if (selectedCircles.size() == 2) {
        // Get the selected circles
        Circle* circle1 = selectedCircles[0];
        Circle* circle2 = selectedCircles[1];

        // Set up spring force between the two selected circles
        float restLength = std::sqrt(std::pow(circle2->physics.getPosition().x - circle1->physics.getPosition().x, 2) +
            std::pow(circle2->physics.getPosition().y - circle1->physics.getPosition().y, 2));

        circle1->physics.addSpring(&circle2->physics, restLength, 0.1f); // Add a method to add spring
        circle2->physics.addSpring(&circle1->physics, restLength, 0.1f); // Add a method to add spring
    }
}
