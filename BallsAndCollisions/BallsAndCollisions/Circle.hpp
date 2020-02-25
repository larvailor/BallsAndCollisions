#pragma once

#include "BaseFigure.hpp"

class Circle : public BaseFigure
{
private:
	/////////////////////////////////////////////////
	// 
	//		VARIABLES
	//
	/////////////////////////////////////////////////

	Point m_center;
	Radius m_radius;

public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Constructors
	//

	Circle(FigureType figureType, Point center, Radius radius, Weight weight);

	//-----------------------------------------------
	//		Destructors
	//

	~Circle();

	//-----------------------------------------------
	//		Accessors
	//

	// Getters

	Point getCenter() const;
	Radius getRadius() const;

	// Setters

	void setCenter(Point center);

};