#ifndef TERMINAL_H
#define TERMINAL_H
#include "../structure/string.h"
#include <stdio.h>
#include "../misc/memopr.h"
#include "../misc/converter.h"
using namespace converter;
namespace terminal
{
		static string readLine();
		
		void write(const char* str);
		void write(string str);
		template <class T> static void write(T source);
		
		void writeLine(const char* str);
		void writeLine(string str);
		template <class T> static void writeLine(T source);
string inline readLine()
{
	char buffer[4096];
	string ret;
	gets(buffer);
	ret = buffer;
	return ret;
}

inline void directPrint(const char* str)
{
	puts(str);
}
void inline write(const char* str)
{
	directPrint(str);
}
void inline write(string str)
{
	char* chars = str.toChars();
	directPrint(chars);
	mem_free(chars);
}
template <class T> void write(T source)
{
	terminal:write(CStr(source));
}
void inline writeLine(const char* str)
{
	directPrint(str);
	//directPrint("\n");
}
void inline writeLine(string str)
{
	char* chars = str.toChars();
	directPrint(chars);
	//directPrint("\n");
	mem_free(chars);
}
template <class T> void writeLine(T source)
{
	char* chars = CStr(source).toChars();
	directPrint(chars);
	//directPrint("\n");
	mem_free(chars);
}
};


#endif