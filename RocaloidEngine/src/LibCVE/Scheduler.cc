#include "Scheduler.h"
#include "LibCyberBase/WaveBuffer.h"
#include "LibCVSCommon/CVSReader.h"
#include "SPKit/misc/converter.h"
#include "Effector/Effector.h"
#include "Effector/MixerWriter.h"

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
		MixerWriterEffector::SetFileOutput(FileName);
	}
	void RunSynthesizer()
	{
		int S1, S2;
		int T1, T2;
		int Overlap;
		int i;

		T1 = SegmentSynthesize(*Synthesizer, CVSData -> SegmentList[0], *Wave1);
		S1 = CInt(CVSData -> SegmentList[0].StartTime * SampleRate);
		Overlap = 0;
		MixerWriterEffector::WriteBlank(S1);
		//CVSData -> SegmentListQ
		for(i = 0;i < CVSData -> SegmentListQ;i ++)
		{
			#if(DebugLevel > 0)
				wLine(CStr("Scheduler: Synthesizing segment ") + CStr(i));
			#endif
			S2 = CInt(CVSData -> SegmentList[i + 1].StartTime * SampleRate);

			//Write to S2
			MixerWriterEffector::Write(*Wave1, Overlap, S2 - S1);
			T2 = SegmentSynthesize(*Synthesizer, CVSData -> SegmentList[i + 1], *Wave2);
			if(S2 < S1 + T1)
			{
				//Mix & Write to S1 + T1 if Overlapped
				MixerWriterEffector::MixAndWrite(*Wave1, *Wave2, S2 - S1, 0, S1 + T1 - S2);
				Overlap = S1 + T1 - S2;
			}else
				Overlap = 0;
			ObjSwap(S1, S2);
			ObjSwap(T1, T2);
			PtrSwap(Wave1, Wave2);
		}
		MixerWriterEffector::Write(*Wave1, Overlap, T1 - Overlap);
		MixerWriterEffector::Finish();
		#if(DebugLevel > 0)
			wLine(CStr("Scheduler: Synthesis finished."));
		#endif
	}
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
		Effector::Render(Wave, _Segment, SSSendBack);
		return Wave.Pointer;
	}
}