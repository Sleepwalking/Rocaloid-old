#include "MixerWriter.h"
#include "LibCyberBase/Overall.h"

using namespace Overall;

PCMWaveFile* MixerWriterEffector::WaveWriter;
string MixerWriterEffector::FileName;
int MixerWriterEffector::WriterCounter;
int MixerWriterEffector::TotalCount;

void MixerWriterEffector::SetFileOutput(string _FileName)
{
	WriterCounter = 0;
	TotalCount = 0;
	WaveWriter = new PCMWaveFile;
	WaveWriter -> header.channel = 1;
	WaveWriter -> header.samplePerSecond = SampleRate;
	WaveWriter -> header.bytePerSecond = SampleRate / 2;
	WaveWriter -> header.blockAlign = 2;
	WaveWriter -> header.bitPerSample = 16;
	
	WaveWriter -> save(_FileName);
}
void MixerWriterEffector::Write(WaveBuffer& Wave, int Start, int Dest)
{
	int i;
	if(Dest > Wave.Pointer)
	{
		for(i = Start;i < Wave.Pointer;i ++)
		{
			WaveWriter -> write(Wave.Data[i]);
			WriterCounter ++;
		}
		WriteBlank(Dest - Wave.Pointer);
	}else
	{
		for(i = Start;i < Dest;i ++)
		{
			WaveWriter -> write(Wave.Data[i]);
			WriterCounter ++;
		}
	}
}
void MixerWriterEffector::MixAndWrite(WaveBuffer& Wave1, WaveBuffer& Wave2,
                                      int S1, int S2, int Duration)
{
	int i;
	for(i = 0;i < Duration;i ++)
		WaveWriter -> write(Wave1.Data[S1 + i] + Wave2.Data[S2 + i]);
}
void MixerWriterEffector::WriteBlank(int Duration)
{
	int i;
	for(i = 0;i < Duration;i ++)
		WaveWriter -> write(0);
}
void MixerWriterEffector::Finish()
{
	WaveWriter -> finishWrite();
	delete WaveWriter;
}