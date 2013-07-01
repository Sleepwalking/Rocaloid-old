/*
 * memoryStream.cc
 *
 * Copyright (C) 2013 - Rocaloid Development Group(RDG)
 *
 * Created by rgwan
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "../structure/string.h"
#include "../misc/memopr.h"
#include "../defs.h"
#include <string.h>
#include "memoryStream.h"


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