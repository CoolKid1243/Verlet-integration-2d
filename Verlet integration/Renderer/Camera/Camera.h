#pragma once

#include <SFML/Graphics.hpp>

class Camera {
public:
    Camera();

    void update(sf::RenderWindow& window);
    void setCenter(sf::Vector2f center);
    void handleZoom(sf::Event event);
    void lockOntoCircle(bool lock);
    bool isLockedOntoCircle() const;
    sf::Vector2f getCenter() const;
    float getZoom() const;

private:
    bool isRightClicking;
    sf::Vector2i lastMousePosition;
    sf::Vector2f cameraCenter;
    float zoomLevel;
    bool lockedOntoCircle;

    void zoomIn();
    void zoomOut();
};