#ifndef MEMORYSTREAM_H
#define MEMORYSTREAM_H
#include "../misc/memopr.h"
#include "../defs.h"
#include <string.h>
class memoryStream
{
	public:
		template <class T> memoryStream(T* ptr);

		template <class T> void setBase(T* ptr);
		inline void setPosition(long newoffset);
		inline long getPosition();

		inline bool readBool();
		inline char readChar();
		inline byte readByte();
		inline int readInt();
		inline uint readUInt();
		inline float readFloat();
		#define readSng() readFloat()
		inline double readDbl();
		inline long readLong();
		inline ulong readULong();
		string readString();
		int readChars(char* buffer);
		void readBuffer(void* buffer, long byteCount);

		inline void write(bool data);
		inline void write(char data);
		inline void write(byte data);
		inline void write(int data);
		inline void write(uint data);
		inline void write(float data);
		inline void write(double data);
		inline void write(long data);
		inline void write(ulong data);
		void write(string data);
		void writeChars(const char* buffer);
		void writeBuffer(void* buffer, long byteCount);
	private:
		void* baseptr;
		long offset;
};
template <class T> memoryStream::memoryStream(T* ptr)
{
	baseptr = (void*) ptr;
}
template <class T> void memoryStream::setBase(T* ptr)
{
	baseptr = (void*) ptr;
}

inline void memoryStream::setPosition(long newoffset)
{
	offset = newoffset;
}
inline long memoryStream::getPosition()
{
	return offset;
}
inline bool memoryStream::readBool()
{
	bool ret = *((bool*)((byte*)baseptr + offset));
	offset ++;
	return ret;
}
inline char memoryStream::readChar()
{
	char ret = *((char*)((byte*)baseptr + offset));
	offset ++;
	return ret;
}
inline byte memoryStream::readByte()
{
	byte ret = *((byte*)baseptr + offset);
	offset ++;
	return ret;
}
inline int memoryStream::readInt()
{
	int ret = *((int*)((byte*)baseptr + offset));
	offset += sizeof(int);
	return ret;
}
inline uint memoryStream::readUInt()
{
	uint ret = *((uint*)((byte*)baseptr + offset));
	offset += sizeof(uint);
	return ret;
}
inline float memoryStream::readFloat()
{
	float ret = *((float*)((byte*)baseptr + offset));
	offset += sizeof(float);
	return ret;
}
inline double memoryStream::readDbl()
{
	double ret = *((double*)((byte*)baseptr + offset));
	offset += sizeof(double);
	return ret;
}
inline long memoryStream::readLong()
{
	long ret = *((long*)((byte*)baseptr + offset));
	offset += sizeof(long);
	return ret;
}
inline ulong memoryStream::readULong()
{
	ulong ret = *((ulong*)((byte*)baseptr + offset));
	offset += sizeof(ulong);
	return ret;
}
string memoryStream::readString()
{
	char* ptr = (char*)((byte*)baseptr + offset);
	string ret;
	ret = ptr;	
	offset += ret.getLength() + 1;
	return ret;
}
int memoryStream::readChars(char* buffer)
{
	char* ptr = (char*)((byte*)baseptr + offset);
	int len = strlen(ptr);
	strcpy(buffer, ptr);

	offset += len + 1;
	return len;
}

inline void memoryStream::write(bool data)
{
	*((bool*)((byte*)baseptr + offset)) = data;
	offset ++;
}
inline void memoryStream::write(char data)
{
	*((char*)((byte*)baseptr + offset)) = data;
	offset ++;
}
inline void memoryStream::write(byte data)
{
	*((byte*)((byte*)baseptr + offset)) = data;
	offset ++;
}
inline void memoryStream::write(int data)
{
	*((int*)((byte*)baseptr + offset)) = data;
	offset += sizeof(int);
}
inline void memoryStream::write(uint data)
{
	*((uint*)((byte*)baseptr + offset)) = data;
	offset += sizeof(uint);
}
inline void memoryStream::write(float data)
{
	*((float*)((byte*)baseptr + offset)) = data;
	offset += sizeof(float);
}
inline void memoryStream::write(double data)
{
	*((double*)((byte*)baseptr + offset)) = data;
	offset += sizeof(double);
}
inline void memoryStream::write(long data)
{
	*((long*)((byte*)baseptr + offset)) = data;
	offset += sizeof(long);
}
inline void memoryStream::write(ulong data)
{
	*((ulong*)((byte*)baseptr + offset)) = data;
	offset += sizeof(ulong);
}
void memoryStream::write(string data)
{
	char* ptr = (char*)((byte*)baseptr + offset);
	memcpy(ptr, data.unsafeHandle(), data.getLength());
	offset += data.getLength();
	*(char*)((byte*)baseptr + offset) = 0;
	offset ++;
}
void memoryStream::writeChars(const char* buffer)
{
	int bufferlen = strlen(buffer);
	char* ptr = (char*)((byte*)baseptr + offset);
	memcpy(ptr, buffer, bufferlen);
	offset += bufferlen;
	*(char*)((byte*)baseptr + offset) = 0;
	offset ++;
}
void memoryStream::writeBuffer(void* buffer, long byteCount)
{
	char* ptr = (char*)((byte*)baseptr + offset);
	memcpy(ptr, buffer, byteCount);
	offset += byteCount;
}
#endif