#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Camera.h"
#include "Circle.h"
#include "Backround.h"
#include "SpawnButton.h"
#include "ImmobleButton.h"
#include "PlayButton.h"
#include "LinkButton.h"


// From dev to dev, log how many days have been waisted on this system here: 5


std::vector<Circle> circles;
Camera camera;
Backround backround(800.f, 600.f);
SpawnButton spawnButton;
ImmobleButton immobleButton;
PlayButton playButton;
LinkButton linkButton;

void Update(float deltaTime, sf::RenderWindow& window) {
    // Update the game objects
    for (auto& circle : circles) {
        circle.update(deltaTime, playButton.playClicked, circles);
    }
    backround.update(deltaTime);

    // Update the camera
    camera.update(window);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Verlet integration");
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle mouse wheel scrolling
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    if (event.mouseWheelScroll.delta > 0) {
                        camera.zoomIn(); // Zoom in
                    }
                    else if (event.mouseWheelScroll.delta < 0) {
                        camera.zoomOut(); // Zoom out
                    }
                }
            }

            spawnButton.handleEvent(event, window);

            immobleButton.handleEvent(event, window, circles);

            playButton.handleEvent(event, window, circles);

            linkButton.handleEvent(event, window, circles);

            // Spawn a new circle when I click
            if (spawnButton.isButtonClicked() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

                // Check if mouse position is under a button
                if (!spawnButton.getGlobalBounds().contains(worldMousePos) && !playButton.getGlobalBounds().contains(worldMousePos) && !immobleButton.getGlobalBounds().contains(worldMousePos) && !linkButton.getGlobalBounds().contains(worldMousePos)) {
                    circles.emplace_back(worldMousePos.x, worldMousePos.y, immobleButton.isButtonClicked());
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        Update(deltaTime, window);

        window.clear(sf::Color::Black);

        // Apply the view transformation
        sf::View view = window.getView();
        view.setCenter(camera.getCenter());
        view.setSize(sf::Vector2f(window.getSize()));
        view.zoom(camera.getZoom());
        window.setView(view);

        // Render the objects
        backround.draw(window);
        for (auto& circle : circles) {
            circle.draw(window);
        }
        spawnButton.draw(window);
        immobleButton.draw(window);
        playButton.draw(window);
        linkButton.draw(window);

        window.display();
    }
    return 0;
}
