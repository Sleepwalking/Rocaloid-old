#include "RUtil/Structure/String.h"
#include "RUtil/IO/StringStream.h"

inline void ReadIgnoreRDLComment(String* Dest, StringStream* Src)
{
    StringStream_ReadWord(Dest, Src);
    if(Dest -> Data_Index == 0 && String_EqualChars(Dest, "#"))
    {
        while(1)
        {
            StringStream_ReadWord(Dest, Src);
            if(Dest -> Data_Index == 0 && String_EqualChars(Dest, "#"))
            {
                StringStream_ReadWord(Dest, Src);
                break;
            }
        }
    }
}

#define String_Read(Dest) String_Copy(Dest, & Buffer)

#define RNext() ReadIgnoreRDLComment(& Buffer, CReader)
#define BufferIs(Chars) String_EqualChars(& Buffer, Chars)
#define IfBufferIs(Chars) if(BufferIs(Chars))
#define IfBufferIsNot(Chars) if(! BufferIs(Chars))

#define TemplateReadFunc(Type)\
    Type##_Read(Type* Dest)
//  {

#define TemplateReadFuncHead\
        String Buffer;\
        String_Ctor(& Buffer);

#define TemplateReadFuncLoop\
        while(1)\
        {\
            RNext();\
            IfBufferIs("End")\
                break;

#define TemplateReadFuncDynamicList(Type, Name)\
            do\
            {\
                RNext();\
                IfBufferIs("End")\
                    break;\
                IfBufferIs(">")\
                {\
                    ArrayType_PushNull(Type, Dest -> Name);\
                    Type##_Ctor(Dest -> Name + Dest -> Name##_Index);\
                    Type##_Read(Dest -> Name + Dest -> Name##_Index);\
                }\
            } while(1)

#define TemplateReadFuncEmbededDynamicList(Type, Name)\
            do\
            {\
                RNext();\
                IfBufferIs("End")\
                    break;\
                ArrayType_PushNull(Type, Dest -> Name);\
                Type##_Ctor(Dest -> Name + Dest -> Name##_Index);\
                Type##_Read(Dest -> Name + Dest -> Name##_Index);\
            } while(1)

#define TemplateReadFuncEnd\
        }\
        String_Dtor(& Buffer);\
        return 1;

#define TemplateReadFuncNonLoopEnd\
        String_Dtor(& Buffer);\
        return 1;
//  }
