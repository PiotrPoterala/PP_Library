#include <cmath>

#include "pp_prog_wedm_gcode_resolver_strategy.h"
#include "pp_text_stream.h"
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
				PTextStream out(destDevice);

        nr_Gkod=data.findValueAfterAcronim('G', GKOD_NIEINTERPRETOWANY);

        if(nr_Gkod!=GKOD_NIEINTERPRETOWANY){
            data.erase(0, data.find("G"));

					
						if(nr_Gkod==90) writeInAboluteValues=true;	//współrzędne absolutne (bezwzględne) w aktywnym lokalnym układzie współrzędnych

						else if(nr_Gkod==91) writeInAboluteValues=false;	//Współrzędne przyrostowe (droga) od aktualnego położenia osi narzędzia.

						else if(nr_Gkod==G92){			//zmiana parametrów pracy
								int dataToWrite;
							
								out<<((G_KOD<<10) | nr_Gkod)<<" ";
							
								dataToWrite=data.findValueAfterAcronim('T', -1);
								if(dataToWrite!=-1)out<<workParams->getParam('T').front()->correctData(dataToWrite*pow_pp(10, workParams->getParamUnit('T')))<<" "; 
								else out<<dataToWrite<<" ";
								
								dataToWrite=data.findValueAfterAcronim('t', -1);
								if(dataToWrite!=-1)out<<workParams->getParam('t').front()->correctData(dataToWrite*pow_pp(10, workParams->getParamUnit('t') ))<<" "; 
								else out<<dataToWrite<<" ";
								
								dataToWrite=data.findValueAfterAcronim('P', -1);
								if(dataToWrite!=-1)out<<workParams->getParam('P').front()->correctData(dataToWrite*pow_pp(10, workParams->getParamUnit('P') ))<<" "; 
								else out<<dataToWrite<<" ";
								
								dataToWrite=data.findValueAfterAcronim('z', -1);
								if(dataToWrite!=-1)out<<workParams->getParam('z').front()->correctData(dataToWrite*pow_pp(10, workParams->getParamUnit('z') ))<<" "; 
								else out<<dataToWrite<<" ";
								
								dataToWrite=data.findValueAfterAcronim('N', -1);
								if(dataToWrite!=-1)out<<workParams->getParam('N').front()->correctData(dataToWrite*pow_pp(10, workParams->getParamUnit('N') ))<<" "; 
								else out<<dataToWrite<<" ";
								
								dataToWrite=data.findValueAfterAcronim('D', -1);
								if(dataToWrite!=-1)out<<workParams->getParam('D').front()->correctData(dataToWrite*pow_pp(10, workParams->getParamUnit('D') ))<<" "; 
								else out<<dataToWrite<<" ";
								
								dataToWrite=data.findValueAfterAcronim('f', -1);
								if(dataToWrite!=-1)out<<workParams->getParam('f').front()->correctData(dataToWrite*pow_pp(10, workParams->getParamUnit('f') ))<<" "; 
								else out<<dataToWrite<<" ";
										
								dataToWrite=data.findValueAfterAcronim('j', -1);										
								if(dataToWrite!=-1)out<<workParams->getParam('j').front()->correctData(dataToWrite*pow_pp(10, workParams->getParamUnit('j') ))<<" "; 
								else out<<dataToWrite<<" ";
							
								out<<"\r\n";

						}else if(nr_Gkod>=54 && nr_Gkod<=58 && basePoint.rGetAxes().empty()){
							int idBPoint=nr_Gkod-54;
							basePoint=basePointsList->at(idBPoint);
							endPoint=basePoint;
							
							out<<((G_KOD<<10) | G50)<<" ";
							writePointParam(basePoint);
							out<<"\r\n";
							
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
											
												auxPoint.setLimits(baseCoord->getParamLimits());
											
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
											
												endCirclePoint.setLimits(baseCoord->getParamLimits());
												circleCenterPoint.setLimits(baseCoord->getParamLimits());
												
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
												
												out<<((G_KOD<<10) | nr_Gkod)<<" ";
												out<<endPoint.getAxValue('X')<<" ";
												out<<endPoint.getAxValue('Y')<<" "; 
												out<<endPoint.getAxValue('Z')<<" "; 
												out<<circleCenterPoint.getX()<<" ";
												out<<circleCenterPoint.getY();
												out<<"\r\n";
                    }else if(nr_Gkod==G04){	//sterowana przerwa w ruchu
                        int timeOfDelay=0;

                        timeOfDelay=data.findValueAfterAcronim('P', 0);
                        timeOfDelay=trim_pp(timeOfDelay, 3600000, 0);
                        out<<((G_KOD<<10) | nr_Gkod)<<" ";
                        out<<timeOfDelay<<" \r\n";
                    }else if(nr_Gkod==G87){	
												double drillingDepth=data.findValueAfterAcronim('z', 0);	
												double maxDistance=data.findValueAfterAcronim('s', 0);
												double departureDistance=data.findValueAfterAcronim('d', 0);

												if(endPoint.exists('z') && basePoint.exists('z')){
													endPoint.setRealAxValue('z', endPoint.getRealAxValue('z')-maxDistance);
													out<<((G_KOD<<10) | G87)<<" ";
													writePointParam(endPoint);
													out<<"\r\n";

													endPoint.setRealAxValue('z', basePoint.getRealAxValue('z')-drillingDepth);
													writeG00Line(endPoint);

													endPoint.setRealAxValue('z', basePoint.getRealAxValue('z')-departureDistance);
													writeG00Line(endPoint);

												}
                    }else if(nr_Gkod==G88){					
												double maxDistance=data.findValueAfterAcronim('s', 0);

												if(endPoint.exists('z')){
													endPoint.setRealAxValue('z', endPoint.getRealAxValue('z')-maxDistance);
													out<<((G_KOD<<10) | G88)<<" ";
													writePointParam(endPoint);
													out<<"\r\n";
												}
												
												
                    }

            }
        }
			}

}



void PProgWedmGcodeResolverStrategy::writePointParam(PPpoint<int> &point){

				PTextStream out(destDevice);
				out<<point.getAxValue('X')<<" "; 
				out<<point.getAxValue('Y')<<" "; 
				out<<point.getAxValue('Z')<<" "; 
				out<<point.getAxValue('U')<<" ";
				out<<point.getAxValue('V')<<" ";
				out<<point.getAxValue('z');
}
