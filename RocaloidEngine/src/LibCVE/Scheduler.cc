#include "Scheduler.h"
#include "LibCyberBase/WaveBuffer.h"
#include "LibCVSCommon/CVSReader.h"
#include "SPKit/misc/converter.h"

#define DebugLevel 1

#if(DebugLevel > 0)
	#include "SPKit/io/terminal.h"
#endif

using namespace converter;
namespace Scheduler
{
	CVSCommon::CVS* CVSData;
	SpeechSynthesizer* Synthesizer;
	WaveBuffer* Wave1;
	WaveBuffer* Wave2;
	SpeechSynthesizerSendBack SSSendBack;

	void Init()
	{
		Synthesizer = new SpeechSynthesizer();
		Wave1 = new WaveBuffer(30 * SampleRate);
		Wave2 = new WaveBuffer(30 * SampleRate);
		CVSData = new CVS;
	}
	void Exit()
	{
		delete Synthesizer;
		delete Wave1;
		delete Wave2;
		delete CVSData;
	}
	void CloseAll()
	{
		//Not ensured yet.
	}
	void OpenCVS(string FileName)
	{
		CVSReader TempReader;
		TempReader.Open(FileName);
		TempReader.Read(*CVSData);
		TempReader.Close();
		#if(DebugLevel > 1)
			wLine(CStr("Scheduler:  ") + FileName + CStr(" loaded. ") + 
		 	      CStr(CVSData -> SegmentListQ + 1) + CStr(" segments in all."));
		#endif
	}
	void SetFileOutput(string FileName)
	{
		//MixerWriterEffector.SetFileOutput(FileName);
	}
	void RunSynthesizer();
	int SegmentSynthesize(SpeechSynthesizer& Synth,
	                      CVSCommon::Segment& _Segment,
	                      WaveBuffer& Wave)
	{
		Synth.SetSegment(_Segment);
		Wave.Pointer = 0;
		FrameBuffer Frame;
		int i = CInt(_Segment.StartTime * SampleRate);
		int j = CInt(CVSCommon::GetSegmentTime(_Segment) * SampleRate) + i;
		while(i < j)
		{
			Synth.Synthesize(CDbl(i) / SampleRate, Frame);
			Wave.Write(Frame);
			i += Frame.Ubound + 1;
		}
		//SSSendBack = GlobalSendBack; Needn't since SSSendBack is in a namespace.
		//Effector::Render(Wave, _Segment, SSSendBack);
		return Wave.Pointer;
	}
}