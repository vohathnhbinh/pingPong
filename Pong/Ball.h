#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
	Vector2f position;
	RectangleShape ballShape;
	float xVelocity = 0;
	float yVelocity = 0;
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