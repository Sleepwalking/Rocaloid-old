#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "LibCyberBase/SPKit/structure/string.h"
#include "Synthesizer/SpeechSynthesizer.h"
#include "LibCVSCommon/CVSCommon.h"
#include "LibCyberBase/Overall.h"

class WaveBuffer;
struct SpeechSynthesizerSendBack
{
	int VOT;
};
namespace Scheduler
{
	extern CVSCommon::CVS* CVSData;
	extern SpeechSynthesizer* Synthesizer;
	extern WaveBuffer* Wave1;
	extern WaveBuffer* Wave2;
	extern SpeechSynthesizerSendBack SSSendBack;
	extern bool Verbose;

	extern void Init();
	extern void Exit();
	extern void CloseAll();
	extern void OpenCVS(string FileName);
	extern void SetFileOutput(string FileName);
	extern void RunSynthesizer();
	extern int SegmentSynthesize(SpeechSynthesizer& Synth,
	                             CVSCommon::Segment& _Segment,
	                             WaveBuffer& Wave);
}
#endif