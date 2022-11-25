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
				
   //     PTextStream outDevice(destDevice);
				PString line;
				int repetitions=0;

        line = sourceFile->readLine();
        if(!line.empty()){
            if(line.at(0)=='%'){
								destDevice->write(START_PROG<<10);
								destDevice->write("\r\n");

                line = sourceFile->readLine();
                while(!line.empty()){											//pobieranie programu linijka po linijce z karty SD
                    if(line.at(0)=='%'){
                        destDevice->write(START_PROG<<10);
												destDevice->write("\r\n");			//zapisanie do pamięci flash znaku określającego koniec programu
                        break;
                    }
										
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
											for(auto&& it:repetitionsList){
												
												interpretGcode(it);
												interpretMcode(it);
													
											}
										}					
									
										
                    line = sourceFile->readLine();
                }

                if(line.at(0)!='%'){
                    ans=InterpretProgErr::idLACK_MODULO;
                }else if(!basePoint.rGetAxes().empty()){
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

				basePoint.clear();

}


void PProgGcodeResolverStrategy::writeG00Line(PPpoint<int> &point){

			if(destDevice->isOpen()){
//				PTextStream out(destDevice);
//				out<<((G_KOD<<10) | G00)<<" ";
				destDevice->write((G_KOD<<10) | G00);
				destDevice->write(" ");
				writePointParam(point);
				destDevice->write("\r\n");
//				out<<"\r\n";
			}
}


void PProgGcodeResolverStrategy::interpretMcode(PString &program){
        int nr_Mkod=MKOD_NIEINTERPRETOWANY;
        PString data=PString(program);

			if(destDevice->isOpen()){
			//	PTextStream out(destDevice);
        nr_Mkod=data.findValueAfterAcronim('M', MKOD_NIEINTERPRETOWANY);

        if(nr_Mkod!=MKOD_NIEINTERPRETOWANY){
    //       out<<((M_KOD<<10) | nr_Mkod)<<" \r\n";
						destDevice->write((M_KOD<<10) | nr_Mkod);
						destDevice->write("\r\n");
        }

			}
}
