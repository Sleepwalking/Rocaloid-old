#include "string.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../misc/memopr.h"
#include "array.h"

//#define MEMCHECK
#ifdef MEMCHECK
static int ccount;
static int dcount = 0;
#endif

//****** String Class ******
string::string()
{
	#ifdef MEMCHECK
	++ ccount;
		//printf("String Ctor %d\n", ++ ccount);
	#endif
	length = 0;
	baseptr = 0;
}
string::string(const string& source)
{
	#ifdef MEMCHECK
	++ ccount;
		//printf("String Ctor %d\n", ++ ccount);
	#endif
	baseptr = (char*)mem_malloc(source.length);
	for(length = 0;length < source.length;length ++)
		baseptr[length] = source.baseptr[length];
}
string::string(const char* source)
{
	#ifdef MEMCHECK
	++ ccount;
		//printf("String Ctor %d\n", ++ ccount);
	#endif
	int len = strlen(source);
	baseptr = (char*)mem_malloc(len);
	for(length = 0;length < len;length ++)
		baseptr[length] = source[length];
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
bool string::operator ==(const char* rhs)
{
	int i;
	for(i = 0;i < length;i ++)
		if(rhs[i] != baseptr[i] || rhs[i] == 0)
			return false;
	if(rhs[length] != 0)
		return false;
	return true;
}
bool string::operator !=(const string& rhs)
{
	int i;
	if(rhs.length != length)
		return true;
	for(i = 0;i < rhs.length;i ++)
		if(rhs.baseptr[i] != baseptr[i])
			return true;
	return false;
}
bool string::operator !=(const char* rhs)
{
	int i;
	for(i = 0;i < length;i ++)
		if(rhs[i] != baseptr[i] || rhs[i] == 0)
			return true;
	if(rhs[length] != 0)
		return true;
	return false;
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
string mid(string& source, int from, int count)
{
	string ret;
	int i;
	if(count + from > source.getLength())
		count = source.getLength() - from;
	if(count < 0)
		count = 0;
	ret.allocLength(count);
	char* rethandle = ret.unsafeHandle();
	char* sourcehandle = source.unsafeHandle();
	for(i = 0;i < count;i ++)
		rethandle[i] = sourcehandle[from + i];
	return ret;
}
string mid(string& source, int from)
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
string right(string& source, int count)
{
	string ret;
	int i;
	if(source.getLength() - count < 0)
		count = source.getLength();
	int from = source.getLength() - count;
	ret.allocLength(count);
	char* rethandle = ret.unsafeHandle();
	char* sourcehandle = source.unsafeHandle();
	for(i = 0;i < count;i ++)
		rethandle[i] = sourcehandle[from + i];
	return ret;
}
string left(string& source, int count)
{
	string ret;
	int i;
	if(count > source.getLength())
		count = source.getLength();
	ret.allocLength(count);
	char* rethandle = ret.unsafeHandle();
	char* sourcehandle = source.unsafeHandle();
	for(i = 0;i < count;i ++)
		rethandle[i] = sourcehandle[i];
	return ret;
}
string lowerCase(string& source)
{
	int i;
	int len = source.getLength();
	string ret;
	ret.allocLength(len);
	for(i = 0;i < len;i ++)
		if(source[i] >= 'A' && source[i] <= 'Z')
			ret[i] = source[i] + ('a' - 'A');
		else
			ret[i] = source[i];
	return ret;
}
string upperCase(string& source)
{
	int i;
	int len = source.getLength();
	string ret;
	ret.allocLength(len);
	for(i = 0;i < len;i ++)
		if(source[i] >= 'a' && source[i] <= 'z')
			ret[i] = source[i] + ('A' - 'a');
		else
			ret[i] = source[i];
	return ret;
}
int instr(string& whole, string part, int from)
{
	int i, j;
	int end = whole.getLength() - part.getLength();
	int partlen = part.getLength();
	for(i = from;i <= end;i ++)
	{
		for(j = 0;j < partlen;j ++)
			if(part[j] != whole[i + j])
				goto cont;
		return i;
		cont:;
	}
	return -1;
}
int instr(string& whole, string part)
{
	return instr(whole, part, 0);
}
int instrRev(string& whole, string part, int from)
{
	int i, j;
	int end = whole.getLength() - part.getLength();
	if(from > end)
		from = end;
	int partlen = part.getLength();
	for(i = from;i >= 0;i --)
	{
		for(j = 0;j < partlen;j ++)
			if(part[j] != whole[i + j])
				goto cont;
		return i;
		cont:;
	}
	return -1;
}
int instrRev(string& whole, string part)
{
	return instrRev(whole, part, whole.getLength());
}
string trim(string& source)
{
	string ret;
	int start=0, end=0, i, sourcelen, retlen;
	sourcelen = source.getLength();
	for(i = 0;i < sourcelen;i ++)
		if(source[i] != ' ' && source[i] != '\t')
		{
			start = i;
			break;
		}
	for(i = sourcelen - 1;i >= 0;i --)
		if(source[i] != ' ' && source[i] != '\t')
		{
			end = i;
			break;
		}
	retlen = end - start + 1;
	ret.allocLength(retlen);
	for(i = 0;i < retlen;i ++)
		ret[i] = source[i + start];
	return ret;
}
string ltrim(string& source)
{
	string ret;
	int start=0, end=0, i, sourcelen, retlen;
	sourcelen = source.getLength();
	start = 0;
	for(i = sourcelen - 1;i >= 0;i --)
		if(source[i] != ' ' && source[i] != '\t')
		{
			end = i;
			break;
		}
	retlen = end - start + 1;
	ret.allocLength(retlen);
	for(i = 0;i < retlen;i ++)
		ret[i] = source[i + start];
	return ret;
}
string rtrim(string& source)
{
	string ret;
	int start=0, end, i, sourcelen, retlen;
	sourcelen = source.getLength();
	end = sourcelen - 1;
	for(i = 0;i < sourcelen;i ++)
		if(source[i] != ' ' && source[i] != '\t')
		{
			start = i;
			break;
		}
	retlen = end - start + 1;
	ret.allocLength(retlen);
	for(i = 0;i < retlen;i ++)
		ret[i] = source[i + start];
	return ret;
}
