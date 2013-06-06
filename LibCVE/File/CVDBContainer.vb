'    存储音源库文件，包括音源数据，帧，元音或辅音，辅音的VOT（存贮在Info中）。提供cbv文件读取。
'    Stores information of sound data files, including sound data, frames,
'    vowel or consonant, VOT of consonant (as stored in Info).
'    Reads cbv files. 
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
#Const DebugLevel = 0
Imports System.IO
Public Class CVDBContainer
	Public Info As CVDBHeader
	Public Buffer As MultiFrameBuffer
	Public Shared LoaderStream As FileStream
	Public Shared Loader As BinaryReader
	Private Name_ As String
	Private BaseFrame_ As Integer
	Public ReadOnly Property BaseFrame() As Integer
		Get
			Return BaseFrame_
		End Get
	End Property
	Public ReadOnly Property Name() As String
		Get
			Return Name_
		End Get
	End Property
	Public ReadOnly Property Symbol() As String
		Get
			If Mid(Name_, 2, 1) = "_" Then
				Return Left(Name_, 1)
			ElseIf Mid(Name_, 3, 1) = "_" Then
				Return Left(Name_, 2)
			Else
				'Throw New Exception("Invalid Note Name " & Name_ & ".")
				Return ""
			End If
		End Get
	End Property
	Public ReadOnly Property Pitch() As String
		Get
			If Mid(Name_, 2, 1) = "_" Then
				Return Mid(Name_, 3, 3)
			ElseIf Mid(Name_, 3, 1) = "_" Then
				Return Mid(Name_, 4, 3)
			Else
				'Throw New Exception("Invalid Note Name " & Name_ & ".")
				Return ""
			End If
		End Get
	End Property
	Public Sub New()
		Buffer = New MultiFrameBuffer(3000,1000)
		Info = New CVDBHeader()
		Name_ = ""
		BaseFrame_ = 0
	End Sub
	Public Sub ClearSymbol()
		Name_ = "nx_C3"
	End Sub
	Private Function GetCirculationBase() As Integer
		Dim i As Integer
		Dim acc As Integer = 0
		For i = 0 To Buffer.Length
			acc = acc + Buffer.Data(i).Length
			If acc > Info.StartPoint Then
				Return i + 1
			End If
		Next
		Return 0
	End Function
	Public Sub Load(ByVal FileName As String)
		Dim DataLen As Integer
		Dim Temp16 As Int16
		Dim b0 As Integer, b1 As Integer
		Dim FrameCount As Integer, DataCount As Integer, SampleCount As Integer
		'Use direct calculations instead of BitConverter to improve performance.
		
		LoaderStream = New FileStream(Compatibility_DataDir & FileName & ".cbv", FileMode.Open)
		
		DataLen = CInt((LoaderStream.Length - 256) / 2) 'Get data length of .cbv files
		Loader = New BinaryReader(LoaderStream)
		
		'Read Header
		Dim Head(3) As Byte, Information(239) As Byte, BinaryBuffer(512*1024) As Byte
		Head=Loader.ReadBytes(4)
		If ByteOperator.ByteToString(Head,4) <> "CVDB" Then
			Throw New Exception(FileName & ".cbv is invalid!")
		End If
		Info.Version = Loader.ReadUInt16
		
		If Info.Version = 1 Then
			'CVDB 0.5
			Info.Consonant = (Loader.ReadByte = 255)
			Info.StartPoint = Loader.ReadInt32
			Info.AveragePeriod = Loader.ReadInt32
			Loader.ReadByte
			Information = Loader.ReadBytes(240)
			Info.Information = ByteOperator.ByteToString(Information, 240)
			#If DebugLevel > 0 Then
				Log.CreateLog("CVDBContainer:	Loaded " & FileName & ".cbv")
				Log.CreateLog("	Version: " & Info.Version _
							& " Consonant:" & CStr(Info.Consonant) _
							& " StartPoint:" & Info.StartPoint)
			#End If
			
			'Read Data
			BinaryBuffer = Loader.ReadBytes(DataLen * 2)	
			FrameCount = 0
			DataCount = 0
			SampleCount = 0
			
			
			If Not Info.Consonant Then
				'If vowel, then skip the first 5 frames.
				'Because the first several frames may not be stable.
				Dim SkipCount As Integer = 0
				While SkipCount < 5
					b0 = BinaryBuffer(DataCount)
					b1 = BinaryBuffer(DataCount + 1)
					If b1 < 128 Then
						'Positive
						Temp16 = CShort((b1 << 8) Or b0)
					Else
						'Negative
						Temp16 = CShort(((b1 << 8) Or b0) - 65536)
					End If
					DataCount += 2
					If Temp16 = 32766 Then
						SkipCount = SkipCount + 1
					End If
				End While
			End If
			FastLoadCycle:
			b0 = BinaryBuffer(DataCount)
			b1 = BinaryBuffer(DataCount + 1)
			If b1 < 128 Then
				'Positive
				Temp16 = CShort((b1 << 8) Or b0)
			Else
				'Negative
				Temp16 = CShort(((b1 << 8) Or b0) - 65536)
			End If
			DataCount += 2
			If Temp16 < 32766 Then
				'Recieve data
				Buffer.Data(FrameCount).Data(SampleCount)=CDbl(Temp16 / 32767)
				SampleCount += 1
			ElseIf Temp16 = 32766 Then
				'Meets a frame
				Buffer.Data(FrameCount).Length = SampleCount - 1
				#If DebugLevel > 1 Then
					CreateLog("	Frame" & FrameCount & " Length:" & SampleCount - 1)
				#End If
				SampleCount = 0
				FrameCount += 1
				If FrameCount >= 3000 Then
					Throw New Exception("Overflow. " & FileName & ".cbv exceeds the length of buffer.")
				End If
			Else
				'Meets end
				Buffer.Data(FrameCount).Length = SampleCount
				GoTo ExitLoadCycle
			End If
			GoTo FastLoadCycle
			ExitLoadCycle:
			Buffer.Length = FrameCount - 1
			#If DebugLevel > 0 Then
				CreateLog("	MultiFrameBuffer Length:" & Buffer.Length)
			#End If
		ElseIf Info.Version = 2 Then
			'CVDB 0.6
			With Loader
				If .ReadByte() = 255 Then
					Info.Consonant = True
				Else
					Info.Consonant = False
				End If
				Info.StartPoint = .ReadInt32()
				.ReadInt32()'Skip the period start position.
				.ReadByte()
				
				Buffer.Length = .ReadUInt16()
				Dim DataQ As Integer = 0
				Dim i As Integer, j As Integer
				For i = 0 To Buffer.Length
					Buffer.Data(i).Length = .ReadUInt16() - 1
					DataQ += Buffer.Data(i).Length
				Next
				Info.AveragePeriod = CInt(DataQ / (Buffer.Length + 1))
				
				'Read Data
				BinaryBuffer = .ReadBytes(DataQ * 2 + 96000)
				
				DataCount = 0
				For i = 0 To Buffer.Length
					For j = 0 To Buffer.Data(i).Length
						b0 = BinaryBuffer(DataCount)
						b1 = BinaryBuffer(DataCount + 1)
						If b1 < 128 Then
							'Positive
							Temp16 = CShort((b1 << 8) Or b0)
						Else
							'Negative
							Temp16 = CShort(((b1 << 8) Or b0) - 65536)
						End If
						Buffer.Data(i).Data(j) = Temp16 / 32767
						DataCount += 2
					Next
				Next
			End With
		End If
		
		Name_ = FileName
		BaseFrame_ = GetCirculationBase()
		'Close
		LoaderStream.Close
		Loader.Close
		Loader.Dispose
		LoaderStream.Dispose
	End Sub
	
End Class
