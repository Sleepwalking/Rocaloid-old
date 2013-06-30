#ifndef TERMINAL_H
#define TERMINAL_H
#include "../structure/string.h"
#include <stdio.h>
#include "../misc/memopr.h"
#include "../misc/converter.h"
using namespace converter;
class terminal
{
	public:
		static string readLine();
		
		static void write(const char* str);
		static void write(string str);
		template <class T> static void write(T source);
		
		static void writeLine(const char* str);
		static void writeLine(string str);
		template <class T> static void writeLine(T source);
};

string terminal::readLine()
{
	char buffer[4096];
	string ret;
	gets(buffer);
	ret = buffer;
	return ret;
}

inline void directPrint(const char* str)
{
	printf(str, 0);
}
void terminal::write(const char* str)
{
	directPrint(str);
}
void terminal::write(string str)
{
	char* chars = str.toChars();
	directPrint(chars);
	mem_free(chars);
}
template <class T> void terminal::write(T source)
{
	terminal:write(CStr(source));
}
void terminal::writeLine(const char* str)
{
	directPrint(str);
	directPrint("\n");
}
void terminal::writeLine(string str)
{
	char* chars = str.toChars();
	directPrint(chars);
	directPrint("\n");
	mem_free(chars);
}
template <class T> void terminal::writeLine(T source)
{
	char* chars = CStr(source).toChars();
	directPrint(chars);
	directPrint("\n");
	mem_free(chars);
}
#endif