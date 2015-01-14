
	typedef unsigned char	u08;
	typedef unsigned int	u16;
	typedef unsigned long	u32;

	#define NOP	asm volatile ("nop");

	u08 EEMEM ERom[8] = {0x14,0x17,0xD7,0x26,0x04,0x00,0x00,0x39};
	u08 EEMEM EStatusReg[1] = {0xFC};
	u08 EEMEM EAppReg[8] = {0x33,0xCB,0xA6,0x11,0x58,0x4C,0xA8,0x2B};
	u08 EEMEM ERam[32] = {0x20,0x02,0x07,0x41,0x20,0x39,0x5A,0x45,0x32,0x33,0x33,0x37,0x0B,0x06,0x01,0xB8,0x05,0xF7,0x6A,0xAE,0x6E,0x00,0x00,0x53,0x20,0x20,0x00,0x00,0x10,0xDD,0xFD,0x79};

	volatile u08 _deviceQ_Is_Reset;		// 0 - ������� �����
