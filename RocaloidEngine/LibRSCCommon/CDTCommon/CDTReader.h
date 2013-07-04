 /*
  * CDTRead.h
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
 #ifndef CDTREADER_H
 #define CDTREADER_H
 
namespace CDTCommon
{
	using namespace Overall;
	extern CaseParameter TestIfIsCaseParameter(string _String);
	extern CaseComparison TestIfIsCaseComparison(string _String);
	extern DEFType TestIfIsDEFType(string _String);

	class CDTReader
	{
		public:
			void Open(string FileName);
			void Close();
			
			void CDT_Read(CDT& _CDT);
			
			void DEFList_Read(CDT& _CDT);
			void DEF_Read(DEF& _DEF);
			void PhoneticInfo_Read(PhoneticInfo& _PhoneticInfo);
			void PhoneSet_Read(PhoneSet& _PhoneSet);
			void DBInfo_Read(DBInfo& _DBInfo);
			void DBSet_Read(DBSet& _DBSet);
		private:
			RDLReader Reader;
			string CDTVersion;
	};
			
};
 
 #endif /*DAERTDC _H */
 