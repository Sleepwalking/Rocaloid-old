#ifndef SPEECHSYNTHESIZER_H
#define SPEECHSYNTHESIZER_H
#include "Synthesizer.h"
#include "PitchPreSynthesizer.h"
#include "LibCyberBase/FrameBuffer.h"
#include "../PitchCalc.h"
#include "LibCVSCommon/CVSCommon.h"

using namespace CVSCommon;
class SpeechSynthesizer : public Synthesizer
{
	public:
		SpeechSynthesizer();
		~SpeechSynthesizer();

		void SetSegment(Segment& _Segment);
		void RegulatePitch(double Time);
		void Synthesize(double Time, FrameBuffer& Dest);
	private:
		int GetNextFreqNumByTime(double Time);
		int GetLastFreqNumByTime(double Time);
		double GetTransitionRatio(int TPhoneNum, double Time);
		double GetTimePassedInTPhone(int TPhoneNum, double Time);
		double GetTimePassed(double Time);
		int GetTPhoneNumByTime(double Time);
		TPhone GetTPhoneByTime(double Time);
		
		PitchPreSynthesizer* PitchSynth1;
		PitchPreSynthesizer* PitchSynth2;
		PitchCalculator* PCalc;
		Segment* SynthSegment;
		double LastTime;
};
#endif