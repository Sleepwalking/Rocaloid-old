/*
 * Generator.cc
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
//Generating RSC from CVS using CDT.
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
#include "Generator.h"
#include "Rearrager.h"
#include "TransitionGen.h"

namespace RSCCommon
{
	using namespace Overall;
	using namespace converter;

	void GenerateCVS(RSC& _RSC, CDTCommon::CDT& _CDT , CVSCommon::CVS& _CVS)
	{
		RSC _RSC2;
		int i, j;
		CDTCommon::DEF DEF;

		CDTCommon::PhoneSet PhoneSet;
		CDTCommon::DBSet DBSet;
		string FirstPhone, FirstPitch, Notation;
		string Lyric;
		
		//wLine ("Start");
		_RSC2 = _RSC;
		//wLine ("RSC2 = RSC");
		_RSC.TimeBake();
		_RSC.VolumeBake();
		//Rearrange(_RSC, _RSC2, _CDT);
		//Exception("test");
		//_RSC.TimeBake();
		//_RSC.VolumeBake();
		//wLine ( "Rearraged");
		
		_CVS.SegmentList.setUbound (_RSC.SegmentListQ);
		_CVS.SegmentListQ = _RSC.SegmentListQ;
		for ( i = 0 ; i<= _RSC.SegmentListQ ; i++)
		{
		//	wLine("Start");
			j = CDTCommon::FindDEFNum(_CDT, _RSC.SegmentList[i]);
			DEF = _CDT.DEFList[j];
			Lyric = _RSC.SegmentList[i].Lyric;
			Notation = CDTCommon::ToSingleNotation(Lyric);
			//wLine(Notation);
			//wLine(DEF.Name);
			CDTCommon::ReplaceDEF(DEF, Notation);
		//	wLine(DEF.TList[0].TFrom);
			FirstPhone = DEF.TList[0].TFrom;
			CDTCommon::GetPhoneSet(_CDT, FirstPhone, PhoneSet);
		//	wLine("GetPhoneSet");
			FirstPitch = GetPitchByFreq(_RSC.SegmentList[i].StartFreq);
			CDTCommon::GetDBSet(_CDT, FirstPhone, FirstPitch, DBSet);
		//	wLine("GetDBSet");
			//wLine(DBSet.Phone);
		//	
			_CVS.SegmentList[i].StartTime = _RSC.SegmentList[i].StartTime;
			_CVS.SegmentList[i].Effects.ElistEnabled = true;
			
			if (_RSC.SegmentList[i].Effects.PElopeEnabled) 
			{
				_CVS.SegmentList[i].Effects.PElopeEnabled = true;
				_CVS.SegmentList[i].Effects.PresetedEnvelope =
					_RSC.SegmentList[i].Effects.PresetedEnvelope;

				GeneratePElope(_RSC, _CVS, PhoneSet, i);
				//.Effects.ADSR = _RSC.SegmentList[i].Effects.ADSR
			}		
			_CVS.SegmentList[i].Effects.Breath = _RSC.SegmentList[i].Effects.Breath;
		//	wLine("GenTPhone");
			GenerateTPhone(_CVS, _RSC, DEF, i);
		//	wLine("GenTrans");
			GenerateTransition(_CVS, _RSC, PhoneSet, DBSet, DEF, i);
		//	wLine("GenOpe");
			GenerateOpeList(_CVS, _RSC, _CDT, i);
		//	wLine("GenENV");
			GenerateEnvelope(_CVS, _RSC, i);
		//	wLine("GenFre");
			GenerateFreq(_CVS, _RSC, i);		
		//	wLine("Loop");
			//wLine(CStr(_RSC.SegmentList[i].StartTime));
			//wLine(CStr(_RSC.SegmentList[i].DurTime));
		}
	}


	void GenerateTPhone(CVSCommon::CVS& _CVS ,
	                    RSC& _RSC ,
	                    CDTCommon::DEF& _DEF ,
	                    int Num)
	{
		Segment RSCSegment;
		int i;
		_CVS.SegmentList[Num].TPhoneList.setUbound (_DEF.TListQ);
		_CVS.SegmentList[Num].TPhoneListQ = _DEF.TListQ;
		for ( i = 0 ; i <= _DEF.TListQ ; i++)
		{
			if ( _DEF.TList[i].TFrom == "p1"  )
			{
				_CVS.SegmentList[Num].TPhoneList[i].Start.Preserved = 1;
				_CVS.SegmentList[Num].TPhoneList[i].Start.Type = false;
			}
			else if ( _DEF.TList[i].TFrom == "p2"  )
			{
				_CVS.SegmentList[Num].TPhoneList[i].Start.Preserved = 2;
				_CVS.SegmentList[Num].TPhoneList[i].Start.Type = false;
			}
			else
			{
				_CVS.SegmentList[Num].TPhoneList[i].Start.Symbol = _DEF.TList[i].TFrom;
				_CVS.SegmentList[Num].TPhoneList[i].Start.Type = true;
			}

			if (_DEF.TList[i].TTo == "p2"  )
			{
				_CVS.SegmentList[Num].TPhoneList[i].Dest.Preserved = 2;
				_CVS.SegmentList[Num].TPhoneList[i].Dest.Type = false;
			}
			else if ( _DEF.TList[i].TTo == "p1"  )
			{
				_CVS.SegmentList[Num].TPhoneList[i].Dest.Preserved = 1;
				_CVS.SegmentList[Num].TPhoneList[i].Dest.Type = false;
			}
			else
			{
				_CVS.SegmentList[Num].TPhoneList[i].Dest.Symbol = _DEF.TList[i].TTo;
				_CVS.SegmentList[Num].TPhoneList[i].Dest.Type = true;
			}
		}
		switch (_DEF.Type)
		{
			case CDTCommon::V:
				_CVS.SegmentList[Num].TPhoneList[0].Transition.StartRatio		= 1;
				_CVS.SegmentList[Num].TPhoneList[0].Transition.EndRatio		= 1;
				break;
			case CDTCommon::VV:
				_CVS.SegmentList[Num].TPhoneList[0].Transition.StartRatio		= 0;
				_CVS.SegmentList[Num].TPhoneList[0].Transition.EndRatio		= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.StartRatio		= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.EndRatio		= _DEF.TRatio;
				if (_DEF.TListQ == 2 )
			{
				_CVS.SegmentList[Num].TPhoneList[2].Transition.StartRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.EndRatio	= 1;
			}
				break;
			case CDTCommon::VVV:
				_CVS.SegmentList[Num].TPhoneList[0].Transition.StartRatio		= 0;
				_CVS.SegmentList[Num].TPhoneList[0].Transition.EndRatio		= 1;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.StartRatio		= 0;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.EndRatio		= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.StartRatio		= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.EndRatio		= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[3].Transition.StartRatio		= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[3].Transition.EndRatio		= 1;
			case CDTCommon::CV:
				_CVS.SegmentList[Num].TPhoneList[0].Transition.StartRatio		= 0;
				_CVS.SegmentList[Num].TPhoneList[0].Transition.EndRatio		= 1;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.StartRatio		= 1;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.EndRatio		= 1;
			case CDTCommon::CVV:
				if (_DEF.TListQ == 2)
			{
				_CVS.SegmentList[Num].TPhoneList[0].Transition.StartRatio	= 0;
				_CVS.SegmentList[Num].TPhoneList[0].Transition.EndRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.StartRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.EndRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.StartRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.EndRatio	= 1;
			}
				if (_DEF.TListQ == 3)
			{
				_CVS.SegmentList[Num].TPhoneList[0].Transition.StartRatio	= 0;
				_CVS.SegmentList[Num].TPhoneList[0].Transition.EndRatio	= 1;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.StartRatio	= 0;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.EndRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.StartRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.EndRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[3].Transition.StartRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[3].Transition.EndRatio	= 1;
			}
			case CDTCommon::CAV:
				if (_DEF.TListQ == 1 )
			{
				_CVS.SegmentList[Num].TPhoneList[0].Transition.StartRatio	= 0;
				_CVS.SegmentList[Num].TPhoneList[0].Transition.EndRatio	= 1;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.StartRatio	= 1;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.EndRatio	= 1;
			}
				if (_DEF.TListQ == 2) 
			{
				_CVS.SegmentList[Num].TPhoneList[0].Transition.StartRatio	= 0;
				_CVS.SegmentList[Num].TPhoneList[0].Transition.EndRatio	= 1;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.StartRatio	= 0;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.EndRatio	= 1;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.StartRatio	= 1;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.EndRatio	= 1;
			}
			case CDTCommon::CAVV:
				_CVS.SegmentList[Num].TPhoneList[0].Transition.StartRatio		= 0;
				_CVS.SegmentList[Num].TPhoneList[0].Transition.EndRatio		= 1;
				if (_DEF.TListQ == 3) 
			{
				_CVS.SegmentList[Num].TPhoneList[1].Transition.StartRatio	= 0;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.EndRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.StartRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.EndRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[3].Transition.StartRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[3].Transition.EndRatio	= 1;
			}
				if ( _DEF.TListQ == 4 )
			{
				_CVS.SegmentList[Num].TPhoneList[1].Transition.StartRatio	= 0;
				_CVS.SegmentList[Num].TPhoneList[1].Transition.EndRatio	= 1;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.StartRatio	= 0;
				_CVS.SegmentList[Num].TPhoneList[2].Transition.EndRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[3].Transition.StartRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[3].Transition.EndRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[4].Transition.StartRatio	= _DEF.TRatio;
				_CVS.SegmentList[Num].TPhoneList[4].Transition.EndRatio	= 1;
			}
		}
	}



	//Must be used after GenerateTPhone!
	void GenerateFreq(CVSCommon::CVS& _CVS, 
	                  RSC& _RSC, int Num)
	{
		int i,j;
		double StartPos, EndPos, DurPos;
		double StartTime, DurTime, SaveTime, FirstSegTime;
		StartPos = _RSC.SegmentList[Num].Position;
		DurPos = _RSC.SegmentList[Num].Duration;
		EndPos = StartPos + DurPos;
		StartTime = _RSC.SegmentList[Num].StartTime;
		DurTime = _RSC.SegmentList[Num].DurTime;

		FirstSegTime = _CVS.SegmentList[Num].TPhoneList[0].Transition.Time;
		_CVS.SegmentList[Num].FreqList.setUbound (_RSC.FreqListQ);
		_CVS.SegmentList[Num].FreqList[0].Time = 0;
		_CVS.SegmentList[Num].FreqList[0].Freq = _RSC.SegmentList[Num].StartFreq;
		i = 1;
		for ( j = 1 ; j <=_RSC.FreqListQ ; j++)
		{
			// _RSC.FreqList
			if (_RSC.FreqList[j].Position > StartPos  )
				if (_RSC.FreqList[j].Position > EndPos  )
				break;

			SaveTime = (_RSC.FreqList[j].Position - StartPos) / DurPos * DurTime;
			//wLine(converter::CStr(SaveTime));
			if ( SaveTime > FirstSegTime && 
			    _CVS.SegmentList[Num].FreqList[i - 1].Time < FirstSegTime  )
			{
				_CVS.SegmentList[Num].FreqList[i].Time = FirstSegTime;
				_CVS.SegmentList[Num].FreqList[i].Freq = _RSC.SegmentList[Num].StartFreq;
				i ++;
			}
			_CVS.SegmentList[Num].FreqList[i].Time = SaveTime;
			_CVS.SegmentList[Num].FreqList[i].Freq = _RSC.FreqList[j].Freq;

			if ( CVSCommon::IsConsonant(_CVS.SegmentList[Num].TPhoneList[0].Start.Symbol)  )
			{
				//Consonant Starting
				//Pitch change before entering real transformation may cause errors.
				if (_CVS.SegmentList[Num].FreqList[i].Time < 
				    _CVS.SegmentList[Num].TPhoneList[0].Transition.Time  )
					_CVS.SegmentList[Num].FreqList[0].Freq = _RSC.FreqList[j].Freq;
				i --;
			}
			
			i++;
		}
		if ( DurTime > FirstSegTime &&  
		    _CVS.SegmentList[Num].FreqList[i - 1].Time < FirstSegTime  )
		{
			_CVS.SegmentList[Num].FreqList[i].Time = FirstSegTime;
			_CVS.SegmentList[Num].FreqList[i].Freq = _RSC.SegmentList[Num].StartFreq;
			i ++;
		}
		_CVS.SegmentList[Num].FreqList[i].Time = DurTime;
		_CVS.SegmentList[Num].FreqList[i].Freq = _RSC.SegmentList[Num].EndFreq;
		_CVS.SegmentList[Num].FreqListQ = i;
		_CVS.SegmentList[Num].FreqList.setUbound (i);
	}




	void GenerateEnvelope(CVSCommon::CVS& _CVS , 
	                      RSC& _RSC , int Num)
	{
		int i,j;
		double StartPos, EndPos, DurPos;
		double StartTime, DurTime;

		StartPos = _RSC.SegmentList[Num].Position;
		DurPos = _RSC.SegmentList[Num].Duration;
		EndPos = StartPos + DurPos;
		StartTime = _RSC.SegmentList[Num].StartTime;
		DurTime = _RSC.SegmentList[Num].DurTime;

		_CVS.SegmentList[Num].Effects.EnvelopeList.setUbound (_RSC.Effects.EnvelopeListQ);
		_CVS.SegmentList[Num].Effects.EnvelopeList[0].Time = 0;
		_CVS.SegmentList[Num].Effects.EnvelopeList[0].Amplitude = _RSC.SegmentList[Num].StartAmplitude;
		i = 1;
		for ( j = 0 ; j <= _RSC.Effects.EnvelopeListQ ; j++)
		{
			if (_RSC.Effects.EnvelopeList[j].Position > StartPos  )
			{
				if (_RSC.Effects.EnvelopeList[j].Position > EndPos  )
					break;

				_CVS.SegmentList[Num].Effects.EnvelopeList[i].Time = (_RSC.Effects.EnvelopeList[j].Position - 
				                                                      StartPos) / DurPos * DurTime;
				_CVS.SegmentList[Num].Effects.EnvelopeList[i].Amplitude = _RSC.Effects.EnvelopeList[j].Amplitude;
				i ++;
			}
		}
		_CVS.SegmentList[Num].Effects.EnvelopeList[i].Time = DurTime;
		_CVS.SegmentList[Num].Effects.EnvelopeList[i].Amplitude = _RSC.SegmentList[Num].EndAmplitude;
		_CVS.SegmentList[Num].Effects.EnvelopeListQ = i;
		_CVS.SegmentList[Num].Effects.EnvelopeList.setUbound (i);
	}
};