#ifndef TERMINAL_H
#define TERMINAL_H
#include "../structure/string.h"
#include <stdlib.h>
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
extern void directPrint(const char* str);
template <class T> void terminal::write(T source)
{
	terminal:write(CStr(source));
}
template <class T> void terminal::writeLine(T source)
{
	char* chars = CStr(source).toChars();
	directPrint(chars);
	directPrint("\n");
	free(chars);
}
#endif