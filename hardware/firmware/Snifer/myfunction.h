	void MainInit(void);	

	void MainInit(void){

	DDRD 	|= 0<<PD2|0<<PD3;
	PORTD |= 0<<PD2|0<<PD3;

	DDRC |= 1<<PC5;
	PORTC |= 1<<PC5;


	MCUCR |= 0<<ISC01|1<<ISC00;
	GIMSK=1<<INT0;

	
	TIMSK=1<<TOIE0;//Разрешение припиваний Т0



	sei();
	
	OwClient_Init();


	};




