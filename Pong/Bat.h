#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat
{
private:
	Vector2f position; // toa do vi tri
	RectangleShape batShape; // hinh dang (thuc the)
	float batSpeed = 400.f; // toc do di chuyen
public:
	Bat(float, float, float, float, Color); // constructor
	void setPosition(float, float);
	FloatRect getPosition();

	RectangleShape getShape();

	void setbatSpeed(float);

	void moveUp(float);

	void moveDown(float);

	void update();
};