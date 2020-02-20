#include <vector>
#include <ctime>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

const unsigned winWidth = 1280;
const unsigned winHeight = 720;

int main()
{
	std::srand(unsigned(std::time(0)));
	
	sf::RenderWindow renderWindow(sf::VideoMode(winWidth, winHeight), "BallsAndCollisions", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

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
			case sf::Event::Closed:
				renderWindow.close();
				break;
			}
		}

		renderWindow.clear();


		renderWindow.display();
	}
	


	return 0;
}
