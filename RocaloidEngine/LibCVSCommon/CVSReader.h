 /*
  * CVSReader.h
  *
  * Copyright (C) 2013 - Rocaloid Development Group(RDG)
  *
  * Created by Sleepwalking
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
#ifndef CVSREADER_H
#define CVSREADER_H
#include "CVSCommon.h"
#include "../LibCyberBase/RDLIO.h"
class string;
namespace CVSReader
{
	using namespace CVSCommon;
	#define Exception(x) Overall::Exception(x);

	RDLReader Reader;
	
	void Reader_Open(string FileName);
	void Reader_Close();

	void CVS_Read(CVS& _CVS);
	void Segment_Read(Segment& _Segment);
	void TPhone_Read(TPhone& _TPhone);
	void TStart_Read(TStart& _TStart);
	void TDest_Read(TDest& _TDest);
	void TTransition_Read(TTransition& _TTransition);
	void FreqSet_Read(FreqSet& _FreqSet);
	void Effects_Read(EffectCollection& _Effects);
	void EnvelopeSet_Read(EnvelopeSet& _EnvelopeSet);
	void ADSREnvelope_Read(ADSREnvelope& _ADSREnvelope);
	void BreathStruct_Read(BreathStruct& _Breath);
};

 #endif /*REDAERSVC _H */
 