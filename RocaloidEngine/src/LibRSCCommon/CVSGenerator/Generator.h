 /*
  * Generator.h
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
//Generating RSC from CVS using CDT.
 #ifndef RSCGENERATOR_H
 #define RSCGENERATOR_H
 namespace RSCCommon
{
		void GenerateEnvelope(CVSCommon::CVS& _CVS , 
	                      RSC& _RSC , int Num);
		void GenerateFreq(CVSCommon::CVS& _CVS, 
	                  RSC& _RSC, int Num);
		void GenerateTPhone(CVSCommon::CVS& _CVS ,
	                    RSC& _RSC ,
	                    CDTCommon::DEF& _DEF ,
	                    int Num);
	void GenerateCVS(RSC& _RSC, 
	                           CDTCommon::CDT& _CDT , 
	                           CVSCommon::CVS& _CVS);

};

 
 #endif /*ROTARENEGCSR _H */
 