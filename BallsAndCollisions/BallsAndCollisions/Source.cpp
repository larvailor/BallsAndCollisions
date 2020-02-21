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
unsigned selectedBallIndex = -1;
bool bSelected = false;



//--------------------------------------------------
//				Forward declarations
//

void generateBalls();
void drawBalls();
void handleMouseInput();
inline void changeCircleShape(sf::CircleShape& cs, sf::Color color, Ball& ball);


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
		drawBalls();

		bSelected = false;
		selectedBallIndex = -1;
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



inline void changeCircleShape(sf::CircleShape& cs, sf::Color color, Ball& ball)
{
	cs.setOutlineColor(color);
	cs.setPosition(ball.x, ball.y);
	cs.setRadius(ball.radius);
	cs.setOrigin(
		sf::Vector2f(
			cs.getLocalBounds().left + ball.radius,
			cs.getLocalBounds().top + ball.radius
		)
	);
}

void drawBalls()
{
	sf::CircleShape cs;
	cs.setOutlineThickness(2);
	cs.setFillColor(sf::Color::Black);

	for (auto& ball : balls)
	{
		if (ball.index == selectedBallIndex) continue;

		changeCircleShape(cs, sf::Color::White, ball);
		renderWindow->draw(cs);
	}

	if (bSelected)
	{
		changeCircleShape(cs, sf::Color::Green, balls[selectedBallIndex]);
		renderWindow->draw(cs);
	}
}



void handleMouseInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		float mouseX = sf::Mouse::getPosition(*renderWindow).x;
		float mouseY = sf::Mouse::getPosition(*renderWindow).y;
		for (auto& ball : balls)
		{
			if (sqrt((mouseX - ball.x) * (mouseX - ball.x) + (mouseY - ball.y) * (mouseY - ball.y)) < ball.radius)
			{
				bSelected = true;
				selectedBallIndex = ball.index;

				ball.x = mouseX;
				ball.y = mouseY;
				return;
			}
		}
	}
}
