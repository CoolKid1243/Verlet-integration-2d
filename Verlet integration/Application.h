#pragma once

#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Circle.h"
#include "Backround.h"
#include "SpawnButton.h"
#include "ImmobleButton.h"
#include "PlayButton.h"
#include "LinkButton.h"

class App {
public:
    std::vector<Circle> circles;
    Camera camera;
    Background background;
    SpawnButton spawnButton;
    ImmobleButton immobleButton;
    PlayButton playButton;
    LinkButton linkButton;
    sf::RenderWindow window;
    sf::Clock clock;

    App() : window(sf::VideoMode(800, 600), "Verlet integration"), background(800.f, 600.f) {}
    void handleEvents();
    void draw();
    void viewTransformations();
    void run();
    void update(float deltaTime, sf::RenderWindow& window);
    void spawnCircleAtMouse();
};
