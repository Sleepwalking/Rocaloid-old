 /*
  * VSQ3Reader.cc
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
#include "defs.h"
#include "io/terminal.h"
#include "structure/string.h"
#include "misc/converter.h"
#include "structure/array.h"
#include "io/fileStream.h"
#include "io/stringStream.h"
#include "misc/memopr.h"

#include "LibCyberBase/Overall.h"
#include "LibCyberBase/RDLIO.h"
#include "LibCVSCommon/CVSCommon.h"
#include "../RSCCommon.h"
#include "VSQ3Reader.h"
//XML支持
namespace VSQXCommon
{
	using namespace Overall;
	using namespace converter;
	
	
	void VSQ3Reader::Open(string FileName)
	{
		if(Reader.open(FileName, READONLY) == false)
			Exception(CStr("Cannot open ") + FileName + "!");
		Buffer.allocLength (Reader.getLength ());//分配空间
		Reader.readBuffer (&Buffer[0], Reader.getLength ());
		Reader.close();
		Pointer = 1;
	}
	
	void VSQ3Reader::Close()
	{
		Buffer.allocLength (0);//Free
	}
	
	void VSQ3Reader::ReadUntil(string _String)
	{
		Pointer = instr(Buffer, _String, Pointer);
	}
	
	int VSQ3Reader::FindNextPos(string _String)
	{
		return instr( Buffer, _String , Pointer);
	}

	int VSQ3Reader::FindLastPos(string _String, int Before)
	{
		int i,len;
		len = _String.getLength();
		len --;
		while (Before > 0)
		{
			for ( i = 0 ; i<= len ; i++)
			{
				if ( Buffer[Before-i] != _String[len - i])
					goto NotCompatible;//真毁程序结构
			}
		//wLine("Founded");
		return Before - _String.getLength() + 1;
		NotCompatible:
			Before --;
		}
		return 0;
	}

	string VSQ3Reader::ReadNextValue(string AttributeName)
	{
		int AttributeStart= instr(Buffer, CStr("<") + AttributeName + ">",Pointer);
		int ValueStart= AttributeStart + AttributeName.getLength() + 2;
		int ValueEnd = instr(Buffer, CStr("</") + AttributeName + ">", Pointer);
		Pointer = ValueEnd;
		return mid(Buffer, ValueStart, ValueEnd - ValueStart);
	}

	string VSQ3Reader::ReadCDATA(string CDATA)
	{
		return mid(CDATA, 9, CDATA.getLength() - 12);//吞音……
	}
};