#ifndef RUTIL_H
#define RUTIL_H

#include "Structure/Array.h"
#include "Structure/String.h"
#include "Misc/Converter.h"
#include "IO/FileStream.h"
#include "IO/StringStream.h"

#define _StructCDtor_(Type)\
    extern void Type##_Ctor(Type* Dest);\
    extern void Type##_Dtor(Type* Dest)

#define AutoClass\
    typedef struct

#define EndClass(Type)\
    Type;\
    _StructCDtor_(Type)

#define _Constructor_(Type) void Type##_Ctor(Type* Dest)
#define _Destructor_(Type) void Type##_Dtor(Type* Dest)

#define DebugPrintf(Type, Statement) printf(#Statement ": %" #Type "\n", Statement);

#endif
