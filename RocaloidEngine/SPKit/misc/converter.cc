#include "converter.h"
#include "../structure/string.h"
#include "../misc/memopr.h"
#include "../defs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
namespace converter
{
	inline string CStr(char source)
	{
		return CStr(&source);
	}
	inline string CStr(string& source)
	{
		return source;
	}
	inline char CChar(string& source)
	{
		return source[0];
	}
	inline byte CByte(char* source)
	{
		return (byte)atoi(source);
	}
	inline int CInt(char* source)
	{
		return atoi(source);
	}
	inline uint CUInt(char* source)
	{
		return (uint)atol(source);
	}
	inline long CLng(char* source)
	{
		return atol(source);
	}
	inline float CSng(char* source)
	{
		return (float)atof(source);
	}
	inline double CDbl(char* source)
	{
		return atof(source);
	}
	
	string CStr(const char* source)
	{
		string ret;
		ret = source;
		return ret;
	}
	string CStr(bool source)
	{
		if(source)
			return CStr("true");
		else
			return CStr("false");
	}
	string CStr(int source)
	{
		char buffer[20];
		sprintf((char*)buffer, "%d", source);
		return CStr(buffer);
	}
	string CStr(byte source)
	{
		char buffer[20];
		sprintf((char*)buffer, "%d", (int)source);
		return CStr(buffer);
	}
	string CStr(long source)
	{
		char buffer[30];
		sprintf((char*)buffer, "%ld", source);
		return CStr(buffer);
	}
	string CStr(float source)
	{
		char buffer[20];
		sprintf((char*)buffer, "%f", source);
		return CStr(buffer);
	}
	string CStr(double source)
	{
		char buffer[30];
		sprintf((char*)buffer, "%f", source);
		return CStr(buffer);
	}
	string CStr(float source, const char* format)
	{
		char buffer[20];
		sprintf((char*)buffer, format, source);
		return CStr(buffer);
	}
	string CStr(double source, const char* format)
	{
		char buffer[30];
		sprintf((char*)buffer, format, source);
		return CStr(buffer);
	}
	
	bool CBool(string& source)
	{
		if(source == CStr("true"))
			return true;
		return false;
	}
	bool CBool(char* source)
	{
		if(strcmp(source, "true"))
			return true;
		return false;
	}
	
	byte CByte(string& source)
	{
		char* chars = source.toChars();
		int ret = atoi(chars);
		mem_free(chars);
		return (byte)ret;
	}
	
	int CInt(string& source)
	{
		char* chars = source.toChars();
		int ret = atoi(chars);
		mem_free(chars);
		return ret;
	}
	
	uint CUInt(string& source)
	{
		char* chars = source.toChars();
		uint ret = (uint)atol(chars);
		mem_free(chars);
		return ret;
	}
	
	long CLng(string& source)
	{
		char* chars = source.toChars();
		long ret = atol(chars);
		mem_free(chars);
		return ret;
	}

	float CSng(string& source)
	{
		char* chars = source.toChars();
		float ret = (float)atof(chars);
		mem_free(chars);
		return ret;
	}
	
	double CDbl(string& source)
	{
		char* chars = source.toChars();
		double ret = atof(chars);
		mem_free(chars);
		return ret;
	}
}
