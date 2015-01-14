#define 		__1_WIRE_DRIVER_				1			//�������������� �������� ���������� (������� �������������� :))


#if defined 	_STDBOOL_H															//���� ���������� (_STDBOOL_H) ����������  - �� ���� �� ������
#else																				//���� ���������� �� ���������� ->>>
	#warning "Library not includet stdbool.h - ���������..."
	#include <stdbool.h>
#endif


#if defined 	__IO_INCLUDE_														//���� ���������� (__IO_INCLUDE_) ����������  - �� ���� �� ������
#else																				//���� ���������� �� ���������� ->>>
	#warning "Library not includet OInclude.h  - ��������� ����������� �������..."

	#define _GetbitL(port,bit) 					(!(port&(1<<bit)))
	#define _GetbitH(port,bit)					(port&(1<<bit))
	#define  GetBitL(x)							_GetbitL(x)
	#define  GetBitH(x)							_GetbitH(x)

	#define _SetBit(port,bit)					(port = port|(1<<bit))				//���������� ������� �������
	#define _ClrBit(port,bit)					(port^= port&(1<<bit))				//����� ������� �������
	#define _InvBit(port,bit)					(port = port^(1<<bit))				//������������� �������
	#define SetBit(x)							_SetBit(x)
	#define ClrBit(x)							_ClrBit(x)
	#define InvBit(x)							_InvBit(x)

 	#define _until_bit_is_set(port,bit)			loop_until_bit_is_set(port, bit)
 	#define until_bit_is_set(x)					_until_bit_is_set(x);

 	#define _until_bit_is_clear(port,bit)		loop_until_bit_is_clear(port, bit)
 	#define until_bit_is_clear(x)				_until_bit_is_clear(x);
#endif

//=======================================================================================================================
//=========================����������� ����� ��� ������ 1-wire  ����������===============================================
//=======================================================================================================================
  #define DeviceQ_IO		PIND
  #define DeviceQ_DDR		DDRD,		2			//��� ��� ������
  #define DeviceQ_PIN		PIND,		2			//��� ��� ������
  #define DeviceQ_PORT	PORTD,	2			//��� �����
  #define _deviceQ_max_count		20			//������������ ����� ��������� �� ����
  
//=======================================================================================================================
//=====================================������� �� ������ � 1 wire ����������=============================================
//=======================================================================================================================
  #define READ_ROM									0x33		//������� ��������� ��������� ���������� ���. � ����� �� ��� ������� DS18S20 �������� 8-������ ��� ��������� (10h), ����� 48-������ �������� �����, � ����� 8-������ CRC ��� �������� ������������ �������� ����������
  #define MATCH_ROM									0x55		//������� ��������� ���������� �� ���� ���������� ���������. ����� ���� ������� ������ ������ �������� ������ 64-������ ���, � ������ ��� ���������, ������� ����� ����� ���, ����� ������������� �� ���������� �������� ������
  #define SKIP_ROM									0xCC		//������� ��������� ���������� ��������� ��������� ��������� ������ � ��� ����� ���������� ����� � ��������, ��� �� ���� ������� ����� ���� ����������
  #define SEARCH_ROM								0xF0		//������� ��������� ���������� �������� ������ ���� �����������, �������������� �� ����
  #define Alarm_Search 								0xEC
//=======================================================================================================================
//=====================================������� �� ������ � DS2430A=======================================================
//=======================================================================================================================
  	
	#define READ_APP_REG						0xC3
	#define CONVERT_T							0x44
  	#define COPY_LOCK_APP_REG					0x5A
  	#define WRITE_APP_REG						0x99

  	#define READ_STATUS_REG						0x66

  	#define READ_SCRATCHPAD						0xBE		//������� ��������� ������� ������ �� �������������� ���
  	#define READ_MEMORY							0xF0
  	#define WRITE_SCRATCHPAD					0x4E		//������� ��������� �������� ������ � ������������� ���
  	#define COPY_SCRATCHPAD						0x48		//������� �������� ����� �� �������������� ��� � ����������������� ������. ��� �������� ������� ����� 10��

//=======================================================================================================================
//=======================������, ����������� ��� ������ � ����������� �� 1 wire ���������================================
//=======================================================================================================================
  volatile unsigned char _1_WIRE_ERROR= 0x00;		
													// 0x00 - ��� ���������� �� ����
  												// 0x01 - ���������� �� ����
  												// 0x02 - �������� ��������� �� �����
													// 0x03 - ��� ���������� � ����
													// 0x04 - �� ������� CRC
													// 0x05 - ������ ������ ����������
													// 0x06 - ������ ��� ������� ������� CONVERT_T
													// 0x07 - ������ ��� ������� ������� READ_SCRATCHPAD
													// 0x08 - ����������� ������ ������


//=======================================================================================================================
//================================ ��������������� �������� �� Dallas AppNote 126 =======================================
//=======================================================================================================================
 #define DeviceQ_delay_A				15
 #define DeviceQ_delay_B				170
 #define DeviceQ_delay_C				60
 #define DeviceQ_delay_D				110
 #define DeviceQ_delay_E				9
 #define DeviceQ_delay_F				145
 #define DeviceQ_delay_G				0
 #define DeviceQ_delay_H				500
 #define DeviceQ_delay_I				70
 #define DeviceQ_delay_J				1400//410


//=======================================================================================================================
//======================================== �������������� ��������� �� ����� ============================================
//=======================================================================================================================
 #define DS18S20_FAMILY_CODE 			0x10
 #define DS18B20_FAMILY_CODE 			0x28
 #define DS1822_FAMILY_CODE 			0x22
 #define DS1990_FAMILY_CODE 			0x01
 #define DS2405_FAMILY_CODE				0x05
 #define DS2430_FAMILY_CODE 			0x14
 #define DS2431_FAMILY_CODE 			0x2D
 #define DS2433_FAMILY_CODE 			0x23



//=======================================================================================================================
//=============================== ����������� ���������� ��� ������ � ����������� =======================================
//=======================================================================================================================
	u08		_deviceQ_all_rom[_deviceQ_max_count][8];					//������ �������� ������� ��������� ([_deviceQ_max_count ����], [���, �����, CRC])
	u08		_deviceQ_ScratchPad[33];
	u08		_deviceQ_rom_array[8];														//����� ����������
	u08		_deviceQ_find_count								= 0;						//���������� �������� ���������
	u08		_deviceQ_select								= 0;


	int		_deviceQ_last_discrepancy					= 0;
 	int		_deviceQ_last_family_discrepancy	= 0;
 	int		_deviceQ_last_device_flag					= 0;


//=======================================================================================================================
//================================================= ������� CRC8 ========================================================
//=======================================================================================================================
 unsigned char			crc8;																//������������� �������� CRC
 u08	dscrc_table[] PROGMEM  = {
        0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
      157,195, 33,127,252,162, 64, 30, 95,  1,227,189, 62, 96,130,220,
       35,125,159,193, 66, 28,254,160,225,191, 93,  3,128,222, 60, 98,
      190,224,  2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
       70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89,  7,
      219,133,103, 57,186,228,  6, 88, 25, 71,165,251,120, 38,196,154,
      101, 59,217,135,  4, 90,184,230,167,249, 27, 69,198,152,122, 36,
      248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91,  5,231,185,
      140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
       17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
      175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
       50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
      202,148,118, 40,171,245, 23, 73,  8, 86,180,234,105, 55,213,139,
       87,  9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
      233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
      116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53};

//=======================================================================================================================
//=================================== ��������� ��������� �� ���������� �� CRC ==========================================
//=======================================================================================================================
unsigned char docrc8(unsigned char value){
   crc8 = pgm_read_byte(dscrc_table+(crc8 ^ value));
   return crc8;
}

 
//=======================================================================================================================
//===================== ��������������� �������� � ������� ��� ������ � 1 wire ���������� ===============================
//=======================================================================================================================
	void			DeviceQ_Init();																// ������������� ���������, ���������������� � ����� ����������
	void			DeviceQ_Pullup(bool LogicVal);												// �������� ����� � + ��� ������� ������������ ��������� Dallas

	u08				DeviceQ_reset();															// ����� ����������
 	void			DeviceQ_write_1();															// ������ 1bit � ����
 	void			DeviceQ_write_0();															// ������ 0bit � ����
 	void			DeviceQ_write_bit(u08 data);										// ������ 1bit or 0bit � ����
 	void			DeviceQ_write_byte(u08 data);										// ������ 1byte � ����
 	u08				DeviceQ_read_bit();															// ������ 1bit �� �����
 	u08				DeviceQ_read_byte();														// ������ 1byte �� �����
 	u08				DeviceQ_read_list_array(u08 * array, u08 i, bool LogicVal);// ��������� ������ (��������, ���������� ����������� ����, 1:����/0:�������� ������������������ ���������� �������)

 	void			DeviceQ_READ_ROM_COMMAND(void);
 	void			DeviceQ_MATCH_ROM_COMMAND(u08 * array_rom);
 	int				DeviceQ_SEARCH_ROM_COMMAND(void);
 	u08				DeviceQ_SKIP_ROM_COMMAND(void);
 	void			DeviceQ_COPY_SCARTCHPAD_COMMAND(void);
 	void			DeviceQ_WRITE_SCARTCHPAD_COMMAND(u08 TH, u08 TL);
 	void			DeviceQ_READ_SCARTCHPAD_COMMAND(u08 * _ScratchPad);

 	int				DeviceQ_First();															// ����� ������� ���������� �� ���� (TRUE: ���� ���������� FALSE: ��� ���������)
 	int				DeviceQ_Next();																// ����� ���������� ���������� �� ���� (TRUE: ���� ���������� FALSE: ��� ���������)
 	int				DeviceQ_Verify();															// �������� ���������� ���������� �� ����
 	void			DeviceQ_TargetSetup(u08 family_code);								// ����� �� ���� ���������� �� ����
 	void			DeviceQ_FamilySkipSetup();													// ���������� �������� ���������� �� ����
 	int				DeviceQ_FIND_ALL(void);														// ����� ��� ���������� �� ����
 	int 			DeviceQ_FIND_DEVICE_CODE(u08 QDevice_code);						// ����� ��������� �� ������
 	int 			DeviceQ_FIND_DEVICE_EXCEPTION_CODE(void);									// ������ ���������� �� �����������....
	void 			DeviceQ_Read_ScratchPad(unsigned char Num_QDevice);

 	u08				docrc8(u08 value);												// �������� CRC8



//=======================================================================================================================
//=============================��������� ���������� ����������� ����� ��� ����������=====================================
//=======================================================================================================================
void DeviceQ_Init(void){
//	cli();
	DeviceQ_Pullup(1);								// ��� ������� ������������ ���������� �� �����
//	DeviceQ_reset();
//	sei();
	}

//=======================================================================================================================
//================================== �������� ��������� ����� ��� ������� ����������=====================================
//=======================================================================================================================
void DeviceQ_Pullup(bool A){
 if (A) {ClrBit(DeviceQ_PORT);	NOP;
	 	 ClrBit(DeviceQ_DDR);	NOP;}				// ��� ������� ������������ ���������� �� �����}
 else 	{ClrBit(DeviceQ_PORT);	NOP;
		 SetBit(DeviceQ_DDR);	NOP;}				// �������� �������� RESET}
}


//=======================================================================================================================
//=========== ������� DeviceQ__RESET -> ���������� ���� 1-Wire � ���������� ������� ������������ ���������.==============
//================= ������ ������ ������ ���� ������� ������� 480 ���. ������ ���� 960 ������� ==========================
//=======================================================================================================================
unsigned char DeviceQ_reset(void){
cli();
	_1_WIRE_ERROR = 0x00;							// ��� ���������� �� ����

	DeviceQ_Pullup(1);								// ��� ������� ������������ ���������� �� �����


	_delay_us(DeviceQ_delay_G);
	DeviceQ_Pullup(0);								// �������� �������� RESET
	_delay_us(DeviceQ_delay_H);						// �������� 480us �� Datasheet
	DeviceQ_Pullup(1);								// ��� ������� ������������ ���������� �� �����
	_delay_us(DeviceQ_delay_I);						// ����� ������� ��� ������ "PRESENCE" �� 1-wire ���������� 

	if (GetBitL(DeviceQ_PIN))						// ���� �� ����� ���������� 0 -> (���������� ������ �������� �� ����� ���� �� 240us) ������� PRESENCE
		_1_WIRE_ERROR = 0x01;						// �� ��������������� ������ �� ����� ���� ���������� (������ ���)

	_delay_us(DeviceQ_delay_J);						// ���� ��������� ���������� ���������� (420us) �� Datasheet ��� �������� 1-wire ���������� � ������� ����� � ����� �����������, ��� ��� �� ��������� �� �����. 

 if (GetBitL(DeviceQ_PIN))							// ���� �� ����� ���������� 0 ����� �������� ������ �� Datasheets -> 
	_1_WIRE_ERROR = 0x02;							// err ��� ���������� �� ���� ��� ��������� �� �����

//	USART_Transmit(_1_WIRE_ERROR);
//	USART_SendEND();

 return _1_WIRE_ERROR;
sei();
}


//=======================================================================================================================
//========================================== WRITE_BIT -> ������ 1 � ���� ==================================================
//=======================================================================================================================
void DeviceQ_write_1(void){

  	DeviceQ_Pullup(0);
		_delay_us(DeviceQ_delay_A);
	DeviceQ_Pullup(1);
		_delay_us(DeviceQ_delay_B);
}


//=======================================================================================================================
//========================================== WRITE_BIT -> ������ 0 � ���� ==================================================
//=======================================================================================================================
void DeviceQ_write_0(void){

 	DeviceQ_Pullup(0);
		_delay_us(DeviceQ_delay_C);
	DeviceQ_Pullup(1);
		_delay_us(DeviceQ_delay_D);
}


//=======================================================================================================================
//================================== WRITE_BIT -> ������ ���� � ����.====================================================
//=======================================================================================================================
void DeviceQ_write_bit(unsigned char data){
cli();
  if (data !=0)		DeviceQ_write_1();				// ������� ��������� ��� ������� � ��������
  else				DeviceQ_write_0();
sei();
}


//=======================================================================================================================
//=================================WRITE_BYTE -> ������ ����� � ����.====================================================
//=======================================================================================================================
void DeviceQ_write_byte(unsigned char data){
cli();
 char count = 8;									// ��������� ������� ���
 do{												// ���� ������ ��� �� ����
  if (data & 0x01) 	DeviceQ_write_1();				// ������� ��������� ��� ������� � ��������
  else				DeviceQ_write_0();
  data >>= 1;										// �������� ������ ������ � ��������� ��������� �����
 }while(--count);
sei();
}


//=======================================================================================================================
//=================================READ_BIT -> ������ ���� �� ����.======================================================
//=======================================================================================================================
unsigned char DeviceQ_read_bit(void){
cli();
 unsigned char result = 0x00;
	DeviceQ_Pullup(0);								// ���������� ����� � 0

	_delay_us(DeviceQ_delay_A);						// �������� 15us 
	DeviceQ_Pullup(1);								// ���������� ����� �� ������������� ���������� (+4,7 �)
	_delay_us(DeviceQ_delay_E);						// �������� 15us �� ������ (������ ������������ �� �����)						

    if (GetBitH(DeviceQ_PIN))	result = 0x01;		// ���� �� ����� ���������� 1 ��������� 1
   else 			result = 0x00;

	_delay_us(DeviceQ_delay_F);						// ��� ����� ���������


 return (result);									// ���������� �������� ����� ������

sei();
}


//=======================================================================================================================
//======================================READ_BYTE -> ������ ����� �� ����================================================
//=======================================================================================================================
unsigned char DeviceQ_read_byte(void){
 cli();
  unsigned char	value =	0;

  for(int i = 0; i < 8; i++)
  	value |= DeviceQ_read_bit() << i;

  return(value);
 sei();
}


//=======================================================================================================================
//=====================================���������� ����� ����� �������====================================================
//=======================================================================================================================
unsigned char DeviceQ_read_list_array(unsigned char * array, unsigned char i, bool LogicVal){
 memset(array,0x00,i);											//������ ���������� ��������

 if (LogicVal) 
	for(unsigned char j=0;j!=i;j++){							//�������� ������ ���������� �� 0 �� i
		array[j] = DeviceQ_read_byte();
	}		
 else
	while (i--){array[i] = DeviceQ_read_byte();}				//�������� ������ ���������� �� i �� 0

 //_1_WIRE_ERROR = CheckRomCRC8(array,0);						//�������� ����������� ����� ���������� 8 ������ ������

 return _1_WIRE_ERROR;   
}


//=======================================================================================================================
//================================������ ������ ������������� ���������� �� ����=========================================
//=======================================================================================================================
void DeviceQ_READ_ROM_COMMAND(void){
	memset(_deviceQ_rom_array,0x00,8);
 	DeviceQ_write_byte(READ_ROM);
 	DeviceQ_read_list_array(_deviceQ_rom_array,8,0);
}


//=======================================================================================================================
//================================����� ������������� ���������� �� ���� �� ������=======================================
//================================= �������� �������� ������ � ����� +����+CRC ==========================================
//=======================================================================================================================
void DeviceQ_MATCH_ROM_COMMAND(unsigned char * array_rom){
 	DeviceQ_write_byte(MATCH_ROM); 											// ������� ������� ������ ������ ���� ���� ����������
	for(int i=0;i<8;i++) DeviceQ_write_byte(array_rom[i]);					// ������� �����
}



//=======================================================================================================================
//=========================================== ��������� COPY SCARTCHPAD =================================================
//=======================================================================================================================
void DeviceQ_COPY_SCARTCHPAD_COMMAND(void){
 if (_1_WIRE_ERROR == 0x01){
		DeviceQ_write_byte(COPY_SCRATCHPAD); 								// ������� ������� ���� ������� ����������
		DeviceQ_Pullup(1);
		_delay_us(200);														// �������������� ����� �� ��������� ���������� 750 ms
		DeviceQ_Pullup(0);
 }	
}


//=======================================================================================================================
//========================================= ��������� WRITE SCARTCHPAD ==================================================
//=======================================================================================================================
void DeviceQ_WRITE_SCARTCHPAD_COMMAND(unsigned char TH, unsigned char TL){
 if (_1_WIRE_ERROR == 0x01){
		DeviceQ_write_byte(WRITE_SCRATCHPAD); 								// ������� ������� ���� ������� ����������
 } 			
}


//=======================================================================================================================
//====================================== ��������� READ SCARTCHPAD ======================================================
//=======================================================================================================================
void DeviceQ_READ_SCARTCHPAD_COMMAND(unsigned char * _ScratchPad){
 if (_1_WIRE_ERROR == 0x01){
		//memset(_ScratchPad,0x00,32);
		DeviceQ_write_byte(READ_SCRATCHPAD); 						// ������� ������� 
		DeviceQ_write_byte(0x00); 						// ������� ������� 
  	DeviceQ_read_list_array(_ScratchPad, 32,1);					// ��������� ����� ���������� �� ������� READ_SCRATCHPAD � �������� � ������ DeviceQ_ScratchPad[9]
		sei();
 }
}




//***********************************************************************************************************************
//***********************************************************************************************************************
//=======================================================================================================================
//========================================= �������� ������ ��������� �� ���� ===========================================
//=======================================================================================================================
//***********************************************************************************************************************
//***********************************************************************************************************************

//=======================================================================================================================
//====================================== ����� ������� ��������� �� ���� ================================================
//=======================================================================================================================
int DeviceQ_First(){
	
   _deviceQ_last_discrepancy = 0;									// ����� ������ ����� ������� �������
   _deviceQ_last_device_flag = false;
   _deviceQ_last_family_discrepancy = 0;

   return DeviceQ_SEARCH_ROM_COMMAND();  							// ������� �� �������� ������� ������


}


//=======================================================================================================================
//=================================== ����� ���������� ���������� �� ���� ===============================================
//=======================================================================================================================
int DeviceQ_Next(){ 
   return DeviceQ_SEARCH_ROM_COMMAND();  							// ������� �� �������� ������� ������
}


//=======================================================================================================================
//=========================================== ���������� ���������� �� ���� =============================================
//============================================== ��������������� ������� ================================================
//=======================================================================================================================
void DeviceQ_TargetSetup(unsigned char family_code){
   int i;
 
   _deviceQ_rom_array[0] = family_code;								// ���������� ��� (�����) ��������� ����������

   for (i = 1; i < 8; i++)     _deviceQ_rom_array[i] = 0;

   _deviceQ_last_discrepancy = 64;
   _deviceQ_last_family_discrepancy = 0;
   _deviceQ_last_device_flag = false;
}


//=======================================================================================================================
//======================================= ��������� ���������� �� ����� ������ ==========================================
//============================================== ��������������� ������� ================================================
//=======================================================================================================================
void DeviceQ_FamilySkipSetup(){  
   _deviceQ_last_discrepancy = _deviceQ_last_family_discrepancy;
   _deviceQ_last_family_discrepancy = 0;
   
   if (_deviceQ_last_discrepancy == 0)	_deviceQ_last_device_flag = true;										// check for end of list   
}


//=======================================================================================================================
//============================================ ����� ���� ��������� �� ���� =============================================
//=======================================================================================================================
int DeviceQ_FIND_ALL(void){
 int rslt, i;
 
  _deviceQ_find_count = 0;

 memset(_deviceQ_all_rom,0x00, (_deviceQ_max_count*8));											//���� ������ �������, � �� ���������� ����� ��� ������ �������� � ������ �� ������ ���������

 rslt = DeviceQ_First();																		// ����� ���� �� ������ ����������

 while (rslt){																					// ���� ���� ������� - �������� ������
	for (i = 0; i < 8; i++)	_deviceQ_all_rom[_deviceQ_find_count][i] = _deviceQ_rom_array[i];	// ������� ���������� ������ � ������ � �������� ([������], [���, ���, crc])
   	++_deviceQ_find_count;																		// ������� ��������� ���������
   	rslt = DeviceQ_Next();																		// ������ ���������
   }

 return _deviceQ_find_count;																	// ��������� ���������� ��������� (0 - ���, 1....)
}	


//=======================================================================================================================
//============================================= ����� ��������� �� ���� =================================================
//=======================================================================================================================
int DeviceQ_FIND_DEVICE_CODE(unsigned char QDevice_code){
 int i;
 
 _deviceQ_find_count = 0;

 DeviceQ_TargetSetup(QDevice_code);

 while (DeviceQ_SEARCH_ROM_COMMAND()){																// check for incorrect type
	if (_deviceQ_rom_array[0] != QDevice_code) break;
 
  	for (i = 7; i >= 0; i--)	_deviceQ_all_rom[_deviceQ_find_count][i] = _deviceQ_rom_array[i];	// ������� ���������� ������ � ������ � �������� ([������], [���, ���, crc])
    ++_deviceQ_find_count;
 }

 return _deviceQ_find_count;
}


//=======================================================================================================================
//=================================== ����� ��������� �� ���� �� ��������������� �������=================================
//===============================================0x04;0x1A;0x01;0x23;0x0A;0x10===========================================
//=======================================================================================================================
int DeviceQ_FIND_DEVICE_EXCEPTION_CODE(void){
 int rslt,i;

 _deviceQ_find_count = 0;

 rslt = DeviceQ_First();																					// ����� ���� �� ������ ����������
 while (rslt){																								// check for incorrect type
      if ((_deviceQ_rom_array[0] == 0x04) || (_deviceQ_rom_array[0] == 0x1A) || 
          (_deviceQ_rom_array[0] == 0x01) || (_deviceQ_rom_array[0] == 0x23) ||
          (_deviceQ_rom_array[0] == 0x0A) || (_deviceQ_rom_array[0] == 0x10))
          DeviceQ_FamilySkipSetup();
      else{																									// print device found
   		 for (i = 8; i >= 0; i--)	_deviceQ_all_rom[_deviceQ_find_count][i] = _deviceQ_rom_array[i];		// ������� ���������� ������ � ������ � �������� ([������], [���, ���, crc])
    	 ++_deviceQ_find_count;
      }

      rslt = DeviceQ_Next();
   }

 return _deviceQ_find_count;
}


//=======================================================================================================================
//===========================================����� ��������� �� ���� �� ������===========================================
//=======================================================================================================================
int DeviceQ_SEARCH_ROM_COMMAND(void){
   int id_bit_number;
   int last_zero, rom_byte_number, search_result;
   int id_bit, cmp_id_bit;
   unsigned char rom_byte_mask, search_direction;

  
   id_bit_number = 1;																		// ������������� ����� �������
   last_zero = 0;
   rom_byte_number = 0;
   rom_byte_mask = 1;
   search_result = 0;
   crc8 = 0;

   if (!_deviceQ_last_device_flag){
      if (!DeviceQ_reset()){																// if the last call was not the last one1-Wire reset reset the search
         _deviceQ_last_discrepancy = 0;
         _deviceQ_last_device_flag = false;
         _deviceQ_last_family_discrepancy = 0;
         return false;
      }


      DeviceQ_write_byte(SEARCH_ROM);														// �������� � ���� ������� ������

      do {																					// read a bit and its complement
         id_bit = DeviceQ_read_bit();
         cmp_id_bit = DeviceQ_read_bit();
 
         if ((id_bit == 1) && (cmp_id_bit == 1)){
		 	DeviceQ_reset();
			break;}																			// check for no devices on 1-wire
         else{
            if (id_bit != cmp_id_bit) search_direction = id_bit;							// all devices coupled have 0 or 1 bit write value for search
            else{																			// if this discrepancy if before the Last Discrepancy on a previous next then pick the same as last time
               if (id_bit_number < _deviceQ_last_discrepancy)        search_direction = ((_deviceQ_rom_array[rom_byte_number] & rom_byte_mask) > 0);
               else   search_direction = (id_bit_number == _deviceQ_last_discrepancy);		// if equal to last pick 1, if not then pick 0
               if (search_direction == 0){													// if 0 was picked then record its position in LastZero
                  last_zero = id_bit_number;
               	  if (last_zero < 9)  _deviceQ_last_family_discrepancy = last_zero;			// check for Last discrepancy in family
               }
            }
            
            if (search_direction == 1)		_deviceQ_rom_array[rom_byte_number] |= rom_byte_mask;		// set or clear the bit in the ROM byte rom_byte_number with mask rom_byte_mask
            else							_deviceQ_rom_array[rom_byte_number] &= ~rom_byte_mask;

            DeviceQ_write_bit(search_direction);											// serial number search direction write bit

            id_bit_number++;																// increment the byte counter id_bit_number and shift the mask rom_byte_mask
            rom_byte_mask <<= 1;
            
            if (rom_byte_mask == 0){														// if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
                docrc8(_deviceQ_rom_array[rom_byte_number]);								// accumulate the CRC
                rom_byte_number++;
                rom_byte_mask = 1;
            }
         }
      } while(rom_byte_number < 8);															// loop until through all ROM bytes 0-7

      
      if (!((id_bit_number < 65) || (crc8 != 0))){											// if the search was successful then
         _deviceQ_last_discrepancy = last_zero;												// search successful so set _deviceQ_last_discrepancy,_deviceQ_last_device_flag,search_result
         if (_deviceQ_last_discrepancy == 0) _deviceQ_last_device_flag = true;				// check for last device
         search_result = true;
      }
   }

   
   if (!search_result || !_deviceQ_rom_array[0]){											// if no device found then reset counters so next 'search' will be like a first
      _deviceQ_last_discrepancy = 0;
      _deviceQ_last_device_flag = false;
      _deviceQ_last_family_discrepancy = 0;
      search_result = false;
   }

   return search_result;
}


/*
unsigned char DeviceQ_Select(unsigned char Num_QDevice){							//�� ���������� ������ ��������� ���������� �����������
	u08 result = false;
	if (_deviceQ_find_count != 0){
		if (_deviceQ_find_count == 1){ result = DeviceQ_SKIP_ROM_COMMAND();}
			else{
  		for (int i = 8; i >= 0; i--)
				_deviceQ_rom_array[i] = _deviceQ_all_rom[Num_QDevice][i];														//����������� ����� ���������� (64bit) �� ��������� ����������
			result = DeviceQ_MATCH_ROM_COMMAND(_deviceQ_rom_array);
			}						
 		}
	return result;
	}
*/