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

	Ball(float x, float y, float radius) : x(x), y(y), radius(radius) { }
};

//--------------------------------------------------
//				Global variables
//

std::unique_ptr<sf::RenderWindow> renderWindow;

std::vector<Ball> balls;



//--------------------------------------------------
//				Forward declarations
//

void generateBalls();
void drawBalls();



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
				minBallRadius + rand() % maxBallRadius
			)
		);
	}
}



void drawBalls()
{
	sf::CircleShape cs;
	cs.setFillColor(sf::Color::Black);
	cs.setOutlineColor(sf::Color::White);
	cs.setOutlineThickness(2);
	for (auto& ball : balls)
	{
		cs.setPosition(ball.x, ball.y);
		cs.setRadius(ball.radius);
		renderWindow->draw(cs);
	}
}
