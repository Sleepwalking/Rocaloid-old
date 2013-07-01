#ifndef STRINGSTREAM_H
#define STRINGSTREAM_H
#include "memoryStream.h"
class stringStream: public memoryStream
{
	public:	
		template <class T> stringStream(T* ptr);

		string readWord();
		string readLine();
		string readAll();

		inline void nextLine();
		void prevLine();

		inline void writeLine(string data);
};
template <class T> stringStream::stringStream(T* ptr) : memoryStream(ptr){}

string stringStream::readWord()
{
	string ret;
	array<char> tmp;
	char tmpchar;

	tmpchar = *((char*)((byte*)baseptr + offset));
	while(tmpchar == ' ' || tmpchar == '\t'|| tmpchar == '\n')
	{
		offset ++;
		tmpchar = *((char*)((byte*)baseptr + offset));
	}
	
	do
	{
		tmpchar = *((char*)((byte*)baseptr + offset));
		tmp.push(tmpchar);
		offset ++;
	}
	while(tmpchar != ' ' && tmpchar != '\t' && tmpchar != '\n' && tmpchar != 0);

	tmp[tmp.pointer] = 0;
	ret = &tmp[0];	
	return ret;
}
string stringStream::readLine()
{
	string ret;
	array<char> tmp;
	char tmpchar;
	
	do
	{
		tmpchar = *((char*)((byte*)baseptr + offset));
		tmp.push(tmpchar);
		offset ++;
	}
	while(tmpchar != '\n' && tmpchar != 0);

	tmp[tmp.pointer] = 0;
	ret = &tmp[0];	
	return ret;
}
string stringStream::readAll()
{
	string ret((char*)((byte*)baseptr + offset));
	return ret;
}

inline void stringStream::writeLine(string data)
{
	write(data + "\n");
}

inline void stringStream::nextLine()
{
	readLine();
}
void stringStream::prevLine()
{
	char tmpchar;	
	do
	{
		tmpchar = *((char*)((byte*)baseptr + offset));
		offset --;
	}
	while(tmpchar != '\n' && offset > 0);
	
	do
	{
		tmpchar = *((char*)((byte*)baseptr + offset));
		offset --;
	}
	while(tmpchar != '\n' && offset > 0);

	if(offset != 0)
		offset +=2;
}
#endif