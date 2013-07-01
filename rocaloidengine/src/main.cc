/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2013 Sleepwalking & rgwan <dv.xw@qq.com>
 * 
 * RSCCommon is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * RSCTool is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "../SPKit/defs.h"
#include "../SPKit/structure/string.h"
#include "../SPKit/structure/array.h"
#include "../SPKit/io/fileStream.h"
#include "../SPKit/io/terminal.h"
#include "../LibCyberBase/Overall.h"
#include "../LibCyberBase/CVSCommon.h"
#include "../LibCyberBase/RDLIO.h"



using namespace Overall;

int main()
{
	int i=10,j=100;
	array<double> x;
	array<string> z;
	string y;
	RDLWriter* rdl = new RDLWriter("/home/rgwan/test.rdl");
	rdl->WriteWord("Hello world,Rocaloid!");
	rdl->NewLine ();
	rdl->Close ();
	delete rdl;
	RDLReader *rdl1=new RDLReader("/home/rgwan/test.rdl");
	rdl1 -> Close();
/*	x.push(10);
	x.push(10);
	PtrSwap(i, j);
	ObjSwap(i,j);
	wLine(CInt(i));
	wLine(CInt(j));
	//for(i=0;i<12*2;i++)
	//wLine(Overall::PitchList[i]+Overall::PitchList[i+24]);
	wLine(GetPitchByFreq(440.0));
	wLine(GetFreqByPitch("C3"));
	wLine(GetDoubleSum(x));
	wLine(y);
	wLine(RDLIO::TestIfIsInt("123.4"));
	wLine(RDLIO::TestIfIsPresetedEnvelope("ADSR"));*/
	
	//Exception("Joke");
	return 0; 
}

