#ifndef DEFS_H
#define DEFS_H
typedef int integer;
typedef bool boolean;
typedef bool bit;
typedef unsigned char byte;
typedef float single;
typedef unsigned int uinteger;
typedef signed char sbyte;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;

typedef short int int16;
typedef int int32;
typedef long int int64;

#define CPtr(x) ((void*)x)
#define GetPtr(x) (&x)

#define PDbl(x) (*(double*)x)
#define PSng(x) (*(single*)x)
#define PLong(x) (*(long*)x)
#define PULong(x) (*(ulong*)x)
#define PInt(x) (*(int*)x)
#define PUInt(x) (*(uint*)x)
#define PChar(x) (*(char*)x)
#define PByte(x) (*(byte*)x)
#define PBool(x) (*(bool*)x)
#define PBit(x) (*(bit*)x)

#define CType(x, y) ((y)x)

#define delegatordef(name, rettype) typedef rettype (*name)()
#define lfor(intvar, time, do) for(int intvar = 0;intvar < time;intvar ++){do};
#define lsum(retvar, from, to, expr) retvar = 0; for(double i = from;i < to;i ++){retvar += expr;}


#define CLI terminal::
#define wLine(x) terminal::writeLine(x)
#define rLine(x) terminal::readLine(x)
#define wr(x) terminal::write(x)
#endif