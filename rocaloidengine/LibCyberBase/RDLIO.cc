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
#include "defs.h"
#include "io/terminal.h"
#include "misc/memopr.h"
#include "structure/string.h"
#include "misc/converter.h"
#include "structure/array.h"
#include "io/fileStream.h"
#include <vector>
#include "Overall.h"
#include "RDLIO.h"

using namespace Overall;
 namespace RDLIO
{	
	bool TestIfIsNumber(string _String)
	{
		char *str=_String.toChars ();
		int i,len=_String.getLength();
		bool res = true;
		for(i=0;i<len;i++)
		{
			if((str[i] < '0' || str[i] > '9') && str[i]!='.' )
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

using namespace converter;
//class RDLReader
void RDLReader::Open(string FileName)
{
	LineBufferQ = 0;
	LineBufferPointer = 0;
	if(Reader.open(FileName,READONLY)==false)
		Exception(CStr("This file: ") + FileName + " is not found!");
}
string RDLReader::Read()
{
	string res;
	res=Reader.readWord();
	return res;
}
void RDLReader::Close()
{
		Reader.close();
}

//class RDLWriter

void RDLWriter::Open(string FileName)
{
	if(Writer.open(FileName,CREATE)==false)
		Exception(CStr("I CANNOT Create File: ") + FileName);
	Indent = "";
	LastWrite = 0;
	NewLineValid=true;
}
RDLWriter::~RDLWriter()
{
	Writer.close();
}
void RDLWriter::WriteWord(string _String)
{
	switch( LastWrite)
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
void RDLWriter::WriteWord(const char * _String)
{
	WriteWord (CStr(_String));
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
		case E_ADSR:
			WriteWord("ADSR");
		break;
	}
}
void RDLWriter::NewLine()
{
	if(NewLineValid)
	{
		Writer.write("\n");
		LastWrite=1;
	}
}
void RDLWriter::IndentPush()
{
	if(NewLineValid)
	{
		Indent=Indent+"\t";
	}
}
void RDLWriter::IndentPop()
{
	if(NewLineValid)
	{
		Indent = left(Indent, Indent.getLength() - 1);
	}
}
void RDLWriter::Close()
{
	Writer.close();
}