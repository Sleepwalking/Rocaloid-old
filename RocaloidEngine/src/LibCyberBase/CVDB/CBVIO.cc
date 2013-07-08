#include "CBVIO.h"
#include "SPKit/defs.h"
#include "SPKit/structure/string.h"
#include "SPKit/misc/converter.h"
#include "SPKit/io/fileStream.h"
#include "SPKit/io/terminal.h"

#include "CVDB.h"
#include "MultiFrameBuffer.h"
#include "FrameBuffer.h"
using namespace converter;

binaryStream CBVFile::fStream;
string CBVFile::DataDir;

bool CBVFile::Open(string FileName, CVDBContainer& Dest)
{
	bool OpenState = fStream.open(DataDir + FileName, READONLY);
	if(! OpenState)
		return false;

	char* CVDBChars = new char[5];
	string CVDBStr;

	fStream.readBuffer(CVDBChars, 4);
	CVDBChars[4] = 0;
	CVDBStr = CVDBChars;

	if(CVDBStr != "CVDB")
	{
		fStream.close();
		return false;
	}
	
	Dest.Info.Version = fStream.readShort();
	Dest.SetName(left(FileName, FileName.getLength() - 4));

	if(Dest.Info.Version == 1)
		OpenCVDB05(Dest);
	else if(Dest.Info.Version == 2)
		OpenCVDB06(Dest);
	else
	{
		fStream.close();
		return false;
	}

	fStream.close();
	delete []CVDBChars;
	
	return true;
}

void CBVFile::OpenCVDB05(CVDBContainer& Dest)
{
	Dest.Info.Consonant = (fStream.readByte() == 255);
	Dest.Info.StartPosition = fStream.readInt();
	Dest.Info.PeriodStartPosition = Dest.Info.StartPosition; //Fill up
	Dest.Info.AveragePeriod = fStream.readInt();
	fStream.setPosition(256); //Skip Information

	int DataSize = fStream.getLength() - fStream.getPosition();
	int DataNum = DataSize / 2 - 3000; //Safe limit for stability
	int PeriodCount, SampleCount, DataCount;
	short int TmpData;

	PeriodCount = 0; SampleCount = 0; DataCount = 0;
	while(DataCount < DataNum)
	{
		TmpData = fStream.readShort();
		if(TmpData == 32766 || TmpData == 32767)
		{
			Dest.Buffer -> Data[PeriodCount] -> Ubound = SampleCount;
			DataCount += SampleCount + 1;
			PeriodCount ++;
			SampleCount = 0;
			if(TmpData == 32767)
				break;
			else
				continue;
		}
		//TmpData != 32766 or 32767, Normal Data
		Dest.Buffer -> Data[PeriodCount] -> Data[SampleCount] = CDbl(TmpData) / 32767;
		SampleCount ++;
	}

	Dest.Buffer -> Ubound = PeriodCount - 1;
}

void CBVFile::OpenCVDB06(CVDBContainer& Dest)
{	
	Dest.Info.Consonant = (fStream.readByte() == 255);
	Dest.Info.StartPosition = fStream.readInt();
	Dest.Info.PeriodStartPosition = fStream.readInt();
	fStream.readByte();
	Dest.Info.ChunkNumber = fStream.readShort();
	Dest.Buffer -> Ubound = Dest.Info.ChunkNumber;

	int i, j;
	int PeriodSize;
	int TotalPeriod = 0;
	for(i = 0;i <= Dest.Info.ChunkNumber;i ++)
	{
		Dest.Buffer -> Data[i] -> Ubound = fStream.readShort() - 1;
		TotalPeriod += Dest.Buffer -> Data[i] -> Ubound + 1;
	}

	Dest.Info.AveragePeriod = TotalPeriod / (Dest.Info.ChunkNumber + 1);

	for(i = 0;i <= Dest.Info.ChunkNumber;i ++)
	{
		PeriodSize = Dest.Buffer -> Data[i] -> Ubound;
		for(j = 0;j <= PeriodSize;j ++)
			Dest.Buffer -> Data[i] -> Data[j] = CDbl(fStream.readShort()) / 32767;
	}
}