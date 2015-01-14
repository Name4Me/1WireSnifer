
	#define UART_BAUD  19200L				/* UART baud rate */	

	typedef unsigned char	u08;
	typedef unsigned int	u16;
	typedef unsigned long	u32;

	#define NOP	asm volatile ("nop");
	
	char StringP[] PROGMEM = "Ready";

	u08		user_flag		= 0;						//Пользовательский флаг

	uint8_t data_buf[32];
	
//	uint8_t EEMEM eeprombyte=0x10;
//	uint8_t EEMEM eeprombyte1=0x10;


