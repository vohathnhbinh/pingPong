#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat
{
private:
	Vector2f position; // vector 2 chieu x,y chua toa do vi tri

	RectangleShape batShape;

	float batSpeed = 400.f;

public:
	Bat(float, float, float, float, Color); // constructor
	void setPosition(float, float);
	FloatRect getPosition();

	RectangleShape getShape();

	void moveUp(float);

	void moveDown(float);

	void update();
};