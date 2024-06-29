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
}

void VerletPhysics::applyGravity(float gravity, float deltaTime) {
    velocity.y += gravity * deltaTime;
}

void VerletPhysics::applyVelocity(float velocity, float deltaTime) {
    this->velocity.x += velocity * deltaTime;
}

void VerletPhysics::applyFriction(float friction) {
    this->velocity.x *= friction;
    this->velocity.y *= friction;
}

void springForce(float deltaTime, const std::vector<VerletPhysics*>& circles) {
    
}

sf::Vector2f VerletPhysics::getPosition() const {
    return position;
}

void VerletPhysics::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
    oldPosition = newPosition;
}

float VerletPhysics::getRadius() const {
    return radius;
}

void VerletPhysics::integrate() {
    sf::Vector2f temp = position;
    position += (position - oldPosition) + velocity;
    oldPosition = temp;
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

    // Circle collisions
    for (auto& other : circles) {
        if (other == this) continue;

        float dx = position.x - other->position.x;
        float dy = position.y - other->position.y;
        float distanceSquared = dx * dx + dy * dy;
        float radiusSum = radius + other->radius;

        if (distanceSquared < radiusSum * radiusSum) {
            float distance = std::sqrt(distanceSquared);
            sf::Vector2f normal = (position - other->position) / distance;
            float overlap = radiusSum - distance;

            position += normal * (overlap / 2.0f);
            other->position -= normal * (overlap / 2.0f);

            sf::Vector2f relativeVelocity = velocity - other->velocity;
            float velocityAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

            if (velocityAlongNormal < 0) {
                float restitution = 0.8f;
                float impulse = (1 + restitution) * velocityAlongNormal;

                sf::Vector2f impulseVector = impulse * normal;
                velocity -= impulseVector * 0.5f;
                other->velocity += impulseVector * 0.5f;
            }
        }
    }
}