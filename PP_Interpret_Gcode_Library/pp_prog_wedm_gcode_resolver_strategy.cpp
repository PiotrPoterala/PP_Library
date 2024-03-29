#include <cmath>

#include <stdexcept> 

#include "pp_prog_wedm_gcode_resolver_strategy.h"
#include "pp_math.h"
#include "pp_math_ext.h"
#include "pp_param.h"
#include "pp_arc_ext.h"

void PProgWedmGcodeResolverStrategy::resetInterpretSettings(){

				PProgGcodeResolverStrategy::resetInterpretSettings();
				endPoint.clear();

}

void PProgWedmGcodeResolverStrategy::interpretGcode(PString &program){
		int nr_Gkod=GKOD_NIEINTERPRETOWANY;
		PString data=PString(program);
	
		if(destDevice->isOpen()){
	//			PTextStream out(destDevice);

        nr_Gkod=data.findValueAfterAcronim('G', GKOD_NIEINTERPRETOWANY);

        if(nr_Gkod!=GKOD_NIEINTERPRETOWANY){
            data.erase(0, data.find("G"));

					
						if(nr_Gkod==90) writeInAboluteValues=true;	//współrzędne absolutne (bezwzględne) w aktywnym lokalnym układzie współrzędnych

						else if(nr_Gkod==91) writeInAboluteValues=false;	//Współrzędne przyrostowe (droga) od aktualnego położenia osi narzędzia.

						else if(nr_Gkod==G92){			//zmiana parametrów pracy
							
								destDevice->write(((G_KOD<<10) | nr_Gkod));
								destDevice->write(" ");
								destDevice->write(getWorkParamFromTextLine(data, 'T'));
								destDevice->write(" ");
								destDevice->write(getWorkParamFromTextLine(data, 't'));
								destDevice->write(" ");
								destDevice->write(getWorkParamFromTextLine(data, 'P'));
								destDevice->write(" ");
								destDevice->write(getWorkParamFromTextLine(data, 'z'));
								destDevice->write(" ");
								destDevice->write(getWorkParamFromTextLine(data, 'N'));
								destDevice->write(" ");
								destDevice->write(getWorkParamFromTextLine(data, 'D'));
								destDevice->write(" ");
								destDevice->write(getWorkParamFromTextLine(data, 'f'));
								destDevice->write(" ");
								destDevice->write(getWorkParamFromTextLine(data, 'j'));
								destDevice->write("\r\n");

						}else if(nr_Gkod>=54 && nr_Gkod<=58 && basePoint.rGetAxes().empty()){
							unsigned int idBPoint=nr_Gkod-54;
//							try {
							if(!basePointsList->empty() && basePointsList->size()>=idBPoint+1){
								basePoint=basePointsList->at(idBPoint);
								endPoint=basePoint;
								
								destDevice->write((G_KOD<<10) | G50);
								destDevice->write(" ");
								writePointParam(basePoint);
								destDevice->write("\r\n");
								
							}
//							}catch (const std::out_of_range& oor) {
//								printf("Out of Range error: %s", oor.what());
//							}
							
							
            }else if(!basePoint.rGetAxes().empty()){

										if(nr_Gkod!=G00 && nr_Gkod!=G01 && G00occured==false){
											G00occured=true;
											writeG00Line(basePoint);
										}
										
										if(nr_Gkod==G81 && GcodeStandardCycle!=G81){						//cykl standardowy wykonywania serii gniazd
                        GcodeStandardCycle=G81;
                        repetitionsList.clear();
                        G81nrOfRepetitions=data.findValueAfterAcronim('L', 0);
                        G81nrOfRepetitions=trim_pp(G81nrOfRepetitions, 100, 0);

                    }else if(nr_Gkod==G00 || nr_Gkod==G01){	
												auto auxPoint=endPoint;
											
												auxPoint.setLimits(baseCoord->getParamsLimits());
											
                        if(writeInAboluteValues==false)auxPoint.setAxesByZero();
												auxPoint.setAxesBasedString(data);

                        if(writeInAboluteValues){
													endPoint=basePoint+auxPoint;
                        }else{
													endPoint+=auxPoint;		
                        }
												writeG00Line(endPoint);

												G00occured=true;

                    }else if(nr_Gkod==G02 || nr_Gkod==G03){	//interpolacja po łuku
												PPpointXY<int>startCirclePoint{endPoint};
												PPpointXY<int>endCirclePoint;
												PPpointXY<int>circleCenterPoint;
											
												endCirclePoint.setLimits(baseCoord->getParamsLimits());
												circleCenterPoint.setLimits(baseCoord->getParamsLimits());
												
												endCirclePoint.setRealX(data.findValueAfterAcronim('X', 0));
												endCirclePoint.setRealY(data.findValueAfterAcronim('Y', 0));
												if(writeInAboluteValues){
													endCirclePoint+=basePoint;
                        }else{
													endCirclePoint+=startCirclePoint;		
                        }
												circleCenterPoint.setRealX(data.findValueAfterAcronim('I', 0));
												circleCenterPoint.setRealY(data.findValueAfterAcronim('J', 0));
												circleCenterPoint+=startCirclePoint;		
														
												int unitY=0, unitX=0, precisionX=1, precisionY=1;
												auto limitY=startCirclePoint.getYLimit();
												if(!limitY.empty()){
													unitY=std::get<3>(limitY.front());
													precisionY=std::get<2>(limitY.front());
												}
												
												auto limitX=startCirclePoint.getXLimit();
												if(!limitX.empty()){
													unitX=std::get<3>(limitX.front());
													precisionX=std::get<2>(limitX.front());
												}
												
                        endCirclePoint=getRealEndPointOfArc(endCirclePoint, circleCenterPoint, startCirclePoint, 
																														precisionX, precisionY,(unitX>=unitY)?unitX:unitY, (nr_Gkod==G02)?CircleTurn::CLOCKWISE:CircleTurn::COUNTERCLOCKWISE);
												
												endPoint.setAxValue('X', endCirclePoint.getX());
												endPoint.setAxValue('Y', endCirclePoint.getY());
												endPoint.setAxValue('U', endCirclePoint.getX());
												endPoint.setAxValue('V', endCirclePoint.getY());
												
												destDevice->write((G_KOD<<10) | nr_Gkod);
												destDevice->write(" ");
												destDevice->write(endPoint.getAxValue('X'));
												destDevice->write(" ");
												destDevice->write(endPoint.getAxValue('Y'));
												destDevice->write(" ");												
												destDevice->write(endPoint.getAxValue('Z'));
												destDevice->write(" ");												
												destDevice->write(circleCenterPoint.getX());
												destDevice->write(" ");
												destDevice->write(circleCenterPoint.getY());										
												destDevice->write("\r\n");
                    }else if(nr_Gkod==G04){	//sterowana przerwa w ruchu
                        int timeOfDelay=0;

                        timeOfDelay=data.findValueAfterAcronim('P', 0);
                        timeOfDelay=trim_pp(timeOfDelay, 3600000, 0);
                        destDevice->write((G_KOD<<10) | nr_Gkod);
												destDevice->write(" ");
                        destDevice->write(timeOfDelay);
												destDevice->write("\r\n");
                    }else if(nr_Gkod==G87){	
												double drillingDepth=data.findValueAfterAcronim('z', 0);	
												double maxDistance=data.findValueAfterAcronim('s', 0);
												double departureDistance=data.findValueAfterAcronim('d', 0);

												if(endPoint.exists('z') && basePoint.exists('z')){
													endPoint.setRealAxValue('z', endPoint.getRealAxValue('z')-maxDistance);
													destDevice->write((G_KOD<<10) | G87);
													destDevice->write(" ");
													writePointParam(endPoint);
													destDevice->write("\r\n");

													endPoint.setRealAxValue('z', basePoint.getRealAxValue('z')-drillingDepth);
													writeG00Line(endPoint);

													endPoint.setRealAxValue('z', basePoint.getRealAxValue('z')+departureDistance);
													writeG00Line(endPoint);

												}
                    }else if(nr_Gkod==G88){					
												double maxDistance=data.findValueAfterAcronim('s', 0);

												if(endPoint.exists('z') && basePoint.exists('z')){
													endPoint.setRealAxValue('z', endPoint.getRealAxValue('z')-maxDistance);
													destDevice->write((G_KOD<<10) | G88);
													destDevice->write(" ");
													writePointParam(endPoint);
													destDevice->write("\r\n");
													
													endPoint.setAxValue('z', basePoint.getAxValue('z'));
												}
                    }

            }
        }
			}

}



void PProgWedmGcodeResolverStrategy::writePointParam(PPpoint<int> &point){

		//		PTextStream out(destDevice);
				destDevice->write(point.getAxValue('X'));
				destDevice->write(" ");
				destDevice->write(point.getAxValue('Y'));
				destDevice->write(" ");
				destDevice->write(point.getAxValue('Z')); 
				destDevice->write(" ");
				destDevice->write(point.getAxValue('U'));
				destDevice->write(" ");
				destDevice->write(point.getAxValue('V'));
				destDevice->write(" ");
				destDevice->write(point.getAxValue('z'));;
}

int PProgWedmGcodeResolverStrategy::getWorkParamFromTextLine(PString data, char acronim){
				int parVal=-1;
	
				auto par=workParams->getParam(acronim);
				auto paramValue=data.findValueAfterAcronim(acronim, -1);
				if(paramValue!=-1 && !par.empty()){
					parVal=par.front()->correctData(paramValue*pow_pp(10, par.front()->getUnit())); 
				}
				
				return parVal;
}
