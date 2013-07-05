#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
	Data = new double[1];
	Size = 1;
	Ubound = 0;
}
FrameBuffer::FrameBuffer(int _Size)
{
	Data = new double[_Size];
	Size = _Size;
	Ubound = 0;
}
FrameBuffer::~FrameBuffer()
{
	delete []Data;
}
void FrameBuffer::Resize(int _Size)
{
	int i;
	int NewSize = _Size < Size ? _Size : Size;
	double* NewData = new double[_Size];
	for(i = 0;i < NewSize;i ++)
		NewData[i] = Data[i];
	delete []Data;
	Data = NewData;
	Size = _Size;
}