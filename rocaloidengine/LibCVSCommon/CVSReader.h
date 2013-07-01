 /*
  * CVSReader.h
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
 #ifndef CVSREADER_H
 #define CVSREADER_H

namespace CVSReader
{
	//#define Exception(x) Overall::Exception(x);
	using namespace CVSCommon;
	void Open(string File);
	void Close();

	void BreathStruct_Read(BreathStruct & _Breath);
	void EnvelopeSet_Read( EnvelopeSet & _EnvelopeSet);
	void ADSREnvelope_Read(ADSREnvelope & _ADSREnvelope  );
	void Effects_Read(EffectCollection & _Effects);
	void FreqSet_Read( FreqSet & _FreqSet );
	void TStart_Read(TStart & _Start);
	void TDest_Read(TDest & _Dest);
	void TTransition_Read(TTransition &  _Transition);
	void TPhone_Read(TPhone & _TPhone);
	void Segment_Read(Segment & _Segment );
	void Read(CVS & _CVS);
};

 #endif /*REDAERSVC _H */
 