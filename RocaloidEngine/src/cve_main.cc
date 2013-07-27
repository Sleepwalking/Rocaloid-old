 /*
  * cve_main.cc
  *
  * Copyright (C) 2013 - Rocaloid Development Group (RDG)
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
 // A shell for LibCVE.
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

#include "LibCVE/Scheduler.h"

#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>//getopt
#include <string.h>

#include "cve_main.h"
#include "config.h"
using namespace Overall;
using namespace converter;

void display_usage(string basename,int argc)
{
	if (argc == 1)
		wLine(basename + " : missing argument!");
	wLine (CStr("Usage: ") + basename + " [Options] [Cyber Script File]");
	wLine ("");
	if (argc != -1 )
	{
		wLine (CStr("Try `") + basename + " --help` for more options.");
		exit(0);
	}
}
void display_help(string basename)
{//VERSION was defined in config.h (configure.ac)
	wLine(CStr("Rocaloid ") + VERSION + CStr(" , A Vocal Synthsis Software."));
	display_usage(basename,-1);
	wLine ("Options:");
	wLine ("	-d,--datadir [CVDB Dir] , Set the engine 's Vocal Data Directory");
	wLine ("	-o,--output [WAVE File] , Set the engine 's output wave file name,default is 'RenaIsAlive.wav'");
	wLine ("	-v,--verbose		, Print debug message from the engine");
	wLine ("	-h,--help		, Show this message on your screen\n");
	wLine ("BUG Report	: <http://github.com/Sleepwalking/Rocaloid/>");
	wLine ("IRC	 : freenode/#RDG");
	exit(0);
}
int main(int argc, char *argv[])
{
	string DataDir = "";
	string CVSFile = "";
	string WaveFile = "RenaIsAlive.wav";
	int opt = 0;
	int longIndex;
	
	opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
	if (opt == -1) 
	{
		display_usage(argv[0],argc);
	}
	
	Scheduler::Verbose = false;
    while (opt != -1)
	{
        switch( opt ) 
		{
            case 'd':
                DataDir = optarg;
                break;
                
            case 'o':
                WaveFile = optarg;
                break;
				
            case 'h': 
				display_help(argv[0]);
				break;
            case '?':
                display_usage(argv[0],argc);
                break;
            case 'v':
				Scheduler::Verbose = true;
				break;
            default:
                /* You won't actually get here. */
                break;
        }
		opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
    }
	
	if(optind == argc)
	{
		Exception("Please enter the Cyber Script File!");
	}
	if(DataDir == "")
	{
		Exception("Please enter the Vocal Data Directory using argument -d !");
	}
	CVSFile = argv[optind];
	
	CBVFile::DataDir = DataDir;
	Scheduler::Init();
	Scheduler::OpenCVS(CVSFile);

	Scheduler::SetFileOutput(WaveFile);
	Scheduler::RunSynthesizer();
	
	Scheduler::Exit();

	return 0; 
}

