ISR (TIMER0_OVF_vect) {
}
ISR (TIMER1_OVF_vect) {
}

ISR(INT0_vect){				// Обработчик прерывания INT0

	}

ISR(INT1_vect){				// Обработчик прерывания INT1
	}

ISR (USART_UDRE_vect) {
	}

ISR(USART_TXC_vect) {
	}

ISR(USART_RXC_vect) {
	u08 DATA; 
	DATA = UDR; 
	rx_buf[0]++;
	if (rx_buf[0] == 50) rx_buf[0] = 1;
	rx_buf[rx_buf[0]]=DATA;
	}
