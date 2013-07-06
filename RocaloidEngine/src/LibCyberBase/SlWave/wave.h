/*
 * wave.h
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
#ifndef WAVE_H
#define WAVE_H
#include "../SPKit/defs.h"
#include "../SPKit/io/fileStream.h"
#include "../SPKit/io/memoryStream.h"

template <class T> class array;
class string;
class binaryStream;
struct PCMWaveHeader
{
	//Required while writing
	short int channel;
	int samplePerSecond;
	int bytePerSecond;
	short int blockAlign;
	short int bitPerSample;

	//Temporary data while reading
	int dataSize;
	int dataPosition;
	int dataNum;
	int bytePerSample;
};
class PCMWaveFile
{
	#define mStreamSize 65536
	public:
		PCMWaveFile();
		~PCMWaveFile();
		
		PCMWaveHeader header;
		bool open(string fileName);
		bool save(string fileName);
		void finishWrite();
		void close();
		
		void fetchAll(array<double>& buffer);
		void fetchAll(array<double>& lbuffer, array<double>& rbuffer);
		void fetchAll(byte* buffer);
		double fetchAt(int sampleNum);
		double fetchLAt(int smapleNum);
		double fetchRAt(int smapleNum);

		void writeAll(array<double>& buffer, int length);
		void writeAll(array<double>& lbuffer, array<double>& rbuffer, int length);
		void writeAll(byte* buffer, int length);
		void write(double data);
		void write(double ldata, double rdata);
	private:
		int writeCounter;
		int writeDataPosition;
		binaryStream fStream;
		memoryStream* mStream;
		void* mBuffer;
};
#endif