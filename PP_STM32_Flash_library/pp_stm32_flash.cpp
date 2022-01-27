#include "pp_stm32_flash.h"

PSTM32Flash::PSTM32Flash(void){

}

PSTM32Flash::PSTM32Flash(const PSTM32Flash &other){
	
	pages.insert(pages.begin(), other.pages.begin(), other.pages.end());
	
}

PSTM32Flash::PSTM32Flash(vector<STM32FlashPage> &page){

    pages.insert(pages.begin(), page.begin(), page.end());

}

PSTM32Flash& PSTM32Flash::operator=(const PSTM32Flash &other){
	
	pages.insert(pages.begin(), other.pages.begin(), other.pages.end());
	return (*this);
	
}

bool PSTM32Flash::isOpen(){
	
	return openFlag;
	
}

int PSTM32Flash::size(){
	
	auto p=pages.begin();
	
	
	return (reinterpret_cast<unsigned int>(focusAdress)-(*p).firstAdress);
	
}

int PSTM32Flash::pos(){
	
	return position;
}

bool PSTM32Flash::atEnd(){
	
	if(pages.empty()==false){
		auto p=pages.end()-1;
		
		if(reinterpret_cast<unsigned int>(focusAdress)>=((*p).firstAdress+(*p).areaSize))return true;
		else return false;	
	}
	return true;
}



bool PSTM32Flash::open(OpenMode mode){

		seek(0);
	
		if(mode==WriteOnly){
			clear();
		}
	
		openFlag=true;
		openMode=mode;
	
		return true;
}

bool PSTM32Flash::close(){

		openFlag=false;
		return true;
}

bool PSTM32Flash::seek(int pos){
	
	auto p=pages.begin();
	
	position=pos;
	focusAdress=reinterpret_cast<unsigned int*>((*p).firstAdress);

	for(int i=0; i<pos; i++)focusAdress++;
	
	return true;
	
}

int PSTM32Flash::read(){
	return *(focusAdress++);
}


bool PSTM32Flash::write(int data){
	#define FLASH_CR_PSIZEx32		0x200
//The Flash memory programming sequence is as follows:
//1. Check that no main Flash memory operation is ongoing by checking the BSY bit in the
//FLASH_SR register.
//2. Set the PG bit in the FLASH_CR register
//3. Perform the data write operation(s) to the desired memory address (inside main
//memory block or OTP area):


			FLASH->KEYR = 0x45670123;	//odblokowanie dostępu do pamieci flash
			FLASH->KEYR = 0xCDEF89AB;	

			while(FLASH->SR & FLASH_SR_BSY); 		//sprawdzenie czy flash nie jest zajety (bit BSY = 0; ustawiany sprzetowo)
			FLASH->CR=(FLASH->CR & ~FLASH_CR_PSIZE)	| FLASH_CR_PSIZEx32;	//włączenie wpisywania zmiennych 32bitowych
			FLASH->CR |= FLASH_CR_PG;					//wlaczenie zapisu do flasha (PG = 1; flash programming chosen)
			*focusAdress=data;
			while(FLASH->SR & FLASH_SR_BSY);	//sprawdzenie czy flash nie jest zajety
			FLASH->CR |= FLASH_CR_LOCK;					//zablokowanie dostępu do pamieci flash

			focusAdress++;
			position++;
			return true;
	
}

bool PSTM32Flash::clear(){		
//To erase a sector, follow the procedure below:
//1. Check that no Flash memory operation is ongoing by checking the BSY bit in the
//FLASH_SR register
//2. Set the SER bit and select the sector out of the 7 sectors in the main memory block you
//wish to erase (SNB) in the FLASH_CR register
//3. Set the STRT bit in the FLASH_CR register
//4. Wait for the BSY bit to be cleared.
	if(pages.empty()==false){
		for(auto it=pages.begin(); it!=pages.end(); it++){
				FLASH->KEYR = 0x45670123;						//odblokowanie dostępu do pamieci flash
				FLASH->KEYR = 0xCDEF89AB;
				while(FLASH->SR & FLASH_SR_BSY); 		//sprawdzenie czy flash nie jest zajety (bit BSY = 0; ustawiany sprzetowo)
				FLASH->CR |= FLASH_CR_SER;					//ustawienie kasowania bloku(SER = 1; sector erase)
				FLASH->CR=(FLASH->CR & ~FLASH_CR_SNB) | ((*it).number<<3);  		//wybór sektora do sczyszczenia	  
				FLASH->CR |= FLASH_CR_STRT;					//zainicjowanie kasowania(STRT = 1; start)
		
				while(FLASH->SR & FLASH_SR_BSY); 		//sprawdzenie czy flash nie jest zajety
				FLASH->CR |= FLASH_CR_LOCK;					//zablokowanie dostępu do pamieci flash
			}
			seek(0);
			return true;
	}
	return false;
}
