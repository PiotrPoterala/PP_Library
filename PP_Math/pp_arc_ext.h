#ifndef _PP_ARC_EXT_H
	#define _PP_ARC_EXT_H

	
	#include "pp_math.h"
	#include "pp_point.h"
	
	
	enum class CircleTurn{CLOCKWISE,COUNTERCLOCKWISE};
	
	double arcImplicitFunction(double X, double Y, double R, unsigned int unit);
	
	unsigned int calculateNrOfStepCircle(PPpointXY<int> &endCirclePoint, PPpointXY<int> &circleCenterPoint, PPpointXY<int> &startCirclePoint, unsigned int precisionX, unsigned int precisionY, unsigned int unit, CircleTurn turnCircle);
	PPpointXY<int> getNextStepPointOnArc(PPpointXY<int> pointTest, unsigned int radius, unsigned int precisionX, unsigned int precisionY, unsigned int unit, CircleTurn turnCircle);
	PPpointXY<int> getRealEndPointOfArc(PPpointXY<int> &endCirclePoint, PPpointXY<int> &circleCenterPoint, PPpointXY<int> &startCirclePoint, unsigned int precisionX, unsigned int precisionY, unsigned int unit, CircleTurn turnCircle);

	
#endif
