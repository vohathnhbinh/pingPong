#include "Ball.h"

Ball::Ball(float startX, float startY, float size)
{
	position.x = startX;
	position.y = startY;

	ballShape.setSize(Vector2f(size, size));
	ballShape.setPosition(position);
	ballShape.setFillColor(Color::Red);
}

void Ball::setPosition(float startX, float startY)
{
	position.x = startX;
	position.y = startY;
}

FloatRect Ball::getPosition()
{
	return ballShape.getGlobalBounds();
}

RectangleShape Ball::getShape()
{
	return ballShape;
}

void Ball::setVelocity(float x, float y)
{
	xVelocity = x;
	yVelocity = y;
}

float Ball::getXVelocity()
{
	return xVelocity;
}

float Ball::getYVelocity()
{
	return yVelocity;
}

void Ball::reboundSides()
{
	yVelocity = -yVelocity;
}

void Ball::reboundBat(float deltaTime)
{
	position.x -= (xVelocity * deltaTime);
	xVelocity = -xVelocity;
}

void Ball::update(float deltaTime)
{
	position.y += (yVelocity * deltaTime);
	position.x += (xVelocity * deltaTime);

	ballShape.setPosition(position);
}