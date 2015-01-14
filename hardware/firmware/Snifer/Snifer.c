	#define F_CPU 16000000L					/* CPU frequency */

	#include "includes.h"	
//-----------------------------------------------------------------------------------------------------------------------
void chek(void){
	while (_deviceQ_Is_Reset!=1);  
	_deviceQ_Is_Reset =2;
	OwClient_check_Ram_CMD(OwClient_read_byte());
	if (_deviceQ_Is_Reset==2) 
		OwClient_check_Rom_CMD(OwClient_read_byte());
	};



int main(void){
	MainInit();
	_deviceQ_Is_Reset = 0;
	while (1){
		chek();
		}
	}

