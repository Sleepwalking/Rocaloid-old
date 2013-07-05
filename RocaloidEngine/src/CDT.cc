	/*CVSCommon::CVS* cvs1 = new CVSCommon::CVS;
	//CVSReader::Reader_Open("/home/rgwan/ramdisk/1.cvs");
	CVSReader Reader;
	CVSWriter Writer;
	Reader.Open("/home/rgwan/ramdisk/1.cvs");
	Reader.Read(*cvs1);
	Reader.Close();

	Writer.Save(CStr("/home/rgwan/ramdisk/test2.cvs"));
	//CVSWriter::Writer.NewLineValid = false;
	Writer.Write(*cvs1);
	Writer.Close();
	delete cvs1;*/
	int i,j;
	CDTCommon::CDTReader cdtr;
	CDTCommon::CDT cdt;
	cdtr.Open("/home/rgwan/ramdisk/HMCHNDICT.cdt");
	cdtr.Read(cdt);
	cdtr.Close();
	wLine (CStr("CDT Version :") + cdt.Version);
	wLine (CStr("LibCDT Version :") + cdt.CDTVersion);
	wLine (CStr("Language :") + cdt.Language);
	wLine (CStr("DEFLists :") + CStr(cdt.DEFListQ));
	wLine ( "Test :");
	for ( i=0 ; i<= cdt.DEFListQ; i ++)
	{
		wLine ( CStr("  Name= ") + cdt.DEFList[i].Name );
		wLine ( CStr("  TRatio= ") + CStr (cdt.DEFList[i].TRatio) );
	}
	wLine ( "PhoneticInfo:" );
	for (i=0 ; i<=cdt.Phonetic.OpennessListQ;i++)
		wLine ( CStr("   Tone : ") + cdt.Phonetic.OpennessList[i].Phone + " OPE: " + CStr(cdt.Phonetic.OpennessList[i].Ope));
	wLine ( "PhoneticInfo:" );
	/*for (i=0 ; i<=cdt.Phonetic.PhoneListQ;i++)
	{
		wLine ( CStr("	  Tone : ") + cdt.Phonetic.PhoneList[i].Phone );
		wLine ( CStr("			Type : ") + CStr(cdt.Phonetic.PhoneList[i].Type) );
		wLine ( CStr("			DataPoint:" ));
		for(i=0;i<=cdt.Phonetic.PhoneList[i].DataPointQ;i++)
		{
			wLine (CStr("			") + CStr ( cdt.Phonetic.PhoneList[i].DataPoint[i * 4] ) );
			wLine ( CStr("			") + CStr ( cdt.Phonetic.PhoneList[i].DataPoint[i * 4 +1] ) );
			wLine ( CStr("			") + CStr( cdt.Phonetic.PhoneList[i].DataPoint[i * 4 +2] ) );
			wLine ( CStr("			") +CStr ( cdt.Phonetic.PhoneList[i].DataPoint[i * 4 +3] ) );
		}
	}*/
	for(i=0;i<=cdt.Phonetic.PhoneListQ;i++)
	{
		wLine ( CStr("	  Tone : ") + cdt.Phonetic.PhoneList[i].Phone );
		wLine ( CStr("			Type : ") + CStr(cdt.Phonetic.PhoneList[i].Type) );

	
		wLine ( CStr("			DataPoint num :" ) + CStr(cdt.Phonetic.PhoneList[i].DataPointQ+1 ));
		for(j=0;j<=cdt.Phonetic.PhoneList[i].DataPointQ;j++)
		{
			wLine (CStr("			") + CStr ( cdt.Phonetic.PhoneList[i].DataPoint[j * 4] ) + " " +CStr ( cdt.Phonetic.PhoneList[i].DataPoint[j * 4 +1] ) + " " + CStr( cdt.Phonetic.PhoneList[i].DataPoint[j * 4 +2] ) + " " +CStr( cdt.Phonetic.PhoneList[i].DataPoint[j * 4 +3] ));
		}
	}
	wLine (CStr("DBInfo:"));
	wLine( CStr("   DBListes : " ) + CStr(cdt.DB.DBListQ));
	for(i=0;i<=cdt.DB.DBListQ;i++)
	{
		wLine ( CStr("	  Tone : ") + cdt.DB.DBList[i].Phone );
		wLine ( CStr("			Pitch : ") + CStr(cdt.DB.DBList[i].Pitch) );
		wLine ( CStr("			Attack:") + CStr(cdt.DB.DBList[i].VOT));
		wLine ( CStr("			PSnk:") + CStr(cdt.DB.DBList[i].PreShrink));
	}
	wLine("completed");