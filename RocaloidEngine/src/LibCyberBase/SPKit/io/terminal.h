#ifndef TERMINAL_H
#define TERMINAL_H
#include "../structure/string.h"
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
#endif