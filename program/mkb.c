//INCLUDE KEYBOARD HEADER FILE
#include"mkb.h"

//DECLARE GLOABL VARIABLE
code const INT8U kb_value[] = "A321B654C987D#0*";	

void KBDinit(void)
{
	KB_PORT = 0x0f;
}
INT8U getkey()
{
	
	INT16U  time_out = 0;
	INT8U digit;

	while(KB_PORT != 0x0f);
	dlyms(KEY_DEBOUNE);					/* key debounce time */
	while(KB_PORT != 0x0f);
	dlyms(KEY_DEBOUNE);					/* key debounce time */

	while(KB_PORT == 0x0f){
		#ifdef NON_BLOCK 
			dlyms(1);
			if(time_out++ >= MAX_TIME_OUT)
				return 0;
		#endif
	}

  if((KB_PORT = 0xef) && MASK != 0x0f)
   		digit = find_col(0x00);
	else if((KB_PORT = 0xdf) && MASK != 0x0f)
   		digit = find_col(0x04); 
	else if((KB_PORT = 0xbf) && MASK != 0x0f)
   		digit = find_col(0x08);	 
	else if((KB_PORT = 0x7f) && MASK != 0x0f)
   		digit = find_col(0x0c);

	return kb_value[digit];
}
	
INT8U find_col(INT8U key){
	KB_PORT &= 0x0f;

	if(KB_PORT == 0x0d)
		key++;
	else if(KB_PORT == 0x0b)
		key +=2;
	else if(KB_PORT == 0x07)
		key +=3;

	return key;

   }

