/* gsm.c:	interface program for GSM modem */
#include "gsm.h"

//GSM AT COMMANDS
code INT8U ATCommand[] 	= "AT\r"; 
code INT8U ATCall[]			= "ATD";
code INT8U SMSCode[] 		= "AT+CMGF=1\r";
code INT8U SMSNumber[] 	= "AT+CMGS=\"0";
code INT8U SMSSettings[]= "AT+CNMI=2,2,2,0,0\r";

void GSMsndmsg(INT8U *PhNum, INT8U *GSMMsg)
{
	lcdclr();
	lcdws("Sending SMS.....");
	if(GSMsndphnum(PhNum)) {
		puts(MSG_START);
		puts(GSMMsg);
		puts(MSG_END);
		putchar(0x1A);
		GSMrxack();
	} else	GSMerr();
	lcdr2();
	lcdws("  SMS SENT -->>");
	dlyms(1000);
}
bit GSMinit(void)
{
	lcdclr();
	lcdws("Init GSM : ");
	
	if(GSMRxResp() && GSMmsgparam() ) {
		lcdws("OK");
		dlyms(1000);
		return 1;
	} else {
		GSMerr();
		return 0;
  } 
//	return 1;
	
}
static void GSMerr(void)
{
	 lcdr2();
	 lcdws("FAILED !");
}
static bit GSMRxResp(void) {
	puts(ATCommand);
	while(getchar() != 'K');
	return 1;
}
static bit GSMmsgparam(void){
	puts(SMSCode);
  while(getchar() != 'K');
	puts(SMSSettings);
  while(getchar() != 'K');
	return 1;
}
static bit GSMsndphnum(INT8U *PhNum)
{
	puts(SMSNumber);
	puts(PhNum);
	puts("\"\r");
	while (getchar() != '>');
	return 1;
}
static void GSMrxack(void)
{
	INT8U x;
	do {
	 	x = getchar();
	 }while(x != 'K' && x != 'E');
	 if(x == 'E') if(! GSMRxResp() ) GSMerr();
}

bit gsm_call_gen(INT8U *PhNum)
{
	puts(ATCall);
	puts(PhNum);
	puts(";\r");
	return 1;
}
