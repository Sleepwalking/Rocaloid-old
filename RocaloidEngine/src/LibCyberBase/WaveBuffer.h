#ifndef WAVEBUFFER_H
#define WAVEBUFFER_H
#include "FrameBuffer.h"
class string;
class WaveBuffer : public FrameBuffer
{
	public:
		WaveBuffer();
		WaveBuffer(int _Size);

		inline void Write(double _Data);
		void Write(FrameBuffer& Frame);

		void Output(string FileName);
		void Load(string FileName);
		int Pointer;
	private:
};
inline void WaveBuffer::Write(double _Data)
{
	Data[Pointer ++] = _Data;
}
#endif