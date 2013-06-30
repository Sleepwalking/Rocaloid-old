/*
 * Overall.cc
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
//数据大丢失
#include "../SPKit/defs.h"
#include "../SPKit/structure/string.h"
#include "Overall.h"
#include <iostream>
namespace Overall
{
	byte WaveHeader[]={
			0x52,0x49,0x46,0x46,0x24,0x10,0x1F,0x00,
			0x57,0x41,0x56,0x45,0x66,0x6D,0x74,0x20,
			0x10,0x00,0x00,0x00,0x01,0x00,0x01,0x00,
			0x00,0x77,0x01,0x00,0x00,0xEE,0x02,0x00, 
			0x02,0x00,0x10,0x00,0x64,0x61,0x74,0x61,
			0x00,0x10,0x1F,0x00
	};
	string PitchList[]={
		"C1","C#1","D1","D#1","E1","F1","F#1","G1","G#1","A1","A#1","B1",
		"C2","C#2","D2","D#2","E2","F2","F#2","G2","G#2","A2","A#2","B2", 
		"C3","C#3","D3","D#3","E3","F3","F#3","G3","G#3","A3","A#3","B3", 
		"C4","C#4","D4","D#4","E4","F4","F#4","G4","G#4","A4","A#4","B4", 
		"C5","C#5","D5","D#5","E5","F5","F#5","G5","G#5","A5","A#5","B5"
	};
	const double FreqList[]=
	{
		65.40639, 69.29565, 73.41619, 77.78175, 82.40689, 87.30706, 
		92.4986, 97.99886, 103.8262, 110, 116.5409, 123.4708, 129.9053, 
		137.7331, 145.8967, 154.5894, 163.8225, 173.5986, 
		183.9081, 194.7262, 206.4516, 218.6788, 231.8841, 245.5243, 
		260.1626, 275.8621, 291.7933, 308.6817, 327.6451, 346.5704, 
		366.4122, 388.664, 412.0172, 436.3636, 463.7681, 489.7959, 
		518.9189, 551.7241, 581.8182, 619.3549, 653.0612, 695.6522, 
		732.8244, 780.4878, 827.5862, 872.7273, 923.0769, 979.5919, 
		1043.478, 1108.73, 1174.659, 1244.508, 1318.51, 1396.913, 
		1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533
	};
}
