#include <cmath>
#include <array>

#include "pp_prog_edf_resolver_strategy.h"
#include "pstring.h"
#include "pp_point.h"
#include "pp_math_ext.h"

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

				if(!basePointsList->empty()){
					basePoint=basePointsList->at(0);	
				}else{
					return InterpretProgErr::idLACK_G50_G59;
				}
				
				
    //    PTextStream outDevice(destDevice);
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
								destDevice->write(START_PROG<<10);
								destDevice->write("\r\n");
                if(changeParListIterator!=changeParList.end() && std::get<0>(*changeParListIterator)==-1){
                    interpretTextLineWithChangeParList(*changeParListIterator);	//zapisanie parametrów startowych
                    changeParListIterator++;
                }

                sourceFile->seek(xyCursor);
                line = sourceFile->readLine();
								line.trimmedRight();
                xyCursor=sourceFile->pos();
                sourceFile->seek(uvCursor);
                secondLine = sourceFile->readLine();
                uvCursor=sourceFile->pos();

                while(!secondLine.empty()){

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
													if(std::get<0>(*changeParListIterator)==blocks && std::get<1>(*changeParListIterator)==auxNrOfSegments-nrOfSegments){
															interpretTextLineWithChangeParList(*changeParListIterator);	//zapisanie parametrów startowych
															changeParListIterator++;
													}
											}

											nrOfSegments--;
											if(nrOfSegments==0){
													blocks++;
												
													if(blocks>=(nrOfBlocks/2)){
														destDevice->write(START_PROG<<10);
														destDevice->write("\r\n");
														break;
													}
												
													if(setBreak){
															setBreak=false;
														  destDevice->write((M_KOD<<10) | M00);
															destDevice->write("\r\n");
													}
											}
									}

									sourceFile->seek(xyCursor);
									line = sourceFile->readLine();
									line.trimmedRight();
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

			changeParList.clear();

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
													changeParList.push_back(EDFlinePar{-1, -1, paramsList.at(1).toInt(16), paramsList.at(2).toInt(16), paramsList.at(3).toInt(16), paramsList.at(4).toInt(16),
																														 paramsList.at(6).toInt(16), paramsList.at(7).toInt(16), paramsList.at(11).toInt(16), paramsList.at(8).toInt(16),
																														 paramsList.at(9).toInt(16), paramsList.at(10).toInt(16), paramsList.at(12).toInt(16)});
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
																			changeParList.push_back(EDFlinePar{paramsList.at(0).toInt(), paramsList.at(1).toInt()});
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
																					std::get<2>(changeParList.at(index))=paramsList.at(1).toInt(16);
																					std::get<3>(changeParList.at(index))=paramsList.at(2).toInt(16);
																					std::get<4>(changeParList.at(index))=paramsList.at(3).toInt(16);
																					std::get<5>(changeParList.at(index))=paramsList.at(4).toInt(16);
																					std::get<6>(changeParList.at(index))=paramsList.at(6).toInt(16);
																					std::get<7>(changeParList.at(index))=paramsList.at(7).toInt(16);
																					std::get<8>(changeParList.at(index))=paramsList.at(11).toInt(16);
																					std::get<9>(changeParList.at(index))=paramsList.at(8).toInt(16);
																					std::get<10>(changeParList.at(index))=paramsList.at(9).toInt(16);
																					std::get<11>(changeParList.at(index))=paramsList.at(10).toInt(16);
																					std::get<12>(changeParList.at(index))=paramsList.at(12).toInt(16);
																					
//																					changeParList.at(index)->threshOfWork=paramsList.at(1).toInt(16);
//																					changeParList.at(index)->threshOfCircuit=paramsList.at(2).toInt(16);
//																					changeParList.at(index)->timeOfImpulse=paramsList.at(3).toInt(16);
//																					changeParList.at(index)->timeOfBreak=paramsList.at(4).toInt(16);
//																					changeParList.at(index)->wireFeed=paramsList.at(6).toInt(16);
//																					changeParList.at(index)->wireTension=paramsList.at(7).toInt(16);
//																					changeParList.at(index)->feed=paramsList.at(11).toInt(16);
//																					changeParList.at(index)->toolsMask1=paramsList.at(8).toInt(16);
//																					changeParList.at(index)->toolsMask2=paramsList.at(9).toInt(16);
//																					changeParList.at(index)->toolsMask3=paramsList.at(10).toInt(16);
//																					changeParList.at(index)->funMask=paramsList.at(12).toInt(16);
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

void PProgEDFResolverStrategy::interpretTextLineWithChangeParList(EDFlinePar &linePar){
	
        if(destDevice->isOpen()){
			//		PTextStream out(destDevice);
	
					int threshOfWork;
					int threshOfCircuit;
					int timeOfImpulse;
					int timeOfBreak;
					int wireFeed;
					int wireTension;
					int feed;
					int toolsMask1;
					int toolsMask2;
					int toolsMask3;
					int funMask;
					
					
					std::tie(std::ignore, std::ignore, threshOfWork, threshOfCircuit, timeOfImpulse, timeOfBreak, wireFeed, wireTension, feed, toolsMask1, toolsMask2, toolsMask3, funMask)=linePar;
					
					destDevice->write(((G_KOD<<10) | G92));
					destDevice->write(" ");
					
					destDevice->write(getWorkParamFromParTab('T', timeOfImpulse-1));
					destDevice->write(" ");
					destDevice->write(getWorkParamFromParTab('t', timeOfBreak-1));
					destDevice->write(" ");
					destDevice->write(getWorkParamFromParTab('P', threshOfWork-1));
					destDevice->write(" ");
					destDevice->write(getWorkParamFromParTab('z', threshOfCircuit-1));
					destDevice->write(" ");
					destDevice->write(getWorkParamFromParTab('N', wireTension-1));
					destDevice->write(" ");
					destDevice->write(getWorkParamFromParTab('D', wireFeed-1));
					destDevice->write(" ");
					destDevice->write(getWorkParamFromParTab('f', feed-1));
					destDevice->write(" ");
					destDevice->write(-1);
					destDevice->write("\r\n");
					
					if(toolsMask1 & 0x1)destDevice->write((M_KOD<<10) | M40);
					else destDevice->write((M_KOD<<10) | M41);

					destDevice->write("\r\n");
					
					if(toolsMask2 & 0x1) destDevice->write((M_KOD<<10) | M44);
					else destDevice->write((M_KOD<<10) | M45);
					
					destDevice->write("\r\n");

					if(toolsMask3 & 0x4) destDevice->write((M_KOD<<10) | M42);
					else destDevice->write((M_KOD<<10) | M43);
					
					destDevice->write("\r\n");

					if(funMask==1) destDevice->write((M_KOD<<10) | M38);
					else destDevice->write((M_KOD<<10) | M39);
					
					destDevice->write("\r\n");

		}
}


int PProgEDFResolverStrategy::getWorkParamFromParTab(char acronim, int index){
				int parVal=-1;
	
				auto par=workParams->getParam(acronim);
				auto alowedValuesIt=changeParRealValueList.find(acronim);
				if(alowedValuesIt!=changeParRealValueList.end() && !alowedValuesIt->second.empty() && !par.empty()){
					index=trim_pp(index, static_cast<int>(alowedValuesIt->second.size())-1, 0);
					
					parVal=par.front()->correctData(alowedValuesIt->second.at(index)*pow_pp(10, par.front()->getUnit())); 
				}
				
				return parVal;
}


PPpoint<int> PProgEDFResolverStrategy::getPointFromTextLine(PString &program){
				PPpoint<int> endPoint{basePoint};
				
				endPoint.setRealAxValue('X', program.mid(9, 9).toDouble()/pow_pp(10,6));
				endPoint.setRealAxValue('Y', program.mid(19, 9).toDouble()/pow_pp(10,6));
				endPoint.setRealAxValue('U', program.mid(57, 9).toDouble()/pow_pp(10,6));
				endPoint.setRealAxValue('V', program.mid(67, 9).toDouble()/pow_pp(10,6));
				
//				endPoint.addAx(pair<char, int>('Y', program.mid(19, 9).toInt()));
//				endPoint.addAx(pair<char, int>('U', program.mid(58, 9).toInt()));
//				endPoint.addAx(pair<char, int>('V', program.mid(68, 9).toInt()));
//				endPoint.addAx(pair<char, int>('d', program.mid(29, 9).toInt()));
				return endPoint;
}

//int PProgEDFResolverStrategy::trimToRange(int value, int upperLimit, int lowerLimit){
//	
//		if(value>=upperLimit)value=upperLimit;
//    else if(value<=lowerLimit)value=lowerLimit;
//	
//		return value;
//}

double PProgEDFResolverStrategy::getDrillingDepthFromTextLine(PString &program){

				return program.mid(29, 9).toDouble()/pow_pp(10,6);
		
}



void PProgEDFResolverStrategy::writeG00Line(PPpoint<int> &point){

			if(destDevice->isOpen()){
		//		PTextStream out(destDevice);
				destDevice->write((G_KOD<<10) | G00);
				destDevice->write(" ");
				writePointParam(point);
				destDevice->write("\r\n");
			}
}


void PProgEDFResolverStrategy::writePointParam(PPpoint<int> &point){

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
				destDevice->write(point.getAxValue('z'));
}



void PProgWedmEDFResolverStrategy::interpretTextLineWithCoordinates(PString &program){
	
		if(destDevice->isOpen()){
				auto endPoint=getPointFromTextLine(program);
			
				writeG00Line(endPoint);
			
			}
}


void PProgDrillEDFResolverStrategy::interpretTextLineWithCoordinates(PString &program){
	
	
		if(destDevice->isOpen()){
	//			PTextStream out(destDevice);
				auto endPoint=getPointFromTextLine(program);
			
				writeG00Line(endPoint);
				if(endPoint.exists('z')){
					
				endPoint.setRealAxValue('z', endPoint.getRealAxValue('z')-20);
				destDevice->write((G_KOD<<10) | G87);
				destDevice->write(" ");
				writePointParam(endPoint);
				destDevice->write("\r\n");

				endPoint.setRealAxValue('z', basePoint.getRealAxValue('z')-getDrillingDepthFromTextLine(program));
				writeG00Line(endPoint);

				endPoint.setRealAxValue('z', basePoint.getRealAxValue('z')+2);
				writeG00Line(endPoint);
					
				}
			}
}