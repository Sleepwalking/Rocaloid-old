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
 * You should have received a copy of the GNU General Public License alonghttp://login.skype.com/
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "structure/string.h"
#include "cvector.h"
#include "io/fileStream.h"
#include "misc/converter.h"
#include "io/terminal.h"
#include "Overall.h"
#include "RDLIO.h"
#include "CVSCommon.h"
#include "CVSWriter.h"
#include "CVSReader.h"

using namespace converter;


int main()
{
	//int i=10,j=100;
	//printf("uBound=%d\n",RDLIO::TestIfIsIntAndPositive(CStr("1")) );	
	CVSCommon::CVS cvs;
	CVSReader::Open("/home/rgwan/ramdisk/Compiled.cvs");
	CVSWriter::Save("/home/rgwan/ramdisk/test2.cvs");
	CVSReader::Read(cvs);
	CVSWriter::Write(cvs);
	CVSReader::Close();
	//rLine();
	CVSWriter::Close();
	//exit(0);
	//while(1);
	//delete &cvs;
	//wLine("尼玛段错误！");
	//return 0;
}

