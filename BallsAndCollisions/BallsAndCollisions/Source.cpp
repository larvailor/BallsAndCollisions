#include <iostream>
#include <vector>
#include <ctime>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "Circle.hpp"
#include "Collisions.hpp"

//--------------------------------------------------
//				Constants
//

const unsigned winWidth = 1280;
const unsigned winHeight = 720;

const unsigned char minBallsCount = 50;
const unsigned char maxBallsCount = 70;

const unsigned char minBallRadius = 10;
const unsigned char maxBallRadius = 50;

struct Ball
{
	float x;
	float y;
	float radius;
	unsigned index;

	Ball(float x, float y, float radius, unsigned index) : x(x), y(y), radius(radius), index(index) { }
};



//--------------------------------------------------
//				Global variables
//

std::unique_ptr<sf::RenderWindow> renderWindow;

std::vector<Ball> balls;

Ball* pSelectedBall = nullptr;



//--------------------------------------------------
//				Forward declarations
//

void generateBalls();
void drawBalls();
void handleMouseInput();
void processCollisions();

	// Calculations

float distanceBetweenPoints(float x1, float y1, float x2, float y2);



//--------------------------------------------------
//				Implementation
//

int main()
{
	generateBalls();

	renderWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(winWidth, winHeight), "BallsAndCollisions", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	sf::Clock fpsClock;
	size_t fps = 0;

	while (renderWindow->isOpen())
	{
		while (renderWindow->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code) 
				{
				case sf::Keyboard::Escape:
					renderWindow->close();
					break;
				}
				break;
			case sf::Event::Closed:
				renderWindow->close();
				break;
			}
		}

		renderWindow->clear();

		handleMouseInput();
		processCollisions();
		drawBalls();

		renderWindow->display();

		fps++;
		if (fpsClock.getElapsedTime().asSeconds() >= 1)
		{
			std::cout << "FPS: " << fps << std::endl;
			fps = 0;
			fpsClock.restart().asSeconds();
		}
	}

	return 0;
}



void generateBalls()
{
	std::srand(unsigned(std::time(0)));

	for (size_t ballN = 0; ballN < minBallsCount + rand() % maxBallsCount; ballN++)
	{
		balls.emplace_back(
			Ball(
				rand() % winWidth,
				rand() % winHeight,
				minBallRadius + rand() % maxBallRadius,
				ballN
			)
		);
	}
}



void handleMouseInput()
{
	auto isMouseOnBall = [](float mouseX, float mouseY, Ball& ball)
	{
		return distanceBetweenPoints(ball.x, ball.y, mouseX, mouseY) < ball.radius;
	};

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		float mouseX = sf::Mouse::getPosition(*renderWindow).x;
		float mouseY = sf::Mouse::getPosition(*renderWindow).y;

		if (pSelectedBall)
		{
			pSelectedBall->x = mouseX;
			pSelectedBall->y = mouseY;
		}
		else
		{
			for (auto& ball : balls)
			{
				if (isMouseOnBall(mouseX, mouseY, ball))
				{
					pSelectedBall = &ball;
					return;
				}
			}
		}
	}
	else
	{
		pSelectedBall = nullptr;
	}
}



void processCollisions()
{
	auto isBallsCollides = [](Ball& ball1, Ball& ball2)
	{
		return distanceBetweenPoints(ball1.x, ball1.y, ball2.x, ball2.y) <= ball1.radius + ball2.radius;
	};

	for (auto& ball : balls)
	{
		for (auto& targetBall : balls)
		{
			if (ball.index != targetBall.index)
			{
				if (isBallsCollides(ball, targetBall))
				{
					float distanceBetweenCenters = distanceBetweenPoints(ball.x, ball.y, targetBall.x, targetBall.y);
					float halfOverlap = 0.5f * (distanceBetweenCenters - ball.radius - targetBall.radius);

					ball.x -= halfOverlap * (ball.x - targetBall.x) / distanceBetweenCenters;
					ball.y -= halfOverlap * (ball.y - targetBall.y) / distanceBetweenCenters;

					targetBall.x += halfOverlap * (ball.x - targetBall.x) / distanceBetweenCenters;
					targetBall.y += halfOverlap * (ball.y - targetBall.y) / distanceBetweenCenters;
				}
			}
		}
	}
}



void drawBalls()
{
	auto changeCircleShape = [](sf::CircleShape& cs, sf::Color color, Ball* ball)
	{
		if (ball->x > winWidth + ball->radius)
			ball->x = 0;
		else if (ball->x < 0 - ball->radius)
			ball->x = winWidth;

		if (ball->y > winHeight + ball->radius)
			ball->y = 0;
		else if (ball->y < 0 - ball->radius)
			ball->y = winHeight;

		cs.setPosition(ball->x, ball->y);

		cs.setRadius(ball->radius);
		cs.setOrigin(
			sf::Vector2f(
				cs.getLocalBounds().left + ball->radius,
				cs.getLocalBounds().top + ball->radius
			)
		);

		cs.setOutlineColor(color);
	};

	sf::CircleShape cs;
	cs.setOutlineThickness(2);
	cs.setFillColor(sf::Color::Black);

	for (auto& ball : balls)
	{
		if (pSelectedBall && ball.index == pSelectedBall->index) continue;

		changeCircleShape(cs, sf::Color::White, &ball);
		renderWindow->draw(cs);
	}

	if (pSelectedBall)
	{
		changeCircleShape(cs, sf::Color::Green, pSelectedBall);
		renderWindow->draw(cs);
	}
}



// Calculations

inline float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}