/*
 * TransitionGen.cc
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
#include "defs.h"
#include "io/terminal.h"
#include "structure/string.h"
#include "misc/converter.h"
#include "structure/array.h"
#include "io/fileStream.h"

#include "LibCyberBase/Overall.h"
#include "LibCVSCommon/CVSCommon.h"
#include "../RSCCommon.h"
#include "../CDTCommon/CDTCommon.h"
#include "TransitionGen.h"
namespace RSCCommon
{
	using namespace Overall;
	using namespace CDTCommon;

	void GenerateTransition(CVSCommon::CVS& _CVS ,
	                        RSC& _RSC ,
	                        CDTCommon::PhoneSet& _PhoneSet ,
	                        CDTCommon::DBSet& _DBSet ,
	                        CDTCommon::DEF& DEF  ,
	                        int Num )
	{
		double TotalTime  = _RSC.SegmentList[Num].DurTime;
		double PreShrink = _DBSet.PreShrink / 96000 / 2;
		double ConsonantTime  = _DBSet.VOT / 96000 + 0.02 + PreShrink;
		double t0, t1, t2, t3, t4;

		_CVS.SegmentList[Num].Effects.Shrink = (PreShrink + _RSC.SegmentList[Num].CutTime)/2;
		_CVS.SegmentList[Num].Effects.ForwardCut = (PreShrink + _RSC.SegmentList[Num].CutTime)/2;
		switch ( DEF.Type)
		{
			case V:
				t0 = TotalTime;
				break;
			case VV:
				if (DEF.TListQ == 2) 
			{
				t0 = 0.13;
				if (TotalTime < 0.4) 
					t0 = 0.13 * TotalTime / 0.4;
				t2 = 0.13;
				if (TotalTime < 0.4) 
					t2 = TotalTime * 0.13 / 0.4;
				t1 = TotalTime - t0 - t2;
			}
				if (DEF.TListQ == 1 )
			{
				t0 = 0.2;
				if (TotalTime < 0.3) 
					t0 = TotalTime * 2 / 3;
				t1 = TotalTime - t0;
			}
				break;
			case VVV:
				t0 = 0.15;
				t1 = 0.1;
				t3 = 0.15;
				if (TotalTime < 0.8) 
					t3 = 0.15 * TotalTime / 0.8;

				if (TotalTime < 0.4)
			{
				t0 = 0.15 * TotalTime / 0.4;
				t1 = 0.1 * TotalTime / 0.4;
			}
				t2 = TotalTime - t0 - t1 - t3;
				break;
			case CV:
				TotalTime -= ConsonantTime;
				t0 = 0.08;
				if (TotalTime < 0.3) 
					t0 = 0.08 * TotalTime / 0.3;

				t0 += ConsonantTime;
				t1 = TotalTime + ConsonantTime - t0;
				break;
			case CVV:
				TotalTime -= ConsonantTime;
				if (DEF.TListQ == 2)
			{
				t0 = 0.1;
				t2 = 0.15;
				if (TotalTime < 0.6) 
					t2 = 0.15 * TotalTime / 0.6;

				if (TotalTime < 0.3) 
					t0 = 0.1 * TotalTime / 0.3;

				t0 += ConsonantTime;
				t1 = TotalTime + ConsonantTime - t0 - t2;
			}
				if ( DEF.TListQ == 3 )
			{
				t0 = 0.10;
				t1 = 0.10;
				t3 = 0.15;
				if (TotalTime < 0.6)
					t3 = 0.15 * TotalTime / 0.6;

				if (TotalTime < 0.5) 
				{
					t0 = 0.10 * TotalTime / 0.5;
					t1 = 0.10 * TotalTime / 0.5;
				}
				t0 += ConsonantTime;
				t2 = TotalTime + ConsonantTime - t0 - t1 - t3;
			}
				break;
			case CAV:
				TotalTime -= ConsonantTime;
				if (DEF.TListQ == 1) 
			{
				t0 = 0.12;
				if (TotalTime < 0.5)
					t0 = 0.14 * TotalTime / 0.5;

				t0 += ConsonantTime;
				t1 = TotalTime + ConsonantTime - t0;
			}
				if (DEF.TListQ == 2 )
			{
				t0 = 0.12;
				t1 = 0.11;
				if (TotalTime < 0.5)
				{
					t0 = 0.12 * TotalTime / 0.5;
					t1 = 0.11 * TotalTime / 0.5;
				}
				t0 += ConsonantTime;
				t2 = TotalTime + ConsonantTime - t0 - t1;
			}
				break;
			case CAVV:
				TotalTime -= ConsonantTime;
				if (DEF.TListQ == 3) 
			{
				t0 = 0.12;
				t1 = 0.11;
				t3 = 0.15;
				if (TotalTime < 0.6)
					t3 = 0.15 * TotalTime / 0.6;

				if (TotalTime < 0.5) 
				{
					t0 = 0.12 * TotalTime / 0.5;
					t1 = 0.11 * TotalTime / 0.5;
				}
				t0 += ConsonantTime;
				t2 = TotalTime + ConsonantTime - t0 - t1 - t3;
			}
				if (DEF.TListQ == 4) 
			{
				t0 = 0.12;
				t1 = 0.11;
				t2 = 0.08;
				t4 = 0.15;
				if (TotalTime < 0.6) 
					t4 = 0.15 * TotalTime / 0.6;

				if (TotalTime < 0.5)
				{
					t0 = 0.12 * TotalTime / 0.5;
					t1 = 0.11 * TotalTime / 0.5;
					t2 = 0.08 * TotalTime / 0.5;
				}
			}
				t0 += ConsonantTime;
				t3 = TotalTime + ConsonantTime - t0 - t1 - t2 - t4;
		}
		_CVS.SegmentList[Num].TPhoneList[0].Transition.Time = t0;
		if (t1 <= 0) t1 = 0.0001;
		if (t2 <= 0) t2 = 0.0001;
		if (t3 <= 0) t3 = 0.0001;
		if (t4 <= 0) t4 = 0.0001;
		if (DEF.TListQ > 0) _CVS.SegmentList[Num].TPhoneList[1].Transition.Time = t1;
		if (DEF.TListQ > 1) _CVS.SegmentList[Num].TPhoneList[2].Transition.Time = t2;
		if (DEF.TListQ > 2) _CVS.SegmentList[Num].TPhoneList[3].Transition.Time = t3;
		if (DEF.TListQ > 3) _CVS.SegmentList[Num].TPhoneList[4].Transition.Time = t4;

	}
};