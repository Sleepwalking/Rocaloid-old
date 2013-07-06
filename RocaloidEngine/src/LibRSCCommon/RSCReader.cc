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
#include "SPKit/defs.h"
#include "SPKit/io/terminal.h"
#include "SPKit/structure/string.h"
#include "SPKit/misc/converter.h"
#include "SPKit/structure/array.h"
#include "SPKit/io/fileStream.h"

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
			StrBuff = Reader.Read();
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
				_RSC.TempoList.setUbound (_RSC.TempoListQ);
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
		string StrBuff;
		int counter=0;
		while (StrBuff != "\\0")
		{
			StrBuff = Reader.Read();
			if (StrBuff != "\\0")
				_Info += StrBuff +" ";
			counter ++;//防止StrBuff == 0 引起段错误
		}
		if (counter == 1 )
			_Info="";
		else
		_Info = trim(_Info);
	}
	void RSCReader::Segment_Read(Segment& _Segment)
	{
		string StrBuff;
		Reader.Read();
		do
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "Position" ) 
			{
				StrBuff = Reader.Read();
				_Segment.Position = TestIfIsDouble(StrBuff);
			}
			else if ( StrBuff == "Lyric")
			{
				StrBuff = Reader.Read();
				_Segment.Lyric = StrBuff;
			}
			else if ( StrBuff == "Duration")
			{
				StrBuff = Reader.Read();
				_Segment.Duration = TestIfIsDouble(StrBuff);
			}
			else if ( StrBuff == "Effects")
			{
				SegmentEffects_Read(_Segment.Effects);
			}
			else if ( StrBuff == "StartFreq")
			{
				StrBuff = Reader.Read();
				_Segment.StartFreq = TestIfIsDouble(StrBuff);
			}
			else if ( StrBuff ==  "EndFreq")
			{
				StrBuff = Reader.Read();
				_Segment.EndFreq = TestIfIsDouble(StrBuff);
			}
			else if ( StrBuff == "End" ) break;
			else
			{
				Exception(CStr("Invalid identifier as ") + StrBuff + ".");
			}
		} while( StrBuff != "End");
	}
	void RSCReader::FreqSet_Read(FreqSet& _FreqSet)
	{
		string StrBuff;
		Reader.Read();
		do
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "Position")
			{
				StrBuff = Reader.Read();
				_FreqSet.Position = TestIfIsDouble(StrBuff);
			}
			else if ( StrBuff == "Freq")
			{
				StrBuff = Reader.Read();
				_FreqSet.Freq = TestIfIsDouble(StrBuff);
			}
			else if ( StrBuff == "End") break;
			else
			{
				Exception(CStr("Invalid identifier as ") + StrBuff + ".");
			}
		} while (StrBuff != "End");
	}
	void RSCReader::Effects_Read(EffectsStruct& _Effects)
	{
		int ResizeQ;
		string StrBuff;
		do
		{
			StrBuff = Reader.Read();
			if ( StrBuff ==  "EnvelopeListQ")
			{
				StrBuff = Reader.Read();
				_Effects.EnvelopeListQ = TestIfIsIntAndPositive(StrBuff) - 1;
				ResizeQ = CInt(_Effects.EnvelopeListQ / 1000 + 1) * 1000;
				_Effects.EnvelopeList.setUbound ( _Effects.EnvelopeListQ );
			}
			else if ( StrBuff ==   "EnvelopeList")
			{
				for ( int i = 0 ; i <= _Effects.EnvelopeListQ ;i++)
				{
					EnvelopeSet_Read(_Effects.EnvelopeList[i]);
				}
				Detect_WrongEnd ();
			}
			else if ( StrBuff == "End") break;
			else
			{
				Exception(CStr("Invalid identifier as ") + StrBuff + ".");
			}
		} while (StrBuff !="End");
	}
	void RSCReader::TempoSet_Read(TempoSet& _TempoSet)
	{
		string StrBuff; 
		while(StrBuff !="End")
		{
			StrBuff = Reader.Read();
			if(StrBuff == "Position")
			{
				StrBuff = Reader.Read();
				_TempoSet.Position = TestIfIsDouble(StrBuff);
			}
			else if ( StrBuff == "Tempo")
			{
				StrBuff = Reader.Read();
				_TempoSet.Tempo = TestIfIsDouble(StrBuff);
			}
			else if ( StrBuff == "End") break;
			else
			{
				// Exception("Invalid identifier as " & StrBuff & ".")
			}
		}
	}
	void RSCReader::BeatSet_Read(BeatSet& _BeatSet)
	{
		string StrBuff;
		while ( StrBuff != "End")
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "BarPosition")
			{
				StrBuff = Reader.Read();
				_BeatSet.BarPosition = TestIfIsInt(StrBuff);
			}
			else if ( StrBuff == "Factor")
			{
				StrBuff = Reader.Read();
				_BeatSet.Beat_Factor = TestIfIsIntAndPositive(StrBuff);
			}
			else if ( StrBuff == "Denominator")
			{
				StrBuff = Reader.Read();
				_BeatSet.Beat_Denominator = TestIfIsIntAndPositive(StrBuff);
			}
			else if ( StrBuff == "End") break;
			else
			{
				//Exception("Invalid identifier as " & StrBuff & ".")
			}
		}
	}
	void RSCReader::Interaction_Read(UserInteraction& _Interaction)
	{
		string StrBuff;
		while ( StrBuff !="End")
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "LastUserPosition")
			{
					StrBuff = Reader.Read();
					_Interaction.LastUserPosition = TestIfIsDouble(StrBuff);
			}
			else if ( StrBuff == "LastUserScale")
			{
					StrBuff = Reader.Read();
					_Interaction.LastUserScale = TestIfIsDoubleAndPositive(StrBuff);
			}
			else if ( StrBuff ==  "ViewType")
			{
					StrBuff = Reader.Read();
					_Interaction.ViewType = TestIfIsViewType(StrBuff);
			}
			else if ( StrBuff == "End") break;
			else
			{
					//Throw New Exception("Invalid identifier as " & StrBuff & ".");
			}
		}
	}
	void RSCReader::SegmentEffects_Read(SegmentEffects& _SEffects)
	{
		string StrBuff;
		while( StrBuff != "End")
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "PElopeEnabled")
			{
					StrBuff = Reader.Read();
					_SEffects.PElopeEnabled = TestIfIsBoolean(StrBuff);
			}
			else if ( StrBuff == "PresetedEnvelope")
			{
					StrBuff = Reader.Read();
					_SEffects.PresetedEnvelope = (CVSCommon::Envelopes)TestIfIsPresetedEnvelope(StrBuff);
			}
			else if ( StrBuff ==  "ADSR")
			{
					ADSR_Read(_SEffects.ADSR);
			}
			else if ( StrBuff == "End") break;
			else
			{
				// Exception("Invalid identifier as " & StrBuff & ".")
			}
		}
	}
	void RSCReader::ADSR_Read(CVSCommon::ADSREnvelope& _ADSREnvelope)
	{
		string StrBuff;
		do
		{
			StrBuff = Reader.Read();
			if(StrBuff == "Amplitude")
			{
				_ADSREnvelope.Amplitude = TestIfIsDoubleNotNegative(Reader.Read());
			}else if(StrBuff == "Attack")
			{
				_ADSREnvelope.Attack = TestIfIsDoubleNotNegative(Reader.Read());
			}else if(StrBuff == "Decline")
			{
				_ADSREnvelope.Decline = TestIfIsDoubleNotNegative(Reader.Read());
			}else if(StrBuff == "Release")
			{
				_ADSREnvelope.Release = TestIfIsDoubleNotNegative(Reader.Read());
			}else
			{
				//Exception
			}
		}while(StrBuff != "End");
	}
	void RSCReader::EnvelopeSet_Read(EnvelopeSet& _EnvelopeSet)
	{
		string StrBuff;
		while(StrBuff != "End")
		{
			StrBuff = Reader.Read();
			if ( StrBuff == "Position")
			{
				StrBuff = Reader.Read();
				_EnvelopeSet.Position = TestIfIsDouble(StrBuff);
			}
			else if ( StrBuff == "Magnitude")
			{
				StrBuff = Reader.Read();
				_EnvelopeSet.Amplitude = TestIfIsDouble(StrBuff);
			}
			else if ( StrBuff == "End") break;
			else
			{
					//Throw New Exception("Invalid identifier as " & StrBuff & ".")
			}
		}
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