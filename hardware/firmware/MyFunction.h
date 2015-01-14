	void MainInit(void);	
	void Catch(void);

	void MainInit(void){

	DDRD 	|= 0<<PD2|0<<PD3;
	PORTD |= 0<<PD2|0<<PD3;

	DDRC |= 1<<PC5;
	PORTC |= 1<<PC5;


	//MCUCR |= 1<<ISC01|0<<ISC00|1<<ISC11|0<<ISC10;
	//GIMSK=1<<INT0|1<<INT1;

	
	//TIMSK=1<<TOIE0;//Разрешение припиваний Т0
	//TCCR0=1		; //Запуск Т0 (предделитель 0-Off, 1-1, 2-8, 3-64, 4-256, 5-1024)

	//hd44780_init();		
	USART_Init(); 

	DeviceQ_Init();											//Установка направления порта 1-wire

	//sprintf((char *)tx_buf,"Count Device = %d\n\r", _deviceQ_find_count);
	//USART_SendBuff(tx_buf);
	//USART_SendBuff(_deviceQ_all_rom[1]);
	

	sei();

	//LCD_CLR();	// Clear the display.
  //hd44780_outcmd(HD44780_ENTMODE(1, 0));	// Entry mode: auto-increment address counter, no display shift in effect.
  //hd44780_outcmd(HD44780_DISPCTL(1, 0, 0));	// Enable display, activate non-blinking cursor.

	//LCD_SendFlash(PSTR("Ready"));

	};


void USART_SendBuffCode(u08 *tbadr,u08 size) {
	uint8_t i = 0;
	while (size > 0) {
		USART_Transmit((tbadr[i]));
		i++;
		size--;
    };
	}

