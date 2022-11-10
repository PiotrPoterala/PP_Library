#include "stdlib.h"
#include "pp_arc_ext.h"




double arcImplicitFunction(double X, double Y, double R, unsigned int unit){

			double x=X/pow_pp(10, unit);
			double y=Y/pow_pp(10, unit);
			double r=R/pow_pp(10, unit);
	
			return (fpow_pp(y, 2)+fpow_pp(x, 2)-fpow_pp(r, 2))*pow_pp(10, unit);
}


unsigned int calculateNrOfStepCircle(PPpointXY<int> &endCirclePoint, PPpointXY<int> &circleCenterPoint, PPpointXY<int> &startCirclePoint, unsigned int precisionX, unsigned int precisionY, unsigned int unit, CircleTurn turnCircle){
			unsigned int il_krok=0;
			PPpointXY<int> pointBegin, pointEnd, pointTest;

			pointBegin=startCirclePoint-circleCenterPoint;
			pointTest=pointBegin;
			pointEnd=endCirclePoint-circleCenterPoint;
			
			int R=sqrt(fpow_pp(static_cast<double>(pointBegin.getX())/pow_pp(10, unit), 2)+fpow_pp(static_cast<double>(pointBegin.getY())/pow_pp(10, unit), 2))*pow_pp(10, unit);
	
	
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

	PPpointXY<int> getRealEndPointOfArc(PPpointXY<int> &endCirclePoint, PPpointXY<int> &circleCenterPoint, PPpointXY<int> &startCirclePoint, unsigned int precisionX, unsigned int precisionY, unsigned int unit, CircleTurn turnCircle){
			double minDistance=0x1FFFFFFF, distance=0;
			PPpointXY<int> pointEndReal, pointBegin, pointEnd, pointTest, vectorToEndPoint;
				
			pointBegin=startCirclePoint-circleCenterPoint;
			pointTest=pointBegin;
			pointEnd=endCirclePoint-circleCenterPoint;
			pointEndReal=pointBegin;
			
			int R=sqrt(fpow_pp(static_cast<double>(pointBegin.getX())/pow_pp(10, unit), 2)+fpow_pp(static_cast<double>(pointBegin.getY())/pow_pp(10, unit), 2))*pow_pp(10, unit);

			do{
				pointTest=getNextStepPointOnArc(pointTest, R, precisionX, precisionY, unit, turnCircle);
		
					vectorToEndPoint=pointEnd-pointTest;
					distance=sqrt(pow(vectorToEndPoint.getX(), 2)+pow(vectorToEndPoint.getY(), 2));
					if(distance<minDistance){
						pointEndReal=pointTest;
						minDistance=distance;
					}

			}while(pointTest!=pointBegin);
			
			pointEndReal+=circleCenterPoint;
			
			return pointEndReal;
			

}


PPpointXY<int> getNextStepPointOnArc(PPpointXY<int> pointTest, unsigned int radius, unsigned int precisionX, unsigned int precisionY, unsigned int unit, CircleTurn turnCircle){
	
				double halfPrecisionX, halfPrecisionY;
	
				halfPrecisionX=(double)precisionX/2;
				halfPrecisionY=(double)precisionY/2;
	
				if(turnCircle==CircleTurn::CLOCKWISE){
					if(pointTest.getY()>0 && pointTest.getX()>=0 && pointTest.getX()<pointTest.getY()){												//opis II oktetu	
						pointTest.setX(pointTest.getX()+precisionX);
						if(arcImplicitFunction(pointTest.getX(), (double)pointTest.getY()-halfPrecisionY, radius, unit)>=0){
							pointTest.setY(pointTest.getY()-precisionY);
						}
					}else if(pointTest.getY()>0 && pointTest.getX()<0 && fabs_pp(pointTest.getX())<=pointTest.getY()){					//opis III oktetu
						pointTest.setX(pointTest.getX()+precisionX);
						if(arcImplicitFunction(pointTest.getX(), (double)pointTest.getY()+halfPrecisionY, radius, unit)<=0)pointTest.setY(pointTest.getY()+precisionY);
					}else if(pointTest.getY()<0 && pointTest.getX()<=0 && fabs_pp(pointTest.getX())<fabs_pp(pointTest.getY())){	//opis VI oktetu
						pointTest.setX(pointTest.getX()-precisionX);
						if(arcImplicitFunction(pointTest.getX(), (double)pointTest.getY()+halfPrecisionY, radius, unit)>=0)pointTest.setY(pointTest.getY()+precisionY);
					}else if(pointTest.getY()<0 && pointTest.getX()>0 && pointTest.getX()<=fabs_pp(pointTest.getY())){				//opis VII oktetu
						pointTest.setX(pointTest.getX()-precisionX);
						if(arcImplicitFunction(pointTest.getX(), (double)pointTest.getY()-halfPrecisionY, radius, unit)<=0)pointTest.setY(pointTest.getY()-precisionY); 
					}
					else if(pointTest.getY()>0 && pointTest.getX()>0 && pointTest.getX()>=pointTest.getY()){									//opis I oktetu	
						pointTest.setY(pointTest.getY()-precisionY);
						if(arcImplicitFunction((double)pointTest.getX()+halfPrecisionX, pointTest.getY(), radius, unit)<=0)pointTest.setX(pointTest.getX()+precisionX);
					}else if(pointTest.getY()<=0 && pointTest.getX()>0 && pointTest.getX()>fabs_pp(pointTest.getY())){					//opis VIII oktetu
						pointTest.setY(pointTest.getY()-precisionY);
						if(arcImplicitFunction((double)pointTest.getX()-halfPrecisionX, pointTest.getY(), radius, unit)>=0)pointTest.setX(pointTest.getX()-precisionX);
					}else if(pointTest.getY()>=0 && pointTest.getX()<0 && fabs_pp(pointTest.getX())>pointTest.getY()){					//opis IV oktetu
						pointTest.setY(pointTest.getY()+precisionY);
						if(arcImplicitFunction((double)pointTest.getX()+halfPrecisionX, pointTest.getY(), radius, unit)>=0)pointTest.setX(pointTest.getX()+precisionX);
					}else if(pointTest.getY()<0 && pointTest.getX()<0 && fabs_pp(pointTest.getX())>=fabs_pp(pointTest.getY())){	//opis V oktetu
						pointTest.setY(pointTest.getY()+precisionY);
						if(arcImplicitFunction((double)pointTest.getX()-halfPrecisionX, pointTest.getY(), radius, unit)<=0)pointTest.setX(pointTest.getX()-precisionX);
					}
				}else{
					if(pointTest.getY()>0 && pointTest.getX()>0 && pointTest.getX()<=pointTest.getY()){												//opis II oktetu	
						pointTest.setX(pointTest.getX()-precisionX);
						if(arcImplicitFunction(pointTest.getX(), (double)pointTest.getY()+halfPrecisionY, radius, unit)<=0)pointTest.setY(pointTest.getY()+precisionY);
					}else if(pointTest.getY()>0 && pointTest.getX()<=0 && fabs_pp(pointTest.getX())<pointTest.getY()){					//opis III oktetu
						pointTest.setX(pointTest.getX()-precisionX);
						if(arcImplicitFunction(pointTest.getX(), (double)pointTest.getY()-halfPrecisionY, radius, unit)>=0)pointTest.setY(pointTest.getY()-precisionY);
					}else if(pointTest.getY()<0 && pointTest.getX()<0 && fabs_pp(pointTest.getX())<=fabs_pp(pointTest.getY())){	//opis VI oktetu
						pointTest.setX(pointTest.getX()+precisionX);
						if(arcImplicitFunction(pointTest.getX(), (double)pointTest.getY()-halfPrecisionY, radius, unit)<=0)pointTest.setY(pointTest.getY()-precisionY);
					}else if(pointTest.getY()<0 && pointTest.getX()>=0 && pointTest.getX()<fabs_pp(pointTest.getY())){				//opis VII oktetu
						pointTest.setX(pointTest.getX()+precisionX);
						if(arcImplicitFunction(pointTest.getX(), (double)pointTest.getY()+halfPrecisionY, radius, unit)>=0)pointTest.setY(pointTest.getY()+precisionY);
					}
					else if(pointTest.getY()>=0 && pointTest.getX()>0 && pointTest.getX()>pointTest.getY()){									//opis I oktetu	
						pointTest.setY(pointTest.getY()-precisionY);
						if(arcImplicitFunction((double)pointTest.getX()-halfPrecisionX, pointTest.getY(), radius, unit)>=0)pointTest.setX(pointTest.getX()-precisionX);
					}else if(pointTest.getY()<0 && pointTest.getX()>0 && pointTest.getX()>=fabs_pp(pointTest.getY())){					//opis VIII oktetu
						pointTest.setY(pointTest.getY()+precisionY);
						if(arcImplicitFunction((double)pointTest.getX()+halfPrecisionX, pointTest.getY(), radius, unit)<=0)pointTest.setX(pointTest.getX()+precisionX);
					}else if(pointTest.getY()>0 && pointTest.getX()<0 && fabs_pp(pointTest.getX())>=pointTest.getY()){					//opis IV oktetu
						pointTest.setY(pointTest.getY()+precisionY);
						if(arcImplicitFunction((double)pointTest.getX()-halfPrecisionX, pointTest.getY(), radius, unit)<=0)pointTest.setX(pointTest.getX()-precisionX);
					}else if(pointTest.getY()<=0 && pointTest.getX()<0 && fabs_pp(pointTest.getX())>fabs_pp(pointTest.getY())){	//opis V oktetu
						pointTest.setY(pointTest.getY()-precisionY);
						if(arcImplicitFunction((double)pointTest.getX()+halfPrecisionX, pointTest.getY(), radius, unit)>=0)pointTest.setX(pointTest.getX()+precisionX);
					}
				}
	
			return pointTest;
}
