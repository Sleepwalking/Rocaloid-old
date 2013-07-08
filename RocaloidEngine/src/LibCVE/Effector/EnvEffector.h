#ifndef ENVEFFECTOR_H
#define ENVEFFECTOR_H

#include "LibCyberBase/WaveBuffer.h"
#include "LibCVSCommon/CVSCommon.h"

namespace EnvelopeEffector
{
	extern void ADSREnvelope(WaveBuffer& _WaveBuffer,
	                         double Amp, int Attack, int Decline, int Release, int EndTime);
	extern void ADSREnvelope(WaveBuffer& _WaveBuffer,
	                         CVSCommon::Segment& _Segment);
	extern void OpennessListRender(WaveBuffer& _WaveBuffer,
	                               CVSCommon::Segment& _Segment);
	extern void EnvelopeListRender(WaveBuffer& _WaveBuffer,
	                               CVSCommon::EnvelopeSet EList[], int EListQ);
	extern void EnvelopeListRender(WaveBuffer& _WaveBuffer,
	                               CVSCommon::Segment& _Segment);
	extern void ForwardCutter(WaveBuffer& _WaveBuffer,
	                          CVSCommon::Segment& _Segment);
}
#endif