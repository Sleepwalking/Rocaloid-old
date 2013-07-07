#include "PitchPreSynthesizer.h"
#include "../PitchCalc.h"
#include "SPKit/misc/converter.h"
#include "LibCyberBase/Overall.h"

#define DebugLevel 1
#define PeriodPredictionEnabled

#if(DebugLevel > 0)
	#include "SPKit/io/terminal.h"
#endif

using namespace Overall;
using namespace converter;
PitchPreSynthesizer::PitchPreSynthesizer()
{
	PreSynthesizer1 = new ConsecutivePreSynthesizer();
	PreSynthesizer2 = new ConsecutivePreSynthesizer();
	SetMixRatio(0);
	ConsonantPitchDeviationGotten = false;
}
PitchPreSynthesizer::PitchPreSynthesizer(string _Symbol)
{
	Symbol = _Symbol;
	PreSynthesizer1 = new ConsecutivePreSynthesizer();
	PreSynthesizer2 = new ConsecutivePreSynthesizer();
	SetMixRatio(0);
	ConsonantPitchDeviationGotten = false;
}
PitchPreSynthesizer::~PitchPreSynthesizer()
{
	delete PreSynthesizer1;
	delete PreSynthesizer2;
}

void PitchPreSynthesizer::SetSymbol(string _Symbol)
{
	Symbol = _Symbol;
	PreSynthesizer1 -> ClearSymbol();
	PreSynthesizer2 -> ClearSymbol();
}
bool PitchPreSynthesizer::IsConsonant()
{
	return PreSynthesizer1 -> CVDB.Info.Consonant;
}
int PitchPreSynthesizer::GetStartPoint()
{
	return PreSynthesizer1 -> CVDB.Info.StartPosition;
}

void PitchPreSynthesizer::HLPitchSynth(PitchCalculator& PCalc, FrameBuffer& Dest)
{
	FrameBuffer tmp;
	PreSynthesizer2 -> Synthesize(tmp);
	FrameStretch(tmp, (CDbl(FreqToPeriod(PCalc.GetCurrentFreq())) / PreSynthesizer2 -> CVDB.Info.AveragePeriod), Dest);
}
void PitchPreSynthesizer::Synthesize(PitchCalculator& PCalc, double Time, FrameBuffer& Dest)
{
	bool SwapOccured = false;
	bool PCalcDirectionUnchanged;
	double StartRatio, EndRatio;

	PCalc.PitchCalc(Time);
	//If symbols of pre-synthesizers don't match, reload them.
	if(PCalc.DirectionIsUp())
	{
		//Low Pitch -> High Pitch
		if(PreSynthesizer1 -> GetSymbol() != Symbol)
		{
			PreSynthesizer1 -> Load(Symbol + CStr("_") + PCalc.GetLowPitch());
			ConsonantPitchDeviationGotten = false;
			#if(DebugLevel > 0)
				wLine(CStr("PitchPreSynthesizer: Load Symbol ") + Symbol + CStr("_") + PCalc.GetLowPitch());
			#endif
		}
		if(PreSynthesizer2 -> GetSymbol() != Symbol)
		{
			PreSynthesizer2 -> Load(Symbol + CStr("_") + PCalc.GetHighPitch());
			ConsonantPitchDeviationGotten = false;
			#if(DebugLevel > 0)
				wLine(CStr("PitchPreSynthesizer: Load Symbol ") + Symbol + CStr("_") + PCalc.GetHighPitch());
			#endif
		}
	}else
	{
		//High Pitch -> Low Pitch
		if(PreSynthesizer1 -> GetSymbol() != Symbol)
		{
			PreSynthesizer1 -> Load(Symbol + CStr("_") + PCalc.GetHighPitch());
			ConsonantPitchDeviationGotten = false;
			#if(DebugLevel > 0)
				wLine(CStr("PitchPreSynthesizer: Load Symbol ") + Symbol + CStr("_") + PCalc.GetHighPitch());
			#endif
		}
		if(PreSynthesizer2 -> GetSymbol() != Symbol)
		{
			PreSynthesizer2 -> Load(Symbol + CStr("_") + PCalc.GetLowPitch());
			ConsonantPitchDeviationGotten = false;
			#if(DebugLevel > 0)
				wLine(CStr("PitchPreSynthesizer: Load Symbol ") + Symbol + CStr("_") + PCalc.GetLowPitch());
			#endif
		}
	}
	//When a new transition starts, rearrange the synthesizers.
	PCalcDirectionUnchanged = (PCalc.DirectionIsUp() == PCalcLastDirection); //See [1]
	if(PCalc.DirectionIsUp())
	{
		if(PCalc.GetHighPitch() != PreSynthesizer2 -> GetPitch())
		{
			if(PCalcDirectionUnchanged)
				//Ascending -> Ascending
				if(PCalc.GetLowPitch() != PreSynthesizer1 -> GetPitch())
					PtrSwap(PreSynthesizer1, PreSynthesizer2);
			else
				//Descending -> Ascending
				PtrSwap(PreSynthesizer1, PreSynthesizer2);
			PreSynthesizer2 -> Load(Symbol + CStr("_") + PCalc.GetHighPitch());
			if(PreSynthesizer1 -> CVDB.Info.Consonant)
				PreSynthesizer2 -> SkipConsonant();
			#if(DebugLevel > 0)
				wLine(CStr("PitchPreSynthesizer: Transition ") + Symbol + CStr("_") + PCalc.GetLowPitch() +
				      CStr(" -> ") + Symbol + CStr("_") + PCalc.GetHighPitch());
			#endif
		}
	}else
	{
		if(PCalc.GetLowPitch() != PreSynthesizer2 -> GetPitch())
		{
			if(PCalcDirectionUnchanged)
				//Descending -> Descending
				if(PCalc.GetHighPitch() != PreSynthesizer1 -> GetPitch())
					PtrSwap(PreSynthesizer1, PreSynthesizer2);
			else
				//Ascending -> Descending
				PtrSwap(PreSynthesizer1, PreSynthesizer2);
			PreSynthesizer2 -> Load(Symbol + CStr("_") + PCalc.GetLowPitch());
			if(PreSynthesizer1 -> CVDB.Info.Consonant)
				PreSynthesizer2 -> SkipConsonant();
			#if(DebugLevel > 0)
				wLine(CStr("PitchPreSynthesizer: Transition ") + Symbol + CStr("_") + PCalc.GetHighPitch() +
				      CStr(" -> ") + Symbol + CStr("_") + PCalc.GetLowPitch());
			#endif
		}
	}
	PCalcLastDirection = PCalc.DirectionIsUp(); //[1]
	//If frequency is beyond C2 - C5, stretch the frames.
	if(PCalc.GetCurrentFreq() >= FreqList[Pitch_C5])
	{
		HLPitchSynth(PCalc, Dest);
		goto EndFunc;
	}
	if(PCalc.GetCurrentFreq() <= FreqList[Pitch_C2])
	{
		HLPitchSynth(PCalc, Dest);
		goto EndFunc;
	}
	//MixRatio Prediction
	#ifdef PeriodPredictionEnabled
	{
		double TR1, TR2;
		TR1 = PCalc.GetTransitionRatio();
		SetStartMixRatio(TR1);
		PCalc.PitchCalc(Time + 1.0f / PCalc.GetFreqAt(Time));
		TR2 = PCalc.GetTransitionRatio();
		if(TR2 > 1)
			TR2 = 1;
		if(TR2 < TR1)
			SetDestMixRatio(1);
		else
			SetDestMixRatio(TR2);
		StartRatio = TR1;
		EndRatio = TR2;
		#if(DebugLevel > 1)
			wLine(CStr("PitchPreSynthesizer: Ratio from ") + CStr(TR1) + CStr(" to ") + CStr(TR2));
		#endif
	}
	#else
	{
		SetMixRatio(PCalc.GetTransitionRatio());
	}
	#endif
	//Always change from Frame1 -> Frame2
	//Skip the consonants
	if(PreSynthesizer1 -> CVDB.Info.Consonant)
	{
		//If one of them is consonant, so is the other.
		if(Time * SampleRate < PreSynthesizer1 -> CVDB.Info.StartPosition + 1000 ||
		   Time * SampleRate < PreSynthesizer2 -> CVDB.Info.StartPosition + 1000)
		{
			if(! ConsonantPitchDeviationGotten)
				ConsonantPitchDeviateTo1 = (EndRatio > 0.5);
			if(ConsonantPitchDeviateTo1)
			{
				PreSynthesizer2 -> Synchronize(*PreSynthesizer1);
				ConsonantSkip = true;
				PreSynthesizer1 -> Synthesize(Frame1);
				while(Frame1.Ubound <= 0)
					PreSynthesizer1 -> Synthesize(Frame1);
			}else
			{
				PreSynthesizer1 -> Synchronize(*PreSynthesizer2);
				ConsonantSkip = true;
				PreSynthesizer2 -> Synthesize(Frame1);
				while(Frame1.Ubound <= 0)
					PreSynthesizer2 -> Synthesize(Frame1);
			}
			Dest = Frame1;
			goto EndFunc;
		}else
		{
			if(ConsonantSkip)
			{
				StartRatio = 0;
				ConsonantSkip = false;
			}
		}
	}
	SetStartMixRatio(StartRatio);
	SetDestMixRatio(EndRatio);
	PreSynthesizer1 -> Synthesize(Frame1);
	PreSynthesizer2 -> Synthesize(Frame2);
	FrameMix(Frame1, Frame2, Dest);

	EndFunc:;
}
