#ifndef TERMINAL_H
#define TERMINAL_H
#include "../structure/string.h"
#include "../misc/converter.h"
#include <stdlib.h>
namespace terminal
{
		string readLine();
		
		void write(const char* str);
		void write(string str);
		template <class T> static void write(T source);
		
		 void writeLine(const char* str);
		 void writeLine(string str);
		template <class T> static void writeLine(T source);

		void directPrint(const char* str);
	
		template <class T> void write(T source)
		{
			terminal:write(CStr(source));
		}
		template <class T> void writeLine(T source)
		{
			char* chars = converter::CStr(source).toChars();
			directPrint(chars);
			free(chars);
		}
};


#endif