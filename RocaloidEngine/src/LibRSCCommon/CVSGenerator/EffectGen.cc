/*
 * EffectGen.cc
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
//   通过CDT从RSC生成部分效果到CVS
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
#include "EffectGen.h"
namespace RSCCommon
{
	void GeneratePElope(RSC& _RSC, CVSCommon::CVS &_CVS, 
	                    CDTCommon::PhoneSet PhoneSet, int Num)
	{
		if (PhoneSet.Type != CDTCommon::Vowel)
		{
			if ( PhoneSet.PType == CDTCommon::PLO)
			{
				_CVS.SegmentList[Num].Effects.ADSR.Attack = 0;
				_CVS.SegmentList[Num].Effects.ADSR.Amplitude = 1;
				_CVS.SegmentList[Num].Effects.ADSR.Decline = 0.1;
				_CVS.SegmentList[Num].Effects.ADSR.Release = 0.07;
			}
			else if ( PhoneSet.PType == CDTCommon::FRC )
			{
				_CVS.SegmentList[Num].Effects.ADSR.Attack = 0.05;
				_CVS.SegmentList[Num].Effects.ADSR.Amplitude = 1;
				_CVS.SegmentList[Num].Effects.ADSR.Decline = 0.1;
				_CVS.SegmentList[Num].Effects.ADSR.Release = 0.07;
			}
			else if ( PhoneSet.PType == CDTCommon::SEM)
			{
				_CVS.SegmentList[Num].Effects.ADSR.Attack = 0.06;
				_CVS.SegmentList[Num].Effects.ADSR.Amplitude = 1;
				_CVS.SegmentList[Num].Effects.ADSR.Decline = 0.1;
				_CVS.SegmentList[Num].Effects.ADSR.Release = 0.07;
			}
			else
			{
				_CVS.SegmentList[Num].Effects.ADSR.Attack = 0.07;
				_CVS.SegmentList[Num].Effects.ADSR.Amplitude = 1;
				_CVS.SegmentList[Num].Effects.ADSR.Decline = 0.1;
				_CVS.SegmentList[Num].Effects.ADSR.Release = 0.1;
			}
		}
		else
		{
			_CVS.SegmentList[Num].Effects.ADSR.Attack = 0.1;
			_CVS.SegmentList[Num].Effects.ADSR.Amplitude = 1.2;
			_CVS.SegmentList[Num].Effects.ADSR.Decline = 0.1;
			_CVS.SegmentList[Num].Effects.ADSR.Release = 0.1;
		}
	}

	void GenerateOpeList(CVSCommon::CVS& _CVS, RSC& _RSC, 
	                     CDTCommon::CDT& _CDT, int Num)
	{
		int i;
		string s1, s2, l1 = "", l2 = "";
		
		_CVS.SegmentList[Num].Effects.OpennessList.setUbound (_CVS.SegmentList[Num].TPhoneListQ + 1);
		_CVS.SegmentList[Num].Effects.OpennessList[0] = 
			CDTCommon::GetOpe(_CDT, _CVS.SegmentList[Num].TPhoneList[0].Start.Symbol);
		
		for ( i = 0 ; i <= _CVS.SegmentList[Num].TPhoneListQ ; i++)
		{
			if (not _CVS.SegmentList[Num].TPhoneList[i].Start.Type)
			{
				//新
				if (_CVS.SegmentList[Num].TPhoneList[i].Start.Preserved == 1 )
					s1 = l1;
				else
					s1 = l2;
			}
			else
			{
				//预留
				s1 = _CVS.SegmentList[Num].TPhoneList[i].Start.Symbol;
			}
			if (not _CVS.SegmentList[Num].TPhoneList[i].Dest.Type)
			{
				//预留
				if (_CVS.SegmentList[Num].TPhoneList[i].Dest.Preserved == 1)
					s2 = l1;
				else 
					s2 = l2;
			}
			else
			{
				//新
				s2 = _CVS.SegmentList[Num].TPhoneList[i].Dest.Symbol;
			}
			_CVS.SegmentList[Num].Effects.OpennessList[i + 1] = CDTCommon::GetOpe(_CDT, s1) * 
				(1 - _CVS.SegmentList[Num].TPhoneList[i].Transition.EndRatio) + 
				CDTCommon::GetOpe(_CDT, s2) * _CVS.SegmentList[Num].TPhoneList[i].Transition.EndRatio;
			l1 = s1;
			l2 = s2;
		}
	}
};
