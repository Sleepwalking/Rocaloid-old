#ifndef CONVERTER_H
#define CONVERTER_H
#include "../structure/string.h"
#include "../misc/memopr.h"
#include "../defs.h"
#include <stdlib.h>
#include <stdio.h>
namespace converter
{
	string CStr(const char* source);
	string CStr(bool source);
	inline string CStr(char source);
	inline string CStr(string& source);
	string CStr(byte source);
	string CStr(int source);
	string CStr(long source);
	string CStr(float source);
	string CStr(double source);
	string CStr(float source, const char* format);
	string CStr(double source, const char* format);

	bool CBool(string& source);
	bool CBool(char* source);
	inline bool CBool(bool source);
	inline bool CBool(char source);
	inline bool CBool(byte source);
	inline bool CBool(int source);
	inline bool CBool(float source);
	inline bool CBool(double source);
	inline bool CBool(long source);
	
	inline char CChar(string& source);
	inline char CChar(char* source);
	inline char CChar(byte source);
	inline char CChar(int source);
	inline char CChar(float source);
	inline char CChar(double source);
	inline char CChar(long source);

	byte CByte(string& source);
	inline byte CByte(char* source);
	inline byte CByte(char source);
	inline byte CByte(byte source);
	inline byte CByte(int source);
	inline byte CByte(float source);
	inline byte CByte(double source);
	inline byte CByte(long source);
	
	int CInt(string& source);
	inline int CInt(char* source);
	inline int CInt(char source);
	inline int CInt(byte source);
	inline int CInt(int source);
	inline int CInt(float source);
	inline int CInt(double source);
	inline int CInt(long source);
	
	uint CUInt(string& source);
	inline uint CUInt(char* source);
	inline uint CUInt(bool source);
	inline uint CUInt(char source);
	inline uint CUInt(byte source);
	inline uint CUInt(int source);
	inline uint CUInt(float source);
	inline uint CUInt(double source);
	inline uint CUInt(long source);
	
	long CLng(string& source);
	inline long CLng(char* source);
	inline long CLng(char source);
	inline long CLng(bool source);
	inline long CLng(byte source);
	inline long CLng(int source);
	inline long CLng(float source);
	inline long CLng(double source);
	inline long CLng(long source);
	
	float CSng(string& source);
	inline float CSng(char* source);
	inline float CSng(bool source);
	inline float CSng(char source);
	inline float CSng(byte source);
	inline float CSng(int source);
	inline float CSng(float source);
	inline float CSng(double source);
	inline float CSng(long source);

	#define CFlt(x) (CSng(x))
	
	double CDbl(string& source);
	inline double CDbl(char* source);
	inline double CDbl(char source);
	inline double CDbl(bool source);
	inline double CDbl(byte source);
	inline double CDbl(int source);
	inline double CDbl(float source);
	inline double CDbl(double source);
	inline double CDbl(long source);
	
	inline string CStr(char source)
	{
		return CStr(&source);
	}
	inline string CStr(string& source)
	{
		return source;
	}
	
	inline bool CBool(bool source)
	{
		return source;
	}
	inline bool CBool(char source)
	{
		return (int)source;
	}
	inline bool CBool(int source)
	{
		return source;
	}
	inline bool CBool(byte source)
	{
		return source;
	}
	inline bool CBool(float source)
	{
		return (int)source;
	}
	inline bool CBool(double source)
	{
		return (int)source;
	}
	inline bool CBool(long source)
	{
		return (int)source;
	}
	
	inline char CChar(string& source)
	{
		return source[0];
	}
	inline char CChar(char* source)
	{
		return source[0];
	}
	inline char CChar(char source)
	{
		return source;
	}
	inline char CChar(int source)
	{
		return source;
	}
	inline char CChar(byte source)
	{
		return source;
	}
	inline char CChar(float source)
	{
		return (int)source;
	}
	inline char CChar(double source)
	{
		return (int)source;
	}
	inline char CChar(long source)
	{
		return (int)source;
	}
	
	inline byte CByte(char* source)
	{
		return (byte)atoi(source);
	}
	inline byte CByte(char source)
	{
		return (byte)source;
	}
	inline byte CByte(int source)
	{
		return (byte)source;
	}
	inline byte CByte(byte source)
	{
		return source;
	}
	inline byte CByte(float source)
	{
		return (byte)source;
	}
	inline byte CByte(double source)
	{
		return (byte)source;
	}
	inline byte CByte(long source)
	{
		return (byte)source;
	}
	
	inline int CInt(char* source)
	{
		return atoi(source);
	}
	inline int CInt(char source)
	{
		return (int)source;
	}
	inline int CInt(int source)
	{
		return source;
	}
	inline int CInt(byte source)
	{
		return source;
	}
	inline int CInt(float source)
	{
		return (int)source;
	}
	inline int CInt(double source)
	{
		return (int)source;
	}
	inline int CInt(long source)
	{
		return (int)source;
	}
	
	inline uint CUInt(char* source)
	{
		return (uint)atol(source);
	}
	inline uint CUInt(bool source)
	{
		return (uint)source;
	}
	inline uint CUInt(char source)
	{
		return (uint)source;
	}
	inline uint CUInt(int source)
	{
		return (uint)source;
	}
	inline uint CUInt(byte source)
	{
		return (uint)source;
	}
	inline uint CUInt(float source)
	{
		return (uint)source;
	}
	inline uint CUInt(double source)
	{
		return (uint)source;
	}
	inline uint CUInt(long source)
	{
		return (uint)source;
	}
	
	inline long CLng(char* source)
	{
		return atol(source);
	}
	inline long CLng(bool source)
	{
		return (long)source;
	}
	inline long CLng(char source)
	{
		return (long)source;
	}
	inline long CLng(int source)
	{
		return (long)source;
	}
	inline long CLng(byte source)
	{
		return (long)source;
	}
	inline long CLng(float source)
	{
		return (long)source;
	}
	inline long CLng(double source)
	{
		return (long)source;
	}
	inline long CLng(long source)
	{
		return source;
	}
	
	inline float CSng(char* source)
	{
		return (float)atof(source);
	}
	inline float CSng(bool source)
	{
		return (float)source;
	}
	inline float CSng(char source)
	{
		return (float)source;
	}
	inline float CSng(int source)
	{
		return (float)source;
	}
	inline float CSng(byte source)
	{
		return (float)source;
	}
	inline float CSng(float source)
	{
		return source;
	}
	inline float CSng(double source)
	{
		return (float)source;
	}
	inline float CSng(long source)
	{
		return (float)source;
	}
	
	inline double CDbl(char* source)
	{
		return atof(source);
	}
	inline double CDbl(bool source)
	{
		return (double)source;
	}
	inline double CDbl(char source)
	{
		return (double)source;
	}
	inline double CDbl(int source)
	{
		return (double)source;
	}
	inline double CDbl(byte source)
	{
		return (double)source;
	}
	inline double CDbl(float source)
	{
		return (double)source;
	}
	inline double CDbl(double source)
	{
		return (double)source;
	}
	inline double CDbl(long source)
	{
		return (double)source;
	}
}
#endif