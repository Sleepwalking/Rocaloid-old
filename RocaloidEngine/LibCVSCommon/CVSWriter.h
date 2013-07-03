 /*
  * CVSWriter.h
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
#ifndef CVSWRITER_H
#define CVSWRITER_H
#include "CVSCommon.h"
#include "../LibCyberBase/RDLIO.h"
class string;
namespace CVSWriter
{
	extern RDLWriter Writer;
	using namespace CVSCommon;
	
	void Writer_Save(string FileName);
	void Writer_Close();

	void CVS_Write(CVS& _CVS);
	void Segment_Write(Segment& _Segment);
	void TPhone_Write(TPhone& _TPhone);
	void Freq_Write(FreqSet& _Freq);
	void Effects_Write(EffectCollection& _Effects);
	void ADSREnvelope_Write(ADSREnvelope& _ADSR);
	void EnvelopeSet_Write(EnvelopeSet& _EnvelopeSet);
	void BreathStruct_Write(BreathStruct& _Breath);
};
 #endif
 