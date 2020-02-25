#pragma once

#include <vector>

#include "Circle.hpp"
#include "Collisions.hpp"

class Simulation
{
private:
	/////////////////////////////////////////////////
	// 
	//		VARIABLES
	//
	/////////////////////////////////////////////////

	unsigned m_fieldWidth;
	unsigned m_fieldHeight;

	std::vector<std::shared_ptr<BaseFigure>> m_figures;

	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Initialization
	//

	void randomizeFigures(unsigned figuresCount);
	void randomizeCircle();

public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Constructors
	//

	Simulation(unsigned fieldWidth, unsigned fieldHeight, unsigned figuresCount);

	//-----------------------------------------------
	//		Accessors
	//

		// Getters

	std::vector<std::shared_ptr<BaseFigure>> getFigures() const;

};
