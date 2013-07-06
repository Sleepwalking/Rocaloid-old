#ifndef PITCHPRESYNTHESIZER_H
#define PITCHPRESYNTHESIZER_H
#include "Synthesizer.h"
#include "ConsecutivePreSynthesizer.h"
#include "SPKit/structure/string.h"
#include "LibCyberBase/FrameBuffer.h"

class PitchCalculator;
class PitchPreSynthesizer : public Synthesizer
{
	public:
		PitchPreSynthesizer();
		PitchPreSynthesizer(string _Symbol);
		~PitchPreSynthesizer();

		void SetSymbol(string _Symbol);
		bool IsConsonant();
		int GetStartPoint();

		void HLPitchSynth(PitchCalculator& PCalc, FrameBuffer& Dest);
		void Synthesize(PitchCalculator& PCalc, double Time, FrameBuffer& Dest);
	private:
		ConsecutivePreSynthesizer* PreSynthesizer1;
		ConsecutivePreSynthesizer* PreSynthesizer2;
		FrameBuffer Frame1;
		FrameBuffer Frame2;
		string Symbol;
		bool ConsonantSkip;
		bool ConsonantPitchDeviateTo1;
		bool ConsonantPitchDeviationGotten;
		bool PCalcLastDirection;
};
#endif