	#define UART_BAUD  19200L				/* UART baud rate */

	typedef unsigned char	u08;
	typedef unsigned int	u16;
	typedef unsigned long	u32;

	#define NOP	asm volatile ("nop");

	volatile u08 _deviceQ_Is_Reset;		// 0 - ќжидаем ресет
