#include "Effector.h"
#include "WaveEffector.h"
#include "EnvEffector.h"
#include "LibCyberBase/Overall.h"
#include "SPKit/misc/converter.h"
#include "../Scheduler.h"

using namespace converter;
using namespace Overall;

void Effector::Render(WaveBuffer& _WaveBuffer, CVSCommon::Segment& _Segment, SpeechSynthesizerSendBack& SendBack)
{
	EnvelopeEffector::OpennessListRender(_WaveBuffer, _Segment);
	if(_Segment.Effects.Shrink != 0)
		WaveEffector::Shrink(_WaveBuffer, _Segment, SendBack);
	if(_Segment.Effects.ForwardCut != 0)
		EnvelopeEffector::ForwardCutter(_WaveBuffer, _Segment);
	WaveEffector::Blur(_WaveBuffer, _Segment);
	if(_Segment.Effects.PElopeEnabled)
	{
		//Use preseted envelope
		switch(_Segment.Effects.PresetedEnvelope)
		{
			case CVSCommon::ADSR:
				EnvelopeEffector::ADSREnvelope(_WaveBuffer, _Segment);
				break;
		}
	}
	if(_Segment.Effects.ElistEnabled)
	{
		//Use envelope list
		EnvelopeEffector::EnvelopeListRender(_WaveBuffer, _Segment);
	}
	if(_Segment.Effects.Breath.Magnitude != 0)
		WaveEffector::BreathNoise(_WaveBuffer, _Segment);
	
}
