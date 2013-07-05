#include "WaveBuffer.h"
#include "SPKit/structure/string.h"
#include "SlWave/wave.h"

WaveBuffer::WaveBuffer() : FrameBuffer()
{
	Pointer = 0;
}
WaveBuffer::WaveBuffer(int _Size) : FrameBuffer(_Size)
{
	Pointer = 0;
}

void WaveBuffer::Write(FrameBuffer& Frame)
{
	int i;
	for(i = 0;i <= Frame.Ubound;i ++)
		Data[i + Pointer] = Frame.Data[i];
	Pointer += Frame.Ubound + 1;
}

void WaveBuffer::Output(string FileName)
{
	int i;
	PCMWaveFile Writer;
	Writer.header.channel = 1;
	Writer.header.samplePerSecond = 96000;
	Writer.header.bytePerSecond = 192000;
	Writer.header.blockAlign = 2;
	Writer.header.bitPerSample = 16;
	
	Writer.save(FileName);
	for(i = 0;i < Pointer;i ++)
		Writer.write(Data[i]);
	Writer.finishWrite();
}
void WaveBuffer::Load(string FileName)
{
	int i;
	PCMWaveFile Reader;
	Reader.open(FileName);
	Resize(Reader.header.dataNum);
	for(i = 0;i < Size;i ++)
		Data[i] = Reader.fetchAt(i);
	Reader.close();
}