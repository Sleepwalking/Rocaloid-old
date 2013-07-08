 /*
  * CVSCommon.h
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
#ifndef CVSCOMMON_H
#define CVSCOMMON_H
#include "LibCyberBase/SPKit/structure/string.h"
#include "LibCyberBase/SPKit/structure/array.h"
namespace CVSCommon
{
	//Here, Q represents "Quantity".
	struct TStart
	{
		bool Type; //True : New, False : Preserved
		string Symbol;
		int Preserved;
	};
	struct TDest
	{
		bool Type; //True : New, False : Preserved
		string Symbol;
		int Preserved;
	};
	struct TTransition
	{
		double StartRatio;
		double EndRatio;
		double Time;
	};
	struct TPhone
	{
		TStart Start;
		TDest Dest; //Avoided using keyword End.
		TTransition Transition;
	};
	struct FreqSet
	{
		double Time;
		double Freq;
	};

	struct EnvelopeSet
	{
		double Time;
		double Amplitude;
	};
	struct BreathStruct
	{
		double Magnitude;
	};
	struct VibrationStruct
	{
		double StartTime;
		double Interval;
		double FreqChange;
	};
	struct ADSREnvelope
	{
		double Amplitude;
		double Attack;
		double Decline;
		double Release;
	};

	struct EffectCollection
	{
		EffectCollection();
		double Shrink;
		double ForwardCut;
		array<EnvelopeSet> EnvelopeList;
		int EnvelopeListQ;
		bool ElistEnabled;
		bool PElopeEnabled;
		int PresetedEnvelope;
		ADSREnvelope ADSR;
		array<double> OpennessList;
		VibrationStruct Vibration;
		BreathStruct Breath;
	};
	struct Segment
	{
		Segment();
		array<TPhone>  TPhoneList;
		array<FreqSet>  FreqList;
		int TPhoneListQ;
		int FreqListQ;
		EffectCollection Effects;
		double StartTime;
	};
	struct CVS
	{
		CVS();
		array<Segment>  SegmentList;
		int SegmentListQ;
	};
	enum Envelopes
	{
		ADSR = 0
	};
	
	extern double GetSegmentTime(Segment& _Segment);
	extern bool IsConsonant(string Symbol);
	#define CVS_VERSION "1.6"
}

 #endif /*NOMMOCSVC _H */
 