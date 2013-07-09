#include "EnvEffector.h"
#include "SPKit/misc/converter.h"
#include "SPKit/structure/array.h"
#include "LibCyberBase/Overall.h"

using namespace converter;
void EnvelopeEffector::ADSREnvelope(WaveBuffer& _WaveBuffer,
                                    double Amp, int Attack, int Decline, int Release, int EndTime)
{
	int i;
	int T0, T1;
	T0 = Attack;
	T1 = EndTime - Release;
	for(i = 0;i < Attack;i ++)
		_WaveBuffer.Data[i] *= Amp * ((double)i / (double)Attack);
	for(i = 0;i < Decline;i ++)
		_WaveBuffer.Data[i + T0] *= Amp * (1.0f - (double)i / Decline) + (double)i / Decline;
	for(i = 0;i < Release;i ++)
		_WaveBuffer.Data[i + T1] *= 1.0f - (double)i / Release;
	//Avoid remaining half frames.
	for(i = EndTime;i < EndTime + 1000;i ++)
		_WaveBuffer.Data[i] = 0;
}
void EnvelopeEffector::ADSREnvelope(WaveBuffer& _WaveBuffer,
                                    CVSCommon::Segment& _Segment)
{
	double Amp;
	int Attack, Release, Decline, EndTime;
	EndTime = _WaveBuffer.Pointer;
	Amp = _Segment.Effects.ADSR.Amplitude;
	Attack = CInt(_Segment.Effects.ADSR.Attack * SampleRate);
	Decline = CInt(_Segment.Effects.ADSR.Decline * SampleRate);
	Release = CInt(_Segment.Effects.ADSR.Release * SampleRate);
	Release = Release > EndTime ? EndTime : Release;
	ADSREnvelope(_WaveBuffer, Amp, Attack, Decline, Release, EndTime);
}
void EnvelopeEffector::OpennessListRender(WaveBuffer& _WaveBuffer,
                                          CVSCommon::Segment& _Segment)
{
	CVSCommon::EnvelopeSet* EList = new CVSCommon::EnvelopeSet[10];
	int EListQ;
	int i;
	double TimeAcc = 0;

	EListQ = _Segment.TPhoneListQ + 1;

	EList[0].Amplitude = _Segment.Effects.OpennessList[0];
	EList[0].Time = 0;
	for(i = 1;i <= EListQ;i ++)
	{
		TimeAcc += _Segment.TPhoneList[i - 1].Transition.Time;
		EList[i].Amplitude = _Segment.Effects.OpennessList[i];
		EList[i].Time = TimeAcc;
	}
	EnvelopeListRender(_WaveBuffer, EList, EListQ);
	
	delete []EList;
}
void EnvelopeEffector::EnvelopeListRender(WaveBuffer& _WaveBuffer,
                                          CVSCommon::EnvelopeSet EList[], int EListQ)
{
	int i;
	int a, b, t;
	double Completeness;
	for(i = 1;i <= EListQ;i ++)
	{
		a = CInt(EList[i - 1].Time * SampleRate);
		b = CInt(EList[i].Time * SampleRate) - 1;
		for(t = a;t <= b;t ++)
		{
			Completeness = ((double)t - a) / ((double)b - a);
			_WaveBuffer.Data[t] *= (1 - Completeness) * EList[i - 1].Amplitude +
									Completeness * EList[i].Amplitude;
		}
	}
}
void EnvelopeEffector::EnvelopeListRender(WaveBuffer& _WaveBuffer,
                                          CVSCommon::Segment& _Segment)
{
	EnvelopeListRender(_WaveBuffer, &_Segment.Effects.EnvelopeList[0], _Segment.Effects.EnvelopeListQ);
}
void EnvelopeEffector::ForwardCutter(WaveBuffer& _WaveBuffer,
                                     CVSCommon::Segment& _Segment)
{
	int i;
	int CutSamples = CInt(_Segment.Effects.ForwardCut * SampleRate);
	int CutLength = _WaveBuffer.Pointer - CutSamples;
	//Left Shift
	for(i = 0;i <= CutLength;i ++)
		_WaveBuffer.Data[i] = _WaveBuffer.Data[i + CutSamples];
	for(i = 1;i <= 1000;i ++)
		_WaveBuffer.Data[i + CutLength] = 0;
	_WaveBuffer.Pointer -= CutSamples;
	ADSREnvelope(_WaveBuffer, 1, CutSamples > 2000 ? 2000 : CutSamples, 0, 0, _WaveBuffer.Pointer);
}