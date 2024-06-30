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

class App {
public:
	std::vector<Circle> circles;
	Camera camera;
	Backround backround(800.f, 600.f);
	SpawnButton spawnButton;
	ImmobleButton immobleButton;
	PlayButton playButton;
	LinkButton linkButton;
	sf::Clock clock;

	App() {}
	void handleEvents();
	void draw();
	void viewTransformations();
	void run();
	void update(float deltaTime, sf::RenderWindow& window);
	void spawnCircleAtMouse();
};
