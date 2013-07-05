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
	void Segment::CopyTo( Segment Target )
	{
			Target.Position = Position;
			Target.Lyric = Lyric;
			Target.Duration = Duration;
			Target.StartTime = StartTime;
			Target.DurTime = DurTime;
			Target.Effects = Effects;
			Target.StartFreq = StartFreq;
			Target.EndFreq = EndFreq;
			Target.StartAmplitude = StartAmplitude;
			Target.EndAmplitude = EndAmplitude;
			Target.CutTime = CutTime;
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
	void RSC::CopyTo(RSC& Target)
	{
		int i;
			Target.Version = Version;
			Target.Author = Author;
			Target.Information = Information;
			Target.SegmentListQ = SegmentListQ;
			Target.SegmentList.setUbound (SegmentListQ );
			//Target.InitSegmentList(0, SegmentListQ);
			Target.FreqListQ = FreqListQ;
			Target.FreqList.setUbound (FreqListQ);
			Target.Effects = Effects;
			Target.TempoListQ = TempoListQ;
			Target.TempoList.setUbound (TempoListQ);
			Target.BeatListQ = BeatListQ;
			Target.BeatList.setUbound (BeatListQ);
			Target.InteractionSave = InteractionSave;
		for (i = 0 ; i<=Target.SegmentListQ ; i++)
			SegmentList[i].CopyTo(Target.SegmentList[i]);
		for (i = 0 ; i<=Target.FreqListQ ; i++)
			Target.FreqList[i] = FreqList[i];
		for (i = 0 ; i<=Target.TempoListQ ; i++)
			Target.TempoList[i] = TempoList[i];
		for (i = 0 ; i<=Target.BeatListQ ; i++)
			Target.BeatList[i] = BeatList[i];
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
				NextChunk = GetNextPositionChunk(i + 0.0001, 0);
			i = NextChunk.Position;
			switch (NextChunk.Type)
			{
				case SegmentStart:
					LastSegmentIndex = NextChunk.Index;
					SegmentList[LastSegmentIndex].StartTime = PositionToTime(NextChunk.Position - 
					                                                         LastTempo.Position , LastTempo.Tempo) + LastTempo_Time;
					break;
				case SegmentEnd:
					EndTime = PositionToTime(NextChunk.Position - LastTempo.Position, LastTempo.Tempo) 
						+ LastTempo_Time;
					SegmentList[LastSegmentIndex].DurTime = EndTime - SegmentList[LastSegmentIndex].StartTime;
					break;
				case TempoStart:
					LastTempo_Time += PositionToTime(NextChunk.Position - LastTempo.Position, LastTempo.Tempo);
					LastTempo = TempoList[NextChunk.Index];
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
		return Position * 2 * 60 / Tempo;
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
		for (i = 0 ; i<= TempoListQ ; i++)
		{
			if ( TempoList[i].Position > Position )
			{
				PChunk2.Type = TempoStart;
				PChunk2.Position = TempoList[i].Position;
				PChunk2.Index = i;
				break;
			}
		}
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
		GetNextPositionChunk(Position , 0);
	}
};