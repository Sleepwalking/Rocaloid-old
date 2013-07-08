#include "WaveEffector.h"
#include "LibCyberBase/Overall.h"
#include "SPKit/misc/converter.h"
#include "../Scheduler.h"

using namespace converter;
using namespace Overall;
void WaveEffector::Blur(WaveBuffer& _WaveBuffer, CVSCommon::Segment& _Segment)
{
	double* Temp = new double[50];
	int i;
	int TempPointer = 0;
	int EndTime = CInt(CVSCommon::GetSegmentTime(_Segment) * SampleRate);
	int Range = -10000;
	QuadResult Equ;
	double Ratio;
	Range = Range < -EndTime ? -EndTime : Range;
	Equ = GenerateQuadEquation(0, 0, -Range, 1, -Range * 0.8, 0.5);

	for(i = 0;i < 50;i ++)
		Temp[i] = 0;
	for(i = Range;i >= 0;i --)
	{
		if(TempPointer == 49)
			TempPointer = 0;
		else
			TempPointer ++;
		Ratio = Equ.a * i * i - Equ.b * i + Equ.c;
		Temp[TempPointer] = _WaveBuffer.Data[i + EndTime];
		_WaveBuffer.Data[i + EndTime] = _WaveBuffer.Data[i + EndTime] * Ratio
										+ GetDoubleSum(Temp, 49) / 50 * (1 - Ratio);
	}
	
	delete []Temp;
}
void WaveEffector::BreathNoise(WaveBuffer& _WaveBuffer, CVSCommon::Segment& _Segment)
{
	//Not ensured yet.
}
void WaveEffector::Shrink(WaveBuffer& _WaveBuffer, CVSCommon::Segment& _Segment, SpeechSynthesizerSendBack& SendBack)
{
	int ShrinkLen = CInt(_Segment.Effects.Shrink * SampleRate);
	int RemainingLen;
	int ConsonantLen = SendBack.VOT;
	int i;
	double* buffer1;
	double* buffer2;
	
	if(ShrinkLen > ConsonantLen / 2)
		ShrinkLen = CInt(ConsonantLen / 2);
	if(ConsonantLen <= 0)
		goto EndFunc;//Vowels needn't shrinking.

	RemainingLen = ConsonantLen - ShrinkLen;
	buffer1 = new double[RemainingLen];
	buffer2 = new double[RemainingLen];

	for(i = 0;i < RemainingLen;i ++)
		buffer1[i] = _WaveBuffer.Data[i] * (1.0f - (double)i / (RemainingLen - 1));
	for(i = ShrinkLen;i < ConsonantLen;i ++)
		buffer2[i - ShrinkLen] = _WaveBuffer.Data[i] * ((double)(i - ShrinkLen)) / (RemainingLen - 1);

	//Left shift the wavebuffer
	for(i = RemainingLen;i <= _WaveBuffer.Pointer;i ++)
		_WaveBuffer.Data[i] = _WaveBuffer.Data[i + ShrinkLen];

	_WaveBuffer.Pointer -= ShrinkLen;

	//Write back;

	for(i = 0;i < RemainingLen;i ++)
		_WaveBuffer.Data[i] = buffer1[i] + buffer2[i];
	
	delete []buffer1;
	delete []buffer2;
	EndFunc:;
}
