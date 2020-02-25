#include "Simulation.hpp"

#include <ctime>

/////////////////////////////////////////////////
// 
//		PRIVATE METHODS
//
/////////////////////////////////////////////////

//-----------------------------------------------
//		Initialization
//


void Simulation::randomizeFigures(unsigned figuresCount)
{
	std::srand(unsigned(std::time(0)));

	for (size_t figureN = 0; figureN < figuresCount; figureN++)
	{
		switch (rand() % 1)
		{
		case 0:
			randomizeCircle();
			break;
		default:
			std::cout << "Unknown figure" << std::endl;
		}
	}
}

void Simulation::randomizeCircle()
{
	Point center{ static_cast<float>(rand() % m_fieldWidth), static_cast<float>(rand() % m_fieldHeight) };
	Radius radius = static_cast<Radius>(20 + rand() % 30);
	Weight weight = static_cast<Radius>(radius * 1.7f);

	m_figures.emplace_back(std::make_shared<Circle>(FigureType::CIRCLE, center, radius, weight));
}



/////////////////////////////////////////////////
// 
//		PUBLIC METHODS
//
/////////////////////////////////////////////////

//-----------------------------------------------
//		Constructors
//

Simulation::Simulation(unsigned fieldWidth, unsigned fieldHeight, unsigned figuresCount) :
	m_fieldWidth(fieldWidth),
	m_fieldHeight(fieldHeight)
{
	randomizeFigures(figuresCount);
}



//-----------------------------------------------
//		Accessors
//

// Getters

std::vector<std::shared_ptr<BaseFigure>> Simulation::getFigures() const
{
	return m_figures;
}
