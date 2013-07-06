#ifndef CONSECUTIVEPRESYNTHESIZER_H
#define CONSECUTIVEPRESYNTHESIZER_H
#include "LibCyberBase/SPKit/defs.h"
#include "LibCyberBase/CVDB/CVDB.h"
#include "LibCyberBase/FrameBuffer.h"
#include "Synthesizer.h"

class string;
class ConsecutivePreSynthesizer : public Synthesizer
{
	public:
		CVDBContainer CVDB;
		
		ConsecutivePreSynthesizer();

		void ClearSymbol();
		void Load(string Name);
		void Synchronize(int _SamplesPassed);
		void Synchronize(ConsecutivePreSynthesizer& Source);
		void SkipConsonant();
		void Synthesize(FrameBuffer& Dest);
		
		string GetSymbol();
		string GetPitch();
		int GetBaseFrame();
		int GetSamplesPassed();
	private:
		int Pointer;
		int SamplesPassed;
};
#endif