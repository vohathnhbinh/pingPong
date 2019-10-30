#include "Bat.h"

Bat::Bat(float startX, float startY, float width, float height, Color color)
{
	/*
	startX, startY: toa do bat dau
	width, height: chieu dai va chieu rong cua cua so
	color: mau sac
	*/
	position.x = startX;
	position.y = startY;

	batShape.setSize(Vector2f(width, height));
	batShape.setPosition(position);
	batShape.setFillColor(color);
	batShape.setOutlineThickness(3);
	batShape.setOutlineColor(Color::Red);

	// Khoi tao va xay dung cac thuoc tinh kich thuoc, vi tri, mau sac
}

void Bat::setPosition(float startX, float startY)
{
	// startX, startY: toa do bat dau
	position.x = startX;
	position.y = startY;
}

FloatRect Bat::getPosition()
{
	return batShape.getGlobalBounds();
	// Lay vi tri hien tai de truy cap toa do x, y, top, left, ... cua thuc the
}

RectangleShape Bat::getShape()
{
	return batShape;
	// Lay thuc the (entity) cua thanh truot
}

void Bat::setbatSpeed(float speed)
{
	// speed: toc do
	batSpeed = speed;
}

void Bat::moveUp(float deltaTime)
{
	// deltaTime: thoi gian chay cua tung khung hinh
	position.y = position.y - (batSpeed * deltaTime);
	// Thanh truot se di chuyen dua vao batSpeed va deltaTime (se duoc giai thich ro hon trong bao cao)
}

void Bat::moveDown(float deltaTime)
{
	// deltaTime: thoi gian chay cua tung khung hinh
	position.y = position.y + (batSpeed * deltaTime);
}

void Bat::update()
{
	batShape.setPosition(position);
	// Cap nhat vi tri cua thanh truot
}