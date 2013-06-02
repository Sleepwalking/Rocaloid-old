'    包含了Main函数，提供命令行参数输入、控制合成器合成。
'    This file contains the Main function ,which detects command line arguments and controls the synthesizers.
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

Class Main
	Public Shared Sub Main()
		Dim OutputFile As String = "RenaIsAlive.wav"
		Dim InputCVS As String = "x.cvs"
		Dim Args() As String = System.Environment.GetCommandLineArgs
		Dim CloseAfterRun As Boolean = False
		Dim Task_Format As Boolean = False
		Dim Task_Break As Boolean = False
		Dim Task_Synthesis As Boolean = True
		Dim OutputFormatCVS As String = "Formated.cvs"
		Dim OutputBreakCVS As String = "Broken.cvs"
		
		Dim i As Integer
		For i = 1 To Args.GetUpperBound(0)
			Select Case Args(i)
				Case "-wav"
					i += 1
					OutputFile = Args(i)
				Case "-cvs"
					i += 1
					InputCVS = Args(i)
				Case "-data"
					i += 1
					Compatibility_DataDir = Args(i)
				Case "-q"
					CloseAfterRun = True
				Case "-format"
					Task_Format = True
					i += 1
					OutputFormatCVS = Args(i)
				Case "-csyn"
					Task_Synthesis = False
				Case "-break"
					Task_Break = True
					i += 1
					OutputBreakCVS = Args(i)
			End Select
		Next
		If Task_Synthesis Then
			Scheduler.SetFileOutput(OutputFile)
			Scheduler.Init()
			Scheduler.OpenCVS(InputCVS)
			Scheduler.RunSynthesizer()
		End If
		If Task_Format Then
			CreateLog("Reading " & InputCVS & "...")
			CVSCommon.RDLWriter.NewLineValid = True
			Dim CVS1 As CVSCommon.CVS = New CVSCommon.CVS()
			CVSCommon.Reader_Open(InputCVS)
			CVSCommon.CVS_Read(CVS1)
			CVSCommon.Reader_Close()
			CreateLog("Writing " & OutputFormatCVS & "...")
			CVSCommon.Writer_Save(OutputFormatCVS)
			CVSCommon.CVS_Write(CVS1)
			CVSCommon.Writer_Close()
			CreateLog("Format done.")
		End If
		If Task_Break Then
			CreateLog("Reading " & InputCVS & "...")
			CVSCommon.RDLWriter.NewLineValid = False
			Dim CVS1 As CVSCommon.CVS = New CVSCommon.CVS()
			CVSCommon.Reader_Open(InputCVS)
			CVSCommon.CVS_Read(CVS1)
			CVSCommon.Reader_Close()
			CreateLog("Writing " & OutputBreakCVS & "...")
			CVSCommon.Writer_Save(OutputBreakCVS)
			CVSCommon.CVS_Write(CVS1)
			CVSCommon.Writer_Close()
			CreateLog("Break done.")
		End If
		
		'Dim Wave As WaveBuffer = New WaveBuffer(3.0)
		'Dim Frame As FrameBuffer = New FrameBuffer()
		'Dim Synth As ConsecutivePreSynthesizer = New ConsecutivePreSynthesizer()
		'Synth.Load("^[_C2")
		'Dim i As Integer
		'While i < 2 * SampleRate
		'	Frame = Synth.Synthesize()
		'	i += Frame.Length
		'	Wave.Write(Frame)
		'End While
		'Scheduler.SegmentSynthesize(Scheduler.Synth1, Scheduler.CVS_.SegmentList(0), Wave)
		'Wave.OutputToWave("a.wav")
		
		If Not CloseAfterRun Then
			Console.Write("Press any key to continue . . . ")
			Console.ReadKey(True)
		End If
	End Sub
End Class
