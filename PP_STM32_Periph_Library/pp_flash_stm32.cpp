#include "pp_flash_stm32.h"

bool PSTM32Flash::writeAtTheEnd(int data){
		constexpr int FLASH_CR_PSIZEx32=0x200;
	
		focusReadAdress=focusWriteAdress;
		if(!atEnd()){
			FLASH->KEYR = 0x45670123;	//odblokowanie dostępu do pamieci flash
			FLASH->KEYR = 0xCDEF89AB;	

			while(FLASH->SR & FLASH_SR_BSY); 		//sprawdzenie czy flash nie jest zajety (bit BSY = 0; ustawiany sprzetowo)
			FLASH->CR=(FLASH->CR & ~FLASH_CR_PSIZE)	| FLASH_CR_PSIZEx32;	//włączenie wpisywania zmiennych 32bitowych
			FLASH->CR |= FLASH_CR_PG;					//wlaczenie zapisu do flasha (PG = 1; flash programming chosen)
			*(focusWriteAdress++)=data;
			while(FLASH->SR & FLASH_SR_BSY);	//sprawdzenie czy flash nie jest zajety
			FLASH->CR |= FLASH_CR_LOCK;					//zablokowanie dostępu do pamieci flash
			
			
			focusReadAdress=focusWriteAdress;
			return true;
		}
		return false;
}



bool PSTM32Flash::clear(){		
//To erase a sector, follow the procedure below:
//1. Check that no Flash memory operation is ongoing by checking the BSY bit in the
//FLASH_SR register
//2. Set the SER bit and select the sector out of the 7 sectors in the main memory block you
//wish to erase (SNB) in the FLASH_CR register
//3. Set the STRT bit in the FLASH_CR register
//4. Wait for the BSY bit to be cleared.
	
	seek(0);
	focusWriteAdress=focusReadAdress;
	
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
			return true;
	}
	return false;
}
