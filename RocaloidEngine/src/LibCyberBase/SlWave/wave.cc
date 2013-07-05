/*
 * wave.cc
 * Copyright (C) 2013 Sleepwalking
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name ``Sleepwalking'' nor the name of any other
 *    contributor may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 * 
 * SlWave IS PROVIDED BY Sleepwalking ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL Sleepwalking OR ANY OTHER CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "wave.h"
#include "SPKit/defs.h"
#include "SPKit/structure/array.h"
#include "SPKit/structure/string.h"
#include "SPKit/misc/memopr.h"
#include "SPKit/misc/converter.h"
#include "SPKit/io/memoryStream.h"
using namespace converter;
bool PCMWaveFile::open(string fileName)
{
	bool openState = fStream.open(fileName, READONLY);
	if(! openState)
		return false;
	
	char* RIFFChars = new char[5];
	char* WAVEChars = new char[5];
	char* FACTChars = new char[5];
	string RIFFStr, WAVEStr, FACTStr;
	
	fStream.readBuffer(RIFFChars, 4); //RIFF
	fStream.readInt(); //Size
	fStream.readBuffer(WAVEChars, 4); //WAVE

	RIFFChars[4] = 0;
	WAVEChars[4] = 0;
	FACTChars[4] = 0;
	RIFFStr = RIFFChars;
	WAVEStr = WAVEChars;
	
	if(RIFFStr != "RIFF")
		return false;
	if(WAVEStr != "WAVE")
		return false;

	fStream.readInt(); //fmt
	int fmtSize = fStream.readInt();
	fStream.readShort(); //FormatTag
	header.channel = fStream.readShort();
	header.samplePerSecond = fStream.readInt();
	header.bytePerSecond = fStream.readInt();
	header.blockAlign = fStream.readShort();
	header.bitPerSample = fStream.readShort();

	if(fmtSize == 16)
	{
		//No extra info
	}else
		fStream.readShort(); //Extra info
	fStream.readBuffer(FACTChars, 4);
	FACTStr = FACTChars;

	if(FACTStr == "fact")
	{
		int factSize = fStream.readInt();
		fStream.setPosition(fStream.getPosition() + factSize + 4);
	}

	header.dataSize = fStream.readInt();
	header.dataPosition = fStream.getPosition();
	header.bytePerSample = header.bitPerSample >> 3;
	header.dataNum = header.dataSize / header.bytePerSample / header.channel;

	delete [] FACTChars;
	delete [] RIFFChars;
	delete [] WAVEChars;
	return true;
}
bool PCMWaveFile::save(string fileName)
{
	bool saveState = fStream.open(fileName, CREATE);
	if(! saveState)
		return false;

	fStream.writeBuffer("RIFF", 4);
	fStream.write(CInt(0)); //Size = 0 by default
	fStream.writeBuffer("WAVE", 4);

	fStream.writeBuffer("fmt ", 4);
	fStream.write(CInt(16)); //No extra
	fStream.write(CShort(1)); //FormatTag = 0x0001
	fStream.write(header.channel);
	fStream.write(header.samplePerSecond);
	fStream.write(header.bytePerSecond);
	fStream.write(header.blockAlign);
	fStream.write(header.bitPerSample);

	fStream.writeBuffer("data", 4);
	fStream.write(CInt(0)); //dataSize = 0 by default

	writeDataPosition = fStream.getPosition();
	writeCounter = 0;
	return true;
}
void PCMWaveFile::finishWrite()
{
	int fileSize = fStream.getPosition();
	
	fStream.setPosition(4); //Size
	fStream.write(CInt(fileSize - 8));
	int dataSize = writeCounter * header.channel * (header.bitPerSample >> 3);
	
	fStream.setPosition(CInt(writeDataPosition - 4)); //dataSize
	fStream.write(dataSize);
	
	fStream.close();
}
void PCMWaveFile::close()
{
	fStream.close();
}

void PCMWaveFile::fetchAll(array<double>& buffer)
{
	int i;
	byte* mbuffer = (byte*)mem_malloc(header.dataSize);
	fetchAll(mbuffer);
	memoryStream mReader(mbuffer);
	mReader.setPosition(0);

	buffer.setUbound(header.dataNum);
	if(header.bitPerSample == 8)
		for(i = 0;i < header.dataNum;i ++)
			buffer[i] = CDbl(mReader.readByte() - 127) / 127;
	if(header.bitPerSample == 16)
		for(i = 0;i < header.dataNum;i ++)
			buffer[i] = CDbl(mReader.readShort()) / 32767;
	
	mem_free(mbuffer);
}
void PCMWaveFile::fetchAll(array<double>& lbuffer, array<double>& rbuffer)
{
	int i;
	byte* mbuffer = (byte*)mem_malloc(header.dataSize);
	fetchAll(mbuffer);
	memoryStream mReader(mbuffer);
	mReader.setPosition(0);
	
	lbuffer.setUbound(header.dataNum);
	rbuffer.setUbound(header.dataNum);
	if(header.bitPerSample == 8)
		for(i = 0;i < header.dataNum;i ++)
		{
			lbuffer[i] = CDbl(mReader.readByte() - 127) / 127;
			rbuffer[i] = CDbl(mReader.readByte() - 127) / 127;
		}
	if(header.bitPerSample == 16)
		for(i = 0;i < header.dataNum;i ++)
		{
			lbuffer[i] = CDbl(mReader.readShort()) / 32767;
			rbuffer[i] = CDbl(mReader.readShort()) / 32767;
		}
	
	mem_free(mbuffer);
}
void PCMWaveFile::fetchAll(byte* buffer)
{
	fStream.setPosition(header.dataPosition);
	fStream.readBuffer(buffer, header.dataSize);
}

double PCMWaveFile::fetchAt(int sampleNum)
{
	fStream.setPosition(header.dataPosition + sampleNum * header.bytePerSample);
	if(header.bitPerSample == 8)
		return CDbl(fStream.readByte() - 127) / 127;
	if(header.bitPerSample == 16)
		return CDbl(fStream.readShort()) / 32767;
	return 0;
}
double PCMWaveFile::fetchLAt(int sampleNum)
{
	fStream.setPosition(header.dataPosition + sampleNum * (header.bytePerSample << 1));
	if(header.bitPerSample == 8)
		return CDbl(fStream.readByte() - 127) / 127;
	if(header.bitPerSample == 16)
		return CDbl(fStream.readShort()) / 32767;
	return 0;
}
double PCMWaveFile::fetchRAt(int sampleNum)
{
	fStream.setPosition(header.dataPosition + sampleNum * (header.bytePerSample << 1) + header.bytePerSample);
	if(header.bitPerSample == 8)
		return CDbl(fStream.readByte() - 127) / 127;
	if(header.bitPerSample == 16)
		return CDbl(fStream.readShort()) / 32767;
	return 0;
}

void PCMWaveFile::writeAll(array<double>& buffer, int length)
{
	int i;
	if(header.bitPerSample == 8)
	{
		for(i = 0;i < length;i ++)
			fStream.write(CByte(buffer[i] * 127 + 127));
	}
	if(header.bitPerSample == 16)
	{
		for(i = 0;i < length;i ++)
			fStream.write(CShort(buffer[i] * 32767));
	}
	writeCounter += length;
}
void PCMWaveFile::writeAll(array<double>& lbuffer, array<double>& rbuffer, int length)
{
	int i;
	if(header.bitPerSample == 8)
		for(i = 0;i < length;i ++)
		{
			fStream.write(CByte(lbuffer[i] * 127 + 127));
			fStream.write(CByte(rbuffer[i] * 127 + 127));
		}
	if(header.bitPerSample == 16)
		for(i = 0;i < length;i ++)
		{
			fStream.write(CShort(lbuffer[i] * 32767));
			fStream.write(CShort(rbuffer[i] * 32767));
		}
	writeCounter += length;
}
void PCMWaveFile::write(double data)
{
	if(header.bitPerSample == 8)
		fStream.write(CByte(data * 127 + 127));
	if(header.bitPerSample == 16)
		fStream.write(CShort(data * 32767));
	writeCounter ++;
}
void PCMWaveFile::write(double ldata, double rdata)
{
	if(header.bitPerSample == 8)
	{
		fStream.write(CByte(ldata * 127 + 127));
		fStream.write(CByte(rdata * 127 + 127));
	}
	if(header.bitPerSample == 16)
	{
		fStream.write(CShort(ldata * 32767));
		fStream.write(CShort(rdata * 32767));
	}
	writeCounter ++;
}