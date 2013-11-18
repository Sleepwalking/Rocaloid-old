#ifndef RDL_H
#define RDL_H

#include "../../RUtil/Structure/String.h"
#include "../../RUtil/IO/StringStream.h"
#include <stdint.h>

extern void RDL_ReadIgnoreComment(String* Dest, StringStream* Src);

extern void RDL_SetWriteStringStream(StringStream* Dest);
extern void RDL_SetWriteInitialSize(int32_t Size);
extern void RDL_WriteString(String* Src);
extern void RDL_WriteChars(char* Src);
extern void RDL_WriteNewLine();
extern void RDL_WritePushIndent();
extern void RDL_WritePopIndent();

#define String_Read(Dest) String_Copy(Dest, & Buffer)
#define float_Read(Dest) *(Dest) = CFloatStr(& Buffer)
#define double_Read(Dest) *(Dest) = CDoubleStr(& Buffer)
#define int_Read(Dest) *(Dest) = CIntStr(& Buffer)

#define String_Write(_Data_) RDL_WriteString(_Data_)
#define int_Write(_Data_) do { CStrInt(& Buffer, *(_Data_)); RDL_WriteString(& Buffer); } while(0)
#define float_Write(_Data_) do { CStrFloat(& Buffer, *(_Data_)); RDL_WriteString(& Buffer);  } while(0)
#define double_Write(_Data_) do { CStrDouble(& Buffer, *(_Data_)); RDL_WriteString(& Buffer);  } while(0)

#define float_Ctor(Dest)
#define double_Ctor(Dest)
#define int_Ctor(Dest)
#define float_Dtor(Dest)
#define double_Dtor(Dest)
#define int_Dtor(Dest)

#define RNext() RDL_ReadIgnoreComment(& Buffer, Reader)
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
                    ArrayType_PushNull(Type, Name);\
                    Type##_Ctor(Name + Name##_Index);\
                    Type##_Read(Name + Name##_Index);\
                }\
            } while(1)

#define TemplateReadFuncStructuredDynamicList(Type, Name, Identifier)\
            do\
            {\
                RNext();\
                IfBufferIs("End")\
                    break;\
                IfBufferIs(Identifier)\
                {\
                    ArrayType_PushNull(Type, Name);\
                    Type##_Ctor(Name + Name##_Index);\
                    Type##_Read(Name + Name##_Index);\
                }\
            } while(1)

#define TemplateReadFuncEmbededDynamicList(Type, Name)\
            do\
            {\
                RNext();\
                IfBufferIs("End")\
                    break;\
                ArrayType_PushNull(Type, Name);\
                Type##_Ctor(Name + Name##_Index);\
                Type##_Read(Name + Name##_Index);\
            } while(1)

#define TemplateReadFuncEmbededStaticList(Type, Name, IndexNum)\
            do\
            {\
                RNext();\
                if(Name##_Index >= IndexNum)\
                    break;\
                ArrayType_PushNull(Type, Name);\
                Type##_Ctor(Name + Name##_Index);\
                Type##_Read(Name + Name##_Index);\
            } while(1)

#define TemplateReadFuncEnd\
        }\
        String_Dtor(& Buffer);\
        return 1;

#define TemplateReadFuncNonLoopEnd\
        String_Dtor(& Buffer);\
        return 1;
//  }

#define TemplateWriteFunc(Type)\
    Type##_Write(Type* Src)
//  {
#define TemplateWriteFuncHead(Identifier)\
        String Buffer;\
        String_Ctor(& Buffer);\
        RDL_WriteChars(Identifier);\
        RDL_WritePushIndent();\
        RDL_WriteNewLine()
#define TemplateWriteFuncEnd\
        RDL_WritePopIndent();\
        RDL_WriteChars("End");\
        RDL_WriteNewLine();\
        String_Dtor(& Buffer);\
        return 1;
//  }

#define TemplateWriteFuncList(Type, Name, Identifier, FullFunc)\
    do\
    {\
        int __i__;\
        RDL_WriteChars(Identifier);\
        RDL_WritePushIndent();\
        if(FullFunc) RDL_WriteNewLine();\
        for(__i__ = 0; __i__ <= Src -> Name##_Index; __i__ ++)\
            Type##_Write((Src -> Name) + __i__);\
        RDL_WritePopIndent();\
        if(! FullFunc) RDL_WriteNewLine();\
        RDL_WriteChars("End");\
    } while(0)\

#define TemplateWriteFuncEmbededStaticList(Type, Name)\
    do\
    {\
        int __i__;\
        for(__i__ = 0; __i__ <= Src -> Name##_Index; __i__ ++)\
            Type##_Write((Src -> Name) + __i__);\
    } while(0)\

#endif
