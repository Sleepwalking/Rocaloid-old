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

class Overall
{
	public:
		//屈服了，QT这么做是有原因的
		inline char *WaveHead();
		enum{WaveHeadLength=44};
		inline char *PitchList(char Pitch);
	private:

};