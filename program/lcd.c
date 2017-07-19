#include "lcd.h"

static INT8U lcdptr;

static void  lcden(void){
    LCD_EN_PIN = HIGH; 
    dly50us();
	dly50us();
    LCD_EN_PIN = LOW; 
}
void lcdwc(INT8U LCDData){
    LCD_RS_PIN = LOW; 
    lcdwb(LCDData);
}
void lcdwd(INT8U LCDData){
    LCD_RS_PIN = HIGH; 
    lcdwb(LCDData);
}
void lcdws(INT8U *s){
	while (*s) {
			#ifdef LCD_20X4
		switch(lcdptr) {
			case 0x80+20:
				lcdptr = 0xC0;
				break;
			case 0xC0+20:
				lcdptr = 0x94;
				break;
			case 0x94+20:
				lcdptr = 0xD4;
				break;
			case 0xD4+20:
				lcdptr = 0x80;
				break;
		}
		#else
			switch(lcdptr) {
				case 0x80+16:
				lcdptr = 0xC0;
				break;
				case 0xC0+16:
				lcdptr = 0x80;
				break;
			}
		#endif
		lcdwc(lcdptr++);
		lcdwd(*s++);
	}
}
void lcdinit(void){
    LCD_EN_PIN		= OUTPUT_PIN; 
    LCD_RS_PIN		= OUTPUT_PIN;
    LCD_DATA_PORT	&=  0x0f;
   	lcdrs();
    lcdwc(0x28);
    lcdwc(0x0C);
    lcdwc(0x06);
    lcdwc(0x01); 
	lcdptr = 0x80;	
	#ifdef DISPLAY_INIT
		lcddinit();
	#endif
}
static void lcdrs(void){
	lcdwc(0x33);
	dlyms(4);
	lcdwc(0x33);
	lcdwc(0x33);
	lcdwc(0x32);
}
void lcddinit(void){
	INT8U i , j , adr;
	lcdws("  INITIALIZING");
	lcdr2();
	for ( j = 0; j < LCD_NSCRL; j++ ) {
		adr = 0xc0;						// 2nd row, first coloumn
		for ( i = 0; i < 16; i++ ) {
			lcdwc(adr);			
			lcdwd(LCD_DOT);				
			if ( i < 8 ) dlyms(200+(50*i)); else dlyms(25);
			lcdwc(adr);			
			lcdwd(LCD_SPC);			
			adr++;					// increment display aadress
		}
	}
	lcdclr();
}
static void  lcdwb(INT8U  LCDData){
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F)|(LCDData & 0xF0);
    lcden();
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F)|(LCDData << 4);
    lcden();
    dlyms(2);
}
void lcdclr(void)
{
	lcdwc(0x01);
	lcdptr = 0x80;	  /* Clear display LCD */
}
void lcdclrr(INT8U rowno){
	INT8U i;
	switch (rowno) {
		case 0:
				lcdr1();
				break;
		case 1:
				lcdr2();
				break;
	}
	for (i = 0; i < 16; i++)
		lcdwd(LCD_SPC);
	switch (rowno) {
		case 0:
				lcdr1();
				break;
		case 1:
				lcdr2();
				break;
	}
 }
 void lcdr1(void)
 {
	lcdwc(0x80); 	  /* Begin at Line 1 */
	lcdptr = 0x80;
 }
  void lcdr2(void)
 {
	lcdwc(0xc0); 	  /* Begin at Line 1 */
	lcdptr = 0xc0;
 }
 void lcdwint(INT8U loc,signed int x)
 {
	 INT8U str[10];
	 lcdptr = loc;
	 lcdws("   ");
	 lcdptr = loc;
	 itoa(x, str);
	 lcdws(str);
 }
 void itoa(signed int n, char s[])
{
	int i, sign;
	
	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}
void reverse(char s[])
{
	int c,i,j;
	for (i = 0, j = strlen(s)-1; i < j; i++,j--) 
		c = s[i], s[i] = s[j], s[j] = c;
} 

