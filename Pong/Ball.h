#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
	Vector2f position; // toa do vi tri
	RectangleShape ballShape; // hinh dang (thuc the)
	float xVelocity = 0; // toc do theo chieu ngang
	float yVelocity = 0; // toc do theo chieu doc
public:
	Ball(float, float, float); // constructor
	void setPosition(float startX, float startY);
	FloatRect getPosition();

	RectangleShape getShape();

	void setVelocity(float, float);
	float getXVelocity();
	float getYVelocity();

	void reboundSides();

	void reboundBat(float);

	void update(float);

};