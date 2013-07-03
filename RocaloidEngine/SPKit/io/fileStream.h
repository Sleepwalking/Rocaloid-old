#ifndef FILESTREAM_H
#define FILESTREAM_H
#include "../defs.h"
#include <stdio.h>
enum openMode
{
	READONLY = 0,
	WRITEONLY = 1,
	READWRITE = 2,
	APPEND = 3,
	CREATE = 4
};
class string;
class binaryStream
{
	public:
		binaryStream();
		~binaryStream();
		
		bool open(string path, openMode fileMode);
		bool open(const char* path, openMode fileMode);
		void close();
		bool flush();
		
		void setPosition(long position);
		long getPosition();
		long getLength();
		
		byte readByte();
		char readChar();
		short int readShort();
		uint readUInt();
		int readInt();
		bool readBool();
		double readDbl();
		float readFloat();
		#define readSng() readFloat()
		long readLong();
		ulong readULong();
		string readString();
		int readChars(char* buffer);
		void readBuffer(void* buffer, long byteCount);

		void write(byte data);
		void write(char data);
		void write(short int data);
		void write(uint data);
		void write(int data);
		void write(bool data);
		void write(double data);
		void write(float data);
		void write(long data);
		void write(ulong data);
		void writeChars(char* buffer);
		void writeBuffer(void* buffer, long byteCount);
	protected:
		void refreshLength();
		openMode fileMode;
		bool isOpen;
		long filePtr;
		FILE* fStream;
		int length;
};
class textStream : public binaryStream
{
	public:
		textStream();
		~textStream();
		
		string readWord();
		string readLine();
		string readAll();

		void nextLine();
		void prevLine();

		void write(string data);
		void writeLine(string data);
};
#endif