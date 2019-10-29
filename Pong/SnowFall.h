#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
void createSnow(std::vector < sf::CircleShape>& vt, int windowWidth)
{
	sf::CircleShape flake(float(rand()) / (float)(RAND_MAX / 3.f) + .5f);
	flake.setPosition(float(rand() % windowWidth), .0f);
	flake.setFillColor(sf::Color::White);

	vt.emplace_back(flake);
}