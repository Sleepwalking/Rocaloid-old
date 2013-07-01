#ifndef STRING_H
#define STRING_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../misc/memopr.h"
class string
{
	public:
		string();
		string(const string& source);
		string(const char* source);
		~string();
		
		int getLength();
		bool allocLength(int newLength);
		
		inline char& operator [](int index);
		string& operator =(const string& rhs);
		string& operator =(const char* rhs);
		string operator +(const string& rhs);
		string operator +(const char* rhs);
		string& operator +=(const string& rhs);
		string& operator +=(const char* rhs);

		bool operator ==(const string& rhs);

		char* toChars();
		inline char* unsafeHandle();

	private:
		int length;
		char* baseptr;
};
inline char& string::operator [](int index)
{
	return baseptr[index];
}
inline char* string::unsafeHandle()
{
	return baseptr;
}
string mid(string& source, int from, int count);
string mid(string& source, int from);
string right(string& source, int count);
string left(string& source, int count);
string lowerCase(string& source);
string upperCase(string& source);
int instr(string& whole, string part, int from);
int instr(string& whole, string part);
int instrRev(string& whole, string part, int from);
int instrRev(string& whole, string part);
string strim(string &source);
string trim(string &source);
string ltrim(string& source);
string rtrim(string& source);
#endif