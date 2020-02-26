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

		// Detection
	
	static bool detectCircleToCircleCollision(std::shared_ptr<Circle> sourceCircle, std::shared_ptr<Circle> destCircle);
	static bool pointInsideCircle(Point& point, std::shared_ptr<Circle> figure);

		// Handling

	static void handleCircleToCircleCollision(std::shared_ptr<Circle> sourceCircle, std::shared_ptr<Circle> destCircle);

public:
	/////////////////////////////////////////////////
	// 
	//		METHODS
	//
	/////////////////////////////////////////////////

	//-----------------------------------------------
	//		Collisions
	//

		// Detection
	
	static bool detectCollision(std::shared_ptr<BaseFigure>& sourceFigure, std::shared_ptr<BaseFigure>& destFigure);
	static bool pointInside(Point point, std::shared_ptr<BaseFigure>& figure);

		// Handling

	static void handleCollision(std::shared_ptr<BaseFigure>& sourceFigure, std::shared_ptr<BaseFigure>& destFigure);
};
