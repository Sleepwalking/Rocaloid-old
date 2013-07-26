/*
 * Rearrager.cc
 *
 * Copyright (C) 2013 - Rocaloid Development Group(RDG)
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
//根据CDT中的语音学数据修改RSC
#include "SPKit/defs.h"
#include "SPKit/io/terminal.h"
#include "SPKit/structure/string.h"
#include "SPKit/misc/converter.h"
#include "SPKit/structure/array.h"
#include "SPKit/io/fileStream.h"

#include "LibCyberBase/Overall.h"
#include "LibCVSCommon/CVSCommon.h"
#include "../RSCCommon.h"
#include "../CDTCommon/CDTCommon.h"
#include "Rearrager.h"

namespace RSCCommon
{
	using namespace converter;
	using namespace Overall;
	inline double min (double x, double y)
	{
		if ( x > y ) return x;
		return y;
	}
	void Rearrange(RSC& _RSC, RSC& RSCOrg, CDTCommon::CDT& _CDT)
	{
		int i;
		CDTCommon::PhoneticData Phonetic;
		CDTCommon::PhoneticData AdjustedPhonetic;
		double ThisStartTime, LastStartTime, ThisDurTime;
		double LastEndTime, IntervalTime, LastDurTime;
		string ThisFirstPhone, ThisPitch;
		CDTCommon::DEF ThisDEF;
		CDTCommon::DBSet ThisDB;
		CDTCommon::PhoneSet ThisPhoneSet;
		double DBVOT;
		LastStartTime = -100;

		
		for ( i = 0 ;  i <= RSCOrg.SegmentListQ ; i++)
		{
			//wLine ("Loop Start");
			//wLine(CStr("Lyric: ")+RSCOrg.SegmentList[i].Lyric);
			ThisStartTime = RSCOrg.SegmentList[i].StartTime;
			ThisDurTime = RSCOrg.SegmentList[i].DurTime;
			//wLine(CStr(ThisStartTime));
			//wLine(CStr(ThisDurTime));
			if (i > 0) 
			{
				LastStartTime = _RSC.SegmentList[i - 1].StartTime;
				LastEndTime = _RSC.SegmentList[i - 1].DurTime + 
					LastStartTime - _RSC.SegmentList[i - 1].CutTime;
			}
			IntervalTime = ThisStartTime - LastStartTime;

			ThisDEF =_CDT.DEFList[CDTCommon::FindDEFNum(_CDT, RSCOrg.SegmentList[i])];
			//wLine (ThisDEF.Name);
			//wLine ("DEFLIST FOUND");
			CDTCommon::ReplaceDEF(ThisDEF, CDTCommon::
				                      ToSingleNotation(RSCOrg.SegmentList[i].Lyric));
			//wLine ("REPLACE");
			ThisFirstPhone = ThisDEF.TList[0].TFrom;
			ThisPitch = GetPitchByFreq(RSCOrg.SegmentList[i].StartFreq);
			CDTCommon::GetDBSet(_CDT, ThisFirstPhone, ThisPitch, ThisDB);
			//wLine ("DB");
			CDTCommon::GetPhoneSet(_CDT, ThisFirstPhone[0], ThisPhoneSet);
			//wLine("PhoneSet");
			DBVOT = CDbl(ThisDB.VOT) / 96000.0;//toreal
			//wLine ("DBVOT");
			//wLine(CStr(LastEndTime - LastStartTime));
			LastDurTime = LastEndTime - LastStartTime;
			if (ThisPhoneSet.Type == CDTCommon::Vowel)
			{
				Phonetic.ForwardOffset = 0.07;
				Phonetic.LastEnd = 0;
				Phonetic.VOT = 0;
			}
			else
			{
				//wLine(ThisDEF.Name);
				CDTCommon::GetData(LastDurTime, ThisPhoneSet, Phonetic);
				//wLine("GetData");
			}
			
			AdjustedPhonetic.ForwardOffset = min(DBVOT, Phonetic.ForwardOffset);
			AdjustedPhonetic.LastEnd = Phonetic.LastEnd - (Phonetic.ForwardOffset - 
			                                               AdjustedPhonetic.ForwardOffset);
			AdjustedPhonetic.VOT = min(DBVOT, Phonetic.VOT);

			if (ThisPhoneSet.PType = CDTCommon::PLO)
				AdjustedPhonetic.VOT = DBVOT / 5.0 * 4.0;


			if (i > 0)
			{
				LastEndTime = min(LastEndTime, ThisStartTime - 
				                  AdjustedPhonetic.LastEnd);
				_RSC.SegmentList[i - 1].DurTime = LastEndTime - 
					_RSC.SegmentList[i - 1].StartTime;
			}


			_RSC.SegmentList[i].StartTime -= AdjustedPhonetic.ForwardOffset;
			_RSC.SegmentList[i].CutTime = DBVOT - AdjustedPhonetic.VOT;
			_RSC.SegmentList[i].DurTime += _RSC.SegmentList[i].CutTime + 
				AdjustedPhonetic.ForwardOffset;
			if (i > 0) 
			{
				if (ThisPhoneSet.Type == CDTCommon::Vowel ||
				    ThisPhoneSet.Type == CDTCommon::Semi )
				{
					_RSC.SegmentList[i - 1].DurTime += 0.03;
					_RSC.SegmentList[i].StartTime -= 0.02;
					_RSC.SegmentList[i].DurTime += 0.02;
				}
				if (_RSC.SegmentList[i - 1].DurTime < 0.15 && 
				    _RSC.SegmentList[i].StartTime > 
				    _RSC.SegmentList[i - 1].DurTime + LastStartTime) 
				{
					//_RSC.SegmentList[i - 1].DurTime =
					//0.5 * (_RSC.SegmentList[i]..StartTime + _RSC.SegmentList[i - 1].DurTime + LastStartTime)
				}
			}
		}	
	}
};