#include <cmath>

#include "pp_prog_gcode_resolver_strategy.h"
#include "pp_text_stream.h"
#include "pp_math.h"

InterpretProgErr PProgGcodeResolverStrategy::interpretProg(){
	      InterpretProgErr  ans=InterpretProgErr::idNO_ERRORS;

	      if(!sourceFile->isOpen()){
					if (!sourceFile->open(PIOdevice::ReadOnly))return InterpretProgErr::idNO_FILES; 
        }else{
					sourceFile->seek(0);
				}
	
        if(!destDevice->isOpen()){
					if (!destDevice->open(PIOdevice::WriteOnly))return InterpretProgErr::idNO_FILES; 
        }else{
					destDevice->seek(0);
				}


				resetInterpretSettings();
				
        PTextStream outDevice(destDevice);
				PString line;
				int repetitions=0;

        line = sourceFile->readLine();
        if(!line.empty()){
            if(line.at(0)=='%'){
                outDevice<<(START_PROG<<10)<<"\r\n";  //zapisanie do pamięci flash znaku określającego początek programu

                line = sourceFile->readLine();
                while(!line.empty()){											//pobieranie programu linijka po linijce z karty SD
                    if(line.at(0)=='%'){
                        outDevice<<(START_PROG<<10)<<" \r\n";			//zapisanie do pamięci flash znaku określającego koniec programu
                        break;
                    }
                    interpretGcode(line);
                    interpretMcode(line);
										
										
										repetitions=0;

										if(GcodeStandardCycle==G81){
											unsigned int nr_Gkod=line.findValueAfterAcronim('G', GKOD_NIEINTERPRETOWANY);
											
											if(nr_Gkod==G80){
												repetitions=G81nrOfRepetitions;
												GcodeStandardCycle=0;
											}else{
												repetitionsList.push_back(line);
											}
											
										}else{
											repetitionsList.clear();
											repetitionsList.push_back(line);
											repetitions=1;
										}
									
										for(int k=0; k<repetitions; k++){
											for(auto it=repetitionsList.begin(); it!=repetitionsList.end(); it++){
												
												interpretGcode(*it);
												interpretMcode(*it);
													
											}
										}					
									
										
                    line = sourceFile->readLine();
                }

                if(line.at(0)!='%'){
                    ans=InterpretProgErr::idLACK_MODULO;
                }else if(!basePoint.axes.empty()){
                    ans=InterpretProgErr::idLACK_G50_G59;
                }
            }else{
                ans=InterpretProgErr::idLACK_MODULO;
            }
        }else{
            ans=InterpretProgErr::idLACK_MODULO;
        }
        sourceFile->close();
        destDevice->close();

        return ans;
}


void PProgGcodeResolverStrategy::resetInterpretSettings(){

				G00occured=false;
        writeInAboluteValues=false;
        GcodeStandardCycle=0;
        G81nrOfRepetitions=0;

				basePoint.axes.clear();
				startPoint.axes.clear();
				endPoint.axes.clear();

}

void PProgGcodeResolverStrategy::interpretGcode(PString &program){
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

						}else if(nr_Gkod>=54 && nr_Gkod<=58 && basePoint.axes.empty()){
							int idBPoint=nr_Gkod-54;
							basePoint=basePointsList->at(idBPoint);
							endPoint=basePoint;
            }else if(!basePoint.axes.empty()){

										if(nr_Gkod!=G00 && nr_Gkod!=G01 && G00occured==false){
											G00occured=true;
											startPoint=basePoint;
											writeG00Line(basePoint);
										}
										
										if(nr_Gkod==G81){						//cykl standardowy wykonywania serii gniazd
                        GcodeStandardCycle=G81;
                        repetitionsList.clear();
                        G81nrOfRepetitions=data.findValueAfterAcronim('L', 0);
                        G81nrOfRepetitions=trimToRange(G81nrOfRepetitions, 100, 0);

                    }else if(nr_Gkod==G00 || nr_Gkod==G01){	
												auto point=endPoint;
											
                        if(writeInAboluteValues==false)point.setAxesByZero();
												point.setAxesBasedString(data);

                        if(writeInAboluteValues){
													endPoint=basePoint+point;
                        }else{
													endPoint+=point;		
                        }
												
												writeG00Line(endPoint);

												if(G00occured==false){
													G00occured=true;
													startPoint=endPoint;
												}
                    }else if(nr_Gkod==G02 || nr_Gkod==G03){	//interpolacja po łuku
												PPpointXY<double>startCirclePoint(endPoint);
												PPpointXY<double>endCirclePoint;
												PPpointXY<double>circleCenterPoint;
											
												endCirclePoint.x=data.findValueAfterAcronim('X', 0);
												endCirclePoint.y=data.findValueAfterAcronim('Y', 0);
												if(writeInAboluteValues){
													endCirclePoint+=basePoint;
                        }else{
													endCirclePoint+=startCirclePoint;		
                        }
												circleCenterPoint.x=data.findValueAfterAcronim('I', 0);
												circleCenterPoint.y=data.findValueAfterAcronim('J', 0);
												circleCenterPoint+=startCirclePoint;		
											
												
												startCirclePoint.roundX(static_cast<double>(phyCoord->getParamPrecision('X'))/pow(10, phyCoord->getParamUnit('X')));
												startCirclePoint.roundY(static_cast<double>(phyCoord->getParamPrecision('Y'))/pow(10, phyCoord->getParamUnit('Y')));
												
												endCirclePoint.roundX(static_cast<double>(phyCoord->getParamPrecision('X'))/pow(10, phyCoord->getParamUnit('X')));
												endCirclePoint.roundY(static_cast<double>(phyCoord->getParamPrecision('Y'))/pow(10, phyCoord->getParamUnit('Y')));
												
												circleCenterPoint.roundX(static_cast<double>(phyCoord->getParamPrecision('X'))/pow(10, phyCoord->getParamUnit('X')));
												circleCenterPoint.roundY(static_cast<double>(phyCoord->getParamPrecision('Y'))/pow(10, phyCoord->getParamUnit('Y')));
												
                        endCirclePoint=getRealEndPointOfArc(circleCenterPoint, startCirclePoint, endCirclePoint, (nr_Gkod==G02)?CLOCKWISE:COUNTERCLOCKWISE);
												
												endPoint.setAxValue('X', endCirclePoint.x);
												endPoint.setAxValue('Y', endCirclePoint.y);
												endPoint.setAxValue('U', endCirclePoint.x);
												endPoint.setAxValue('V', endCirclePoint.y);
												
												out<<((G_KOD<<10) | nr_Gkod)<<" ";
												if(phyCoord->exists('X') && endPoint.exists('X'))out<<phyCoord->getParam('X').front()->correctData(endPoint.axes.find('X')->second*pow(10, phyCoord->getParamUnit('X')))<<" "; else out<<0<<" ";
												if(phyCoord->exists('Y') && endPoint.exists('Y'))out<<phyCoord->getParam('Y').front()->correctData(endPoint.axes.find('Y')->second*pow(10, phyCoord->getParamUnit('Y')))<<" "; else out<<0<<" ";
												if(phyCoord->exists('Z') && endPoint.exists('Z'))out<<phyCoord->getParam('Z').front()->correctData(endPoint.axes.find('Z')->second*pow(10, phyCoord->getParamUnit('Z')))<<" "; else out<<0<<" ";
												if(phyCoord->exists('X'))out<<phyCoord->getParam('X').front()->correctData(circleCenterPoint.x*pow(10, phyCoord->getParamUnit('X')))<<" "; else out<<0<<" ";
												if(phyCoord->exists('Y'))out<<phyCoord->getParam('Y').front()->correctData(circleCenterPoint.y*pow(10, phyCoord->getParamUnit('Y')))<<" "; else out<<0<<" ";
												out<<"\r\n";
                    }else if(nr_Gkod==G04){	//sterowana przerwa w ruchu
                        int timeOfDelay=0;

                        timeOfDelay=data.findValueAfterAcronim('P', 0);
                        timeOfDelay=trimToRange(timeOfDelay, 3600000, 0);
                        out<<((G_KOD<<10) | nr_Gkod)<<" ";
                        out<<timeOfDelay<<" \r\n";
                    }else if(nr_Gkod==G87){	
												double drillingDepth=data.findValueAfterAcronim('z', 0);	
												double maxDistance=data.findValueAfterAcronim('s', 0);
												double departureDistance=data.findValueAfterAcronim('d', 0);

												if(endPoint.exists('z')){
														
													endPoint.axes.find('z')->second=basePoint.axes.find('z')->second-maxDistance;
													out<<((G_KOD<<10) | G87)<<" ";
													writePointParam(endPoint);
													out<<"\r\n";

													endPoint.axes.find('z')->second=basePoint.axes.find('z')->second-drillingDepth;
													writeG00Line(endPoint);

													endPoint.axes.find('z')->second=basePoint.axes.find('z')->second+departureDistance;
													writeG00Line(endPoint);

												}
                    }else if(nr_Gkod==G88){	
												double maxDistance=data.findValueAfterAcronim('s', 0);

												if(endPoint.exists('z')){
														
													endPoint.axes.find('z')->second=basePoint.axes.find('z')->second-maxDistance;
													out<<((G_KOD<<10) | G88)<<" ";
													writePointParam(endPoint);
													out<<"\r\n";

												}
                    }

            }
        }
			}

}


void PProgGcodeResolverStrategy::writeG00Line(PPpoint<double> &point){

			if(destDevice->isOpen()){
				PTextStream out(destDevice);
				out<<((G_KOD<<10) | G00)<<" ";
				writePointParam(point);
				out<<"\r\n";
			}
}

void PProgGcodeResolverStrategy::writePointParam(PPpoint<double> &point){

				PTextStream out(destDevice);
				if(phyCoord->exists('X') && point.exists('X'))out<<phyCoord->getParam('X').front()->correctData(point.axes.find('X')->second*pow(10, phyCoord->getParamUnit('X')))<<" "; else out<<0<<" ";
				if(phyCoord->exists('Y') && point.exists('Y'))out<<phyCoord->getParam('Y').front()->correctData(point.axes.find('Y')->second*pow(10, phyCoord->getParamUnit('Y')))<<" "; else out<<0<<" ";
				if(phyCoord->exists('Z') && point.exists('Z'))out<<phyCoord->getParam('Z').front()->correctData(point.axes.find('Z')->second*pow(10, phyCoord->getParamUnit('Z')))<<" "; else out<<0<<" ";
				if(phyCoord->exists('U') && point.exists('U'))out<<phyCoord->getParam('U').front()->correctData(point.axes.find('U')->second*pow(10, phyCoord->getParamUnit('U')))<<" "; else out<<0<<" ";
				if(phyCoord->exists('V') && point.exists('V'))out<<phyCoord->getParam('V').front()->correctData(point.axes.find('V')->second*pow(10, phyCoord->getParamUnit('V')))<<" "; else out<<0<<" ";
				if(phyCoord->exists('z') && point.exists('z'))out<<phyCoord->getParam('z').front()->correctData(point.axes.find('z')->second*pow(10, phyCoord->getParamUnit('z')))<<" "; else out<<0;
}

PPpointXY<int> PProgGcodeResolverStrategy::getRealEndPointOfArc(PPpointXY<int> &circleCenterPoint, PPpointXY<int> &startCirclePoint, PPpointXY<int> &endCirclePoint, int turnCircle){
            double minDistance=0x1FFFFFFF, distance=0;
						PPpointXY<int> pointEndReal, pointBegin, pointEnd, pointTest, vectorToEndPoint;
            double radius;
						double precisionX=0.01, precisionY=0.01, halfPrecisionX=0.005, halfPrecisionY=0.005;
		
						if(phyCoord->exists('X')){
							precisionX=static_cast<double>(phyCoord->getParam('X').front()->getPrecision())/pow(10, phyCoord->getParam('X').front()->getUnit());
							halfPrecisionX=precisionX/2;
						}
						if(phyCoord->exists('Y')){
							precisionY=static_cast<double>(phyCoord->getParam('Y').front()->getPrecision())/pow(10, phyCoord->getParam('Y').front()->getUnit());
							halfPrecisionY=precisionY/2;
						}
							
						pointBegin=startCirclePoint-circleCenterPoint;
						pointTest=pointBegin;
						pointEnd=endCirclePoint-circleCenterPoint;
						pointEndReal=pointBegin;

						radius=sqrt(fpow_pp(pointBegin.x, 2)+fpow_pp(pointBegin.y, 2));
	
						
            do{
                if(turnCircle==CLOCKWISE){
                    if(pointTest.y>0 && pointTest.x>=0 && pointTest.x<pointTest.y){												//opis II oktetu
                        pointTest.x+=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y-halfPrecisionY, radius)>=0)pointTest.y-=precisionY;
                    }else if(pointTest.y>0 && pointTest.x<0 && abs(pointTest.x)<=pointTest.y){					//opis III oktetu
                        pointTest.x+=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y+halfPrecisionY, radius)<=0)pointTest.y+=precisionY;
                    }else if(pointTest.y<0 && pointTest.x<=0 && abs(pointTest.x)<abs(pointTest.y)){	//opis VI oktetu
                        pointTest.x-=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y+halfPrecisionY, radius)>=0)pointTest.y+=precisionY;
                    }else if(pointTest.y<0 && pointTest.x>0 && pointTest.x<=abs(pointTest.y)){				//opis VII oktetu
                        pointTest.x-=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y-halfPrecisionY, radius)<=0)pointTest.y-=precisionY;
                    }
                    else if(pointTest.y>0 && pointTest.x>0 && pointTest.x>=pointTest.y){									//opis I oktetu
                        pointTest.y-=precisionY;
                        if(arcImplicitFunction(pointTest.x+halfPrecisionX, pointTest.y, radius)<=0)pointTest.x+=precisionX;
                    }else if(pointTest.y<=0 && pointTest.x>0 && pointTest.x>abs(pointTest.y)){					//opis VIII oktetu
                        pointTest.y-=precisionY;
                        if(arcImplicitFunction(pointTest.x-halfPrecisionX, pointTest.y, radius)>=0)pointTest.x-=precisionX;
                    }else if(pointTest.y>=0 && pointTest.x<0 && abs(pointTest.x)>pointTest.y){					//opis IV oktetu
                        pointTest.y+=precisionY;
                        if(arcImplicitFunction(pointTest.x+halfPrecisionX, pointTest.y, radius)>=0)pointTest.x+=precisionX;
                    }else if(pointTest.y<0 && pointTest.x<0 && abs(pointTest.x)>=abs(pointTest.y)){	//opis V oktetu
                        pointTest.y+=precisionY;
                        if(arcImplicitFunction(pointTest.x-halfPrecisionX, pointTest.y, radius)<=0)pointTest.x-=precisionX;
                    }
                }else{
                    if(pointTest.y>0 && pointTest.x>0 && pointTest.x<=pointTest.y){												//opis II oktetu
                        pointTest.x-=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y+halfPrecisionY, radius)<=0)pointTest.y+=precisionY;
                    }else if(pointTest.y>0 && pointTest.x<=0 && abs(pointTest.x)<pointTest.y){					//opis III oktetu
                        pointTest.x-=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y-halfPrecisionY, radius)>=0)pointTest.y-=precisionY;
                    }else if(pointTest.y<0 && pointTest.x<0 && abs(pointTest.x)<=abs(pointTest.y)){	//opis VI oktetu
                        pointTest.x+=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y-halfPrecisionY, radius)<=0)pointTest.y-=precisionY;
                    }else if(pointTest.y<0 && pointTest.x>=0 && pointTest.x<abs(pointTest.y)){				//opis VII oktetu
                        pointTest.x+=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y+halfPrecisionY, radius)>=0)pointTest.y+=precisionY;
                    }
                    else if(pointTest.y>=0 && pointTest.x>0 && pointTest.x>pointTest.y){									//opis I oktetu
                        pointTest.y+=precisionY;
                        if(arcImplicitFunction(pointTest.x-halfPrecisionX, pointTest.y, radius)>=0)pointTest.x-=precisionX;
                    }else if(pointTest.y<0 && pointTest.x>0 && pointTest.x>=abs(pointTest.y)){					//opis VIII oktetu
                        pointTest.y+=precisionY;
                        if(arcImplicitFunction(pointTest.x+halfPrecisionX, pointTest.y, radius)<=0)pointTest.x+=precisionX;
                    }else if(pointTest.y>0 && pointTest.x<0 && abs(pointTest.x)>=pointTest.y){					//opis IV oktetu
                        pointTest.y-=precisionY;
                        if(arcImplicitFunction(pointTest.x-halfPrecisionX, pointTest.y, radius)<=0)pointTest.x-=precisionX;
                    }else if(pointTest.y<=0 && pointTest.x<0 && abs(pointTest.x)>abs(pointTest.y)){	//opis V oktetu
                        pointTest.y-=precisionY;
                        if(arcImplicitFunction(pointTest.x+halfPrecisionX, pointTest.y, radius)>=0)pointTest.x+=precisionX;
                    }
                }
								
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

double PProgGcodeResolverStrategy::getNextStepPointOnArc(){
	
	            double minDistance=0x1FFFFFFF, distance=0;
						PPpointXY<double> pointEndReal, pointBegin, pointEnd, pointTest, vectorToEndPoint;
            double radius;
						double precisionX=0.01, precisionY=0.01, halfPrecisionX=0.005, halfPrecisionY=0.005;
		
						if(phyCoord->exists('X')){
							precisionX=static_cast<double>(phyCoord->getParam('X').front()->getPrecision())/pow(10, phyCoord->getParam('X').front()->getUnit());
							halfPrecisionX=precisionX/2;
						}
						if(phyCoord->exists('Y')){
							precisionY=static_cast<double>(phyCoord->getParam('Y').front()->getPrecision())/pow(10, phyCoord->getParam('Y').front()->getUnit());
							halfPrecisionY=precisionY/2;
						}
							
						pointBegin=startCirclePoint-circleCenterPoint;
						pointTest=pointBegin;
						pointEnd=endCirclePoint-circleCenterPoint;
						pointEndReal=pointBegin;

						radius=sqrt(pow(pointBegin.x, 2)+pow(pointBegin.y, 2));
	
						
            do{
                if(turnCircle==CLOCKWISE){
                    if(pointTest.y>0 && pointTest.x>=0 && pointTest.x<pointTest.y){												//opis II oktetu
                        pointTest.x+=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y-halfPrecisionY, radius)>=0)pointTest.y-=precisionY;
                    }else if(pointTest.y>0 && pointTest.x<0 && abs(pointTest.x)<=pointTest.y){					//opis III oktetu
                        pointTest.x+=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y+halfPrecisionY, radius)<=0)pointTest.y+=precisionY;
                    }else if(pointTest.y<0 && pointTest.x<=0 && abs(pointTest.x)<abs(pointTest.y)){	//opis VI oktetu
                        pointTest.x-=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y+halfPrecisionY, radius)>=0)pointTest.y+=precisionY;
                    }else if(pointTest.y<0 && pointTest.x>0 && pointTest.x<=abs(pointTest.y)){				//opis VII oktetu
                        pointTest.x-=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y-halfPrecisionY, radius)<=0)pointTest.y-=precisionY;
                    }
                    else if(pointTest.y>0 && pointTest.x>0 && pointTest.x>=pointTest.y){									//opis I oktetu
                        pointTest.y-=precisionY;
                        if(arcImplicitFunction(pointTest.x+halfPrecisionX, pointTest.y, radius)<=0)pointTest.x+=precisionX;
                    }else if(pointTest.y<=0 && pointTest.x>0 && pointTest.x>abs(pointTest.y)){					//opis VIII oktetu
                        pointTest.y-=precisionY;
                        if(arcImplicitFunction(pointTest.x-halfPrecisionX, pointTest.y, radius)>=0)pointTest.x-=precisionX;
                    }else if(pointTest.y>=0 && pointTest.x<0 && abs(pointTest.x)>pointTest.y){					//opis IV oktetu
                        pointTest.y+=precisionY;
                        if(arcImplicitFunction(pointTest.x+halfPrecisionX, pointTest.y, radius)>=0)pointTest.x+=precisionX;
                    }else if(pointTest.y<0 && pointTest.x<0 && abs(pointTest.x)>=abs(pointTest.y)){	//opis V oktetu
                        pointTest.y+=precisionY;
                        if(arcImplicitFunction(pointTest.x-halfPrecisionX, pointTest.y, radius)<=0)pointTest.x-=precisionX;
                    }
                }else{
                    if(pointTest.y>0 && pointTest.x>0 && pointTest.x<=pointTest.y){												//opis II oktetu
                        pointTest.x-=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y+halfPrecisionY, radius)<=0)pointTest.y+=precisionY;
                    }else if(pointTest.y>0 && pointTest.x<=0 && abs(pointTest.x)<pointTest.y){					//opis III oktetu
                        pointTest.x-=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y-halfPrecisionY, radius)>=0)pointTest.y-=precisionY;
                    }else if(pointTest.y<0 && pointTest.x<0 && abs(pointTest.x)<=abs(pointTest.y)){	//opis VI oktetu
                        pointTest.x+=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y-halfPrecisionY, radius)<=0)pointTest.y-=precisionY;
                    }else if(pointTest.y<0 && pointTest.x>=0 && pointTest.x<abs(pointTest.y)){				//opis VII oktetu
                        pointTest.x+=precisionX;
                        if(arcImplicitFunction(pointTest.x, pointTest.y+halfPrecisionY, radius)>=0)pointTest.y+=precisionY;
                    }
                    else if(pointTest.y>=0 && pointTest.x>0 && pointTest.x>pointTest.y){									//opis I oktetu
                        pointTest.y+=precisionY;
                        if(arcImplicitFunction(pointTest.x-halfPrecisionX, pointTest.y, radius)>=0)pointTest.x-=precisionX;
                    }else if(pointTest.y<0 && pointTest.x>0 && pointTest.x>=abs(pointTest.y)){					//opis VIII oktetu
                        pointTest.y+=precisionY;
                        if(arcImplicitFunction(pointTest.x+halfPrecisionX, pointTest.y, radius)<=0)pointTest.x+=precisionX;
                    }else if(pointTest.y>0 && pointTest.x<0 && abs(pointTest.x)>=pointTest.y){					//opis IV oktetu
                        pointTest.y-=precisionY;
                        if(arcImplicitFunction(pointTest.x-halfPrecisionX, pointTest.y, radius)<=0)pointTest.x-=precisionX;
                    }else if(pointTest.y<=0 && pointTest.x<0 && abs(pointTest.x)>abs(pointTest.y)){	//opis V oktetu
                        pointTest.y-=precisionY;
                        if(arcImplicitFunction(pointTest.x+halfPrecisionX, pointTest.y, radius)>=0)pointTest.x+=precisionX;
                    }
                }
								
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


double PProgGcodeResolverStrategy::arcImplicitFunction(double X, double Y, double R){
			double F=0;

			F=pow(Y,2)+pow(X,2)-pow(R,2);	

			return F;
}

void PProgGcodeResolverStrategy::interpretMcode(PString &program){
        int nr_Mkod=MKOD_NIEINTERPRETOWANY;
        PString data=PString(program);

			if(destDevice->isOpen()){
				PTextStream out(destDevice);
        nr_Mkod=data.findValueAfterAcronim('M', MKOD_NIEINTERPRETOWANY);

        if(nr_Mkod!=MKOD_NIEINTERPRETOWANY){
            if(nr_Mkod==0 || (nr_Mkod>=38 && nr_Mkod<=45)){
               out<<((M_KOD<<10) | nr_Mkod)<<" \r\n";
            }
        }

			}
}

int PProgGcodeResolverStrategy::trimToRange(int value, int upperLimit, int lowerLimit){
	
		if(value>=upperLimit)value=upperLimit;
    else if(value<=lowerLimit)value=lowerLimit;
	
		return value;
}