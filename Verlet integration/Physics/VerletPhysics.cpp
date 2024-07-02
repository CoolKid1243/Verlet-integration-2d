#include "VerletPhysics.h"
#include <cmath>
#include <vector>

VerletPhysics::VerletPhysics(float posX, float posY, float radius) :
    position(posX, posY),
    oldPosition(posX, posY),
    velocity(0.f, 0.f),
    radius(radius) {
}

void VerletPhysics::update(float deltaTime, const std::vector<VerletPhysics*>& circles) {
    integrate();
    handleCollision(circles);

    for (auto& spring : springs) {
        sf::Vector2f direction = spring.other->position - position;
        float currentLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        float displacement = currentLength - spring.restLength;

        if (currentLength != 0) {
            direction /= currentLength;
        }

        sf::Vector2f force = spring.stiffness * displacement * direction;
        position += force * deltaTime;
        spring.other->position -= force * deltaTime;
    }
}

void VerletPhysics::applyGravity(float gravity, float deltaTime) {
    velocity.y += gravity * deltaTime;
}

void VerletPhysics::applyVelocity(float velocity, float deltaTime) {
    //position += velocity * deltaTime;
}

void VerletPhysics::applyFriction(float friction) {
    velocity *= friction;
}

void VerletPhysics::springForce(float deltaTime, const std::vector<VerletPhysics*>& circles) {
    for (auto& circle : circles) {
        sf::Vector2f direction = circle->position - position;
        float currentLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        float displacement = currentLength - radius;

        if (currentLength != 0) {
            direction /= currentLength;
        }

        sf::Vector2f force = displacement * direction;
        position += force * deltaTime;
    }
}

void VerletPhysics::addSpring(VerletPhysics* other, float restLength, float stiffness) {
    springs.push_back({ other, restLength, stiffness });
}

sf::Vector2f VerletPhysics::getPosition() const {
    return position;
}

void VerletPhysics::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
}

float VerletPhysics::getRadius() const {
    return radius;
}

void VerletPhysics::integrate() {
    sf::Vector2f newPosition = position + (position - oldPosition) + velocity;
    oldPosition = position;
    position = newPosition;
}

void VerletPhysics::handleCollision(const std::vector<VerletPhysics*>& circles) {
    // Collision with window
    sf::Vector2f windowSize(800.f, 600.f);
    float restitution = 0.8f;

    if (position.x < radius) {
        position.x = radius;
        velocity.x = -velocity.x * restitution;
    }
    if (position.x > windowSize.x - radius) {
        position.x = windowSize.x - radius;
        velocity.x = -velocity.x * restitution;
    }
    if (position.y < radius) {
        position.y = radius;
        velocity.y = -velocity.y * restitution;
    }
    if (position.y > windowSize.y - radius) {
        position.y = windowSize.y - radius;
        velocity.y = -velocity.y * restitution;
    }

    for (auto& circle : circles) {
        if (circle == this) continue;

        sf::Vector2f direction = position - circle->position;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        float minDist = radius + circle->radius;

        if (distance < minDist) {
            if (distance != 0) {
                direction /= distance;
            }
            float displacement = minDist - distance;
            position += direction * displacement * 0.5f;
            circle->position -= direction * displacement * 0.5f;
        }
    }
}
