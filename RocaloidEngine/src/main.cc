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
using namespace Overall;
using namespace converter;
int main()
{
<<<<<<< HEAD

=======
	int i,j;
	CDTCommon::CDTReader cdtr;
	CDTCommon::CDT cdt;
	cdtr.Open("/tmp/HMCHNDICT.cdt");
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
	
	for(i=0;i<=cdt.Phonetic.PhoneListQ;i++)
	{
		wLine ( CStr("	  Tone : ") + cdt.Phonetic.PhoneList[i].Phone );
		wLine ( CStr("			Type : ") + CStr(cdt.Phonetic.PhoneList[i].Type) );

	
		wLine ( CStr("			DataPoint num :" ) + CStr(cdt.Phonetic.PhoneList[i].DataPointQ+1 ));
		for(j=0;j<=cdt.Phonetic.PhoneList[i].DataPointQ;j++)
		{
			wLine (CStr("			") + CStr ( cdt.Phonetic.PhoneList[i].DataPoint[j * 4] ) + " " +CStr ( cdt.Phonetic.PhoneList[i].DataPoint[j * 4 +1] ) + " " + CStr( cdt.Phonetic.PhoneList[i].DataPoint[j * 4 +2] ) + " " +CStr( cdt.Phonetic.PhoneList[i].DataPoint[j * 4 +3] ));
		}
	}
	wLine (CStr("DBInfo:"));
	wLine( CStr("   DBListes : " ) + CStr(cdt.DB.DBListQ));
	for(i=0;i<=cdt.DB.DBListQ;i++)
	{
		wLine ( CStr("	  Tone : ") + cdt.DB.DBList[i].Phone );
		wLine ( CStr("			Pitch : ") + CStr(cdt.DB.DBList[i].Pitch) );
		wLine ( CStr("			Attack:") + CStr(cdt.DB.DBList[i].VOT));
		wLine ( CStr("			PSnk:") + CStr(cdt.DB.DBList[i].PreShrink));
	}
	wLine("completed");
>>>>>>> d9996a55073a71e1766226b31f1f4cca6e0ca81e
	return 0; 
}

