#include <vector>
#include <ctime>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

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

unsigned selectedBallIndex = -1;
bool bSelected = false;



//--------------------------------------------------
//				Forward declarations
//

void generateBalls();
void drawBalls();
void handleMouseInput();
void processCollisions();



//--------------------------------------------------
//				Implementation
//

int main()
{
	generateBalls();

	renderWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(winWidth, winHeight), "BallsAndCollisions", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

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
		return (mouseX - ball.x) * (mouseX - ball.x) + (mouseY - ball.y) * (mouseY - ball.y) < ball.radius * ball.radius;
	};

	float mouseX = sf::Mouse::getPosition(*renderWindow).x;
	float mouseY = sf::Mouse::getPosition(*renderWindow).y;

	if (pSelectedBall)
	{
		pSelectedBall->x = mouseX;
		pSelectedBall->y = mouseY;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
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
	else
	{
		pSelectedBall = nullptr;
	}
}



void processCollisions()
{
	auto isBallsCollides = [](Ball& ball1, Ball& ball2)
	{
		return ((ball2.x - ball1.x) * (ball2.x - ball1.x) + (ball2.y - ball1.y) * (ball2.y - ball1.y)) <= (ball1.radius + ball2.radius) * (ball1.radius + ball2.radius);
	};

	for (auto& ball : balls)
	{
		for (auto& targetBall : balls)
		{
			if (ball.index != targetBall.index)
			{
				if (isBallsCollides(ball, targetBall))
				{
					float distanceBetweenCenters = sqrt((targetBall.x - ball.x) * (targetBall.x - ball.x) + (targetBall.y - ball.y) * (targetBall.y - ball.y));
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
		cs.setOutlineColor(color);
		cs.setPosition(ball->x, ball->y);
		cs.setRadius(ball->radius);
		cs.setOrigin(
			sf::Vector2f(
				cs.getLocalBounds().left + ball->radius,
				cs.getLocalBounds().top + ball->radius
			)
		);
	};

	sf::CircleShape cs;
	cs.setOutlineThickness(2);
	cs.setFillColor(sf::Color::Black);

	for (auto& ball : balls)
	{
		if (ball.index == selectedBallIndex) continue;

		changeCircleShape(cs, sf::Color::White, &ball);
		renderWindow->draw(cs);
	}

	if (pSelectedBall)
	{
		changeCircleShape(cs, sf::Color::Green, pSelectedBall);
		renderWindow->draw(cs);
	}
}
