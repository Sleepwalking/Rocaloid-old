#include "memoryStream.h"
#include "../structure/string.h"
#include "../misc/memopr.h"
#include <string.h>

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