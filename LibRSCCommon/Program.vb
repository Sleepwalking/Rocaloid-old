'    读取命令行参数并调用功能
'    Reads commond line arguments and calls functions.
'    Copyright (C) 2013 Sleepwalking
'
'    This program is free software: you can redistribute it and/or modify
'    it under the terms of the GNU General Public License as published by
'    the Free Software Foundation, either version 3 of the License, or
'    (at your option) any later version.
'
'    This program is distributed in the hope that it will be useful,
'    but WITHOUT ANY WARRANTY; without even the implied warranty of
'    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
'    GNU General Public License for more details.
'
'    You should have received a copy of the GNU General Public License
'    along with this program.  If not, see <http://www.gnu.org/licenses/>.
Module Program
	Sub Main()
		Dim MainRSC As RSC = New RSC()
		Dim RSCInput As String = "a.rsc"
		Dim RSCOutput As String = "Z:\test.rsc"
		Dim RSCBreakOutput As String = "Z:\break.rsc"
		Dim CDTInput As String = "HMCHNDICT.cdt"
		Dim CVSOutput As String = "x.cvs"
		Dim VSQXInput As String = "melt.vsqx"
		Dim CloseAfterRun As Boolean = False
		Dim Task_Format As Boolean = False
		Dim Task_Convert As Boolean = True
		Dim Task_Break As Boolean = False
		Dim Task_OpenVSQX As Boolean = False
		Dim Args() As String = System.Environment.GetCommandLineArgs
		Dim i As Integer
		For i = 1 To Args.GetUpperBound(0)
			Select Case Args(i)
				Case "-rsc"
					i += 1
					RSCInput = Args(i)
				Case "-cvs"
					i += 1
					CVSOutput = Args(i)
				Case "-vsqx"
					i += 1
					VSQXInput = Args(i)
				Case "-cdt"
					i += 1
					CDTInput = Args(i)
				Case "-q"
					CloseAfterRun = True
				Case "-format"
					Task_Format = True
					i += 1
					RSCOutput = Args(i)
				Case "-ccnvt"
					Task_Convert = False
				Case "-cvsqx"
					Task_OpenVSQX = True
				Case "-break"
					Task_Break = True
					i += 1
					RSCBreakOutput = Args(i)
			End Select
		Next
		
		If Not Task_OpenVSQX Then
			RSCRead.Reader_Open(RSCInput)
			RSCRead.RSC_Read(MainRSC)
			RSCRead.Reader_Close()
		Else
			VSQXRead.Reader_Open(VSQXInput)
			VSQXRead.VSQX_Read(MainRSC)
			VSQXRead.Reader_Close()
		End If
		
		If Task_Format Then
			RSCWrite.Writer_Save(RSCOutput)
			RSCWrite.RSC_Write(MainRSC)
			RSCWrite.Writer_Close()
		End If
		
		If Task_Break Then
			RSCWrite.Writer.NewLineValid = False
			RSCWrite.Writer_Save(RSCBreakOutput)
			RSCWrite.RSC_Write(MainRSC)
			RSCWrite.Writer_Close()
		End If
		
		If Task_Convert Then
			MainRSC.TimeBake()
			MainRSC.PositionBake()
			MainRSC.VolumeBake()
			
			Dim MainCDT As CDTCommon.CDT = New CDTCommon.CDT()
			CDTCommon.Reader_Open(CDTInput)
			CDTCommon.CDT_Read(MainCDT)
			CDTCommon.Reader_Close()
			If MainCDT.Version = "2.33" Then CDTCommon.Compile(MainCDT)
			
			Dim MainCVS As CVSCommon.CVS = GenerateCVS(MainRSC, MainCDT)
			CVSCommon.Writer_Save(CVSOutput)
			CVSCommon.Write.CVS_Write(MainCVS)
			CVSCommon.Writer_Close()
		End If
		
		If Not CloseAfterRun Then
			Console.WriteLine("Completed.")
			Console.WriteLine("Press any key to continue . . . ")
			Console.ReadKey(True)
		End If
	End Sub
End Module