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

#include "LibCyberBase/SPKit/defs.h"
#include "LibCyberBase/SPKit/structure/string.h"
#include "LibCyberBase/SPKit/structure/array.h"
#include "LibCyberBase/SPKit/io/fileStream.h"
#include "LibCyberBase/SPKit/io/terminal.h"
#include "LibCyberBase/SPKit/misc/converter.h"

#include "LibCyberBase/Overall.h"
#include "LibCyberBase/RDLIO.h"

#include "LibCVSCommon/CVSCommon.h"
#include "LibCVSCommon/CVSReader.h"
#include "LibCVSCommon/CVSWriter.h"

#include "LibRSCCommon/RSCCommon.h"
#include "LibRSCCommon/CDTCommon/CDTCommon.h"
#include "LibRSCCommon/CDTCommon/CDTReader.h"
#include "LibRSCCommon/RSCReader.h"

#include "LibRSCCommon/RSCWriter.h"
#include "LibRSCCommon/CVSGenerator/Generator.h"

using namespace Overall;
using namespace converter;
int main()
{

	/*VSQXCommon::VSQXReader r;
	RSCCommon::RSC rsc;
	RSCCommon::RSCWriter w;
	r.Open("/home/rgwan/ramdisk/test.vsqx");
	r.Read(rsc);
	r.Close ();
	w.Save("/home/rgwan/ramdisk/convert.rsc");
	w.Write(rsc);
	w.Close();*/
	CVSCommon::CVS cvs;
	RSCCommon::RSC rsc;
	CVSCommon::CVSWriter w;
	RSCCommon::RSCReader r;	
	CDTCommon::CDT cdt;
	CDTCommon::CDTReader cr;
	r.Open("/home/rgwan/ramdisk/test.rsc");
	r.Read(rsc);
	r.Close();
	cr.Open("/home/rgwan/ramdisk/HMCHNDICT.cdt");
	cr.Read(cdt);
	cr.Close ();
	RSCCommon::GenerateCVS ( rsc , cdt , cvs);
	return 0; 
}

