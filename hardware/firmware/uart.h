#ifndef USART_H_
	#define USART_H_
	#define bauddivider (F_CPU/(16*UART_BAUD)-1)
	#define HI(x) ((x)>>8)
	#define LO(x) ((x)& 0xFF)
	
	uint8_t tx_buf[30];
	uint8_t rx_buf[50];

void USART_Init() {
	UBRRL = LO(bauddivider);//
	UBRRH = HI(bauddivider);//
	UCSRA = 0;
	UCSRB = _BV(RXEN)|_BV(TXEN)|1<<RXCIE|0<<TXCIE|1<<UDR;
	UCSRC = 1<<URSEL|1<<UCSZ0|1<<UCSZ1;
	}


void USART_Transmit(uint8_t data) {
	while (!(UCSRA&(1<<UDRE)));	// Wait for empty transmit buffer
	tx_buf[0]=0;
	UDR = data;			// Put data into buffer, send data
	}

void USART_SendBuff(char *tbadr) {
	uint8_t i = 0;
	while (((tbadr[i]!= '\n') & (tbadr[i]!= 0))) {
		USART_Transmit((tbadr[i]));
		i++;
    };
	USART_Transmit(10); 
	}
void USART_SendEND(void) {
	USART_Transmit(0x0D);
	USART_Transmit(0x0A);	 
	}

void SendStr_P(char *string) {				// Отправка строки из флеша
	while (pgm_read_byte(string)!='\0') {
		USART_Transmit(pgm_read_byte(string));
		string++;
		};
	USART_SendEND();
	}

#endif /* USART_H_ */

