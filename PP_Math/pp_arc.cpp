#include "stdlib.h"
#include "pp_arc.h"




double arcImplicitFunction(double X, double Y, double R, unsigned int unit){

			double x=X/pow_pp(10, unit);
			double y=Y/pow_pp(10, unit);
			double r=R/pow_pp(10, unit);
	
			return (fpow_pp(y, 2)+fpow_pp(x, 2)-fpow_pp(r, 2))*pow_pp(10, unit);
}


unsigned int calculateNrOfStepCircle(PPpointXY<int> &endCirclePoint, PPpointXY<int> &circleCenterPoint, PPpointXY<int> &startCirclePoint, unsigned int precisionX, unsigned int precisionY, unsigned int unit, int turnCircle){
			unsigned int il_krok=0;
			PPpointXY<int> pointBegin, pointEnd, pointTest;

			pointBegin=startCirclePoint-circleCenterPoint;
			pointTest=pointBegin;
			pointEnd=endCirclePoint-circleCenterPoint;
			
			int R=sqrt(fpow_pp(static_cast<double>(pointBegin.x)/pow_pp(10, unit), 2)+fpow_pp(static_cast<double>(pointBegin.y)/pow_pp(10, unit), 2))*pow_pp(10, unit);
	
	
			while(pointTest!=pointEnd){
				pointTest=getNextStepPointOnArc(pointTest, R, precisionX, precisionY, unit, turnCircle);
		
				il_krok++;
				if(pointTest==pointBegin){
					il_krok=0;
					break;	//jeżeli okrąg jest źle zapisany i w trakcie obliczania ilości kroków wrócimy do tego samego miejsca to nie wykonuj łuku
				}
			};


			return il_krok;
}

	PPpointXY<int> getRealEndPointOfArc(PPpointXY<int> &endCirclePoint, PPpointXY<int> &circleCenterPoint, PPpointXY<int> &startCirclePoint, unsigned int precisionX, unsigned int precisionY, unsigned int unit, int turnCircle){
			double minDistance=0x1FFFFFFF, distance=0;
			PPpointXY<int> pointEndReal, pointBegin, pointEnd, pointTest, vectorToEndPoint;
				
			pointBegin=startCirclePoint-circleCenterPoint;
			pointTest=pointBegin;
			pointEnd=endCirclePoint-circleCenterPoint;
			pointEndReal=pointBegin;
			
			int R=sqrt(fpow_pp(static_cast<double>(pointBegin.x)/pow_pp(10, unit), 2)+fpow_pp(static_cast<double>(pointBegin.y)/pow_pp(10, unit), 2))*pow_pp(10, unit);

			do{
				pointTest=getNextStepPointOnArc(pointTest, R, precisionX, precisionY, unit, turnCircle);
		
					vectorToEndPoint=pointEnd-pointTest;
					distance=sqrt(pow(vectorToEndPoint.x, 2)+pow(vectorToEndPoint.y, 2));
					if(distance<minDistance){
						pointEndReal=pointTest;
						minDistance=distance;
					}

			}while(pointTest!=pointBegin);
			
			pointEndReal+=circleCenterPoint;
			
			return pointEndReal;
			

}


PPpointXY<int> getNextStepPointOnArc(PPpointXY<int> pointTest, unsigned int radius, unsigned int precisionX, unsigned int precisionY, unsigned int unit, int turnCircle){
	
				double halfPrecisionX, halfPrecisionY;
	
				halfPrecisionX=(double)precisionX/2;
				halfPrecisionY=(double)precisionY/2;
	
				if(turnCircle==CLOCKWISE){
					if(pointTest.y>0 && pointTest.x>=0 && pointTest.x<pointTest.y){												//opis II oktetu	
						pointTest.x+=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y-halfPrecisionY, radius, unit)>=0){
							pointTest.y-=precisionY; 
						}
					}else if(pointTest.y>0 && pointTest.x<0 && fabs_pp(pointTest.x)<=pointTest.y){					//opis III oktetu
						pointTest.x+=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y+halfPrecisionY, radius, unit)<=0)pointTest.y+=precisionY;
					}else if(pointTest.y<0 && pointTest.x<=0 && fabs_pp(pointTest.x)<fabs_pp(pointTest.y)){	//opis VI oktetu
						pointTest.x-=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y+halfPrecisionY, radius, unit)>=0)pointTest.y+=precisionY;
					}else if(pointTest.y<0 && pointTest.x>0 && pointTest.x<=fabs_pp(pointTest.y)){				//opis VII oktetu
						pointTest.x-=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y-halfPrecisionY, radius, unit)<=0)pointTest.y-=precisionY; 
					}
					else if(pointTest.y>0 && pointTest.x>0 && pointTest.x>=pointTest.y){									//opis I oktetu	
						pointTest.y-=precisionY;
						if(arcImplicitFunction((double)pointTest.x+halfPrecisionX, pointTest.y, radius, unit)<=0)pointTest.x+=precisionX;
					}else if(pointTest.y<=0 && pointTest.x>0 && pointTest.x>fabs_pp(pointTest.y)){					//opis VIII oktetu
						pointTest.y-=precisionY;
						if(arcImplicitFunction((double)pointTest.x-halfPrecisionX, pointTest.y, radius, unit)>=0)pointTest.x-=precisionX;
					}else if(pointTest.y>=0 && pointTest.x<0 && fabs_pp(pointTest.x)>pointTest.y){					//opis IV oktetu
						pointTest.y+=precisionY;
						if(arcImplicitFunction((double)pointTest.x+halfPrecisionX, pointTest.y, radius, unit)>=0)pointTest.x+=precisionX;
					}else if(pointTest.y<0 && pointTest.x<0 && fabs_pp(pointTest.x)>=fabs_pp(pointTest.y)){	//opis V oktetu
						pointTest.y+=precisionY;
						if(arcImplicitFunction((double)pointTest.x-halfPrecisionX, pointTest.y, radius, unit)<=0)pointTest.x-=precisionX;
					}
				}else{
					if(pointTest.y>0 && pointTest.x>0 && pointTest.x<=pointTest.y){												//opis II oktetu	
						pointTest.x-=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y+halfPrecisionY, radius, unit)<=0)pointTest.y+=precisionY;
					}else if(pointTest.y>0 && pointTest.x<=0 && fabs_pp(pointTest.x)<pointTest.y){					//opis III oktetu
						pointTest.x-=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y-halfPrecisionY, radius, unit)>=0)pointTest.y-=precisionY; 
					}else if(pointTest.y<0 && pointTest.x<0 && fabs_pp(pointTest.x)<=fabs_pp(pointTest.y)){	//opis VI oktetu
						pointTest.x+=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y-halfPrecisionY, radius, unit)<=0)pointTest.y-=precisionY;
					}else if(pointTest.y<0 && pointTest.x>=0 && pointTest.x<fabs_pp(pointTest.y)){				//opis VII oktetu
						pointTest.x+=precisionX;
						if(arcImplicitFunction(pointTest.x, (double)pointTest.y+halfPrecisionY, radius, unit)>=0)pointTest.y+=precisionY;
					}
					else if(pointTest.y>=0 && pointTest.x>0 && pointTest.x>pointTest.y){									//opis I oktetu	
						pointTest.y+=precisionY;
						if(arcImplicitFunction((double)pointTest.x-halfPrecisionX, pointTest.y, radius, unit)>=0)pointTest.x-=precisionX;
					}else if(pointTest.y<0 && pointTest.x>0 && pointTest.x>=fabs_pp(pointTest.y)){					//opis VIII oktetu
						pointTest.y+=precisionY;
						if(arcImplicitFunction((double)pointTest.x+halfPrecisionX, pointTest.y, radius, unit)<=0)pointTest.x+=precisionX;
					}else if(pointTest.y>0 && pointTest.x<0 && fabs_pp(pointTest.x)>=pointTest.y){					//opis IV oktetu
						pointTest.y-=precisionY;
						if(arcImplicitFunction((double)pointTest.x-halfPrecisionX, pointTest.y, radius, unit)<=0)pointTest.x-=precisionX;
					}else if(pointTest.y<=0 && pointTest.x<0 && fabs_pp(pointTest.x)>fabs_pp(pointTest.y)){	//opis V oktetu
						pointTest.y-=precisionY;
						if(arcImplicitFunction((double)pointTest.x+halfPrecisionX, pointTest.y, radius, unit)>=0)pointTest.x+=precisionX;
					}
				}
	
			return pointTest;
}
