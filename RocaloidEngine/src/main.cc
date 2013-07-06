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

#include "LibCyberBase/CVDB/CVDB.h"
#include "LibCyberBase/CVDB/CBVIO.h"
#include "LibCyberBase/WaveBuffer.h"
#include "LibCyberBase/FrameBuffer.h"
#include "LibCyberBase/SlWave/wave.h"

#include "LibCyberBase/Overall.h"
#include "LibCyberBase/RDLIO.h"

#include "LibCVSCommon/CVSCommon.h"
#include "LibCVSCommon/CVSReader.h"
#include "LibCVSCommon/CVSWriter.h"

#include "LibRSCCommon/RSCCommon.h"
//#include "LibRSCCommon/CDTCommon/CDTCommon.h"
//#include "LibRSCCommon/CDTCommon/CDTReader.h"
#include "LibRSCCommon/RSCReader.h"
#include "LibRSCCommon/RSCWriter.h"

#include "LibCVE/Synthesizer/ConsecutivePreSynthesizer.h"
#include "LibCVE/Synthesizer/Synthesizer.h"

using namespace Overall;
using namespace converter;
int main()
{
	CBVFile::DataDir = "/tmp/data/";
	ConsecutivePreSynthesizer syn;
	WaveBuffer wb(SampleRate * 100);
	FrameBuffer a(1000);
	
	syn.Load("a_C3");

	int i;
	for(i = 0;i < 20000;i ++)
	{
		syn.Synthesize(a);
		wb.Write(a);
	}

	wb.Output("/tmp/RenaIsAlive.wav");
	return 0; 
}

