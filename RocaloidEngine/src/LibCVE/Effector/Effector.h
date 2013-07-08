#ifndef EFFECTOR_H
#define EFFECTOR_H

#include "LibCyberBase/WaveBuffer.h"
#include "LibCVSCommon/CVSCommon.h"

struct SpeechSynthesizerSendBack;
namespace Effector
{
	extern void Render(WaveBuffer& _WaveBuffer, CVSCommon::Segment& _Segment, SpeechSynthesizerSendBack& SendBack);
}
#endif