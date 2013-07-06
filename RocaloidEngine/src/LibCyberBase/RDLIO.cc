/*
 * RDLIO.cc
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
#include "SPKit/defs.h"
#include "SPKit/io/terminal.h"
#include "SPKit/structure/string.h"
#include <stdlib.h>
#include "SPKit/misc/converter.h"
#include "SPKit/misc/memopr.h"
#include "SPKit/structure/array.h"
#include "SPKit/io/fileStream.h"
#include "SPKit/io/stringStream.h"

#include "RDLIO.h"
#include "Overall.h"

using namespace Overall;
using namespace converter;
namespace RDLIO
{	
	bool TestIfIsNumber(string _String)
	{
		char *str=_String.toChars ();
		int i,len=_String.getLength();
		bool res = true;
		for(i=0;i<len;i++)
		{
			if((str[i] < '0' || str[i] > '9') && str[i]!='.' && str[i]!='-')
			{
				//Exception( _String + "  is n't a number!");
				res = false;
			}
		}
		mem_free(str);
		return res;
	}
	double TestIfIsDouble(string _String)
	{
		_String=Trim(_String);
		if (  ! (TestIfIsNumber(_String) ) ) Exception( _String + "  is n't a number!");
		return converter::CDbl(_String);
	}
	int TestIfIsInt(string _String)
	{
		_String=Trim(_String);
		if ( ! (TestIfIsNumber(_String) ) ) Exception( _String + "  is n't a number!");
		return converter::CInt(_String);
	}
	double TestIfIsDoubleAndPositive(string _String)
	{
		double x;
		_String=Trim(_String);
		if (  ! (TestIfIsNumber(_String) ) ) Exception( _String + "  is n't a number!");
		x= converter::CDbl(_String);
		//printf("x=%f\n",x);
		if(x<=0)
			Exception ( _String + "  is n't positive!");
		return x;
	}		
	
	int TestIfIsIntAndPositive(string _String) 
	{
		int x;
		_String=Trim(_String);
		if (  ! (TestIfIsNumber(_String) ) ) Exception( _String + "  is n't a number!");
		x= converter::CInt(_String);
		
		if(x<=0)
			Exception ( _String + "  is n't positive!");
		return x;
	}		
	double TestIfIsDoubleNotNegative(string _String)
	{
		double x;
		_String=Trim(_String);
		if (  ! (TestIfIsNumber(_String) ) ) Exception( _String + "  is n't a number!");
		x= converter::CDbl(_String);
		if(x<0)
			Exception ( _String + "  is n't positive or 0!");
		return x;
	}		
	
	int TestIfIsIntNotNegative(string _String) 
	{
		int x;
		_String=Trim(_String);
		if (  ! (TestIfIsNumber(_String) ) ) Exception( _String + "  is n't a number!");
		x= converter::CInt(_String);
		if(x<0)
			Exception ( _String + "  is n't positive or 0!");
		return x;
	}		
	bool TestIfIsBoolean(string _String)
	{
		string t;
		_String=Trim(_String);
		t=lowerCase(_String);
		if ( t == converter::CStr("true"))
		{
			return true;
		}
		else if( t == converter::CStr("false"))
		{
			return false;
		}
		Exception ( _String + "  is not a boolean. Only true or false are allowed.");
		return false;
	}
	int TestIfIsPresetedEnvelope(string _String)
	{
		_String=Trim(_String);
		if( _String == converter::CStr("ADSR"))
			return 0;
		else
			Exception(_String + " is not a valid PresetedEnvelope!");
		return -1;
	}
}

RDLReader::RDLReader()
{
	buffer = 0;
}
RDLReader::~RDLReader()
{
	if(buffer != 0)
		Close();
}
void RDLReader::Open(string FileName)
{
	if(Reader.open(FileName, READONLY) == false)
		Exception(CStr("Cannot open ") + FileName + "!");
	buffer = mem_malloc(Reader.getLength());
	Reader.readBuffer(buffer, Reader.getLength());
	SReader = new stringStream(buffer);
	SReader -> setPosition(0);
	Reader.close();
}
void RDLReader::Close()
{
	delete SReader;
	mem_free(buffer);
	buffer = 0;
}

string RDLReader::Read()
{
	return SReader -> readWord();
}

//class RDLWriter
RDLWriter::~RDLWriter()
{
	Writer.close();
}

void RDLWriter::Open(string FileName)
{
	if(Writer.open(FileName, CREATE) == false)
		Exception(CStr("Cannot create ") + FileName);
	Indent = "";
	LastWrite = 0;
	NewLineValid = true;
}
void RDLWriter::Close()
{
	Writer.close();
}

void RDLWriter::WriteWord(string _String)
{
	switch(LastWrite)
	{
		case 0:
			Writer.write(_String);
		break;
		case 1:
			Writer.write(Indent + _String);
		break;
		case 2:
			Writer.write(CStr(" ") + _String);
		break;
	}
	LastWrite = 2;
}
void RDLWriter::WriteWord(int Integer)
{
	WriteWord (CStr(Integer));
}
void RDLWriter::WriteWord(const char* _String)
{
	WriteWord(CStr(_String));
}
void RDLWriter::WriteWord(double Double)
{
	WriteWord (CStr(Double));
}
void RDLWriter::WriteWord(bool Boolean)
{
	WriteWord (CStr(Boolean));
}

void RDLWriter::WritePresetedEnvelope(int  _Envelopes)
{
	switch(_Envelopes)
	{
		case 0:
			WriteWord("ADSR");
		break;
	}
}
void RDLWriter::NewLine()
{
	if(NewLineValid)
	{
		Writer.write("\n");
		LastWrite = 1;
	}
}
void RDLWriter::IndentPush()
{
	if(NewLineValid)
	{
		Indent = Indent + CStr("\t");
	}
}
void RDLWriter::IndentPop()
{
	if(NewLineValid)
	{
		Indent = left(Indent, Indent.getLength() - 1);
	}
}