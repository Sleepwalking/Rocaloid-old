#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
	Data = new double[FrameBufferInitialSize];
	Size = FrameBufferInitialSize;
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
	Ubound = Ubound >= Size ? Size - 1 : Ubound;
	for(i = 0;i <= Ubound;i ++)
		NewData[i] = Data[i];
	delete []Data;
	Data = NewData;
	Size = _Size;
}
FrameBuffer& FrameBuffer::operator =(FrameBuffer& Source)
{
	int i;
	Ubound = -1;
	if(Size != Source.Size)
		Resize(Source.Size);
	Ubound = Source.Ubound;
	for(i = 0;i <= Ubound;i ++)
		Data[i] = Source.Data[i];
}