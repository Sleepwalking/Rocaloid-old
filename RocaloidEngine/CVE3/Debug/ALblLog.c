#include "ALblLog.h"
#include "../RUtil/IO/FileStream.h"
#include <string.h>

#define ALblLog_TimeIncrement 0.00001

FileStream ALblLog_TxtStream;
char ALblLog_Buffer[1024];
char ALblLog_TimeBuffer[100];
float ALblLog_Time = 0;

int ALblLog_Enabled = 1;

void ALblLog_Create(String* Dest)
{
    FileStream_Ctor(& ALblLog_TxtStream);
    FileStream_Open(& ALblLog_TxtStream, Dest, CREATE);
}

void ALblLog_Print(const char* Format, ...)
{
    if(ALblLog_Enabled)
    {
        va_list VList;

        va_start(VList, Format);
        vsprintf(ALblLog_Buffer, Format, VList);
        va_end(VList);
        strcat(ALblLog_Buffer, "\n");

        sprintf(ALblLog_TimeBuffer, "%f\t%f\t", ALblLog_Time, ALblLog_Time);
        FileStream_WriteChars(& ALblLog_TxtStream, ALblLog_TimeBuffer);
        FileStream_WriteChars(& ALblLog_TxtStream, ALblLog_Buffer);

        ALblLog_Time += ALblLog_TimeIncrement;
    }
}

void ALblLog_SetTime(float Time)
{
    ALblLog_Time = Time;
}

void ALblLog_Enable()
{
    ALblLog_Enabled = 1;
}

void ALblLog_Disable()
{
    ALblLog_Enabled = 0;
}

void ALblLog_Save()
{
    FileStream_Flush(& ALblLog_TxtStream);
    FileStream_Close(& ALblLog_TxtStream);
    FileStream_Dtor(& ALblLog_TxtStream);
}
