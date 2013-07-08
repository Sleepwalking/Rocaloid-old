#include "SpeechSynthesizer.h"
#include "SPKit/misc/converter.h"
#include "../Scheduler.h"

#define DebugLevel 1
#define PeriodPrediction

#if(DebugLevel > 0)
	#include "SPKit/io/terminal.h"
#endif

using namespace converter;
SpeechSynthesizer::SpeechSynthesizer()
{
	PitchSynth1 = new PitchPreSynthesizer();
	PitchSynth2 = new PitchPreSynthesizer();
	PCalc = new PitchCalculator();
	LastTime = -1;
}
SpeechSynthesizer::~SpeechSynthesizer()
{
	delete PitchSynth1;
	delete PitchSynth2;
	delete PCalc;
}

void SpeechSynthesizer::SetSegment(Segment& _Segment)
{
	SynthSegment = &_Segment;
	LastTime = -1;
	PCalc -> Restore();
}
void SpeechSynthesizer::RegulatePitch(double Time)
{
	int Last_NextFreqSetNum, NextFreqSetNum;
	FreqSet *NextFreqSet, *LastFreqSet;
	Last_NextFreqSetNum = GetNextFreqNumByTime(LastTime);
	NextFreqSetNum = GetNextFreqNumByTime(Time);
	if(NextFreqSetNum == -1)
	{
		NextFreqSetNum = SynthSegment -> FreqListQ + 1;
		NextFreqSet = &(SynthSegment -> FreqList[SynthSegment -> FreqListQ]);
	}else
		NextFreqSet = &(SynthSegment -> FreqList[NextFreqSetNum]);
	if(Last_NextFreqSetNum == -1)
		Last_NextFreqSetNum = NextFreqSetNum;
	//Only regulates when entering new FreqSet
	if(NextFreqSetNum == Last_NextFreqSetNum)
	{
		//No Change.
	}else if(NextFreqSetNum == Last_NextFreqSetNum + 1)
	{
		//Entering new FreqSet
		if(NextFreqSetNum == SynthSegment -> FreqListQ + 1)
		{
			//After FreqList
			PCalc -> SetTarget(
				NextFreqSet -> Freq, NextFreqSet -> Time,
				NextFreqSet -> Freq, INFINITY
			);
			#if(DebugLevel > 0)
				wLine(CStr("Speech Synthesizer: PCalc exceeds target."));
			#endif
		}else
		{
			LastFreqSet = &(SynthSegment -> FreqList[Last_NextFreqSetNum]);
			PCalc -> SetTarget(
				LastFreqSet -> Freq, LastFreqSet -> Time,
				NextFreqSet -> Freq, NextFreqSet -> Time
			);
			#if(DebugLevel > 0)
				wLine(CStr("Speech Synthesizer: PCalc set target: ") +
				      CStr(LastFreqSet -> Freq) + CStr("Hz, at ") +
				      CStr(LastFreqSet -> Time) + CStr("sec, ") +
				      CStr(NextFreqSet -> Freq) + CStr("Hz, at ") +
				      CStr(NextFreqSet -> Time) + CStr("sec."));
			#endif
		}
	}else
	{
		Exception("Speech Synthesizer: Invalid FreqSet.");
	}
}
void SpeechSynthesizer::Synthesize(double Time, FrameBuffer& Dest)
{
	Time = GetTimePassed(Time);

	if(Time < LastTime)
		Exception("Time to synthesize is smaller than the previous call.");

	RegulatePitch(Time);

	int LastTPhoneNum, CurrentTPhoneNum;
	TPhone CurrentTPhone;
	FrameBuffer Frame1, Frame2;
	
	LastTPhoneNum = GetTPhoneNumByTime(LastTime);
	CurrentTPhoneNum = GetTPhoneNumByTime(Time);
	if(CurrentTPhoneNum == -1)
	{
		EmptyFrame(Dest);
		goto EndFunc;
	}
	CurrentTPhone = SynthSegment -> TPhoneList[CurrentTPhoneNum];

	if(CurrentTPhoneNum == LastTPhoneNum)
	{
		//Continue Synthesizing
	}else if(CurrentTPhoneNum == LastTPhoneNum + 1)
	{
		//After a transition
		//First seek for "Preserved"
		if(! CurrentTPhone.Start.Type)
		{
			if(CurrentTPhone.Start.Preserved == 1)
			{
				//Preserves the start of LastTPhone.(Though no real effects.)
			}else if(CurrentTPhone.Start.Preserved == 2)
			{
				//Preserves the End of LastTPhone.
				PtrSwap(PitchSynth1, PitchSynth2);
				#if(DebugLevel > 0)
					wLine(CStr("Speech Synthesizer: PitchSynth Swaps."));
				#endif
			}else
			{
				Exception(CStr("Invalid Preserve Target as ") + CStr(CurrentTPhone.Start.Preserved));
			}
		}
		if(! CurrentTPhone.Dest.Type)
		{
			if(CurrentTPhone.Dest.Preserved == 2)
			{
				//Preserves the end of LastTPhone.(Though no real effects.)
			}else if(CurrentTPhone.Dest.Preserved == 1)
			{
				//Preserves the start of LastTPhone, though no real use.
				PtrSwap(PitchSynth1, PitchSynth2);
				#if(DebugLevel > 0)
					wLine(CStr("Speech Synthesizer: PitchSynth Swaps."));
				#endif
			}else
			{
				Exception(CStr("Invalid Preserve Target as ") + CStr(CurrentTPhone.Dest.Preserved));
			}
			if(CurrentTPhone.Dest.Preserved == CurrentTPhone.Start.Preserved)
			{
				Exception(CStr("Same Preserve Target as ") + CStr(CurrentTPhone.Start.Preserved));
			}
		}
		//Second seek for "New"
		if(CurrentTPhone.Start.Type)
		{
			PitchSynth1 -> SetSymbol(CurrentTPhone.Start.Symbol);
			#if(DebugLevel > 0)
				wLine(CStr("Speech Synthesizer: ") + CStr(CurrentTPhone.Start.Symbol) + CStr(" -> ") + CStr("PitchSynth1"));
			#endif
		}
		if(CurrentTPhone.Dest.Type)
		{
			PitchSynth2 -> SetSymbol(CurrentTPhone.Dest.Symbol);
			#if(DebugLevel > 0)
				wLine(CStr("Speech Synthesizer: ") + CStr(CurrentTPhone.Start.Symbol) + CStr(" -> ") + CStr("PitchSynth2"));
			#endif
		}
	}else
	{
		//Skipping TPhone(s).
	}

	PCalc -> PitchCalc(Time);
	PitchSynth1 -> Synthesize(*PCalc, Time, Frame1);
	PitchSynth2 -> Synthesize(*PCalc, Time, Frame2);
	double TR1, TR2;
	#ifdef PeriodPrediciton
	{
		TR1 = GetTransitionRatio(CurrentTPhoneNum, Time);
		SetStartMixRatio(TR1);
		TR2 = GetTransitionRatio(CurrentTPhoneNum, Time + CDbl(Frame2.Ubound) / SampleRate);
		//In very rare cases, especially when approaching the next TPhone, GetTransitionRatio may be different
		//from the real situation (TR2 -> 0, or TR2 > 1).
		if(abs(TR2 - TR1) > 0.3 && TR2 < TR1)
			TR2 = 1;
		if(TR2 > 1)
			TR2 = 1;
		SetDestMixRatio(TR2);
		#if(DebugLevel > 1)
			wLine(CStr("SpeechSynthesizer: Ratio from ") + CStr(TR1) + CStr(" to ") + CStr(TR2));
		#endif
	}
	#else
	{
		SetMixRatio(GetTransitionRatio(CurrentTPhoneNum, Time));
	}
	#endif
	//Get prepared for the next synthesis.
	LastTime = Time;
	FrameMix(Frame1, Frame2, Dest);
	EndFunc:;
}

int SpeechSynthesizer::GetNextFreqNumByTime(double Time)
{
	int i;
	for(i = 0;i <= SynthSegment -> FreqListQ;i ++)
		if(SynthSegment -> FreqList[i].Time > Time)
			return i;
	//After FreqSets
	return -1;
}
int SpeechSynthesizer::GetLastFreqNumByTime(double Time)
{
	int i;
	for(i = 0;i <= SynthSegment -> FreqListQ;i ++)
		if(SynthSegment -> FreqList[i].Time > Time)
			return i - 1;
	//After FreqSets
	return SynthSegment -> FreqListQ;
}
double SpeechSynthesizer::GetTransitionRatio(int TPhoneNum, double Time)
{
	double Completeness;
	double ConsonantLen = 0;
	//Skip the consonant
	if(PitchSynth1 -> IsConsonant() &&
	   SynthSegment -> TPhoneList[TPhoneNum].Transition.StartRatio == 0)
	{
		Scheduler::SSSendBack.VOT = PitchSynth1 -> GetStartPoint();
		ConsonantLen = CDbl(PitchSynth1 -> GetStartPoint()) / SampleRate;
	}
	if(PitchSynth2 -> IsConsonant())
		ConsonantLen = CDbl(PitchSynth2 -> GetStartPoint() > ConsonantLen ?
							PitchSynth2 -> GetStartPoint() : ConsonantLen)
							/ SampleRate;
	Time -= ConsonantLen;
	if(Time < 0)
		return 0;
	Completeness = GetTimePassedInTPhone(TPhoneNum, Time) /
					(SynthSegment -> TPhoneList[TPhoneNum].Transition.Time - ConsonantLen);
	return Completeness * SynthSegment -> TPhoneList[TPhoneNum].Transition.EndRatio +
		(1 - Completeness) * SynthSegment -> TPhoneList[TPhoneNum].Transition.StartRatio;
}
double SpeechSynthesizer::GetTimePassedInTPhone(int TPhoneNum, double Time)
{
	int i;
	double acc = 0;
	for(i = 0;i < TPhoneNum;i ++)
		acc += SynthSegment -> TPhoneList[i].Transition.Time;
	return Time - acc;
}
double SpeechSynthesizer::GetTimePassed(double Time)
{
	return Time - SynthSegment -> StartTime;
}
int SpeechSynthesizer::GetTPhoneNumByTime(double Time)
{
	if(Time < 0)
		return -1;
	int i;
	double acc = 0;
	for(i = 0;i <= SynthSegment -> TPhoneListQ;i ++)
	{
		acc += SynthSegment -> TPhoneList[i].Transition.Time;
		if(acc >= Time)
			return i;
	}
	return -1;
}
TPhone SpeechSynthesizer::GetTPhoneByTime(double Time)
{
	int i = GetTPhoneNumByTime(Time);
	if(i > 0)
		return SynthSegment -> TPhoneList[i];
	TPhone EmptyTPhone;
	EmptyTPhone.Start.Type = true;
	EmptyTPhone.Start.Symbol = "NULL";
	EmptyTPhone.Dest.Type = true;
	EmptyTPhone.Dest.Symbol = "NULL";
	return EmptyTPhone;
}