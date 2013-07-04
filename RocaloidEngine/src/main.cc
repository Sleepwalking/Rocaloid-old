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
	int i,j;
	CDTCommon::CDTReader cdtr;
	CDTCommon::CDT cdt;
	cdtr.Open("/home/rgwan/ramdisk/HMCHNDICT.cdt");
	cdtr.Read(cdt);
	cdtr.Close();
	wLine (CStr("CDT Version :") + cdt.Version);
	wLine (CStr("LibCDT Version :") + cdt.CDTVersion);
	wLine (CStr("Language :") + cdt.Language);
	wLine (CStr("DEFLists :") + CStr(cdt.DEFListQ));
	wLine ( "Test :");
	for ( i=0 ; i<= cdt.DEFListQ; i ++)
	{
		wLine ( CStr("  Name= ") + cdt.DEFList[i].Name );
		wLine ( CStr("  TRatio= ") + CStr (cdt.DEFList[i].TRatio) );
	}
	wLine ( "PhoneticInfo:" );
	for (i=0 ; i<=cdt.Phonetic.OpennessListQ;i++)
		wLine ( CStr("   Tone : ") + cdt.Phonetic.OpennessList[i].Phone + " OPE: " + CStr(cdt.Phonetic.OpennessList[i].Ope));
	wLine ( "PhoneticInfo:" );
	/*for (i=0 ; i<=cdt.Phonetic.PhoneListQ;i++)
	{
		wLine ( CStr("	  Tone : ") + cdt.Phonetic.PhoneList[i].Phone );
		wLine ( CStr("			Type : ") + CStr(cdt.Phonetic.PhoneList[i].Type) );
		wLine ( CStr("			DataPoint:" ));
		for(i=0;i<=cdt.Phonetic.PhoneList[i].DataPointQ;i++)
		{
			wLine (CStr("			") + CStr ( cdt.Phonetic.PhoneList[i].DataPoint[i * 4] ) );
			wLine ( CStr("			") + CStr ( cdt.Phonetic.PhoneList[i].DataPoint[i * 4 +1] ) );
			wLine ( CStr("			") + CStr( cdt.Phonetic.PhoneList[i].DataPoint[i * 4 +2] ) );
			wLine ( CStr("			") +CStr ( cdt.Phonetic.PhoneList[i].DataPoint[i * 4 +3] ) );
		}
	}*/
	i=1;
		wLine ( CStr("	  Tone : ") + cdt.Phonetic.PhoneList[i].Phone );
		wLine ( CStr("			Type : ") + CStr(cdt.Phonetic.PhoneList[i].Type) );
		wLine ( CStr("			DataPoint num :" ) + CStr(cdt.Phonetic.PhoneList[i].DataPointQ+1 ));
		for(j=0;j<=cdt.Phonetic.PhoneList[i].DataPointQ;j++)
		{
			wLine (CStr("			") + CStr ( cdt.Phonetic.PhoneList[i].DataPoint[j * 4] ) + CStr ( cdt.Phonetic.PhoneList[i].DataPoint[j * 4 +1] ) + CStr( cdt.Phonetic.PhoneList[i].DataPoint[j * 4 +2] ) );
		}
	//wLine (CStr("DEFLists :") + CStr(cdt.));
	wLine (CStr("DBInfo:"));
	wLine( CStr("   DBListes : " ) + CStr(cdt.DB.DBListQ));
	wLine("completed");
	return 0; 
}

