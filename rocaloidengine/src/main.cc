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

#include <stdio.h>
#include "defs.h"
#include "structure/string.h"
#include "structure/array.h"
#include "io/fileStream.h"
#include "io/terminal.h"
#include "Overall.h"
#include "CVSCommon.h"
#include "CVSWriter.h"

using namespace Overall;

int main()
{
	int i=10,j=100;
	array<double> x;
	array<string> z;
	string str;
	CVSReader::Open(
	CVSWriter::Save("/home/rgwan/ramdisk/test.cvs");
	CVSWriter::Close();


	return 0; 
}

