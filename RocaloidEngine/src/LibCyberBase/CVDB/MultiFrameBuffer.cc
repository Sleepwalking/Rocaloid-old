#include "MultiFrameBuffer.h"
#include "FrameBuffer.h"

MultiFrameBuffer::MultiFrameBuffer()
{
	Data = new FrameBuffer*[1];
	*Data = new FrameBuffer();
	Size = 1;
	Ubound = 0;
}
MultiFrameBuffer::MultiFrameBuffer(int _Size)
{
	int i;
	Data = new FrameBuffer*[_Size];
	Size = _Size;
	Ubound = 0;
	for(i = 0;i < Size;i ++)
		Data[i] = new FrameBuffer();
}
MultiFrameBuffer::MultiFrameBuffer(int _Size, int _InnerSize)
{
	int i;
	Data = new FrameBuffer*[_Size];
	Size = _Size;
	Ubound = 0;
	for(i = 0;i < Size;i ++)
		Data[i] = new FrameBuffer(_InnerSize);
}
MultiFrameBuffer::~MultiFrameBuffer()
{
	int i;
	for(i = 0;i < Size;i ++)
		delete Data[i];
	delete []Data;
}
void MultiFrameBuffer::Resize(int _Size)
{
	int i;
	int NewSize = _Size < Size ? _Size : Size;
	FrameBuffer** NewData = new FrameBuffer*[_Size];
	for(i = 0;i < NewSize;i ++)
		NewData[i] = Data[i];
	for(i = _Size;i < Size;i ++)
		delete Data[i];
	delete []Data;
	Data = NewData;
	Size = _Size;
}