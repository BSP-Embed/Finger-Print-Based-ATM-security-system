
//INCLUDE HEADER FILE
#include "fp.h"

code const INT8U GenImg[12]   = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x01, 0x00, 0x05};
code const INT8U Img2Tz[11]   = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x02, 0x07};
code const INT8U RegModel[12] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x05, 0x00, 0x09};

code const INT8U Store[13]    = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x06, 0x06, 0x01, 0x00, 0x0e};
code const INT8U Search[17]   = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x08, 0x04, 0x01, 0x00, 0x00, 0x00, 0xff, 0x01, 0x0D};
code const INT8U DeletChar[15]= {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x0C, 0x00, 0x00, 0x01, 0x00, 0x15};
code const INT8U Empty[12]    = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x0d, 0x00, 0x11};

code const INT8U WriteNotepad[12] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x24, 0x18, 0x00, 0x3d}; 
code const INT8U ReadNotepad[13]  = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x19, 0x00, 0x00, 0x1E};
code const INT8U GetRandomCode[12]= {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x14, 0x00, 0x18};

INT8U idata PageID;
INT8U idata DeletingPageID;
INT8U idata fingerstat = 0;

/******************************************************************************
*** Finger Enroll-> Store the new fingerprint image template into device's  ***
***   				flash library in particular pageID. 		    		***
******************************************************************************/
INT8U FingerEnroll(void)
{
	lcdclr();
	lcdws("ENROLLING FINGER");
	dlyms(1000);
	
	PageID = NotepadRead();			//read Notepad where pageID of next template to be stored is written
	
	if(GenerateTemplate(0x00))
		if(!SearchFinger())					
			if(StoreFinger())						
				return (1);				//returns 1 on success
	
	return (0);						//returns 0 on failure
}

/*********************************************************************
*** Finger Match -> Captures the fingerprint image from the device ***
***				    Search for the template in the flash library.  ***
*********************************************************************/
INT8U FingerMatch(void)
{
	if(GenerateTemplate(0x01))
		if(SearchFinger())
			return (1);						//Returns 1 on Success

	return (0);								//Returns 0 on failure
}

/***********************************************************************************
*** Finger Delete -> Delete the stored finger print template if input template   ***
***                  is matched with the stored one in the flash library.        ***
***********************************************************************************/

INT8U FingerDelete(void)
{
	lcdclr();
	lcdws("DELETING FINGER");
	dlyms(1000);
	
	if(GenerateTemplate(0x00))
		if(SearchFinger())
			if(DeleteTemplate(DeletingPageID))	//Sends the pageID of template which is matched
				return (1);						//Returns 1 on Success
	
	return (0);									 	//Returns 0 on failure
}

/******************************************************************/

static INT8U ReadFinger(INT8U ReadByte)
{
	INT8U idata DataRequired;
	INT8U idata DummyVariable;
	INT8U idata Count;
	
	if(ReadByte == 0x00) {
		lcdclr();
		lcdws(" PLACE A FINGER");
		dlyms(1500);
	}

	for(Count = 0; Count < 12; Count++)	{
		putchar(GenImg[Count]);			//To read finger present on the device
	} 
	
	for(Count = 0; Count < 12; Count++)				//Receive acknowledgement 
	{
		if(Count == 9)
			DataRequired = getchar();	//Stores confirmation byte 
		else
			DummyVariable = getchar();	//Stores other bytes
	}
	
	
	lcdr2();
	if(DataRequired == 0x00)						//checks the status of confirmation byte
	{
		if(ReadByte == 0x00)
		{
			lcdws("    SUCCESS");
			dlyms(600);
		}

		return (1);									//returns 1 on success
	}
	else if(DataRequired == 0x02)
	{
		if(ReadByte == 0x00)
		{
			lcdws("CANNOT DETECTED");
			dlyms(800);
		}

		return (0);									//returns 0 on failure
	}											
}

/*********************************************************************/

static INT8U CreateBuffer(INT8U BufferID)
{
	INT8U idata DataRequired;
	INT8U idata DummyVariable;
	INT8U idata Count;
		
	for(Count = 0; Count < 10; Count++)
	{
		putchar(Img2Tz[Count]);			//stores capture fingerprint image to charbuff1
	}

	putchar(BufferID);
	putchar(0x00);
	putchar(BufferID + Img2Tz[10]);
	
	for(Count = 0; Count < 12; Count++)				//Receive acknowledgement  
	{
		if(Count == 9)
			DataRequired = getchar();	//Stores confirmation byte
		else
			DummyVariable = getchar();	//Stores other bytes
	} 

	if(DataRequired == 0x00)
		return (1);									//On success of deletion returns value 1
	else
		return (0);									//On failure returns value 0
}

/**********************************************************************/

static INT8U GenerateTemplate(INT8U ReadByte)
{
	INT8U idata DataRequired;
	INT8U idata DummyVariable;
	INT8U idata Count;
	
	if(ReadFinger(ReadByte))
	{
		if(CreateBuffer(0x01))
		{
			if(ReadFinger(ReadByte))
			{
				if(CreateBuffer(0x02))
				{
					for(Count = 0; Count < 12; Count++)
					{
						putchar(RegModel[Count]);			//Generates template by combining charbuff1 and charbuff2 images
					} 
					
					for(Count = 0; Count < 12; Count++)				//Receive acknowledgement  
					{
						if(Count == 9)
							DataRequired = getchar();	//Stores confirmation byte
						else
							DummyVariable = getchar();	//Stores other bytes
					}
					
					lcdclr();
					if(DataRequired == 0x00)						//checks the status of the confirmation byte
						return (1);									//returns 1 on success
					else
						return (0);									//returns 0 on failure
				 }
			}
		}
	}
}

/******************************************************************/

static INT8U StoreFinger(void)
{
	INT8U idata DataRequired;
	INT8U idata DummyVariable;
	INT8U idata Count;
		
	for(Count = 0; Count < 12; Count++)
	{
		putchar(Store[Count]);				//stores the generated template into particular pageID
	} 
	
	putchar(PageID);						//PageID Template to be stored
	putchar(0x00);							//Higher byte of checksum
	putchar(PageID + Store[12]);			//Lower byte of checksum 
	
	for(Count = 0; Count < 12; Count++)				//Receive acknowledgement
	{
		if(Count == 9)
			DataRequired = getchar();	//Stores confirmation byte
		else
			DummyVariable = getchar();	//Stores other bytes
	}
	
	lcdclr();
	if(DataRequired == 0x00)						//checks the status of the confirmation bytes
	{
		lcdws("   REGISTERED");
		if(PageID == 0xff)							//whether pageID is overflow
		{
			lcdr2();
			lcdws("STACK OVERFLOW");
		}
		else										//not 
		{
			PageID++;								//Increase PageID
			NotepadWrite(PageID);					//write it to notepad
		}
		dlyms(1000);
		return (1);									//returns 1 on success
	} 
	else
		return (0);									//returns 0 on failure
}

/*****************************************************************************/

static INT8U SearchFinger(void)
{
	INT8U idata DataRequired;
	INT8U idata DummyVariable;
	INT8U idata Count;
	
	for(Count = 0; Count < 17; Count++)
	{
		putchar(Search[Count]);				//Search for template in flash library
	} 
	
	for(Count = 0; Count < 16; Count++)		
	{
		if(Count == 9)
			DataRequired = getchar();		//Stores confirmation byte
		else if(Count == 11)
			DeletingPageID = getchar();		//Stores pageID of matched template 
		else			
			DummyVariable = getchar();		//Stores other bytes
	}
	
	lcdclr();
	if(DataRequired == 0x00)							//checks status of Confirmation byte
	{
		lcdws("  MATCH FOUND");
		fingerstat = 0;
		dlyms(800);	
		return (1);										//returns 1 on success
	}
	else if(DataRequired == 0x09)
	{	
		lcdws(" NO MATCH FOUND");
		fingerstat = 1;
		dlyms(800);
		return (0);										//returns 0 on failure
	}
}

/******************************************************************/
static INT8U DeleteTemplate(INT8U ID)
{
	INT8U idata DataRequired;
	INT8U idata DummyVariable;
	INT8U idata Count;
	
	for(Count = 0; Count < 11; Count++)
	{
		putchar(DeletChar[Count]);			//to delete matched template in flash library
	}
	
	putchar(ID);							//ID is a pageID of the matched template
	putchar(DeletChar[11]);				//Higher byte of pages to be deleted
	putchar(DeletChar[12]);				//Lower byte of pages to be deleted
	putchar(DeletChar[13]);				//higher byte of checksum
	putchar(ID + DeletChar[14]);			//Lower byte of checksum
	
	for(Count = 0; Count < 12; Count++)				//Receive acknowledgement
	{
		if(Count == 9)
			DataRequired = getchar();	//Store confirmation byte
		else
			DummyVariable = getchar();	//Store other bytes
	}
	
	lcdclr();

	if(DataRequired == 0x00)						//checks status of Confirmation byte
	{
		lcdws(" DELETE SUCCESS");
		dlyms(1000);
		return (1);									//Returns 1 on Success
	}
	else
	{
		lcdws(" FAIL TO DELETE");
		dlyms(1000);
		return (0);									//Returns 0 on failure
	} 
}

/******************************************************************/

INT8U DeleteAllFingers(void)
{
	INT8U idata Count = 0;						//Deletes all the templates in the Flash library 
	INT8U idata DataRequired;
	INT8U idata DummyVariable;
	
	for(Count = 0; Count < 12; Count++)						
	{
		putchar(Empty[Count]);				//to erase all templates
	}
	
	for(Count = 0; Count < 12; Count++)				//Receive acknowledgement
	{
		if(Count == 9)
			DataRequired = getchar();	//Stores confirmation byte
		else
			DummyVariable = getchar();	//Stores other bytes
	}
	
	NotepadWrite(0x00);								//store page id as 00 in notepad
		
	if(DataRequired == 0x00)						//On success of deletion returns value 1
		return (1);
	else
		return (0);									//On failure returns value 0			   
}

/************************************************************/

static void NotepadWrite(INT8U Byte)
{
	INT8U idata WRData;
	INT8U idata Count;
	
	for(Count = 0; Count < 11; Count++)
	{
		putchar(WriteNotepad[Count]);		//To Write pageID(where next template to be stored) to 0th byte of Notepad
	} 
	
	putchar(Byte);							//PageID
	
	for(Count = 12; Count < 44; Count++)					
	{
		putchar(0x00);						//31 byte of content has to be 0x00, here only one (0th) byte is used among 32
	} 												//Higher byte of checksum also sent here
	
	putchar(Byte + WriteNotepad[11]);		//checksum of writenotepad is the sum of byte and writenotepad[11]
	
	for(Count = 0; Count < 12; Count++)
	{
		WRData = getchar();				//Receive acknowledgement
	}  
}

/******************************************************************/

static INT8U NotepadRead(void)
{
	INT8U idata DataRequired;
	INT8U idata DummyVariable;
	INT8U idata Count;
	
	for(Count = 0; Count < 13; Count++)
	{
		putchar(ReadNotepad[Count]);		//To Read the pageID written in 0th byte of Notepad
	}
	
	for(Count = 0; Count < 44; Count++)				//Receive acknowledgement
	{
		if(Count == 10)
			DataRequired = getchar();	//Stores pageID written in notepad
		else
			DummyVariable = getchar();
	} 
	
	return (DataRequired);							//returns PageID
}

/*******************************************************************/

INT8U genpass(INT8U *RandomNumber)
{
	INT8U idata RandNumber[2];
	INT8U idata DataRequired;
	INT8U idata DummyVariable;
	INT8U idata Count;
	
	for(Count = 0; Count < 12; Count++)
	{
		putchar(GetRandomCode[Count]);		//To Read the pageID written in 0th byte of Notepad
	}
	
	for(Count = 0; Count < 16; Count++)				//Receive acknowledgement
	{
		if(Count == 9)
			DataRequired = getchar();	//Stores pageID written in notepad

		else if((Count > 9) && (Count < 12))
		{
			RandNumber[Count-10] = getchar();
		}
		else
			DummyVariable = getchar();
	} 
	
	if(DataRequired == 0x00)						//On success of deletion returns value 1
	{
		for(Count = 0; Count < 2; Count++)
		{
			if(( RandNumber[Count] / 100 ) == 0)
				*RandomNumber++ = 0x30;			
		  	else
				*RandomNumber++ = ((RandNumber[Count] / 100) | 0x30);
		   
		    if(((RandNumber[Count] % 100) / 10) == 0)
				if(( RandNumber[Count] / 100 ) == 0)
					*RandomNumber++ = 0x30;	
				else
					*RandomNumber++ = (((RandNumber[Count] % 100) / 10) | 0x30);
		  	else
				*RandomNumber++ = (((RandNumber[Count] % 100) / 10) | 0x30);
		
			*RandomNumber++ = ((RandNumber[Count] % 10) | 0x30);
		}
		return (1);
	}
	else
		return (0);							//returns PageID
}



