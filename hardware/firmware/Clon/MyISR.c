ISR (TIMER0_OVF_vect) {
	_deviceQ_last_line=255;
	}

ISR(INT0_vect){				// Обработчик прерывания INT0
	if (GetBitH(DeviceQ_PIN)){
		TCCR0=0;
		if (_deviceQ_last_line != 255) _deviceQ_last_line = TCNT0;
		if (_deviceQ_last_line >110) _deviceQ_Is_Reset=1;	
		}
		else {
			TCNT0=0;
			SFIOR=1<<PSR10;
			TCCR0=3;
			_deviceQ_last_line=0;
			};
	}

