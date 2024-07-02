#pragma once

#include <SFML/Graphics.hpp>
#include "VerletPhysics.h"
#include <vector>

class Circle {
public:
    Circle(float x, float y, bool immobleState = false);
    void update(float deltaTime, bool paused, std::vector<Circle>& circles);
    void draw(sf::RenderWindow& window);
    void setImmoble(bool immoble);

    void toggleSelection();
    bool isSelected() const;
    void setColor(const sf::Color& color);
    sf::FloatRect getGlobalBounds() const;

    static std::vector<Circle*> getSelectedCircles();
    static void createSpringForceBetweenSelectedCircles(std::vector<Circle>& circles);

    VerletPhysics physics;

private:
    sf::CircleShape circle;
    sf::Color circleColor;
    sf::Texture texture;
    bool immoble;
    float immoblePosX;
    float immoblePosY;
    bool useTexture;
    bool selected;

    std::vector<VerletPhysics*> getPhysicsPointers(std::vector<Circle>& circles);
    static std::vector<Circle*> selectedCircles;
};
