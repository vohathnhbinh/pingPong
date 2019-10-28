#include "Bat.h"

Bat::Bat(float startX, float startY, float width, float height) // Toa do bat dau cua thanh truot
{
	position.x = startX;
	position.y = startY;

	batShape.setSize(Vector2f(width, height));
	batShape.setPosition(position);
}

void Bat::setPosition(float startX, float startY)
{
	position.x = startX;
	position.y = startY;
}

FloatRect Bat::getPosition()
{
	return batShape.getGlobalBounds();
}

RectangleShape Bat::getShape()
{
	return batShape;
}

void Bat::moveUp(float deltaTime)
{
	position.y = position.y - (batSpeed * deltaTime);
}

void Bat::moveDown(float deltaTime)
{
	position.y = position.y + (batSpeed * deltaTime);
}

void Bat::update()
{
	batShape.setPosition(position);
}