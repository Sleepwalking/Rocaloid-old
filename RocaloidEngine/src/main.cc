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
#include "../SPKit/misc/converter.h"

#include "../LibCyberBase/Overall.h"
#include "../LibCyberBase/RDLIO.h"

#include "../LibCVSCommon/CVSCommon.h"
#include "../LibCVSCommon/CVSReader.h"
#include "../LibCVSCommon/CVSWriter.h"

#include "RSCCommon.h"
#include "CDTCommon/CDTCommon.h"
#include "CDTCommon/CDTReader.h"
using namespace Overall;
using namespace converter;
int main()
{
	/*CVSCommon::CVS* cvs1 = new CVSCommon::CVS;
	//CVSReader::Reader_Open("/home/rgwan/ramdisk/1.cvs");
	CVSReader Reader;
	CVSWriter Writer;
	Reader.Open("/home/rgwan/ramdisk/1.cvs");
	Reader.Read(*cvs1);
	Reader.Close();

	Writer.Save(CStr("/home/rgwan/ramdisk/test2.cvs"));
	//CVSWriter::Writer.NewLineValid = false;
	Writer.Write(*cvs1);
	Writer.Close();
	delete cvs1;*/
	CDTCommon::CDTReader cdt;
	cdt.Open("/home/rgwan/ramdisk/HMCHNDICT.cdt");
	cdt.Close();
	wLine("completed");
	return 0; 
}

