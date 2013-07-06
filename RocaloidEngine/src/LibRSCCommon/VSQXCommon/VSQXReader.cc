 /*
  * VSQXReader.cc
  *
  * Copyright (C) 2013 - Rocaloid Development Group(RDG)
  *
  * Created by rgwan
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation; either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program. If not, see <http://www.gnu.org/licenses/>.
  */
 #include "defs.h"
#include "io/terminal.h"
#include "structure/string.h"
#include "misc/converter.h"
#include "structure/array.h"
#include "io/fileStream.h"
#include "io/stringStream.h"
#include "misc/memopr.h"

#include "LibCyberBase/Overall.h"
#include "LibCyberBase/RDLIO.h"
#include "LibCVSCommon/CVSCommon.h"
#include "RSCCommon.h"
#include "VSQ3Reader.h"
#include "VSQXReader.h"
namespace VSQXCommon
{
	using namespace converter;
	using namespace Overall;
	using namespace RDLIO;
		void VSQXReader::Open(string FileName)
		{
			Reader.Open(FileName);
		}

		void VSQXReader::Close()
		{
			Reader.Close();
		}

		
		void VSQXReader::Read(RSC& _RSC)
		{
			Reader.ReadUntil("<masterTrack>");
			_RSC.Information = Reader.ReadCDATA (Reader.ReadNextValue("comment"));
			Reader.ReadUntil("<resolution>");
			Resolution = TestIfIsInt(Reader.ReadNextValue("resolution")) * 2;
			ReadTempos(_RSC, "</masterTrack>");
			ReadMusicalPart(_RSC);
		}

		void VSQXReader::ReadTempos(RSC& _RSC, string EndTag)
		{
			_RSC.TempoListQ = 0;
			int EndTagPos = Reader.FindNextPos(EndTag);
			//wLine(CStr(EndTagPos));
			int EndPos= Reader.FindLastPos("</tempo>", EndTagPos);
			TempoSet TempoSet_;
			//wLine(CStr(EndPos));
			//wLine(CStr(Reader.Pointer));
			while (Reader.Pointer < EndPos)
			{
				TempoSet_.Position = TestIfIsInt (Reader.ReadNextValue("posTick")) / Resolution;
				TempoSet_.Tempo = TestIfIsInt (Reader.ReadNextValue("bpm")) / 100;
				//wLine(CStr(TempoSet_.Tempo));
				_RSC.TempoList.push(TempoSet_);
				_RSC.TempoListQ++;
				Reader.ReadUntil("</tempo>");
			}
			TempoSet_.Position = 99999;
			TempoSet_.Tempo = 120;
			_RSC.TempoList.push ( TempoSet_);
			_RSC.TempoListQ++;
			
		}


		void VSQXReader::ReadMusicalPart(RSC& _RSC)
		{
			_RSC.SegmentListQ = 0;
			Reader.ReadUntil("<posTick>");
			MusicalPartStartPos = TestIfIsInt (Reader.ReadNextValue("posTick")) / Resolution;
			Reader.ReadUntil("<note>");
			int EndPos = Reader.FindLastPos("</note>", Reader.FindNextPos("</musicalPart>"));
			Segment Segment_;
			int Pitch;
			CVSCommon::ADSREnvelope EachADSR;
			EachADSR.Amplitude = 1;
			EachADSR.Attack = 0.05;
			EachADSR.Decline = 0.1;
			EachADSR.Release = 0.1;
			while (Reader.Pointer < EndPos)
			{
				Segment_.Position = TestIfIsInt(Reader.ReadNextValue("posTick")) / Resolution 
					+ MusicalPartStartPos;
				Segment_.Duration = TestIfIsInt(Reader.ReadNextValue("durTick")) / Resolution;
				Pitch = TestIfIsInt(Reader.ReadNextValue("noteNum")) - 36;
				Segment_.StartFreq = FreqList[Pitch];
				Segment_.EndFreq = FreqList[Pitch];

				Segment_.Lyric = Reader.ReadCDATA(Reader.ReadNextValue("lyric"));
				
				Segment_.StartAmplitude = 1;
				Segment_.EndAmplitude = 1;
				Segment_.Effects.PElopeEnabled = true;
				Segment_.Effects.PresetedEnvelope = CVSCommon::ADSR;
				Segment_.Effects.ADSR = EachADSR;
				Segment_.Effects.Breath.Magnitude = 0;
					
				_RSC.SegmentList.push(Segment_);
				_RSC.SegmentListQ++;
				Reader.ReadUntil("</note>");
				
			}
			//wLine(Segment_.Lyric);
			//wLine(CStr(Pitch));
			_RSC.Effects.EnvelopeList.setUbound (0);
			_RSC.Effects.EnvelopeListQ = 0;
			_RSC.Effects.EnvelopeList[0].Amplitude = 1;
			_RSC.Effects.EnvelopeList[0].Position = 0;
			
			_RSC.FreqList.setUbound (0);
			_RSC.FreqListQ = 0;
			_RSC.FreqList[0].Freq = 270;
			_RSC.FreqList[0].Position = 0;
			_RSC.BeatList.setUbound (0);
			_RSC.BeatListQ = 0;
			_RSC.BeatList[0].BarPosition = 0;
			_RSC.BeatList[0].Beat_Denominator = 4;
			_RSC.BeatList[0].Beat_Factor = 4;
			_RSC.Version = "2.0";
			_RSC.Author = "Unknown";
			_RSC.InteractionSave.LastUserScale = 1;
		}

};