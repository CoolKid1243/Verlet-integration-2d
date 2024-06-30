#include "Application.h"

void App::run() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Verlet integration");
    while (window.isOpen()) {
        
        
        handleEvents();

        float deltaTime = clock.restart().asSeconds();

        update(deltaTime, window);

        window.clear(sf::Color::Black);

        viewTransformations();

        draw();

        window.display();
    }
}

void App::update(float deltaTime, sf::RenderWindow& window) {
    for (auto& circle : circles) {
        circle.update(deltaTime, playButton.playClicked, circles);
    }

    backround.update(deltaTime);

    camera.update(window);
}

void App::handleEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        camera.handleZoom(event);

        spawnButton.handleEvent(event, window);

        immobleButton.handleEvent(event, window, circles);

        playButton.handleEvent(event, window, circles);

        linkButton.handleEvent(event, window, circles);

        if (spawnButton.isButtonClicked() && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            spawnCircleAtMouse();
        }
    }
}

void App::draw() {
    backround.draw(window);

    for (auto& circle : circles) {
        circle.draw(window);
    }

    spawnButton.draw(window);
    immobleButton.draw(window);
    playButton.draw(window);
    linkButton.draw(window);
}

void App::viewTransformations() {
    sf::View view = window.getView();

    view.setCenter(camera.getCenter());
    view.setSize(sf::Vector2f(window.getSize()));

    view.zoom(camera.getZoom());
    window.setView(view);
}

void App::spawnCircleAtMouse() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

    if (!spawnButton.getGlobalBounds().contains(worldMousePos) && !playButton.getGlobalBounds().contains(worldMousePos) && !immobleButton.getGlobalBounds().contains(worldMousePos) && !linkButton.getGlobalBounds().contains(worldMousePos)) {
        circles.emplace_back(worldMousePos.x, worldMousePos.y, immobleButton.isButtonClicked());
    }
}