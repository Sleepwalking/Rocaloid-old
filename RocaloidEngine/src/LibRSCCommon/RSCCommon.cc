/*
 * RSCCommon.cc
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
#include "LibCyberBase/SPKit/defs.h"
#include "LibCyberBase/SPKit/io/terminal.h"
#include "LibCyberBase/SPKit/structure/string.h"
#include "LibCyberBase/SPKit/misc/converter.h"
#include "LibCyberBase/SPKit/structure/array.h"
#include "LibCyberBase/SPKit/io/fileStream.h"

#include "LibCyberBase/Overall.h"
#include "LibCVSCommon/CVSCommon.h"
#include "RSCCommon.h"
namespace RSCCommon
{
	using namespace Overall;
	
	Segment& Segment::operator =(Segment& Source)
	{
			Position = Source.Position;
			Lyric = Source.Lyric;
			Duration = Source.Duration;
			StartTime = Source.StartTime;
			DurTime = Source.DurTime;
			Effects = Source.Effects;
			StartFreq = Source.StartFreq;
			EndFreq = Source.EndFreq;
			StartAmplitude = Source.StartAmplitude;
			EndAmplitude = Source.EndAmplitude;
			CutTime = Source.CutTime;
		return *this;
	}
	
	bool Segment::IsConnectedTo ( Segment& _Segment)
	{
		if ( abs ( Position + Duration - _Segment.Position) < 0.01 ) 
			return true;
		else
			return false;
	}
	ViewTypes TestIfIsViewType(string String)
	{
		if (String == "NotesEditor")
			return NotesEditor;
		else if (String == "FreqEditor")
			return FreqEditor;
		else if (String == "EnvelopEditor")
			return EnvelopeEditor;
		else if (String == "BreathEditor")
			return BreathEditor;
		else
				Exception(String + " is not a valid View Type!");
		return Other;
	}
	//class RSC
	RSC& RSC::operator =(RSC& Source)
	{
		int i;
			Version = Source.Version;
			Author = Source.Author;
			Information = Source.Information;
			SegmentListQ = Source.SegmentListQ;
			SegmentList.setUbound ( Source.SegmentListQ );
			//Target.InitSegmentList(0, SegmentListQ);
			FreqListQ = Source.FreqListQ;
			FreqList.setUbound (FreqListQ);
			Effects = Source.Effects;
			TempoListQ = Source.TempoListQ;
			TempoList.setUbound (TempoListQ);
			BeatListQ = Source.BeatListQ;
			BeatList.setUbound (BeatListQ);
			InteractionSave = Source.InteractionSave;
		for (i = 0 ; i<=SegmentListQ ; i++)
			SegmentList[i]=Source.SegmentList[i];
		for (i = 0 ; i<=FreqListQ ; i++)
			FreqList[i] = Source.FreqList[i];
		for (i = 0 ; i<=TempoListQ ; i++)
			TempoList[i] = Source.TempoList[i];
		for (i = 0 ; i<=BeatListQ ; i++)
			BeatList[i] = Source.BeatList[i];
		return *this;
	}
	
	void RSC::TimeBake()
	{
		double i = -1;
		PositionChunk NextChunk;
		PositionChunk LastChunk;
		double LastTempo_Time = 0;
		TempoSet LastTempo;
		int LastSegmentIndex = 0;
		double EndTime = 0;
		LastTempo.Position = 0;
		LastTempo.Tempo = 120;
		while ( i < (SegmentList[SegmentListQ].Position + SegmentList[SegmentListQ].Duration))
		{
			if (LastChunk.Type == SegmentEnd) 
				NextChunk = GetNextPositionChunk(i - 0.0001, LastChunk.Index + 1);
			else
			{
				if ( i < 0)
					NextChunk = GetNextPositionChunk(0, 0);
				else
					NextChunk = GetNextPositionChunk(i + 0.0001, 0);
			}
			i = NextChunk.Position;
			//wLine(converter::CStr(i));
			
			switch (NextChunk.Type)
			{
				case SegmentStart:
					LastSegmentIndex = NextChunk.Index;
					SegmentList[LastSegmentIndex].StartTime = PositionToTime(NextChunk.Position - 
					                                                         LastTempo.Position , LastTempo.Tempo) + LastTempo_Time;
					//wLine(converter::CStr(SegmentList[LastSegmentIndex].StartTime));
					break;
				case SegmentEnd:
					EndTime = PositionToTime(NextChunk.Position - LastTempo.Position, LastTempo.Tempo) 
						+ LastTempo_Time;
					SegmentList[LastSegmentIndex].DurTime = EndTime - SegmentList[LastSegmentIndex].StartTime;
					break;
				case TempoStart:
					LastTempo_Time += PositionToTime(NextChunk.Position - LastTempo.Position, LastTempo.Tempo);
					LastTempo = TempoList[NextChunk.Index];
					//wLine("Tempo");
					//wLine(converter::CStr(LastTempo.Tempo));
			}
			if (NextChunk.Type == SegmentEnd && NextChunk.Index == SegmentListQ)
				break;
			LastChunk = NextChunk;
		}
	}
	
	void RSC::PositionBake()
	{
		int i = 0;
		BeatSet LastBeat;
		LastBeat.BarPosition = 0;
		LastBeat.Beat_Denominator = 4;
		LastBeat.Beat_Factor = 4;
		LastBeat.Position = 0;
		for ( i = 0 ; i<= BeatListQ ; i++)
		{
			BeatList[i].Position = (BeatList[i].BarPosition 
									- LastBeat.BarPosition) 
									* GetBarLength(LastBeat) + LastBeat.Position;
			LastBeat = BeatList[i];
		}
	}
	
	void RSC::VolumeBake()
	{
		for ( int i=0 ; i <=SegmentListQ ; i++)
		{
			SegmentList[i].StartAmplitude = GetVolumeAt(SegmentList[i].Position );
			SegmentList[i].EndAmplitude = GetVolumeAt(SegmentList[i].Position + SegmentList[i].Duration);
		}
	}
	
	double RSC::GetVolumeAt(double Position)
	{
		int i;
		double pos1,pos2,ratio;
		bool found = false;
		double res = 1;
		for ( i = 0 ; i<= Effects.EnvelopeListQ ; i++)
		{
			if (Effects.EnvelopeList[i].Position >= Position)
			{
				found = true;
				if (i == 0)
				{
					res = Effects.EnvelopeList[0].Amplitude;
					break;
				}
				pos1 = Effects.EnvelopeList[i - 1].Position;
				pos2 = Effects.EnvelopeList[i].Position;
				ratio = (Position - pos1) / (pos2 - pos1);
				res = Effects.EnvelopeList[i - 1].Amplitude * (1 - ratio) +
							  Effects.EnvelopeList[i].Amplitude * ratio;
				break;			
			}
		}
		if (not found)
			res = Effects.EnvelopeList[Effects.EnvelopeListQ].Amplitude;
		return res;
	}
	
	double RSC::GetBarLength(BeatSet& _BeatSet)
	{
		return _BeatSet.Beat_Factor / _BeatSet.Beat_Denominator * 2;
	}
	
	double RSC::PositionToTime(double Position ,double Tempo)
	{
		//wLine(converter::CStr(Tempo));
		return Position * 2.0 * 60.0 / Tempo;
	}
	
	PositionChunk RSC::GetNextPositionChunk(double Position , int SegmentNum)
	{
		PositionChunk PChunk, PChunk2;
		int i =0;
		if (NextChunk_Coincidence) 
		{
			NextChunk_Coincidence = false;
			return NextChunk_Chunk;
		}
		for ( i = SegmentNum ; i<= SegmentListQ ; i++)
		{
			if (SegmentList[i].Position > Position )
			{
				PChunk.Type = SegmentStart;
				PChunk.Position = SegmentList[i].Position;
				PChunk.Index = i;
				break;
			}
			if (SegmentList[i].Position + SegmentList[i].Duration > Position)
			{
				PChunk.Type = SegmentEnd;
				PChunk.Position = SegmentList[i].Position + SegmentList[i].Duration;
				PChunk.Index = i;
				break;
			}
		}
		//wLine(converter::CStr(Position));
		for (i = 0 ; i<= TempoListQ ; i++)
		{
			if ( TempoList[i].Position >= Position )
			{
				//wLine("Tempo");
				PChunk2.Type = TempoStart;
				PChunk2.Position = TempoList[i].Position;
				PChunk2.Index = i;
				//wLine(converter::CStr(TempoList[i].Tempo));
				break;
			}
		}
		//wLine(converter::CStr(Position));
		//wLine(converter::CStr(TempoList[i].Tempo));
		if (PChunk.Position <= PChunk2.Position) 
			return PChunk;
		else
		{
			if (PChunk.Position == PChunk2.Position)
			{
				NextChunk_Coincidence = true;
				NextChunk_Chunk = PChunk;
			}
			return PChunk2;
		}
	}
	PositionChunk RSC::GetNextPositionChunk(double Position)
	{
		PositionChunk res;
		res = GetNextPositionChunk(Position , 0);
		return res;
	}
};