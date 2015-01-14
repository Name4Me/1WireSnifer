	#define F_CPU 8000000L					/* CPU frequency */
	#include "includes.h"	

void chek(void){
	u08 fl = 0;
	if ((rx_buf[rx_buf[0]] == 10) && (rx_buf[rx_buf[0]-1]==13)) {
		
		USART_Transmit(1);
		USART_SendEND();
		
		if (rx_buf[1]=='?') {
			SendStr_P(StringP);
			fl = 1;
		};
//----------------------------------------------------------------------------------------------------------
		if (rx_buf[0] == 2) {								//	<--------------------------------------RESET
			USART_Transmit(DeviceQ_reset());
			USART_SendEND();
			fl = 1;
		};

//----------------------------------------------------------------------------------------------------------
		if ((rx_buf[1] == SEARCH_ROM) && (rx_buf[0] == 3)) {	//	<-----------------------------SEARCH_ROM

			USART_Transmit(DeviceQ_FIND_ALL());
			USART_SendEND();
			if (_deviceQ_find_count>0) {
				for (int n = 0; n < _deviceQ_find_count; n++) {
					for (int i = 0; i < 8; i++) {
						USART_Transmit(_deviceQ_all_rom[n][i]);
						};
					USART_SendEND();
					};
				};
				fl = 1;
			};	
//----------------------------------------------------------------------------------------------------------
		if ((rx_buf[1] == READ_ROM) && (rx_buf[0] == 3)) {	//	<-----------------------------------READ_ROM
			DeviceQ_write_byte(READ_ROM);
 			DeviceQ_read_list_array(_deviceQ_rom_array,8,1);
			for (int i = 0; i < 8; i++) USART_Transmit(_deviceQ_rom_array[i]);
			USART_SendEND();
			fl = 1;
			};
//----------------------------------------------------------------------------------------------------------
		if ((rx_buf[1] == 0x34) && (rx_buf[0] == 11)) {		//	<----------------------------------WRITE_ROM
			for (int i = 0; i < 9; i++)	DeviceQ_write_byte(rx_buf[1+i]);
			fl = 1;
			};
//----------------------------------------------------------------------------------------------------------		
		if ((rx_buf[1] == MATCH_ROM) && (rx_buf[0] == 11)) {//	<----------------------------------MATCH_ROM
			for (int i = 0; i < 9; i++)	_deviceQ_rom_array[i]=rx_buf[2+i];
			DeviceQ_MATCH_ROM_COMMAND(_deviceQ_rom_array); 
			USART_Transmit('1');
			USART_SendEND();
			fl = 1;
			};
//----------------------------------------------------------------------------------------------------------		
		if ((rx_buf[1] == 0xB4) && (rx_buf[0] == 3)) {		//	<-------------------------------Power_Status
			unsigned char ow_power_state;
			//DeviceQ_reset();
			DeviceQ_write_byte(0xB4);
			ow_power_state = DeviceQ_read_bit();
			USART_Transmit(ow_power_state);
			USART_SendEND();
			fl = 1;
			};	
//----------------------------------------------------------------------------------------------------------				
		if ((rx_buf[1] == READ_SCRATCHPAD) && (rx_buf[0] == 3)) {	//	<--------------------READ_SCRATCHPAD
			DeviceQ_write_byte(0xBE);
			DeviceQ_read_list_array(_deviceQ_ScratchPad, 9,1);					// прочитать ответ устройства на команду READ_SCRATCHPAD и записать в массив DeviceQ_ScratchPad[9]
			for (int i = 0; i < 9; i++) {
				USART_Transmit(_deviceQ_ScratchPad[i]);			
				};
			USART_SendEND();
			fl = 1;

			};
//----------------------------------------------------------------------------------------------------------				
		if ((rx_buf[1] == READ_MEMORY) && (rx_buf[0] == 5)) {	//	<--------------------READ_MEMORY
			DeviceQ_write_byte(READ_MEMORY);
			DeviceQ_write_byte(rx_buf[2]);						//Стартовый адрес
			uint8_t	n = rx_buf[3];								//Количество байт
			DeviceQ_read_list_array(data_buf,n,1);					// прочитать ответ устройства на команду READ_SCRATCHPAD и записать в массив DeviceQ_ScratchPad[9]
			for (int i = 0; i < n; i++) {
				USART_Transmit(data_buf[i]);
				};
			USART_SendEND();
			fl = 1;
			};
//----------------------------------------------------------------------------------------------------------				
		if ((rx_buf[1] == 0xAA) && (rx_buf[0] == 5)) {	//	<--------------------Flash
			DeviceQ_write_byte(0xAA);
			DeviceQ_write_byte(rx_buf[2]);						//Стартовый адрес
			uint8_t	n = rx_buf[3];								//Количество байт

			DeviceQ_read_list_array(data_buf,n,1);					// прочитать ответ устройства на команду READ_SCRATCHPAD и записать в массив DeviceQ_ScratchPad[9]
			for (int i = 0; i < n; i++) {
				USART_Transmit(data_buf[i]);
				
				};

			USART_SendEND();
			fl = 1;

			};
//----------------------------------------------------------------------------------------------------------

		if ((rx_buf[1] == WRITE_SCRATCHPAD) && (rx_buf[0] == 6)){	//	<-----------WRITE_SCRATCHPAD
 			DeviceQ_write_byte(WRITE_SCRATCHPAD); 
			for (int i = 0; i < 3; i++)	{
				DeviceQ_write_byte(rx_buf[2+i]);
				};
			fl = 1;
		};


		
		if ((!fl) & (rx_buf[0] == 3)) {
			DeviceQ_write_byte(rx_buf[1]); 	// посылаю команду 
			fl = 1;
			};




		user_flag = 0;
		rx_buf[0]=0;	
		//DeviceQ_reset();
		sei();			
		};
//					
//DeviceQ_reset();	
	};
int main(void){
	//eeprom_write_byte(1,2);
	MainInit();

	while (1){

		//			sei();
		chek();
		//_delay_ms(9);

		};	
	};
