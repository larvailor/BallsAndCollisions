#include <iostream>

#include "Circle.hpp"

class CollisionsDetector
{
private:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	////////////////////////////////////////////////

	// Abstract class
	CollisionsDetector() = delete;
	
	//-----------------------------------------------
	//		Helpers
	//

	static inline Length distanceBetweenPoints(Point sourcePoint, Point destPoint);

	//-----------------------------------------------
	//		Collisions
	//

	static bool detectCircleToCircleCollision(std::shared_ptr<Circle>& sourceCircle, std::shared_ptr<Circle>& destCircle);
	static bool pointInsideCircle(Point& point, std::shared_ptr<Circle>& figure);

public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Collisions
	//

	static bool detectCollision(std::shared_ptr<BaseFigure>& sourceFigure, std::shared_ptr<BaseFigure>& destFigure);
	static bool pointInside(Point point, std::shared_ptr<BaseFigure>& figure);
};
