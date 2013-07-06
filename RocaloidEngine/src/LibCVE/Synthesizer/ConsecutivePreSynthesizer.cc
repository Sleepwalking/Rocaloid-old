#include "ConsecutivePreSynthesizer.h"
#include "LibCyberBase/SPKit/structure/string.h"
#include "LibCyberBase/SPKit/misc/converter.h"
#include "LibCyberBase/CVDB/CBVIO.h"
#include "LibCyberBase/MultiFrameBuffer.h"
#include "LibCyberBase/Overall.h"

#define ConsecutivePreSynthesizer_DebugLevel 0

#if(ConsecutivePreSynthesizer_DebugLevel > 0)
	#include "LibCyberBase/SPKit/io/terminal.h"
#endif

using namespace converter;
ConsecutivePreSynthesizer::ConsecutivePreSynthesizer()
{
	Pointer = 0;
	SamplesPassed = 0;
}
void ConsecutivePreSynthesizer::ClearSymbol()
{
	CVDB.ClearSymbol();
}
void ConsecutivePreSynthesizer::Load(string Name)
{
	if(CVDB.GetName() != Name)
	{
		CBVFile::Open(Name + CStr(".cbv"), CVDB);
		Pointer = 0;
		SamplesPassed = 0;
		#if(ConsecutivePreSynthesize_DebugLevel > 0)
			wLine(CStr("ConsecutivePreSynthesizer") + Name);
		#endif
	}
}
void ConsecutivePreSynthesizer::Synchronize(int _SamplesPassed)
{
	while(SamplesPassed < _SamplesPassed)
	{
		SamplesPassed += CVDB.Buffer -> Data[Pointer] -> Ubound;
		Pointer ++;
	}
}
void ConsecutivePreSynthesizer::Synchronize(ConsecutivePreSynthesizer& Source)
{
	Synchronize(Source.SamplesPassed);
}
void ConsecutivePreSynthesizer::SkipConsonant()
{
	Pointer = CVDB.GetBaseFrame() + CInt(0.1 * SampleRate / CDbl(CVDB.Info.AveragePeriod));
}
void ConsecutivePreSynthesizer::Synthesize(FrameBuffer& Dest)
{
	#if(ConsecutivePreSynthesizer_DebugLevel > 2)
		wLine(CStr("ConsecutivePreSynthesizer: ") + CVDB.GetName() + CStr(" Pointer:") + CStr(Pointer));
	#endif
	int Pointer2;
	double Ratio;
	int CirculationBase, CirculationQuantity;
	if(CVDB.Info.Consonant)
	{
		CirculationQuantity = CInt(0.2 * SampleRate / CDbl(CVDB.Info.AveragePeriod));
		CirculationBase = CInt((CVDB.Info.StartPosition + 0.1 * SampleRate) / CDbl(CVDB.Info.AveragePeriod));
	}else
	{
		CirculationQuantity = CInt(0.3 * SampleRate / CDbl(CVDB.Info.AveragePeriod));
		CirculationBase = CInt(0.1 * SampleRate / CDbl(CVDB.Info.AveragePeriod));
	}
	if(Pointer < CVDB.Buffer -> Ubound - CirculationQuantity)
	{
		Dest = *(CVDB.Buffer -> Data[Pointer]);
		Pointer ++;
		SamplesPassed += Dest.Ubound + 1;
	}else
	{
		Pointer2 = Pointer - CVDB.Buffer -> Ubound + CirculationQuantity;
		Ratio = CDbl(Pointer2) / CirculationQuantity;
		#if(ConsecutivePreSynthesizer_DebugLevel > 1)
			wLine(CStr("ConsecutivePreSynthesizer:  ") + CVDB.GetName() + CStr(" Ratio:") + CStr(Ratio));
		#endif
		SetStartMixRatio(Ratio);
		SetDestMixRatio(Ratio + 1.0f / CirculationQuantity);
		FrameMix(*CVDB.Buffer -> Data[Pointer], *CVDB.Buffer -> Data[Pointer2 + CirculationBase], Dest);
		Pointer ++;
		if(Pointer2 >= CirculationQuantity)
		{
			Pointer = CirculationBase + 1;
			#if(ConsecutivePreSynthesizer_DebugLevel > 1)
				wLine(CStr("ConsecutivePreSynthesizer:  Circulate at pointer:") + CStr(Pointer));
			#endif
		}
		SamplesPassed += Dest.Ubound + 1;
	}
}
string ConsecutivePreSynthesizer::GetSymbol()
{
	return CVDB.GetSymbol();
}
string ConsecutivePreSynthesizer::GetPitch()
{
	return CVDB.GetPitch();
}
int ConsecutivePreSynthesizer::GetBaseFrame()
{
	return CVDB.GetBaseFrame();
}
int ConsecutivePreSynthesizer::GetSamplesPassed()
{
	return SamplesPassed;
}