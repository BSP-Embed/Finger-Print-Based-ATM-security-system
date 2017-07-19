#ifndef fingerprint_H
#define fingerprint_H

//INCLUDE HEADER FILE

//INCLUDE USER DEFINED HEADER FILE
#include "includes.h"

//DEFINE PORTS/PINS

//DEFINE MACROS

//DEFINE CONSTANT


//DEFINE USER DEFINED DATA TYPE

//DEFINE FUNCTION PROTOTYPE
INT8U FingerEnroll		(void);
INT8U FingerMatch		(void);
INT8U FingerDelete		(void);
INT8U DeleteAllFingers	(void);

static INT8U ReadFinger(INT8U ReadByte);
static INT8U CreateBuffer(INT8U BufferID);
static INT8U GenerateTemplate(INT8U ReadByte);
static INT8U StoreFinger(void);
static INT8U SearchFinger(void);
static INT8U DeleteTemplate(INT8U ID);
static void NotepadWrite(INT8U Byte);
static INT8U NotepadRead(void);
INT8U genpass(INT8U *RandomNumber);

#endif

