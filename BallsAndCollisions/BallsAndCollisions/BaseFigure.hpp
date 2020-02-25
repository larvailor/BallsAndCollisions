#pragma once

#include "Types.hpp"

class BaseFigure
{
protected:
	/////////////////////////////////////////////////
	// 
	//		VARIABLES
	//
	/////////////////////////////////////////////////

	Weight m_weight;
	Velocity m_currVelocity;
	FigureType m_figureType;

public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Constructors
	//

	BaseFigure(FigureType figureType, Weight weight);

	//-----------------------------------------------
	//		Destructors
	//

	virtual ~BaseFigure();

	//-----------------------------------------------
	//		Accessors
	//

		// Getters

	Weight getWeight() const;
	Velocity getCurrVelocity() const;
	FigureType getFigureType() const;

		// Setters

	void setWeight(Weight weight);
	void setCurrVelocity(Velocity velocity);
};
