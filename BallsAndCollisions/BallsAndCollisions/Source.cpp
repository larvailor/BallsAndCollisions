#include <iostream>
#include <vector>
#include <ctime>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "Simulation.hpp"

//--------------------------------------------------
//				Constants
//

const unsigned winWidth = 1280;
const unsigned winHeight = 720;


//--------------------------------------------------
//				Global variables
//

std::shared_ptr<BaseFigure> selectedFigure;



//--------------------------------------------------
//				Forward declarations
//

void handleMouseInput(sf::RenderWindow& renderWindow, std::vector<std::shared_ptr<BaseFigure>> figures);

void handleCollisions(std::vector<std::shared_ptr<BaseFigure>> figures);

void drawFigures(sf::RenderWindow& renderWindow, std::vector<std::shared_ptr<BaseFigure>> figures);
void drawCircle(sf::RenderWindow& renderWindow, std::shared_ptr<Circle>& circle);
	


//--------------------------------------------------
//				Implementation
//

int main()
{
	Simulation simulation(winWidth, winHeight, 70);

	sf::RenderWindow renderWindow(sf::VideoMode(winWidth, winHeight), "BallsAndCollisions", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	sf::Clock fpsClock;
	size_t fps = 0;

	while (renderWindow.isOpen())
	{
		while (renderWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code) 
				{
				case sf::Keyboard::Escape:
					renderWindow.close();
					break;
				}
				break;
			case sf::Event::Closed:
				renderWindow.close();
				break;
			}
		}

		renderWindow.clear();

		handleMouseInput(renderWindow, simulation.getFigures());
		handleCollisions(simulation.getFigures());
		drawFigures(renderWindow, simulation.getFigures());

		renderWindow.display();

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



void handleMouseInput(sf::RenderWindow& renderWindow, std::vector<std::shared_ptr<BaseFigure>> figures)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Point mousePos(static_cast<float>(sf::Mouse::getPosition(renderWindow).x), static_cast<float>(sf::Mouse::getPosition(renderWindow).y));

		if (selectedFigure)
		{
			std::dynamic_pointer_cast<Circle>(selectedFigure)->setCenter(mousePos);
		}
		else
		{
			for (auto& figure : figures)
			{
				if (CollisionsDetector::pointInside(mousePos, figure))
				{
					selectedFigure = figure;
					return;
				}
			}
		}
	}
	else
	{
		selectedFigure = nullptr;
	}
}



void handleCollisions(std::vector<std::shared_ptr<BaseFigure>> figures)
{
	for (auto& figure : figures)
	{
		for (auto& targetFigure : figures)
		{
			if (figure.get() != targetFigure.get())
			{
				if (CollisionsDetector::detectCollision(figure, targetFigure))
				{
					CollisionsDetector::handleCollision(figure, targetFigure);
				}
			}
		}
	}
}



void drawFigures(sf::RenderWindow& renderWindow, std::vector<std::shared_ptr<BaseFigure>> figures)
{
	for (auto& figure : figures)
	{
		switch (figure->getFigureType())
		{
		case FigureType::CIRCLE:
			auto circle = std::dynamic_pointer_cast<Circle>(figure);
			drawCircle(renderWindow, circle);
			break;
		}
	}
}	

void drawCircle(sf::RenderWindow& renderWindow, std::shared_ptr<Circle>& circle)
{
	static sf::CircleShape cs;
	cs.setOutlineThickness(-2);
	if (selectedFigure.get() == circle.get())
		cs.setOutlineColor(sf::Color::Green);
	else
		cs.setOutlineColor(sf::Color::White);

	cs.setFillColor(sf::Color::Black);

	cs.setPosition(circle->getCenter().x, circle->getCenter().y);
	cs.setRadius(static_cast<float>(circle->getRadius()));
	cs.setOrigin(
		sf::Vector2f(
			cs.getLocalBounds().left + 0.5f * cs.getLocalBounds().width,
			cs.getLocalBounds().top + 0.5f * cs.getLocalBounds().height
		)
	);

	renderWindow.draw(cs);
}
