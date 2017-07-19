#ifndef GSM_H
#define GSM_H

//INCLUDE HEADER FILES
#include "includes.h"

#define MSG_START	""
#define MSG_END		".Automated SMS By: FingerPrint Based ATM Security System."

//FUNCTION PROTOTYPES	
				void 	GSMsndmsg			(INT8U *PhNum, INT8U *GSMMsg);
				bit 	GSMinit				(void);
static 	void 	GSMerr				(void);
static 	bit 	GSMRxResp			(void);
static 	bit 	GSMmsgparam		(void);
static 	bit 	GSMsndphnum		(INT8U *PhNum);
static 	void	GSMrxack			(void);
				bit 	gsm_call_gen	(INT8U *PhNum);

#endif
