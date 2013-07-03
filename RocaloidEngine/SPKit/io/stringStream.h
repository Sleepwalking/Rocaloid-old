#ifndef STRINGSTREAM_H
#define STRINGSTREAM_H
#include "memoryStream.h"
#include "../structure/string.h"
class memoryStream;
class string;
class stringStream: public memoryStream
{
	public:	
		template <class T> stringStream(T* ptr);

		string readWord();
		string readLine();
		string readAll();
		void skipWord();
		void skipLine();

		#define nextLine() skipLine()
		void prevLine();

		inline void writeLine(string data);
};

inline void stringStream::writeLine(string data)
{
	write(data + "\n");
}

template <class T> stringStream::stringStream(T* ptr) : memoryStream(ptr){}


#endif