#include <cmath>
#include <array>

#include "pp_prog_edf_resolver_strategy.h"
#include "pp_text_stream.h"
#include "pstring.h"
#include "pp_point.h"


InterpretProgErr PProgEDFResolverStrategy::interpretProg(){
	InterpretProgErr  ans=InterpretProgErr::idNO_ERRORS;
        int nrOfBlocks, blocks=0;
        int nrOfSegments=0, auxNrOfSegments=0;
        int xyCursor=0, uvCursor=0;
        bool setBreak=false;


        if(getPointOfChangeParFromEDFprog()==InterpretProgErr::idNO_FILES)return InterpretProgErr::idNO_FILES;
	
				auto changeParListIterator=changeParList.begin();

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


        PTextStream outDevice(destDevice);
        PString line, secondLine;


        line = sourceFile->readLine();
        if(!line.empty()){
            nrOfBlocks=line.mid(1, 3).toInt();      //pobranie informacji o liczbie bloków
            if(!(nrOfBlocks%2)){				//liczba bloków musi być parzysta

                xyCursor=sourceFile->pos();
                uvCursor=sourceFile->pos();

                line = sourceFile->readLine();
                while(!line.empty() && blocks<(nrOfBlocks/2)+1){	//pobranie kursora początku zapisu w pliku informacji o dolnej głowicy
                    uvCursor=sourceFile->pos();
                    nrOfSegments=line.mid(0, 3).toInt(); 
                    if(nrOfSegments!=0){
                        blocks++;
                    }
                    line = sourceFile->readLine();
                }
                uvCursor-=1;    //NIE WIEM DLACZEGO TO JEST TU POTRZEBNE!!!

                nrOfSegments=0;
                blocks=0;
                outDevice<<(START_PROG<<10)<<" \r\n";     //zapisanie do pamięci flash znaku określającego początek programu
                if(changeParListIterator!=changeParList.end() && (*changeParListIterator)->block==-1){
                    interpretTextLineWithChangeParList(*(*changeParListIterator));	//zapisanie parametrów startowych
                    changeParListIterator++;
                }

                sourceFile->seek(xyCursor);
                line = sourceFile->readLine();
                xyCursor=sourceFile->pos();
                sourceFile->seek(uvCursor);
                secondLine = sourceFile->readLine();
                uvCursor=sourceFile->pos();

                while(!secondLine.empty()){
                    if(blocks>=(nrOfBlocks/2)){
                        outDevice<<(START_PROG<<10)<<" \r\n";  //zapisanie do pamięci flash znaku określającego koniec programu
                        break;
                    }

                    if(nrOfSegments==0){
                        auxNrOfSegments=line.mid(0, 3).toInt(); 
                        if(auxNrOfSegments>0){
                            nrOfSegments=auxNrOfSegments;
                            setBreak=true;
                        }else if(auxNrOfSegments<0){
                            nrOfSegments=abs(auxNrOfSegments);
                        }
                    }else{

                        line+=secondLine;
                        interpretTextLineWithCoordinates(line);
                        if(changeParListIterator!=changeParList.end()){
                            if((*changeParListIterator)->block==blocks && (*changeParListIterator)->segment==auxNrOfSegments-nrOfSegments){
                                interpretTextLineWithChangeParList(*(*changeParListIterator));	//zapisanie parametrów startowych
																changeParListIterator++;
                            }
                        }

                        nrOfSegments--;
                        if(nrOfSegments==0){
                            blocks++;
                            if(setBreak){
                                setBreak=false;
                                outDevice<<((M_KOD<<10) | M00)<<" \r\n";
                            }
                        }
                    }

                sourceFile->seek(xyCursor);
                line = sourceFile->readLine();
                xyCursor=sourceFile->pos();
                sourceFile->seek(uvCursor);
                secondLine = sourceFile->readLine();
                uvCursor=sourceFile->pos();

                }


            }else{
                ans=InterpretProgErr::idINCORRECT_NR_OF_BLOCKS;
            }
        }


        sourceFile->close();
        destDevice->close();
        return ans;
}

InterpretProgErr PProgEDFResolverStrategy::getPointOfChangeParFromEDFprog(){
	InterpretProgErr ans=InterpretProgErr::idNO_ERRORS;
	
	if(sourceFile->isOpen()){
			sourceFile->seek(0);
			PString line;
			vector<PString> paramsList;


			int numHash=0, numDolar=0, posOfChange=0;
			int numOfChange=-1;
			bool getPosOfChange=false;
			bool getStartPar=false;

					line = sourceFile->readLine();
					while(!line.empty()){
							if(line.at(0)==3) break;	//zgodnie z tablicą ASCII dec 3 = char ETX, czyli END OF TRANSMISION
							else if(line.at(0)=='#'){
									numHash++;
							}else if(line.at(0)=='$'){
									numDolar++;
							}else{
									if(numHash==1){
											paramsList=line.split(' ');
											if(paramsList.size()>=13){
													changeParList.push_back(new PEDFlinePar(-1, -1, paramsList.at(1).toInt(16), paramsList.at(2).toInt(16), paramsList.at(3).toInt(16), paramsList.at(4).toInt(16),
																														 paramsList.at(6).toInt(16), paramsList.at(7).toInt(16), paramsList.at(11).toInt(16), paramsList.at(8).toInt(16),
																														 paramsList.at(9).toInt(16), paramsList.at(10).toInt(16), paramsList.at(12).toInt(16)));
													getStartPar=true;
											}
									}else if(numDolar==1){
													if(numOfChange==-1){
															numOfChange=line.mid(0, 3).toInt(); //pobranie informacji o liczbie zmian parametrów
															if(numOfChange<=0)break;
													}else{
															if(!getPosOfChange){
																	paramsList=line.split(' ');
																	if(paramsList.size()>=2){
																			changeParList.push_back(new PEDFlinePar(paramsList.at(0).toInt(), paramsList.at(1).toInt()));
																	}
																	posOfChange++;
																	if(posOfChange>=numOfChange){
																			getPosOfChange=true;
																			posOfChange=0;
																	}
															}else{
																	if(posOfChange<numOfChange){
																			paramsList=line.split(' ');
																			if(paramsList.size()>=13){
																					int index=0;
																					if(getStartPar==true){
																							index=posOfChange+1;
																					}else{
																							index=posOfChange;
																					}
																					changeParList.at(index)->threshOfWork=paramsList.at(1).toInt(16);
																					changeParList.at(index)->threshOfCircuit=paramsList.at(2).toInt(16);
																					changeParList.at(index)->timeOfImpulse=paramsList.at(3).toInt(16);
																					changeParList.at(index)->timeOfBreak=paramsList.at(4).toInt(16);
																					changeParList.at(index)->wireFeed=paramsList.at(6).toInt(16);
																					changeParList.at(index)->wireTension=paramsList.at(7).toInt(16);
																					changeParList.at(index)->feed=paramsList.at(11).toInt(16);
																					changeParList.at(index)->toolsMask1=paramsList.at(8).toInt(16);
																					changeParList.at(index)->toolsMask2=paramsList.at(9).toInt(16);
																					changeParList.at(index)->toolsMask3=paramsList.at(10).toInt(16);
																					changeParList.at(index)->funMask=paramsList.at(12).toInt(16);
																			}
																			posOfChange++;
																	}
															}
													}
											}
									}
							line = sourceFile->readLine();
					}

				}else{
					ans=InterpretProgErr::idNO_FILES; 
				}
				
				return ans;
}

void PProgEDFResolverStrategy::interpretTextLineWithChangeParList(PEDFlinePar &linePar){
	
        if(destDevice->isOpen()){
					PTextStream out(destDevice);
					unique_ptr<PEDFlinePar> lineParWithRealValue(new PEDFlinePar());
	
					array<int, 9> threshOfWorkAllowedRealValues={10,20,30,40,50,60,70,80,90};
					array<int, 9> threshOfCircuitAllowedRealValues={10,20,30,40,50,60,70,80,90};
					array<int, 9> wireFeedAllowedRealValues={1, 2, 3, 4, 5, 6, 7, 8, 9};
					array<int, 3> wireTensionAllowedRealValues={1, 2, 3};
					array<int, 3> timeOfImpulseAllowedRealValues={4, 6, 8};
					array<int, 9> timeOfBreakAllowedRealValues={20, 40, 60, 80, 100, 120, 160, 200, 400};
					array<int, 16> feedAllowedRealValues={1, 2, 5, 7, 11, 16, 22, 32, 47, 67, 95, 137, 203, 282, 425, 567};
					
					out<<((G_KOD<<10) | G92)<<" ";
					
					if(workParams->exists('T')){
						out<<workParams->getParam('T').front()->correctData(timeOfImpulseAllowedRealValues.at(trimToRange(linePar.threshOfWork, timeOfImpulseAllowedRealValues.size(), 1)-1)* pow(10, workParams->getParamUnit('T') ))<<" "; 
					}else out<<timeOfImpulseAllowedRealValues.at(trimToRange(linePar.threshOfWork, timeOfImpulseAllowedRealValues.size(), 1)-1)<<" ";
					
					if(workParams->exists('t')){
						out<<workParams->getParam('t').front()->correctData(timeOfBreakAllowedRealValues.at(trimToRange(linePar.threshOfWork, timeOfBreakAllowedRealValues.size(), 1)-1)* pow(10, workParams->getParamUnit('t') ))<<" "; 
					}else out<<timeOfBreakAllowedRealValues.at(trimToRange(linePar.threshOfWork, timeOfBreakAllowedRealValues.size(), 1)-1)<<" ";
					
					if(workParams->exists('P')){
						out<<workParams->getParam('P').front()->correctData(threshOfWorkAllowedRealValues.at(trimToRange(linePar.threshOfWork, threshOfWorkAllowedRealValues.size(), 1)-1)* pow(10, workParams->getParamUnit('P') ))<<" "; 
					}else out<<threshOfWorkAllowedRealValues.at(trimToRange(linePar.threshOfWork, threshOfWorkAllowedRealValues.size(), 1)-1)<<" ";
					
					if(workParams->exists('z')){
						out<<workParams->getParam('z').front()->correctData(threshOfCircuitAllowedRealValues.at(trimToRange(linePar.threshOfWork, threshOfCircuitAllowedRealValues.size(), 1)-1)* pow(10, workParams->getParamUnit('z') ))<<" "; 
					}else out<<threshOfCircuitAllowedRealValues.at(trimToRange(linePar.threshOfWork, threshOfCircuitAllowedRealValues.size(), 1)-1)<<" ";
					
					if(workParams->exists('N')){
						out<<workParams->getParam('N').front()->correctData(wireTensionAllowedRealValues.at(trimToRange(linePar.threshOfWork, wireTensionAllowedRealValues.size(), 1)-1)* pow(10, workParams->getParamUnit('N') ))<<" "; 
					}else out<<wireTensionAllowedRealValues.at(trimToRange(linePar.threshOfWork, wireTensionAllowedRealValues.size(), 1)-1)<<" ";
					
					if(workParams->exists('D')){
						out<<workParams->getParam('D').front()->correctData(wireFeedAllowedRealValues.at(trimToRange(linePar.threshOfWork, wireFeedAllowedRealValues.size(), 1)-1)* pow(10, workParams->getParamUnit('D') ))<<" "; 
					}else out<<wireFeedAllowedRealValues.at(trimToRange(linePar.threshOfWork, wireFeedAllowedRealValues.size(), 1)-1)<<" ";
					
					if(workParams->exists('f')){
						out<<workParams->getParam('f').front()->correctData(feedAllowedRealValues.at(trimToRange(linePar.threshOfWork, feedAllowedRealValues.size(), 1)-1)* pow(10, workParams->getParamUnit('f') ))<<" "; 
					}else out<<feedAllowedRealValues.at(trimToRange(linePar.threshOfWork, feedAllowedRealValues.size(), 1)-1)<<" ";
					
					if(linePar.toolsMask1 & 0x1) out<<((M_KOD<<10) | M40)<<"\r\n";
					else out<<((M_KOD<<10) | M41)<<"\r\n";

					if(linePar.toolsMask2 & 0x1) out<<((M_KOD<<10) | M44)<<"\r\n";
					else out<<((M_KOD<<10) | M45)<<"\r\n";

					if(linePar.toolsMask3 & 0x4) out<<((M_KOD<<10) | M42)<<"\r\n";
					else out<<((M_KOD<<10) | M43)<<"\r\n";

					if(linePar.funMask==1) out<<((M_KOD<<10) | M38)<<"\r\n";
					else out<<((M_KOD<<10) | M39)<<"\r\n";

		}
}

PPpoint<int> PProgEDFResolverStrategy::getPointFromTextLine(PString &program){
				PPpoint<int> endPoint;
				
				endPoint.axes.insert(pair<char, int>('X', program.mid(9, 9).toInt()));
				endPoint.axes.insert(pair<char, int>('Y', program.mid(19, 9).toInt()));
				endPoint.axes.insert(pair<char, int>('U', program.mid(58, 9).toInt()));
				endPoint.axes.insert(pair<char, int>('V', program.mid(68, 9).toInt()));
				endPoint.axes.insert(pair<char, int>('d', program.mid(29, 9).toInt()));
				return endPoint;
}

int PProgEDFResolverStrategy::trimToRange(int value, int upperLimit, int lowerLimit){
	
		if(value>=upperLimit)value=upperLimit;
    else if(value<=lowerLimit)value=lowerLimit;
	
		return value;
}



void PProgWedmEDFResolverStrategy::interpretTextLineWithCoordinates(PString &program){
	
		if(destDevice->isOpen()){
				PTextStream out(destDevice);
				auto endPoint=getPointFromTextLine(program);
			
				out<<((G_KOD<<10) | G00)<<" ";
				if(phyCoord->exists('X'))out<<phyCoord->getParam('X').front()->correctData(endPoint.axes.find('X')->second*pow(10, phyCoord->getParamUnit('X')-6))<<" "; else out<<endPoint.axes.find('X')->second<<" ";
				if(phyCoord->exists('Y'))out<<phyCoord->getParam('Y').front()->correctData(endPoint.axes.find('Y')->second*pow(10, phyCoord->getParamUnit('Y')-6))<<" "; else out<<endPoint.axes.find('Y')->second<<" ";
				if(phyCoord->exists('Z'))out<<phyCoord->getParamValue('Z')<<" "; else out<<0<<" ";
				if(phyCoord->exists('U'))out<<phyCoord->getParam('U').front()->correctData(endPoint.axes.find('U')->second*pow(10, phyCoord->getParamUnit('U')-6))<<" "; else out<<endPoint.axes.find('U')->second<<" ";
				if(phyCoord->exists('V'))out<<phyCoord->getParam('V').front()->correctData(endPoint.axes.find('V')->second*pow(10, phyCoord->getParamUnit('V')-6))<<" "; else out<<endPoint.axes.find('V')->second<<" ";
				if(phyCoord->exists('z'))out<<phyCoord->getParamValue('z')<<" "; else out<<0<<" ";
        out<<"\r\n";
			}
}


void PProgDrillEDFResolverStrategy::interpretTextLineWithCoordinates(PString &program){
	
	
		if(destDevice->isOpen()){
				PTextStream out(destDevice);
				PPpoint<int> endPoint=getPointFromTextLine(program);
			
				out<<((G_KOD<<10) | G00)<<" ";		
				if(phyCoord->exists('X'))out<<phyCoord->getParam('X').front()->correctData(endPoint.axes.find('X')->second)<<" "; else out<<endPoint.axes.find('X')->second<<" ";
				if(phyCoord->exists('Y'))out<<phyCoord->getParam('Y').front()->correctData(endPoint.axes.find('Y')->second)<<" "; else out<<endPoint.axes.find('Y')->second<<" ";
				if(phyCoord->exists('Z'))out<<phyCoord->getParamValue('Z')<<" "; else out<<0<<" ";
				if(phyCoord->exists('U'))out<<phyCoord->getParam('U').front()->correctData(endPoint.axes.find('U')->second)<<" "; else out<<endPoint.axes.find('U')->second<<" ";
				if(phyCoord->exists('V'))out<<phyCoord->getParam('V').front()->correctData(endPoint.axes.find('V')->second)<<" "; else out<<endPoint.axes.find('V')->second<<" ";
				if(phyCoord->exists('z'))out<<phyCoord->getParamValue('z')<<" "; else out<<0<<" ";
        out<<"\r\n";

				out<<((G_KOD<<10) | G87)<<" ";
				if(phyCoord->exists('X'))out<<phyCoord->getParam('X').front()->correctData(endPoint.axes.find('X')->second)<<" "; else out<<endPoint.axes.find('X')->second<<" ";
				if(phyCoord->exists('Y'))out<<phyCoord->getParam('Y').front()->correctData(endPoint.axes.find('Y')->second)<<" "; else out<<endPoint.axes.find('Y')->second<<" ";
				if(phyCoord->exists('Z'))out<<phyCoord->getParamValue('Z')<<" "; else out<<0<<" ";
				if(phyCoord->exists('U'))out<<phyCoord->getParam('U').front()->correctData(endPoint.axes.find('U')->second)<<" "; else out<<endPoint.axes.find('U')->second<<" ";
				if(phyCoord->exists('V'))out<<phyCoord->getParam('V').front()->correctData(endPoint.axes.find('V')->second)<<" "; else out<<endPoint.axes.find('V')->second<<" ";
				if(phyCoord->exists('z'))out<<phyCoord->getParamValue('z')-(20*pow(10, phyCoord->getParamUnit('z')))<<" "; else out<<0<<" ";
				out<<"\r\n";

				out<<((G_KOD<<10) | G00)<<" ";		
				if(phyCoord->exists('X'))out<<phyCoord->getParam('X').front()->correctData(endPoint.axes.find('X')->second)<<" "; else out<<endPoint.axes.find('X')->second<<" ";
				if(phyCoord->exists('Y'))out<<phyCoord->getParam('Y').front()->correctData(endPoint.axes.find('Y')->second)<<" "; else out<<endPoint.axes.find('Y')->second<<" ";
				if(phyCoord->exists('Z'))out<<phyCoord->getParamValue('Z')<<" "; else out<<0<<" ";
				if(phyCoord->exists('U'))out<<phyCoord->getParam('U').front()->correctData(endPoint.axes.find('U')->second)<<" "; else out<<endPoint.axes.find('U')->second<<" ";
				if(phyCoord->exists('V'))out<<phyCoord->getParam('V').front()->correctData(endPoint.axes.find('V')->second)<<" "; else out<<endPoint.axes.find('V')->second<<" ";
				if(phyCoord->exists('z'))out<<phyCoord->getParamValue('z')-phyCoord->getParam('z').front()->correctData(endPoint.axes.find('d')->second)-(2*pow(10, phyCoord->getParamUnit('z')))<<" "; else out<<0<<" ";
				out<<"\r\n";

				out<<((G_KOD<<10) | G00)<<" ";		
				if(phyCoord->exists('X'))out<<phyCoord->getParam('X').front()->correctData(endPoint.axes.find('X')->second)<<" "; else out<<endPoint.axes.find('X')->second<<" ";
				if(phyCoord->exists('Y'))out<<phyCoord->getParam('Y').front()->correctData(endPoint.axes.find('Y')->second)<<" "; else out<<endPoint.axes.find('Y')->second<<" ";
				if(phyCoord->exists('Z'))out<<phyCoord->getParamValue('Z')<<" "; else out<<0<<" ";
				if(phyCoord->exists('U'))out<<phyCoord->getParam('U').front()->correctData(endPoint.axes.find('U')->second)<<" "; else out<<endPoint.axes.find('U')->second<<" ";
				if(phyCoord->exists('V'))out<<phyCoord->getParam('V').front()->correctData(endPoint.axes.find('V')->second)<<" "; else out<<endPoint.axes.find('V')->second<<" ";
				if(phyCoord->exists('z'))out<<phyCoord->getParamValue('z')<<" "; else out<<0<<" ";
				out<<"\r\n";

			}
}