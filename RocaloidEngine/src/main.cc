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

#include "../LibCVSCommon/CVSCommon.h"
#include "../LibCVSCommon/CVSReader.h"

using namespace Overall;
int main()
{
	CVSCommon::CVS* cvs1 = new CVSCommon::CVS;
	CVSReader::Reader_Open("/home/sleepwalking/x.cvs");
	CVSReader::CVS_Read(*cvs1);
	CVSReader::Reader_Close();
	delete cvs1;
	terminal::readLine();
	return 0; 
}

