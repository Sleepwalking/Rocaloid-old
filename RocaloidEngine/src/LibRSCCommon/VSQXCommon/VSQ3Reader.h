 /*
  * VSQ3Reader.h
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
 #ifndef VSQ3READER_H
 #define VSQ3READER_H

namespace VSQXCommon
{
	class VSQ3Reader
	{
		public:
			int Pointer;
			
			void Open(string FileName);
			void Close();

			void ReadUntil(string _String);
			int FindNextPos(string _String);
			int FindLastPos(string _String, int Before);
			string ReadNextValue(string AttributeName);
			string ReadCDATA(string CDATA);
		private:
			textStream Reader;
			string Buffer;
	};
};
 
 #endif /* REDAER3*QSV _H */
 