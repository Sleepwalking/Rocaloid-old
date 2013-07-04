#include "terminal.h"
#include <stdio.h>
#include "../misc/memopr.h"
#include "../misc/converter.h"

using namespace converter;
string terminal::readLine()
{
	char buffer[4096];
	string ret;
	gets(buffer);
	ret = buffer;
	return ret;
}

void directPrint(const char* str)
{
	puts(str);
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
}
void terminal::writeLine(string str)
{
	char* chars = str.toChars();
	directPrint(chars);
	mem_free(chars);
}
template <class T> void terminal::writeLine(T source)
{
	char* chars = CStr(source).toChars();
	directPrint(chars);
	mem_free(chars);
}