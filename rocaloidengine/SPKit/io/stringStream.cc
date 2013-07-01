/*
 * stringStream.cc
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
#include "memoryStream.h"
#include "stringStream.h"

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
void stringStream::skipWord()
{
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
		offset ++;
	}
	while(tmpchar != ' ' && tmpchar != '\t' && tmpchar != '\n' && tmpchar != 0);
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
void stringStream::skipLine()
{
	char tmpchar;
	
	do
	{
		tmpchar = *((char*)((byte*)baseptr + offset));
		offset ++;
	}
	while(tmpchar != '\n' && tmpchar != 0);
}
string stringStream::readAll()
{
	string ret((char*)((byte*)baseptr + offset));
	return ret;
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
void split(string& source, array<string>& dest)
{
	int sourcelen = source.getLength();
	int wordnum = 0;
	char* tmpchars = (char*)mem_malloc(sourcelen + 1);
	memcpy(tmpchars, source.unsafeHandle(), sourcelen);
	tmpchars[sourcelen] = 0;
	stringStream tmpstream(tmpchars);

	/*tmpstream.setPosition(0);
	while(tmpstream.getPosition() < sourcelen)
	{
		tmpstream.skipWord();
		wordnum ++;
	}
	dest.setUbound(wordnum);*/
	
	tmpstream.setPosition(0);
	while(tmpstream.getPosition() < sourcelen)
		dest.push(tmpstream.readWord());
	
	mem_free(tmpchars);
}