#ifndef VERLETPHYSICS_H
#define VERLETPHYSICS_H

#include <SFML/Graphics.hpp>
#include <vector>

class VerletPhysics {
public:
    VerletPhysics(float posX, float posY, float radius);
    void update(float deltaTime, const std::vector<VerletPhysics*>& circles);
    void applyGravity(float gravity, float deltaTime);
    void applyVelocity(float velocity, float deltaTime);
    void applyFriction(float friction);
    void springForce(float deltaTime, const std::vector<VerletPhysics*>& circles);
    void addSpring(VerletPhysics* other, float restLength, float stiffness); // New method

    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& newPosition);
    float getRadius() const;

private:
    sf::Vector2f position;
    sf::Vector2f oldPosition;
    sf::Vector2f velocity;
    float radius;

    struct Spring {
        VerletPhysics* other;
        float restLength;
        float stiffness;
    };
    std::vector<Spring> springs; // New member to store springs

    void integrate();
    void handleCollision(const std::vector<VerletPhysics*>& circles);
};

#endif // VERLETPHYSICS_H
