 /*
  * RSCWriter.h
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
 #ifndef RSCWRITER_H
 #define RSCWRITER_H
 
namespace RSCCommon
{
	using namespace RDLIO;
	using namespace Overall;
	class RSCWriter
	{
		public:
			void Save(string FileName);
			void Close();
			
			void Write(RSC& _RSC);
			
			void Segment_Write(Segment& _Segment);
			void FreqSet_Write(FreqSet& _FreqSet);
			void Effects_Write(EffectsStruct& _Effects);
			void TempoSet_Write(TempoSet& _TempoSet);
			void BeatSet_Write(BeatSet& _BeatSet);
			void Interaction_Write(UserInteraction& _Interaction);
			void SegmentEffects_Write(SegmentEffects& _SEffects);
			void ADSR_Write(CVSCommon::ADSREnvelope& _ADSR);
			void EnvelopeSet_Write(EnvelopeSet& _ESet);
			void WriteViewType(int _View);
		private:
			RDLWriter Writer;
	};
};
 
 #endif /*RETIRWCSR _H */
 