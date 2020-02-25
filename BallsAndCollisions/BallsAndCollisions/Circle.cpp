#include "Circle.hpp"

/////////////////////////////////////////////////
// 
//		PUBLIC METHODS
//
/////////////////////////////////////////////////

//-----------------------------------------------
//		Constructors
//

Circle::Circle(FigureType figureType, Point center, Radius radius, Weight weight) :
	BaseFigure(figureType, weight),
	m_center(center),
	m_radius(radius)
{

}



//-----------------------------------------------
//		Destructors
//

Circle::~Circle()
= default;



//-----------------------------------------------
//		Accessors
//

// Getters

Point Circle::getCenter() const
{
	return m_center;
}

Radius Circle::getRadius() const
{
	return m_radius;
}



//	Setters

void Circle::setCenter(Point center)
{
	m_center = center;
}
