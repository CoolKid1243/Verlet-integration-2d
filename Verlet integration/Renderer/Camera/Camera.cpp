#include "Camera.h"

Camera::Camera() :
    isRightClicking(false),
    lastMousePosition(0, 0),
    cameraCenter(400.f, 300.f),
    zoomLevel(1.0f),
    lockedOntoCircle(false)
{
}

void Camera::update(sf::RenderWindow& window) {
    if (lockedOntoCircle) return;

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (!isRightClicking) {
            isRightClicking = true;
            lastMousePosition = mousePosition;
        }

        // Calculate movement offset
        sf::Vector2i offset = mousePosition - lastMousePosition;
        cameraCenter -= static_cast<sf::Vector2f>(offset);

        // Update last mouse position
        lastMousePosition = mousePosition;
    }
    else {
        isRightClicking = false;
    }
}

void Camera::setCenter(sf::Vector2f center) {
    cameraCenter = center;
}

void Camera::handleZoom(sf::Event event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            if (event.mouseWheelScroll.delta > 0) {
                zoomIn(); 
            }
            else if (event.mouseWheelScroll.delta < 0) {
                zoomOut(); 
            }
        }
    }
}

void Camera::zoomIn() {
    zoomLevel /= 1.9f;
}

void Camera::zoomOut() {
    zoomLevel += 1.00001f;
}

void Camera::lockOntoCircle(bool lock) {
    lockedOntoCircle = lock;
}

bool Camera::isLockedOntoCircle() const {
    return lockedOntoCircle;
}

sf::Vector2f Camera::getCenter() const {
    return cameraCenter;
}

float Camera::getZoom() const {
    return zoomLevel;
}
