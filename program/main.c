/* main.c:	application program for overloaded vehicle detection */
#include "main.h"

#ifdef TESTING
	code const INT8U UPhNum[] = "9980237552";
	code const INT8U MPhNum[] = "9980237552";
#else
	code const INT8U UPhNum[] = "8105631379";
	code const INT8U MPhNum[] = "8861519511";
#endif

code const INT8U MSG1[] =	"Your high security password for the transaction is:";
code const INT8U MSG2[] = "Your Transaction is completed. To know balance Dial CC";
code const INT8U MSG3[] = "Person is in trouble at canara bank  ATM, Ponnampet";  
code const INT8U MSG4[] = "Theft at canara bank  ATM, Ponnampet";  

extern INT8U idata DeletingPageID;
extern INT8U idata fingerstat;

bit fireflag = 0;
bit theftflag = 0;

INT8U idata randpass[7];

void main(void)
{								
	INT8U i, InVldCnt, pass[6], userID[10];
	init();
	
	for (i = 0; i < 10; i++)
		userID[i] = 1;
	InVldCnt = 0;
	randpass[6] = '\0';
	
	
	while (TRUE)	{
		if (FingerMatch()) {
			if ( userID[DeletingPageID]) {
				lcdclr();
				beep(1,100);
				genpass(randpass);
				sendSMS(1);
	CHK_PASS:	
					lcdclr();
					lcdws(" ENTER PASSWORD");
					lcdr2();
					read_pass(pass);
					switch(verpass(pass)) {
						case 1:
									beep(1,100);
									lcdws("    Verified");
									dlyms(1000);
									mot1on();
									lcdclr();
									lcdws("Collect ur Cash");
									dlyms(5000);
									mot1off();
									sendSMS(2);
									InVldCnt = 0;
									break;
						case 2:
									sendSMS (3);
									break;
						default:
									buzon();
									lcdclr();
									lcdws("Wrong Password");
									dlyms(500);
									buzoff();
									if ( ++InVldCnt >= MAX_CNT ) {
										displock();
										userID[DeletingPageID] = 0;				/* Block the ID */ 
									} else goto CHK_PASS;
									break;
					}
					EnFP();
					disptitle();
		} else {
				displock();
				EnFP();
				disptitle();
		}
	}	else {
			if (fingerstat) {
					lcdclr();
					lcdws("!!Unauthorised!!");
					beep(3,100);
					fingerstat = 0;
					dlyms(3000);
					disptitle();
			}
	}
	if (fireflag) {
		fireflag = 0;
		buzon();
		lcdclr();
		lcdws("  Fire occured");
		lcdr2();
		lcdws(" System Locked!");
		rlyon();
		dlyms(5000);
		rlyoff();
		EA = 0;		/* disable interrupt */
		ledon();
		PCON |= 0x02;
	}
	if (theftflag) {
		theftflag = 0;
		mot2on();
		sendSMS(4);
		lcdclr();
		lcdws("  Theft occured");
		lcdr2();
		lcdws(" System Locked!");
		dlyms(2000);
		mot2off();
		EA = 0;		/* disable interrupt */
		ledon();
		buzon();
		PCON |= 0x02;
	}
	dlyms(500);
	}
}
static void displock(void)
{
		lcdclr();
		lcdws("Your Transaction");
		lcdr2();
		lcdws("  is Blocked!");
		dlyms(3000);
}
static void sendSMS (INT8U situ) {
	INT8U idata i, GSMmsg[80];
	EnGSM();
	dlyms(100);
	
 	for(i = 0; i < 80; i++)
		GSMmsg[i] = '\0';

	switch (situ) {
		case 1:
					strcat(GSMmsg, MSG1);
					strcat(GSMmsg, randpass);
					GSMsndmsg(UPhNum, GSMmsg);
					break;
		case 2:
					strcat(GSMmsg, MSG2);
					GSMsndmsg(UPhNum, GSMmsg);
					break;
		case 3:
					strcat(GSMmsg, MSG3);
					GSMsndmsg(MPhNum, GSMmsg);
					break;
		case 4:
				  strcat(GSMmsg, MSG4);
					GSMsndmsg(MPhNum, GSMmsg);
					break;
	}
}
static INT8U verpass (INT8U pmsg[])
{
	INT8U i, msg;
	
	msg = 1;
	for (i = 0; randpass[i] != '\0'; i++) 
		 if (randpass[i] != pmsg[i])
		 		msg = 0;
	if (!msg) {
		for (i = 0; randpass[i] != '\0'; i++) 
			if (randpass[i] != pmsg[5-i])
					return msg;
		return 2;
	 } else return 1;
	
}
static void disptitle(void)
{
	lcdclr();
	lcdws("ATM Security SYS");
}
static void init(void)
{
	mot1off();
	mot2off();
	beep(2,100);
	KBDinit();
	lcdinit();					  
	uartinit();
	tmrinit();
	EnGSM();
	dlyms(100);
	GSMinit();	
	EnFP();
	dlyms(100);
	genpass(randpass);			/* dummy number to init RAND func */
	if (FP_SW_PIN == LOW) 
			fpsett();
	disptitle();
	starttmr();
	EXTint_int();
}
static void fpsett(void)
{
	lcdclr();
	lcdws("Enter Choice:");
	dlyms(1000);
	switch(getkey()) {
		case 'A':
							FingerEnroll();
							break;
		case 'D':
							FingerDelete();
							break;
		case 'E':
							break;
	}
}
					
static void tmrinit(void)
{
	TMOD = TMOD & 0xf0 | 0x01;
	TH0 = 0x4B;
	TL0 = 0xFD;
	EA = ET0 = 1;
}
		
/* timer overflows for every 50ms */
static void tmr0ISR() interrupt 1 using 2
{
	static INT8U i,j;
	TH0 = 0x4B;
	TL0 = 0xFD;
	if (++i >= 2) {
		i = 0;
		if (++j >= 50) j = 0;
		switch(j) {
			case 0: case 2: ledon(); break;
			case 1: case 3: ledoff(); break;
		}
	}
} 

static bit read_pass(INT8U pass_temp[])
{
	INT8U i;
	
	lcdr2();
	lcdwc(0xC5);
	for (i = 0; i < 6; i++) {  
		pass_temp[i] = getkey();	
		lcdwd('*');
		beep(1,50);
	}
	return 1;
}
static void EXTint_int(void)
{
	EX0 = EX1 = 1;		/* Enable external Interrupt 0&1 */
	IT0 = IT1 = 1;		/* EDGE triggeres */
}
void EXTint0ISR() interrupt 0 using 3
{
	fireflag = 1;
}
void EXTint1ISR() interrupt 2 using 3
{
	theftflag = 1;
}