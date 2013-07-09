#ifndef MIXERWRITER_H
#define MIXERWRITER_H

#include "SlWave/wave.h"
#include "SPKit/structure/string.h"
#include "LibCyberBase/WaveBuffer.h"

namespace MixerWriterEffector
{
	extern PCMWaveFile* WaveWriter;
	extern string FileName;
	extern int WriterCounter;
	extern int TotalCount;
	extern void SetFileOutput(string _FileName);
	extern void Write(WaveBuffer& Wave, int Start, int Dest);
	extern void MixAndWrite(WaveBuffer& Wave1, WaveBuffer& Wave2,
	                        int S1, int S2, int Duration);
	extern void WriteBlank(int Duration);
	extern void Finish();
}

#endif
