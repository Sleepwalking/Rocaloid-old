#include "RDL.h"
#include <string.h>
#include <malloc.h>

StringStream* Write_Stream;
int32_t Write_Size;
String Indent;
int LastWrite;
int NewLineValid;

void RDL_ReadIgnoreComment(String* Dest, StringStream* Src)
{
    Next:
    StringStream_ReadWord(Dest, Src);
    if(Dest -> Data_Index == 0 && String_EqualChars(Dest, "#"))
    {
        while(1)
        {
            StringStream_ReadWord(Dest, Src);
            if(Dest -> Data_Index == 0 && String_EqualChars(Dest, "#"))
                goto Next;
        }
    }
}

void RDL_WriterInit() __attribute__ ((constructor));
void RDL_WriterExit() __attribute__ ((destructor));

void RDL_WriterInit()
{
    String_Ctor(& Indent);
    LastWrite = 0;
    NewLineValid = 1;
}
void RDL_WriterExit()
{
    String_Dtor(& Indent);
}

void RDL_SetWriteStringStream(StringStream* Dest)
{
    Write_Stream = Dest;
    String_SetChars(& Indent, "");
    LastWrite = 0;
    NewLineValid = 1;
}

void RDL_SetWriteInitialSize(int32_t Size)
{
    Write_Size = Size;
}

void RDL_CheckStreamSize(int32_t NewSize)
{
    if(NewSize > Write_Size)
    {
        Write_Stream -> BasePtr = realloc(Write_Stream -> BasePtr, NewSize * 5 / 3);
        Write_Size = NewSize * 5 / 3;
    }
}

void RDL_WriteString(String* Src)
{
    String Buffer;
    String_Ctor(& Buffer);
    switch(LastWrite)
    {
        case 0:
            break;
        case 1:
            String_Copy(& Buffer, & Indent);
            break;
        case 2:
            String_SetChars(& Buffer, "\t");
            break;
    }
    String_Join(& Buffer, Src);

    RDL_CheckStreamSize(Write_Stream -> Offset + Buffer.Data_Index + 1);

    memcpy(Write_Stream -> BasePtr + Write_Stream -> Offset, Buffer.Data, Buffer.Data_Index + 1);
    Write_Stream -> Offset += Buffer.Data_Index + 1;
    LastWrite = 2;
    String_Dtor(& Buffer);
}

void RDL_WriteChars(char* Src)
{
    String Buffer;
    String_Ctor(& Buffer);
    switch(LastWrite)
    {
        case 0:
            break;
        case 1:
            String_Copy(& Buffer, & Indent);
            break;
        case 2:
            String_SetChars(& Buffer, "\t");
            break;
    }
    String_JoinChars(& Buffer, Src);

    RDL_CheckStreamSize(Write_Stream -> Offset + Buffer.Data_Index + 1);

    memcpy(Write_Stream -> BasePtr + Write_Stream -> Offset, Buffer.Data, Buffer.Data_Index + 1);
    Write_Stream -> Offset += Buffer.Data_Index + 1;
    LastWrite = 2;
    String_Dtor(& Buffer);
}

void RDL_WriteNewLine()
{
    if(NewLineValid)
    {
        RDL_CheckStreamSize(Write_Stream -> Offset + 1);

        Write_Stream -> BasePtr[Write_Stream -> Offset] = '\n';
        Write_Stream -> Offset ++;
        LastWrite = 1;
    }
}

void RDL_WritePushIndent()
{
    if(NewLineValid)
    {
        String_JoinChars(& Indent, "\t");
    }
}

void RDL_WritePopIndent()
{
    if(NewLineValid)
    {
        if(Indent.Data_Index >= 0)
            Indent.Data_Index --;
    }
}
