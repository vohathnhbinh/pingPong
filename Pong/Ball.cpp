#include "Ball.h"

Ball::Ball(float startX, float startY, float size)
{
	/*
	startX, startY: toa do bat dau
	size: kich thuoc qua bong
	*/
	position.x = startX;
	position.y = startY;

	ballShape.setSize(Vector2f(size, size));
	ballShape.setPosition(position);
	ballShape.setFillColor(Color::Red);
	// Khoi tao va xay dung cac thuoc tinh kich thuoc, vi tri, mau sac
}

void Ball::setPosition(float startX, float startY)
{
	// startX, startY: toa do bat dau
	position.x = startX;
	position.y = startY;
}

FloatRect Ball::getPosition()
{
	return ballShape.getGlobalBounds();
	// Lay vi tri hien tai de truy cap toa do x, y, top, left, ... cua thuc the
}

RectangleShape Ball::getShape()
{
	return ballShape;
	// Lay thuc the (entity) cua qua bong
}

void Ball::setVelocity(float x, float y)
{
	// x, y: toc do chieu ngang, doc
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
	// Xu li tinh huong cham vao tuong, toc do chieu doc se duoc dao nguoc
}

void Ball::reboundBat(float deltaTime)
{
	// deltaTime: thoi gian chay cua tung khung hinh
	position.x -= (xVelocity * deltaTime);
	xVelocity = -xVelocity;
	// Xu li tinh huong cham vao thanh truot, se duoc giai thich ro hon trong bao cao
}

void Ball::update(float deltaTime)
{
	// deltaTime: thoi gian chay cua tung khung hinh
	position.y += (yVelocity * deltaTime);
	position.x += (xVelocity * deltaTime);

	ballShape.setPosition(position);
	// Cap nhat vi tri cua thanh truot
}