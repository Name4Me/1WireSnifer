	#include "hd44780.c"	

	void LCD_SendBuffer(char *badr);
	void LCD_SendFlash(char *string);
	void LCD_CLR(void);




void LCD_SendBuffer(char *badr) {
  uint8_t i;
	i=0;
	while (((badr[i]!= '\n') & (badr[i]!= 0))) {
		hd44780_outdata(badr[i]);
		i++;
    }
	}

// Отправка строки из флеша
void LCD_SendFlash(char *string) {
	while (pgm_read_byte(string)!='\0') {
		hd44780_outdata(pgm_read_byte(string));
		string++;
		}
	}


void LCD_CLR(void) {
	hd44780_outcmd(HD44780_CLR);	
	};
