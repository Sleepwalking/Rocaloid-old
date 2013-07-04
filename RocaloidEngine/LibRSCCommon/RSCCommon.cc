/*
 * RSCCommon.cc
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
 #include "defs.h"
#include "io/terminal.h"
#include "structure/string.h"
#include "misc/converter.h"
#include "structure/array.h"
#include "io/fileStream.h"

#include "Overall.h"
#include "CVSCommon.h"
#include "RSCCommon.h"
namespace RSC
{
	void Segment::CopyTo( Segment Target )
	{
			Target.Position = Position;
			Target.Lyric = Lyric;
			Target.Duration = Duration;
			Target.StartTime = StartTime;
			Target.DurTime = DurTime;
			Target.Effects = Effects;
			Target.StartFreq = StartFreq;
			Target.EndFreq = EndFreq;
			Target.StartAmplitude = StartAmplitude;
			Target.EndAmplitude = EndAmplitude;
			Target.CutTime = CutTime;
	}
	
	bool Segment::IsConnectedTo ( Segment& _Segment)
	{
		if ( abs ( Position + Duration - _Segment.Position) < 0.01 ) 
			return true;
		else
			return false;
	}
};