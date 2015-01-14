#if defined 	__IO_INCLUDE_
	#else
		#define		_GetbitL(port,bit) 					(!(port&(1<<bit)))
		#define 	_GetbitH(port,bit)					(port&(1<<bit))
		#define  	GetBitL(x)							_GetbitL(x)
		#define  	GetBitH(x)							_GetbitH(x)

		#define 	_SetBit(port,bit)					(port = port|(1<<bit))				//установить высокий уровень
		#define 	_ClrBit(port,bit)					(port^= port&(1<<bit))				//снять высокий уровень
		#define 	_InvBit(port,bit)					(port = port^(1<<bit))				//инвертировать уровень
		#define 	SetBit(x)							_SetBit(x)
		#define 	ClrBit(x)							_ClrBit(x)
		#define 	InvBit(x)							_InvBit(x)

 		#define 	_until_bit_is_set(port,bit)			loop_until_bit_is_set(port, bit)
 		#define 	until_bit_is_set(x)					_until_bit_is_set(x);

 		#define 	_until_bit_is_clear(port,bit)		loop_until_bit_is_clear(port, bit)
 		#define 	until_bit_is_clear(x)				_until_bit_is_clear(x);
	#endif
