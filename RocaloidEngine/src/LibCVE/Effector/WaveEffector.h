#ifndef WAVEEFFECTOR_H
#define WAVEEFFECTOR_H

#include "LibCyberBase/WaveBuffer.h"
#include "LibCVSCommon/CVSCommon.h"

struct SpeechSynthesizerSendBack;
namespace WaveEffector
{
	extern void Blur(WaveBuffer& _WaveBuffer, CVSCommon::Segment& _Segment);
	extern void BreathNoise(WaveBuffer& _WaveBuffer, CVSCommon::Segment& _Segment);
	extern void Shrink(WaveBuffer& _WaveBuffer, CVSCommon::Segment& _Segment, SpeechSynthesizerSendBack& SendBack);
}
#endif