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
	
template <class T>
static inline void ObjSwap(T &a, T &b)
{//泛型交换
	T tmp = a;
	a = b;
	b = tmp;
}

struct QuadEqu
{
	double a;
	double b;
	double c;
};

void PtrSwap(int &p1, int &p2);
extern double GetFreqByPitch(string Pitch);
extern double GetDoubleSum(array<double>& Arr);
extern string GetPitchByFreq(double Freq);
QuadEqu GenerateQuadEquation(double x1, double y1, 
										 double x2, double y2,  
										double x3, double y3 );
}
#endif /*OVERALL_H */