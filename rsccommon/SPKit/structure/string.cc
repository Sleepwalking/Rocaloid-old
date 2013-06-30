#include "string.h"
//#define MEMCHECK
//****** String Class ******

#ifdef MEMCHECK
static int ccount;
static int dcount = 0;
#endif

string::string()
{
#ifdef MEMCHECK
	printf("String Ctor %d\n", ++ ccount);
#endif
	length = 0;
	baseptr = 0;
}
string::string(const string& source)
{
#ifdef MEMCHECK
	printf("String Ctor %d\n", ++ ccount);
#endif
	baseptr = (char*)mem_malloc(source.length);
	for(length = 0;length < source.length;length ++)
		baseptr[length] = source.baseptr[length];
}
string::~string()
{
#ifdef MEMCHECK
	printf("String Destr = %d Ctor = %d\n", ++ dcount, ccount);
#endif
	if(baseptr != 0)
		mem_free(baseptr);
}
int string::getLength()
{
	return length;
}
bool string::allocLength(int newLength)
{
	if(baseptr != 0)
		mem_free(baseptr);
	baseptr = (char*)mem_malloc(newLength);
	if(baseptr == 0)
		return false;
	length = newLength;
	return true;
}
string& string::operator =(const string& rhs)
{
	if(baseptr != 0)
		mem_free(baseptr);
	baseptr = (char*)mem_malloc(rhs.length);
	for(length = 0;length < rhs.length;length ++)
		baseptr[length] = rhs.baseptr[length];
	return *this;
}
string& string::operator =(const char* rhs)
{
	if(baseptr != 0)
		mem_free(baseptr);
	int rhslen = strlen(rhs);
	baseptr = (char*)mem_malloc(rhslen);
	for(length = 0;length < rhslen;length ++)
		baseptr[length] = rhs[length];
	return *this;
}
string string::operator +(const string& rhs)
{
	int i;
	string ret;
	ret.baseptr = (char*)mem_malloc(rhs.length + length);
	for(i = 0;i < length;i ++)
		ret.baseptr[i] = baseptr[i];
	for(i = 0;i < rhs.length;i ++)
		ret.baseptr[i + length] = rhs.baseptr[i];
	ret.length = length + rhs.length;
	return ret;
}
string string::operator +(const char* rhs)
{
	int i;
	string ret;
	int rhslen = strlen(rhs);
	ret.baseptr = (char*)mem_malloc(rhslen + length);
	for(i = 0;i < length;i ++)
		ret.baseptr[i] = baseptr[i];
	for(i = 0;i < rhslen;i ++)
		ret.baseptr[i + length] = rhs[i];
	ret.length = length + rhslen;
	return ret;
}
string& string::operator +=(const char* rhs)
{
	int i;
	int rhslen = strlen(rhs);
	char* newptr = (char*)mem_malloc(rhslen + length);
	for(i = 0;i < length;i ++)
		newptr[i] = baseptr[i];
	for(i = 0;i < rhslen;i ++)
		newptr[i + length] = rhs[i];
	length += rhslen;
	free(baseptr);
	baseptr = newptr;
	return *this;
}
string& string::operator +=(const string& rhs)
{
	int i;
	char* newptr = (char*)mem_malloc(rhs.length + length);
	for(i = 0;i < length;i ++)
		newptr[i] = baseptr[i];
	for(i = 0;i < rhs.length;i ++)
		newptr[i + length] = rhs.baseptr[i];
	length += rhs.length;
	free(baseptr);
	baseptr = newptr;
	return *this;
}
bool string::operator ==(const string& rhs)
{
	int i;
	if(rhs.length != length)
		return false;
	for(i = 0;i < rhs.length;i ++)
		if(rhs.baseptr[i] != baseptr[i])
			return false;
	return true;	
}
char* string::toChars()
{
	char* retptr = (char*)mem_malloc(length + 1);
	int i;
	for(i = 0;i < length;i ++)
		retptr[i] = baseptr[i];
	retptr[length] = 0;
	return retptr;
}
// ****** String Utils ******
string mid(string source, int from, int count)
{
	string ret;
	int i;
	ret.allocLength(count);
	char* rethandle = ret.unsafeHandle();
	char* sourcehandle = source.unsafeHandle();
	for(i = 0;i < count;i ++)
		rethandle[i] = sourcehandle[from + i];
	return ret;
}
string mid(string source, int from)
{
	string ret;
	int i;
	int count = source.getLength() - from;
	ret.allocLength(count);
	char* rethandle = ret.unsafeHandle();
	char* sourcehandle = source.unsafeHandle();
	for(i = 0;i < count;i ++)
		rethandle[i] = sourcehandle[from + i];
	return ret;
}
string right(string source, int count)
{
	string ret;
	int i;
	int from = source.getLength() - count;
	ret.allocLength(count);
	char* rethandle = ret.unsafeHandle();
	char* sourcehandle = source.unsafeHandle();
	for(i = 0;i < count;i ++)
		rethandle[i] = sourcehandle[from + i];
	return ret;
}
string left(string source, int count)
{
	string ret;
	int i;
	ret.allocLength(count);
	char* rethandle = ret.unsafeHandle();
	char* sourcehandle = source.unsafeHandle();
	for(i = 0;i < count;i ++)
		rethandle[i] = sourcehandle[i];
	return ret;
}