#include "BaseFigure.hpp"

/////////////////////////////////////////////////
// 
//		PUBLIC METHODS
//
/////////////////////////////////////////////////

//-----------------------------------------------
//		Constructors
//

BaseFigure::BaseFigure(FigureType figureType, Weight weight) :
	m_figureType(figureType),
	m_weight(weight),
	m_currVelocity(0)
{

}



//-----------------------------------------------
//		Destructors
//

BaseFigure::~BaseFigure()
= default;



//-----------------------------------------------
//		Accessors
//

//	Getters


Weight BaseFigure::getWeight() const
{
	return m_weight;
}

Velocity BaseFigure::getCurrVelocity() const
{
	return m_currVelocity;
}



//	Setters

void BaseFigure::setWeight(Weight weight)
{
	m_weight = weight;
}

void BaseFigure::setCurrVelocity(Velocity velocity)
{
	m_currVelocity = velocity;
}
