	#define F_CPU 16000000L					/* CPU frequency */

	#include "includes.h"	
//-----------------------------------------------------------------------------------------------------------------------
void chek(void){
	while (_deviceQ_Is_Reset!=1);  
	OwClient_Present();
	_deviceQ_Is_Reset =2;
	OwClient_check_Ram_CMD(OwClient_read_byte());
	if (_deviceQ_Is_Reset==2) 
		OwClient_check_Rom_CMD(OwClient_read_byte());
	};



int main(void){
	MainInit();
	eeprom_read_block(_OwClient_rom,ERom,8);
	eeprom_read_block(_OwClient_StatusReg,EStatusReg,1);
	eeprom_read_block(_OwClient_AppReg,EAppReg,8);
	eeprom_read_block(_OwClient_ScratchPad,ERam,32);
	OwClient_Present();

	_deviceQ_Is_Reset = 0;
	while (1){
		chek();
		}
	}

