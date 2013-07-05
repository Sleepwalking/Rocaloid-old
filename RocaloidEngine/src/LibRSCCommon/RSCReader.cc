 /*
  * RSCReader.cc
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
  * along with this program. if not, see <http://www.gnu.org/licenses/>.
  */
 #include "defs.h"
#include "io/terminal.h"
#include "structure/string.h"
#include "misc/converter.h"
#include "structure/array.h"
#include "io/fileStream.h"

#include "LibCyberBase/Overall.h"
#include "LibCyberBase/RDLIO.h"
#include "LibCVSCommon/CVSCommon.h"
#include "RSCCommon.h"
#include "RSCReader.h"
//Module for reading RSC file

namespace RSCCommon
{
	using namespace converter;
	inline void RSCReader::Detect_WrongEnd ()
	{
		if (Reader.Read() != "End")
			Exception("List without an End.");
	}
			void RSCReader::Open(string FileName)
			{
				Reader.Open(FileName);
				if (Reader.Read() != "#RSC") 
					//Not Cybervoice Script
					Exception("The file is not a Rocaloid Script !");
				if (Reader.Read() != RSC_VERSION)
					Exception("Wrong RSC version.");
			}
			void RSCReader::Close()
			{
				Reader.Close();
			}
			void RSCReader::Read(RSC& _RSC)
			{
				_RSC.Version = RSC_VERSION;
				string StrBuff;
				int ResizeQ;
				while(StrBuff != "End")
				{
					if ( StrBuff ==  "Author")
						_RSC.Author = Reader.Read();
					else if ( StrBuff == "Information" )
						Information_Read(_RSC.Information);
					else if ( StrBuff == "SegmentListQ")
					{
						StrBuff = Reader.Read();
						_RSC.SegmentListQ = TestIfIsIntAndPositive(StrBuff) - 1;
						ResizeQ = CInt(_RSC.SegmentListQ / 1000 + 1) * 1000;
						_RSC.SegmentList.setUbound (ResizeQ);
						//_RSC.InitSegmentList(0, ResizeQ)
					}
					else if ( StrBuff == "SegmentList" )
					{
						for ( int i = 0 ; i <= _RSC.SegmentListQ ; i++)
							Segment_Read(_RSC.SegmentList[i]);
						Detect_WrongEnd ();
					}
					else if ( StrBuff == "FreqListQ")
					{
						StrBuff = Reader.Read();
						_RSC.FreqListQ = TestIfIsIntAndPositive(StrBuff) - 1;
						ResizeQ = CInt(_RSC.FreqListQ / 1000 + 1) * 1000;
						_RSC.FreqList.setUbound ( _RSC.FreqListQ);
					}
					else if ( StrBuff == "FreqList")
					{
						for ( int i = 0 ; i<= _RSC.FreqListQ ; i++)
							FreqSet_Read(_RSC.FreqList[i]);
						Detect_WrongEnd ();
					}
					else if ( StrBuff == "Effects")
						Effects_Read(_RSC.Effects);
					else if ( StrBuff == "TempoListQ")
					{
						StrBuff = Reader.Read();
						_RSC.TempoListQ = TestIfIsIntAndPositive(StrBuff) - 1;
						ResizeQ = CInt(_RSC.TempoListQ / 1000 + 1) * 1000;
						//_RSC.TempoList.setUbound (RSC.TempoListQ);
					}
					else if ( StrBuff == "TempoList")
					{
						for (int i=0 ; i<= _RSC.TempoListQ ; i++)
							TempoSet_Read(_RSC.TempoList[i]);
						Detect_WrongEnd ();
					}
					else if ( StrBuff == "BeatListQ")
					{
						StrBuff = Reader.Read();;
						_RSC.BeatListQ = TestIfIsIntAndPositive(StrBuff) - 1;
						ResizeQ = CInt(_RSC.BeatListQ / 1000 + 1) * 1000;
						_RSC.BeatList.setUbound (_RSC.BeatListQ);
					}
					else if ( StrBuff == "BeatList")
					{
						for ( int i = 0 ; i <=_RSC.BeatListQ ; i++)
							BeatSet_Read(_RSC.BeatList[i]);
						Detect_WrongEnd ();
					}
					else if ( StrBuff == "InteractionSave")
						Interaction_Read(_RSC.InteractionSave);
					else
					{
						// Exception("Invalid identifier as " & StrBuff & ".")
					}
				}
			}
			void RSCReader::Information_Read(string& _Info)
			{
				
			}
			void RSCReader::Segment_Read(Segment& _Segment)
			{
			}
			void RSCReader::FreqSet_Read(FreqSet& _FreqSet)
			{
			}
			void RSCReader::Effects_Read(EffectsStruct& _Effects)
			{
			}
			void RSCReader::TempoSet_Read(TempoSet& _TempoSet)
			{
			}
			void RSCReader::BeatSet_Read(BeatSet& _BeatSet)
			{
			}
			void RSCReader::Interaction_Read(UserInteraction& _Interaction)
			{
			}
			void RSCReader::SegmentEffects_Read(SegmentEffects& _SEffects)
			{
			}
			void RSCReader::ADSR_Read(CVSCommon::ADSREnvelope& _ADSREnvelope)
			{
			}
//Template
//	Public Sub RSC_Read(ByRef _RSC As RSC)
//		Dim StrBuff As String
//		Do
//			StrBuff = Reader.Read()
//			Select Case StrBuff
//				Case ""
//				Case Else
//					// Exception("Invalid identifier as " & StrBuff & ".")
//			End Select
//		Loop While StrBuff != "End"
//	End Sub
};