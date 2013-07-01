#include "fileStream.h"
#include "../structure/string.h"
#include "../structure/array.h"
#include "../misc/memopr.h"
#include <string.h>
#include <stdlib.h>
char fModes[5][5] = {"rb", "wb", "rwb+", "ab+", "wb+"};
binaryStream::binaryStream()
{
	isOpen = false;
	filePtr = 0;
}
binaryStream::~binaryStream()
{
	if(isOpen)
		fclose(fStream);
}
void binaryStream::refreshLength()
{
	fseek(fStream, 0, SEEK_END);
	length = ftell(fStream);
	fseek(fStream, filePtr, SEEK_SET);
}

bool binaryStream::open(string path, openMode fileMode)
{
	char* chars = path.toChars();
	char* fmode = fModes[fileMode];
	fStream = fopen(chars, fmode);
	
	mem_free(chars);
	isOpen = true;
	if(fStream == 0)
		isOpen = false;
	filePtr = 0;
	
	if(isOpen)
		refreshLength();
	return isOpen;
}
bool binaryStream::open(const char* path, openMode fileMode)
{
	char* fmode = fModes[fileMode];
	
	fStream = fopen(path, fmode);
	
	isOpen = true;
	if(fStream == 0)
		isOpen = false;
	filePtr = 0;
	
	if(isOpen)
		refreshLength();
	return isOpen;
}
void binaryStream::close()
{
	if(isOpen)
	{
		isOpen = false;
		fclose(fStream);
	}
}
bool binaryStream::flush()
{
	if(fflush(fStream) == 0)
		return true;
	return false;
}
void binaryStream::setPosition(long position)
{
	filePtr = position;
	fseek(fStream, filePtr, SEEK_SET);
}
long binaryStream::getPosition()
{
	return filePtr;
}
long binaryStream::getLength()
{
	return length;
}
byte binaryStream::readByte()
{
	byte tmp;
	fread(&tmp, 1, 1, fStream);
	filePtr ++;
	fseek(fStream, filePtr, SEEK_SET);
	return tmp;
}
char binaryStream::readChar()
{
	char tmp;
	fread(&tmp, 1, 1, fStream);
	filePtr ++;
	fseek(fStream, filePtr, SEEK_SET);
	return tmp;
}
uint binaryStream::readUInt()
{
	uint tmp;
	fread(&tmp, sizeof(uint), 1, fStream);
	filePtr += sizeof(uint);
	fseek(fStream, filePtr, SEEK_SET);
	return tmp;
}
int binaryStream::readInt()
{
	int tmp;
	fread(&tmp, sizeof(int), 1, fStream);
	filePtr += sizeof(int);
	fseek(fStream, filePtr, SEEK_SET);
	return tmp;
}
bool binaryStream::readBool()
{
	bool tmp;
	fread(&tmp, sizeof(bool), 1, fStream);
	filePtr += sizeof(bool);
	fseek(fStream, filePtr, SEEK_SET);
	return tmp;
}
float binaryStream::readFloat()
{
	float tmp;
	fread(&tmp, sizeof(float), 1, fStream);
	filePtr += sizeof(float);
	fseek(fStream, filePtr, SEEK_SET);
	return tmp;
}
long binaryStream::readLong()
{
	long tmp;
	fread(&tmp, sizeof(long), 1, fStream);
	filePtr += sizeof(long);
	fseek(fStream, filePtr, SEEK_SET);
	return tmp;
}
ulong binaryStream::readULong()
{
	ulong tmp;
	fread(&tmp, sizeof(ulong), 1, fStream);
	filePtr += sizeof(ulong);
	fseek(fStream, filePtr, SEEK_SET);
	return tmp;
}
string binaryStream::readString()
{
	//int count;
	char tmpchar;
	array<char> tmp;
	string ret;
	tmp.setUbound(30);

	do
	{
		fread(&tmpchar, 1, 1, fStream);
		tmp.push(tmpchar);
		filePtr ++;
		fseek(fStream, filePtr, SEEK_SET);
	}
	while(tmpchar != 0 && filePtr < length);

	ret = &tmp[0];
	setPosition(filePtr);
	return ret;	
}
int binaryStream::readChars(char* buffer)
{
	int count = 0;
	char tmpchar;

	do
	{
		fread(&tmpchar, 1, 1, fStream);
		buffer[count] = tmpchar;
		count ++;
		filePtr ++;
		fseek(fStream, filePtr, SEEK_SET);
	}
	while(tmpchar != 0 && filePtr < length);
	
	setPosition(filePtr);
	return count;
}
void binaryStream::readBuffer(void* buffer, long byteCount)
{
	fread(buffer, 1, byteCount, fStream);
	filePtr += byteCount;
	fseek(fStream, filePtr, SEEK_SET);
}
void binaryStream::write(byte data)
{
	fwrite(&data, 1, 1, fStream);
	filePtr ++;
	fseek(fStream, filePtr, SEEK_SET);
}
void binaryStream::write(char data)
{
	fwrite(&data, 1, 1, fStream);
	filePtr ++;
	fseek(fStream, filePtr, SEEK_SET);
}
void binaryStream::write(uint data)
{
	fwrite(&data, sizeof(uint), 1, fStream);
	filePtr += sizeof(uint);
	fseek(fStream, filePtr, SEEK_SET);
}
void binaryStream::write(int data)
{
	fwrite(&data, sizeof(int), 1, fStream);
	filePtr += sizeof(int);
	fseek(fStream, filePtr, SEEK_SET);
}
void binaryStream::write(bool data)
{
	fwrite(&data, sizeof(bool), 1, fStream);
	filePtr += sizeof(bool);
	fseek(fStream, filePtr, SEEK_SET);
}
void binaryStream::write(double data)
{
	fwrite(&data, sizeof(double), 1, fStream);
	filePtr += sizeof(double);
	fseek(fStream, filePtr, SEEK_SET);
}
void binaryStream::write(float data)
{
	fwrite(&data, sizeof(float), 1, fStream);
	filePtr += sizeof(float);
	fseek(fStream, filePtr, SEEK_SET);
}
void binaryStream::write(long data)
{
	fwrite(&data, sizeof(long), 1, fStream);
	filePtr += sizeof(long);
	fseek(fStream, filePtr, SEEK_SET);
}
void binaryStream::write(ulong data)
{
	fwrite(&data, sizeof(ulong), 1, fStream);
	filePtr += sizeof(ulong);
	fseek(fStream, filePtr, SEEK_SET);
}
void binaryStream::writeChars(char* data)
{
	int len = strlen(data);
	fwrite(&data[0], 1, len, fStream);
	filePtr += len;
	fseek(fStream, filePtr, SEEK_SET);
}
void binaryStream::writeBuffer(void* data, long count)
{
	fwrite(data, 1, count, fStream);
	filePtr += count;
	fseek(fStream, filePtr, SEEK_SET);	
}

textStream::textStream()
{
	isOpen = false;
	filePtr = 0;
}
textStream::~textStream()
{
	if(isOpen)
		fclose(fStream);
}

string textStream::readWord()
{
	string ret;
	array<char> tmp;
	char tmpchar;
	
	fread(&tmpchar, 1, 1, fStream);
	while(tmpchar == ' ' || tmpchar == '\t'|| tmpchar == '\n')
	{
		filePtr ++;
		fseek(fStream, filePtr, SEEK_SET);
		fread(&tmpchar, 1, 1, fStream);
	}
	
	fseek(fStream, filePtr, SEEK_SET);
	do
	{
		fread(&tmpchar, 1, 1, fStream);
		tmp.push(tmpchar);
		filePtr ++;
		fseek(fStream, filePtr, SEEK_SET);
	}
	while(tmpchar != ' ' && tmpchar != '\t' && tmpchar != '\n' && tmpchar != 0 && filePtr < length);

	tmp[tmp.pointer] = 0;
	ret = &tmp[0];	
	return ret;
}
string textStream::readLine()
{
	string ret;
	array<char> tmp;
	char tmpchar;
	
	do
	{
		fread(&tmpchar, 1, 1, fStream);
		tmp.push(tmpchar);
		filePtr ++;
		fseek(fStream, filePtr, SEEK_SET);
	}
	while(tmpchar != '\n' && tmpchar != 0 && filePtr < length);

	tmp[tmp.pointer] = 0;
	ret = &tmp[0];	
	return ret;
}
string textStream::readAll()
{
	string ret;
	array<char> tmp;
	tmp.setUbound(length);

	fseek(fStream, 0, SEEK_SET);
	fread(&tmp[0], 1, length, fStream);
	tmp[length] = 0;

	ret = &tmp[0];
	filePtr = length;
	return ret;
}
void textStream::write(string data)
{
	writeBuffer(data.unsafeHandle(), data.getLength());
}
void textStream::writeLine(string data)
{
	write(data + "\n");
}
void textStream::nextLine()
{
	readLine();
}
void textStream::prevLine()
{
	char tmpchar;	
	do
	{
		fread(&tmpchar, 1, 1, fStream);
		filePtr --;
		fseek(fStream, filePtr, SEEK_SET);
	}
	while(tmpchar != '\n' && filePtr > 0);
	
	do
	{
		fread(&tmpchar, 1, 1, fStream);
		filePtr --;
		fseek(fStream, filePtr, SEEK_SET);
	}
	while(tmpchar != '\n' && filePtr > 0);

	if(filePtr != 0)
		filePtr +=2;
	fseek(fStream, filePtr, SEEK_SET);
}