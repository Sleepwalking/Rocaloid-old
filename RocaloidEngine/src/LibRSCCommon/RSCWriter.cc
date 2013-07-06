 /*
  * RSCWriter.cc
  *
  * Copyright (C) 2013 - Rocaloid Development Group (RDG)
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
#include "RSCWriter.h"

namespace RSCCommon
{
	using namespace RDLIO;
	using namespace Overall;

	void RSCWriter::Save(string FileName)
	{
		Writer.Open(FileName);
		Writer.WriteWord("#RSC");
		Writer.WriteWord(RSC_VERSION);
		Writer.NewLine();
	}
	void RSCWriter::Close()
	{
		Writer.Close();
	}

	void RSCWriter::Write(RSC& _RSC)
	{
		int i;
		Writer.WriteWord("RSC");
		Writer.IndentPush();
		Writer.NewLine();
		//Author
		Writer.WriteWord("Author");
		Writer.WriteWord(_RSC.Author);
		Writer.NewLine();
		//Information
		Writer.WriteWord("Information");
		Writer.WriteWord(_RSC.Information);
		Writer.WriteWord("\\0");
		Writer.NewLine();
		//SegmentList
		Writer.WriteWord("SegmentListQ");
		Writer.WriteWord(_RSC.SegmentListQ + 1);
		Writer.NewLine();
		
		Writer.WriteWord("SegmentList");
		Writer.IndentPush();
		Writer.NewLine();
		for ( i=0; i<= _RSC.SegmentListQ ; i++)
			Segment_Write(_RSC.SegmentList[i]);
			
		Writer.IndentPop();
		Writer.WriteWord("End");
		Writer.NewLine();
		//FreqList
		Writer.WriteWord("FreqListQ");
		Writer.WriteWord(_RSC.FreqListQ + 1);
		Writer.NewLine();
		
		Writer.WriteWord("FreqList");
		Writer.IndentPush();
		Writer.NewLine();
		for ( i=0 ; i<= _RSC.FreqListQ ; i++)
			FreqSet_Write(_RSC.FreqList[i]);
		
		Writer.IndentPop();
		Writer.WriteWord("End");
		Writer.NewLine();
		//Effects
		Effects_Write(_RSC.Effects);
		//TempoList
		Writer.WriteWord("TempoListQ");
		Writer.WriteWord(_RSC.TempoListQ + 1);
		Writer.NewLine();
		
		Writer.WriteWord("TempoList");
		Writer.IndentPush();
		Writer.NewLine();
		for ( i =0 ; i <= _RSC.TempoListQ ; i++)
			TempoSet_Write(_RSC.TempoList[i]);

		Writer.IndentPop();
		Writer.WriteWord("End");
		Writer.NewLine();
		//BeatList
		Writer.WriteWord("BeatListQ");
		Writer.WriteWord(_RSC.BeatListQ + 1);
		Writer.NewLine();
		
		Writer.WriteWord("BeatList");
		Writer.IndentPush();
		Writer.NewLine();
		for ( i=0 ; i <= _RSC.BeatListQ ; i++)
			BeatSet_Write(_RSC.BeatList[i]);

		Writer.IndentPop();
		Writer.WriteWord("End");
		Writer.NewLine();
		//InteractionSave
		Interaction_Write(_RSC.InteractionSave);
		
		Writer.IndentPop();
		Writer.WriteWord("End");
		Writer.NewLine();
	}

	void RSCWriter::Segment_Write(Segment& _Segment)
	{
		Writer.WriteWord("Segment");
		Writer.IndentPush();
		Writer.NewLine();
		
		Writer.WriteWord("Position");
		Writer.WriteWord(_Segment.Position);
		Writer.NewLine();
		
		Writer.WriteWord("Duration");
		Writer.WriteWord(_Segment.Duration);
		Writer.NewLine();
		
		Writer.WriteWord("Lyric");
		Writer.WriteWord(_Segment.Lyric);
		Writer.NewLine();
		
		SegmentEffects_Write(_Segment.Effects);
		
		Writer.WriteWord("StartFreq");
		Writer.WriteWord(_Segment.StartFreq);
		Writer.NewLine();
		
		Writer.WriteWord("EndFreq");
		Writer.WriteWord(_Segment.EndFreq);
		Writer.NewLine();
		
		Writer.IndentPop();
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	void RSCWriter::FreqSet_Write(FreqSet& _FreqSet)
	{
		Writer.WriteWord("FreqSet");
		
		Writer.WriteWord("Position");
		Writer.WriteWord(_FreqSet.Position);
		
		Writer.WriteWord("Freq");
		Writer.WriteWord(_FreqSet.Freq);
		
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	void RSCWriter::Effects_Write(EffectsStruct& _Effects)
	{
		int i;
		Writer.WriteWord("Effects");
		Writer.IndentPush();
		Writer.NewLine();
		
		Writer.WriteWord("EnvelopeListQ");
		Writer.WriteWord(_Effects.EnvelopeListQ + 1);
		Writer.NewLine();
		
		Writer.WriteWord("EnvelopeList");
		Writer.IndentPush();
		Writer.NewLine();
		for ( i=0 ; i<= _Effects.EnvelopeListQ ; i++)
			EnvelopeSet_Write(_Effects.EnvelopeList[i]);

		Writer.IndentPop();
		Writer.WriteWord("End");
		
		Writer.IndentPop();
		Writer.NewLine();
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	void RSCWriter::TempoSet_Write(TempoSet& _TempoSet)
	{
		Writer.WriteWord("TempoSet");
		
		Writer.WriteWord("Position");
		Writer.WriteWord(_TempoSet.Position);
		
		Writer.WriteWord("Tempo");
		Writer.WriteWord(_TempoSet.Tempo);
		
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	void RSCWriter::BeatSet_Write(BeatSet& _BeatSet)
	{
		Writer.WriteWord("BeatSet");
		
		Writer.WriteWord("BarPosition");
		Writer.WriteWord(_BeatSet.BarPosition);
		
		Writer.WriteWord("Factor");
		Writer.WriteWord(_BeatSet.Beat_Factor);
		
		Writer.WriteWord("Denominator");
		Writer.WriteWord(_BeatSet.Beat_Denominator);
		
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	void RSCWriter::Interaction_Write(UserInteraction& _Interaction)
	{
		Writer.WriteWord("InteractionSave");
		Writer.IndentPush();
		Writer.NewLine();
		
		Writer.WriteWord("LastUserPosition");
		Writer.WriteWord(_Interaction.LastUserPosition);
		Writer.NewLine();
		
		Writer.WriteWord("LastUserScale");
		Writer.WriteWord(_Interaction.LastUserScale);
		Writer.NewLine();
		
		Writer.WriteWord("ViewType");
		WriteViewType(_Interaction.ViewType);
		
		Writer.IndentPop();
		Writer.NewLine();
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	void RSCWriter::WriteViewType(int _View)
	{
		switch (_View)
		{
			case NotesEditor:
				Writer.WriteWord("NotesEditor");
				break;
			case FreqEditor:
				Writer.WriteWord("FreqEditor");
				break;
			case EnvelopeEditor:
				Writer.WriteWord("EnvelopeEditor");
				break;
			case BreathEditor:
				Writer.WriteWord("BreathEditor");
				break;
			default:
				Writer.WriteWord("Other");
				break;
		}
	}
	void RSCWriter::SegmentEffects_Write(SegmentEffects& _Effects)
	{
		Writer.WriteWord("Effects");
		Writer.IndentPush();
		Writer.NewLine();
		
		Writer.WriteWord("PElopeEnabled");
		Writer.WriteWord(_Effects.PElopeEnabled);
		Writer.NewLine();
		
		if (_Effects.PElopeEnabled)
		{
			
			Writer.WriteWord("PresetedEnvelope");
			Writer.WritePresetedEnvelope(_Effects.PresetedEnvelope);
			Writer.NewLine();
			
			if (_Effects.PresetedEnvelope == CVSCommon::ADSR)
					ADSR_Write(_Effects.ADSR);
		}
		
		Writer.IndentPop();
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	void RSCWriter::ADSR_Write(CVSCommon::ADSREnvelope& _ADSR)
	{
		Writer.WriteWord("ADSR");
		
		Writer.WriteWord("Amplitude");
		Writer.WriteWord(_ADSR.Amplitude);
		Writer.WriteWord("Attack");
		Writer.WriteWord(_ADSR.Attack);
		Writer.WriteWord("Decline");
		Writer.WriteWord(_ADSR.Decline);
		Writer.WriteWord("Release");
		Writer.WriteWord(_ADSR.Release);
		
		Writer.WriteWord("End");
		Writer.NewLine();
	}
	void RSCWriter::EnvelopeSet_Write(EnvelopeSet& _ESet)
	{
		Writer.WriteWord("EnvelopeSet");
		
		Writer.WriteWord("Position");
		Writer.WriteWord(_ESet.Position);
		Writer.WriteWord("Magnitude");
		Writer.WriteWord(_ESet.Amplitude);
		
		Writer.WriteWord("End");
		Writer.NewLine();
	}
};