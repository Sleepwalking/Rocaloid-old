#include "PitchCalc.h"
#include "SPKit/structure/string.h"
#include "SPKit/misc/converter.h"

#define DebugLevel 0

#if(DebugLevel > 0)
	#include "SPKit/io/terminal.h"
#endif

using namespace converter;
PitchCalculator::PitchCalculator()
{
	TargetFreq = 0;
	TargetTime = 0;
	StartFreq = 0;
	StartTime = 0;
	TimeResolution = 0.03;
}

void PitchCalculator::PitchCalc(double Time)
{
	double Freq = GetFreqAt(Time);
	int Quantity = CInt((TargetTime - StartTime) / TimeResolution) + 1;
	int Range;
	double Interval;
	double i;
	CurrentFreq = Freq;

	if(DirectionIsUp())
	{
		//Low Pitch -> High Pitch
		Range = GetFloorPitch(TargetFreq) - GetFloorPitch(StartFreq) + 2;
		Interval = CDbl(Range) / CDbl(Quantity);
		for(i = GetFloorPitch(StartFreq);i <= GetFloorPitch(TargetFreq) + 1;i += Interval)
			if(Freq >= FreqList[CInt(i)] && Freq < FreqList[CInt(i + Interval)])
			{
				LowPitch = CInt(i);
				HighPitch = CInt(i + Interval);
				if(HighPitch > GetFloorPitch(TargetFreq) + 1)
					HighPitch = GetFloorPitch(TargetFreq) + 1;
				break;
			}
		TransitionRatio = (Freq - FreqList[LowPitch]) / (FreqList[HighPitch] - FreqList[LowPitch]);
	}else
	{
		//High Pitch -> Low Pitch
		Range = GetFloorPitch(StartFreq) - GetFloorPitch(TargetFreq) + 2;
		Interval = CDbl(Range) / CDbl(Quantity);
		for(i = GetFloorPitch(StartFreq) + 1;i >= GetFloorPitch(TargetFreq);i -= Interval)
			if(Freq < FreqList[CInt(i)] && Freq >= FreqList[CInt(i - Interval)])
			{
				HighPitch = CInt(i);
				LowPitch = CInt(i - Interval);
				if(LowPitch < GetFloorPitch(TargetFreq))
					LowPitch = GetFloorPitch(TargetFreq);
				break;
			}
		TransitionRatio = (FreqList[HighPitch] - Freq) / (FreqList[HighPitch] - FreqList[LowPitch]);
	}
	#if(DebugLevel > 0)
		wLine(CStr("Pitch Calc: Freq:") + CStr(Freq) + CStr("   Quantity:") + CStr(Quantity)
		      + CStr("  Range:") + CStr(Range));
		wLine(CStr("	LowPitch:") + CStr(LowPitch) + CStr("   HighPitch:") + CStr(HighPitch));
	#endif
	
}
double PitchCalculator::GetFreqAt(double Time)
{
	return StartFreq + (TargetFreq - StartFreq) * (Time - StartTime) / (TargetTime - StartTime);
}

void PitchCalculator::Restore()
{
	TargetFreq = 0;
	TargetTime = 0;
	StartFreq = 0;
	StartTime = 0;
	TimeResolution = 0.03;
	LowPitch = 0;
	HighPitch = 0;
	TransitionRatio = 0;
}
void PitchCalculator::SetTarget(double _StartFreq, double _StartTime, double _TargetFreq, double _TargetTime)
{
	if(_TargetTime <= _StartTime)
		Exception("Target Time is smaller or equal to Start Time!");
	TargetFreq = _TargetFreq;
	StartFreq = _StartFreq;
	TargetTime = _TargetTime;
	StartTime = _StartTime;
}
void PitchCalculator::SetResolution(double _TimeResolution)
{
	TimeResolution = _TimeResolution;
}
string PitchCalculator::GetLowPitch()
{
	if(LowPitch > Pitch_C5)
		return PitchList[Pitch_C5];
	else if(LowPitch < Pitch_C2)
		return PitchList[Pitch_C2];
	else
		return PitchList[LowPitch];
}
string PitchCalculator::GetHighPitch()
{
	if(HighPitch > Pitch_C5)
		return PitchList[Pitch_C5];
	else if(HighPitch < Pitch_C2)
		return PitchList[Pitch_C2];
	else
		return PitchList[HighPitch];	
}
double PitchCalculator::GetTransitionRatio()
{
	return TransitionRatio;
}
double PitchCalculator::GetCurrentFreq()
{
	return CurrentFreq;
}
bool PitchCalculator::DirectionIsUp()
{
	if(TargetFreq > StartFreq)
		return true;
	else
		return false;
}

int PitchCalculator::GetPitch(double Freq)
{
	int i;
	if(Freq < (FreqList[1] + FreqList[2]) / 2)
		return 0;
	if(Freq >= (FreqList[PitchListQ - 1] + FreqList[PitchListQ]) / 2)
		return PitchListQ;
	for(i = 1;i < PitchListQ;i ++)
		if((Freq < (FreqList[i] + FreqList[i + 1]) / 2) &&
		   (Freq >= (FreqList[i] + FreqList[i - 1]) / 2))
			return i;
	return -1;
}
int PitchCalculator::GetFloorPitch(double Freq)
{
	int i;
	for(i = 0;i <= PitchListQ;i ++)
		if(Freq < FreqList[i])
			return i - 1;
}