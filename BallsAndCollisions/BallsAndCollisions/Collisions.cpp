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

// Detection

bool CollisionsDetector::detectCircleToCircleCollision(std::shared_ptr<Circle> sourceCircle, std::shared_ptr<Circle> destCircle)
{
	return distanceBetweenPoints(sourceCircle->getCenter(), destCircle->getCenter()) <= sourceCircle->getRadius() + destCircle->getRadius();
}

bool CollisionsDetector::pointInsideCircle(Point& point, std::shared_ptr<Circle> figure)
{
	return distanceBetweenPoints(point, figure->getCenter()) <= figure->getRadius();
}



// Handling

void CollisionsDetector::handleCircleToCircleCollision(std::shared_ptr<Circle> sourceCircle, std::shared_ptr<Circle> destCircle)
{
	auto distanceBetweenCenters = distanceBetweenPoints(sourceCircle->getCenter(), destCircle->getCenter());
	auto halfOverlap = 0.5f * static_cast<float>(distanceBetweenCenters - sourceCircle->getRadius() - destCircle->getRadius());

	sourceCircle->setCenter(
		Point(
			sourceCircle->getCenter().x - halfOverlap * (sourceCircle->getCenter().x - destCircle->getCenter().x) / static_cast<float>(distanceBetweenCenters),
			sourceCircle->getCenter().y - halfOverlap * (sourceCircle->getCenter().y - destCircle->getCenter().y) / static_cast<float>(distanceBetweenCenters)
		)
	);

	destCircle->setCenter(
		Point(
			destCircle->getCenter().x + halfOverlap * (sourceCircle->getCenter().x - destCircle->getCenter().x) / static_cast<float>(distanceBetweenCenters),
			destCircle->getCenter().y + halfOverlap * (sourceCircle->getCenter().y - destCircle->getCenter().y) / static_cast<float>(distanceBetweenCenters)
		)
	);

}



/////////////////////////////////////////////////
// 
//		PUBLIC METHODS
//
/////////////////////////////////////////////////

//-----------------------------------------------
//		Collisions
//

// Detection

bool CollisionsDetector::detectCollision(std::shared_ptr<BaseFigure>& sourceFigure, std::shared_ptr<BaseFigure>& destFigure)
{
	if (sourceFigure->getFigureType() == FigureType::CIRCLE && destFigure->getFigureType() == FigureType::CIRCLE)
	{
		return detectCircleToCircleCollision(std::dynamic_pointer_cast<Circle>(sourceFigure), std::dynamic_pointer_cast<Circle>(destFigure));
	}

	return false;
}

bool CollisionsDetector::pointInside(Point point, std::shared_ptr<BaseFigure>& figure)
{
	if (figure->getFigureType() == FigureType::CIRCLE)
	{
		return pointInsideCircle(point, std::dynamic_pointer_cast<Circle>(figure));
	}

	return false;
}



// Handling

void CollisionsDetector::handleCollision(std::shared_ptr<BaseFigure>& sourceFigure, std::shared_ptr<BaseFigure>& destFigure)
{
	if (sourceFigure->getFigureType() == FigureType::CIRCLE && destFigure->getFigureType() == FigureType::CIRCLE)
	{
		return handleCircleToCircleCollision(std::dynamic_pointer_cast<Circle>(sourceFigure), std::dynamic_pointer_cast<Circle>(destFigure));
	}
}
