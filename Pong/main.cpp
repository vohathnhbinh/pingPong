#include <sstream>
#include <math.h>
#include "Bat.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "time.h"
#include <iostream>
#include "SnowFall.h"

using namespace sf;

void main()
{
	const int windowWidth = 960;
	const int windowHeight = 720;
	const int batWidth = 10; const int batHeight = 100;
	const int ballSize = 20;
	RenderWindow window(VideoMode(windowWidth, windowHeight), "pingPong", Style::Close);
	window.setFramerateLimit(60);

	// Load man hinh nen
	Texture texture;
	texture.loadFromFile("image/background.png");
	IntRect SourceSprite(0, 0, windowWidth, windowHeight);
	Sprite sprite(texture, SourceSprite);

	// Khoi tao thanh truot va bong
	Bat Player1(50, windowHeight / 2 - batHeight / 2, batWidth, batHeight, Color::White);
	Bat Player2(windowWidth - 50 - batWidth, windowHeight / 2 - batHeight / 2, batWidth, batHeight, Color::White);
	Ball ball(windowWidth / 2, windowHeight / 2 - ballSize, ballSize);
	

	// Snowfall
	unsigned int elapsed = 0;
	srand((unsigned int)time(0));
	std::vector<CircleShape> vt;
	int num = 100;
	int delay = 7;
	vt.reserve(num);

	// Van ban
	Text hud;
	Font font;
	font.loadFromFile("font140.otf");
	hud.setFont(font);
	hud.setCharacterSize(40);
	hud.setFillColor(sf::Color::White);
	hud.setString("Nhan Enter de bat dau tro choi");

	// Am thanh
	Music music;
	music.openFromFile("sound/music.ogg");
	music.play();
	music.setLoop(true);
	SoundBuffer soundbuffer1, soundbuffer2, soundbuffer0;
	soundbuffer1.loadFromFile("sound/hitbat.ogg");
	Sound hitbat(soundbuffer1);
	hitbat.setVolume(50);
	soundbuffer2.loadFromFile("sound/hitwall.ogg");
	Sound hitwall(soundbuffer2);
	hitwall.setVolume(50);
	soundbuffer0.loadFromFile("sound/end.ogg");
	Sound end(soundbuffer0);

	Clock animation; // Dieu chinh toc do animation cua background
	Clock clock; // Tinh thoi gian de game co the chay phu hop voi tung loai may tinh
	bool isPlaying = false;
	while (window.isOpen())
	{
		elapsed++;

		Event event;
		while (window.pollEvent(event)) // Kiem tra xem co tin hieu nao gui den OS khong
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) // Tin hieu dong
			{
				window.close(); // Cua so se duoc dong
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter)) // Nhan Enter de bat dau choi
			{
				if (!isPlaying)
				{
					// Reset lai vi tri cua cac doi tuong khi bat dau mot game moi
					Player1.setPosition(50, windowHeight / 2 - batHeight / 2);
					Player2.setPosition(windowWidth - 50 - batWidth, windowHeight / 2 - batHeight / 2);
					ball.setPosition(windowWidth / 2, windowHeight / 2 - ballSize);

					// Set toc do ban dau cho qua bong
					srand(time(NULL));
					int arr[2] = { -1, 1 };
					int random0 = rand() % 2;
					int random1 = rand() % 2;
					ball.setVelocity(200.f * arr[random0], 200.f * arr[random1]);

					isPlaying = true; // Bat dau lai tro choi
					clock.restart();
				}
			}
		}

		if (animation.getElapsedTime().asSeconds() > .1f)
		{
			if (SourceSprite.top == windowHeight * 7)
				SourceSprite.top = 0;
			else
				SourceSprite.top += windowHeight;
			sprite.setTextureRect(SourceSprite);
			animation.restart();
		}
		if (isPlaying)
		{
			float deltaTime = clock.restart().asSeconds();

			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				if (Player1.getPosition().top >= 0)
					Player1.moveUp(deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				if (Player1.getPosition().top + batHeight <= windowHeight)
					Player1.moveDown(deltaTime);
			}


			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (Player2.getPosition().top >= 0)
					Player2.moveUp(deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				if (Player2.getPosition().top + batHeight <= windowHeight)
					Player2.moveDown(deltaTime);
			}

			if (ball.getPosition().left >= 150)
			{
				if ((Player2.getPosition().top + batHeight / 2) <= (ball.getPosition().top) + 5)
				{
					if (Player2.getPosition().top + batHeight <= windowHeight)
						Player2.moveDown(deltaTime);
				}

				if ((Player2.getPosition().top + batHeight / 2) >= (ball.getPosition().top + ballSize - 5))
				{
					if (Player2.getPosition().top >= 0)
						Player2.moveUp(deltaTime);
				}
			}

			// Banh vuot qua mot trong hai thanh truot
			if (ball.getPosition().left < 50)
			{
				end.play();
				isPlaying = false;
				hud.setString("Nguoi choi 2 thang!\nNhan dup Enter de khoi dong lai tro choi!");
			}
			if (ball.getPosition().left + ballSize > windowWidth - 50)
			{
				end.play();
				isPlaying = false;
				hud.setString("Nguoi choi 1 thang!\nNhan dup Enter de khoi dong lai tro choi!");
			}

			// Banh va cham vao tuong
			if (ball.getPosition().top <= 0 || ball.getPosition().top + ballSize >= windowHeight)
			{
				ball.reboundSides();
				hitwall.play();
			}

			// Banh va cham vao thanh truot
			if (ball.getPosition().intersects(Player1.getPosition()) || ball.getPosition().intersects(Player2.getPosition()))
			{
				ball.reboundBat(deltaTime);
				hitbat.play();
				ball.setVelocity(ball.getXVelocity() * 1.1, ball.getYVelocity() * 1.1);
			}

			// Gioi han toc do cua qua bong
			if (ball.getXVelocity() > (200.f * pow(1.1, 10)) && ball.getYVelocity() > (200.f * pow(1.1, 10)))
				ball.setVelocity(ball.getXVelocity() / 1.1, ball.getYVelocity() / 1.1);

			// Cap nhat vi tri cho cac doi tuong Ball, Bat
			ball.update(deltaTime);
			Player1.update();
			Player2.update();
		}

		hud.setPosition(windowWidth / 2 - hud.getLocalBounds().width / 2, windowHeight / 2 - hud.getLocalBounds().height / 2);


		if (isPlaying)
		{
			window.draw(sprite);

			if (elapsed >= delay && vt.size() < num)
			{
				createSnow(vt, windowWidth);
				elapsed = 0;
			}

			for (int i = 0; i < vt.size(); i++)
			{
				vt[i].move(.0f, vt[i].getRadius() * .4f);
				window.draw(vt[i]);

				if (vt[i].getPosition().y > windowHeight)
					vt.erase(vt.begin() + i);
			}

			window.draw(Player1.getShape());
			window.draw(Player2.getShape());
			window.draw(ball.getShape());
		}
		else
			window.draw(hud);

		window.display();
	}
}