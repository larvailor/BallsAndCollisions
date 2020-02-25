#include "Collisions.hpp"

/////////////////////////////////////////////////
// 
//		PRIVATE METHODS
//
/////////////////////////////////////////////////

//-----------------------------------------------
//		Helpers
//

Length CollisionsDetector::distanceBetweenPoints(Point sourcePoint, Point destPoint)
{
	return (Length)sqrt((sourcePoint.x - destPoint.x) * (sourcePoint.x - destPoint.x) + (sourcePoint.y - destPoint.y) * (sourcePoint.y - destPoint.y));
}



//-----------------------------------------------
//		Collisions
//

bool CollisionsDetector::detectCircleToCircleCollision(std::shared_ptr<Circle>& sourceCircle, std::shared_ptr<Circle>& destCircle)
{
	return distanceBetweenPoints(sourceCircle->getCenter(), destCircle->getCenter()) <= sourceCircle->getRadius() + sourceCircle->getRadius();
}

bool CollisionsDetector::pointInsideCircle(Point& point, std::shared_ptr<Circle>& figure)
{
	return distanceBetweenPoints(point, figure->getCenter()) <= figure->getRadius();
}



/////////////////////////////////////////////////
// 
//		PUBLIC METHODS
//
/////////////////////////////////////////////////

//-----------------------------------------------
//		Collisions
//

bool CollisionsDetector::detectCollision(std::shared_ptr<BaseFigure>& sourceFigure, std::shared_ptr<BaseFigure>& destFigure)
{
	if (sourceFigure->getFigureType() == FigureType::CIRCLE && destFigure->getFigureType() == FigureType::CIRCLE)
	{
		auto sourceCircle = std::dynamic_pointer_cast<Circle>(sourceFigure);
		auto destCircle = std::dynamic_pointer_cast<Circle>(destFigure);
		return detectCircleToCircleCollision(sourceCircle, destCircle);
	}
}

bool CollisionsDetector::pointInside(Point point, std::shared_ptr<BaseFigure>& figure)
{
	if (figure->getFigureType() == FigureType::CIRCLE)
	{
		auto circle = std::dynamic_pointer_cast<Circle>(figure);
		return pointInsideCircle(point, circle);
	}
}
