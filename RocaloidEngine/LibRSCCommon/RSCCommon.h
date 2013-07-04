 /*
  * RSCCommon.h
  *
  * Copyright (C) 2013 - Rocaloid Development Group(RDG)
  *
  * Created by rgwan
  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General License as published by
  * the Free Software Foundation; either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General License for more details.
  *
  * You should have received a copy of the GNU General License
  * along with this program. If not, see <http://www.gnu.org/licenses/>.
  */
namespace RSC
{
	using namespace RSC;
	struct EnvelopeList;
	struct EnvelopeSet;
	enum ViewTypes
	{
		NotesEditor,
		FreqEditor,
		EnvelopeEditor,
		BreathEditor,
		Other
	};
	enum PositionChunkType
	{
		SegmentStart,
		SegmentEnd,
		TempoStart
	};
	
	 struct PositionChunk
	{
		PositionChunkType Type;
		double Position;
		int Index;
	};

	struct SegmentEffects
	{
		//Dim Vibration As VibrationStruct
		bool PElopeEnabled;
		CVSCommon::Envelopes PresetedEnvelope;
		CVSCommon::ADSREnvelope ADSR;
		CVSCommon::BreathStruct Breath;
	};

	struct EffectsStruct
	{
		int EnvelopeListQ;
		array<EnvelopeSet> EnvelopeList;
	};

	struct TempoSet
	{
		double Position;
		double Tempo;
	};

	struct BeatSet
	{
		double Position;
		int BarPosition;
		int Beat_Factor;
		int Beat_Denominator;
	};

	struct EnvelopeSet
	{
		double Position;
		double Amplitude;
	};

	struct UserInteraction
	{
		double LastUserPosition;
		double LastUserScale;
		ViewTypes ViewType;
	};

	struct FreqSet
	{
		double Position;
		double Freq;
	};
	class Segment
	{
		public:
			double Position;
			string Lyric;
			double Duration;
			double StartTime;
			double DurTime;
			SegmentEffects Effects;
			double StartFreq;
			double EndFreq;
			double StartAmplitude;
			double EndAmplitude;
			double CutTime;
			void CopyTo( Segment Target );
			Segment();
			bool IsConnectedTo ( Segment& _Segment);
	};
	class RSC
	{
		public:
			string Version;
			string Author;
			string Information;
			int SegmentListQ;
			array<Segment> SegmentList;
			int FreqListQ;
			array<FreqSet> FreqList;
			EffectsStruct Effects;
			int TempoListQ;
			array<TempoSet> TempoList;
			int BeatListQ;
			array<BeatSet> BeatList;
			UserInteraction InteractionSave;
			
	};
#define RSC_VERSION "2.0"
};