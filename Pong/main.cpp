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
	RenderWindow window(VideoMode(windowWidth, windowHeight), "pingPong", Style::Close); // Thiet lap cua so game
	window.setFramerateLimit(60); // Gioi han so luong khung hinh chay trong 1s

	// Load man hinh nen
	Texture texture;
	texture.loadFromFile("image/background.png");
	IntRect SourceSprite(0, 0, windowWidth, windowHeight);
	Sprite sprite(texture, SourceSprite);

	// Khoi tao thanh truot va bong
	Bat Player1(50, windowHeight / 2 - batHeight / 2, batWidth, batHeight, Color::White);
	Bat Player2(windowWidth - 50 - batWidth, windowHeight / 2 - batHeight / 2, batWidth, batHeight, Color::White);
	Ball ball(windowWidth / 2, windowHeight / 2 - ballSize, ballSize);

	// Khoi tao vector va cac bien xu li hieu ung tuyet roi
	unsigned int elapsed = 0;
	srand((unsigned int)time(0));
	std::vector<CircleShape> vt;
	int num = 200;
	int delay = 5;
	vt.reserve(num);

	// Van ban
	Text hud;
	Font font;
	font.loadFromFile("font140.otf");
	hud.setFont(font);
	hud.setCharacterSize(40);
	hud.setFillColor(sf::Color::White);

	Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(80);
	pauseMessage.setFillColor(sf::Color::White);
	pauseMessage.setString("S N O W Y");

	Text Single;
	Single.setFont(font);
	Single.setCharacterSize(40);
	Single.setFillColor(sf::Color::White);
	Single.setString("Single player");

	Text Multi;
	Multi.setFont(font);
	Multi.setCharacterSize(40);
	Multi.setFillColor(sf::Color::White);
	Multi.setString("Multi player");

	int selected = 0;
	bool leftKey = Keyboard::isKeyPressed(Keyboard::Key::Left);
	bool rightKey = Keyboard::isKeyPressed(Keyboard::Key::Right);

	// Am thanh
	Music music;
	music.openFromFile("sound/music.ogg");
	music.play();
	music.setLoop(true);
	SoundBuffer soundbuffer1, soundbuffer2, soundbuffer0, soundbuffer3;
	soundbuffer1.loadFromFile("sound/hitbat.ogg");
	Sound hitbat(soundbuffer1);
	hitbat.setVolume(50);
	soundbuffer2.loadFromFile("sound/hitwall.ogg");
	Sound hitwall(soundbuffer2);
	hitwall.setVolume(50);
	soundbuffer0.loadFromFile("sound/end.ogg");
	Sound end(soundbuffer0);
	soundbuffer3.loadFromFile("sound/laugh.ogg");
	Sound enter(soundbuffer3);

	// Secret
	Music secret_music;
	secret_music.openFromFile("sound/secret.ogg");
	secret_music.setLoop(true);
	Texture secret_texture;
	secret_texture.loadFromFile("image/secret.png");
	Sprite secret(secret_texture, IntRect(0, 0, windowWidth, windowWidth));

	Clock animation; // Dieu chinh toc do animation cua background
	Clock clock; // Tinh thoi gian de game co the chay phu hop voi tung loai may tinh
	bool isPlaying = false;
	bool check = false;
	while (window.isOpen())
	{
		elapsed++;

		Event event;
		while (window.pollEvent(event)) // Kiem tra xem co tin hieu nao gui den OS khong
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::Left) && !leftKey)
			{
				hitbat.play();
				selected -= 1;
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Right) && !rightKey)
			{
				hitbat.play();
				selected += 1;
			}

			if (selected < 0)
				selected = 1;
			if (selected > 1)
				selected = 0;
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) // Tin hieu dong
			{
				window.close(); // Cua so se duoc dong
				break;
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter)) // Nhan Enter de bat dau choi
			{
				if (!isPlaying)
				{
					enter.play();

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

					// Bat dau lai tro choi
					isPlaying = true;
					clock.restart();
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			check = true;
			music.stop();
			secret_music.play();
			pauseMessage.setFillColor(Color::Red);
			pauseMessage.setString("The End");
		}

		// Chay hinh nen dong
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

			// Dieu khien nguoi choi 1
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				if (Player1.getPosition().top > 5)
					Player1.moveUp(deltaTime);
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				if (Player1.getPosition().top + batHeight < windowHeight - 5)
					Player1.moveDown(deltaTime);
			}

			// Dieu khien nguoi choi 2
			if (selected == 1)
			{
				Player2.setbatSpeed(400.f);
				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					if (Player2.getPosition().top > 5)
						Player2.moveUp(deltaTime);
				}
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					if (Player2.getPosition().top + batHeight < windowHeight - 5)
						Player2.moveDown(deltaTime);
				}
			}

			// Xu li nguoi choi may tinh (computer player)
			if (selected == 0)
			{
				Player2.setbatSpeed(550.f);
				if (ball.getPosition().left >= 150)
				{
					if ((Player2.getPosition().top + batHeight) < (ball.getPosition().top + ballSize + ballSize / 2))
					{
						if (Player2.getPosition().top + batHeight < windowHeight - 5)
							Player2.moveDown(deltaTime);
					}
					else if (Player2.getPosition().top > (ball.getPosition().top - ballSize / 2))
					{
						if (Player2.getPosition().top > 5)
							Player2.moveUp(deltaTime);
					}
				}
			}

			// Banh vuot qua mot trong hai thanh truot
			if (ball.getPosition().left < 50)
			{
				if (!check)
					end.play();
				isPlaying = false;
				hud.setString("Nguoi choi 2 thang!");
			}
			if (ball.getPosition().left + ballSize > windowWidth - 50)
			{
				if (!check)
					end.play();
				isPlaying = false;
				hud.setString("Nguoi choi 1 thang!");
			}

			// Banh va cham vao tuong
			if (ball.getPosition().top <= 0 || ball.getPosition().top + ballSize >= windowHeight)
			{
				ball.reboundSides(deltaTime);
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

		// Dieu chinh vi tri cua tung doan van ban
		pauseMessage.setPosition(window.getSize().x / 2 - pauseMessage.getLocalBounds().width / 2, window.getSize().y / 6);
		Single.setPosition(window.getSize().x / 4 - Single.getLocalBounds().width / 2, window.getSize().y / 1.8);
		Multi.setPosition(window.getSize().x * .75f - Multi.getLocalBounds().width / 2, window.getSize().y / 1.8);
		hud.setPosition(windowWidth / 2 - hud.getLocalBounds().width / 2, windowHeight / 2 - 90);

		if (isPlaying)
		{
			if (check)
				window.draw(secret);
			else
				window.draw(sprite);

			// Xu li hieu ung tuyet roi
			if (elapsed >= delay && vt.size() < num)
			{
				if (check)
					createSnow(vt, windowWidth, Color::Red);
				else
					createSnow(vt, windowWidth, Color::White);
				elapsed = 0;
			}
			for (int i = 0; i < vt.size(); i++)
			{
				vt[i].move(.0f, vt[i].getRadius() * .4f);
				window.draw(vt[i]);

				if (vt[i].getPosition().y > windowHeight)
					vt.erase(vt.begin() + i);
			}

			// Hien thi thanh truot va qua bong len man hinh
			window.draw(Player1.getShape());
			window.draw(Player2.getShape());
			window.draw(ball.getShape());
		}
		else
		{
			window.clear();
			Single.setFillColor(Color::White);
			Multi.setFillColor(Color::White);
			switch (selected)
			{
			case 0:
				Single.setFillColor(Color::Green);
				break;
			case 1:
				Multi.setFillColor(Color::Green);
				break;
			}

			// Hien thi cac van ban len man hinh
			window.draw(hud);
			window.draw(pauseMessage);
			window.draw(Single);
			window.draw(Multi);
		}

		// Ket thuc khung hinh va hien thi noi dung len man hinh
		window.display();
	}
}