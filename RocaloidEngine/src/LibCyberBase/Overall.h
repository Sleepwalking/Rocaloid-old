/*
 * Overall.h
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
#ifndef OVERALL_H
#define OVERALL_H
#include "SPKit/defs.h"
#include "SPKit/structure/array.h"
#include "SPKit/structure/string.h"

namespace Overall
{
	#define SampleRate  96000
	#define INFINITY  99999
	#define PitchListQ  59
	#define Pitch_C5  48
	#define Pitch_C2  12
	#define WaveHeadLength  44

	extern const byte WaveHeader[];
	extern const string PitchList[];
	extern const double FreqList[];
	extern int VOT;//Attack Time

	template <class T> inline void ObjSwap(T &a, T &b)
	{
		//Generic ByRef Swap.
		T tmp = a;
		a = b;
		b = tmp;
	}
	
	template <class T> inline void PtrSwap(T*& p1, T*& p2)
	{
		//Switch by pointer.
		T* Temp = p1;
		p1 = p2;
		p2 = Temp;
	}

	struct QuadResult
	{
		double a;
		double b;
		double c;
	};

	extern double GetFreqByPitch(string Pitch);
	extern double GetDoubleSum(array<double>& Arr);
	extern int FreqToPeriod(double Freq);
	extern string GetPitchByFreq(double Freq);
	extern QuadResult GenerateQuadEquation
	(
		 double x1, double y1,
		 double x2, double y2,
		 double x3, double y3
	);
	extern void Exception(string errorMsg);
}
#endif /*OVERALL_H */