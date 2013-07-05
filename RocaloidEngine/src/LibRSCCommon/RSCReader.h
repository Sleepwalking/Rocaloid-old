 /*
  * RSCReader.h
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
 #ifndef RSCREADER_H
 #define RSCREADER_H
 
namespace RSCCommon
{
	using namespace RDLIO;
	using namespace Overall;
	class RSCReader
	{
		public:
			void Open(string FileName);
			void Close();
			void Read(RSC& _RSC);
			void Information_Read(string& _Info);
			void Segment_Read(Segment& _Segment);
			void FreqSet_Read(FreqSet& _FreqSet);
			void Effects_Read(EffectsStruct& _Effects);
			void TempoSet_Read(TempoSet& _TempoSet);
			void BeatSet_Read(BeatSet& _BeatSet);
			void Interaction_Read(UserInteraction& _Interaction);
			void SegmentEffects_Read(SegmentEffects& _SEffects);
			void ADSR_Read(CVSCommon::ADSREnvelope& _ADSREnvelope);
			void EnvelopeSet_Read(EnvelopeSet& _EnvelopeSet);
		private:
			RDLReader Reader;
			inline void Detect_WrongEnd();
	};
};
 
 #endif /*REDAERTDC _H */
 