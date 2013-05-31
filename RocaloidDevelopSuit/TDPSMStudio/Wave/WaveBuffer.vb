'    加载和存储波形数据
'    Loads and stores wave data.
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

Imports System.IO
Public Class WaveBuffer
	Const SampleRate = 96000
	Public Data() As Double
	Public Size As Integer
	Public Pointer As Integer
	Public Offset As Integer
	Shared Lock As Object = New Object()
	
	Public Sub New(ByVal _Size As Integer)
		If _Size > 0 Then
			Size = _Size
			Pointer = 0
			Offset = 0
			ReDim Data(Size)
		Else
			Throw New Exception("Size of buffer is too small!")
		End If
	End Sub
	
	Public Sub New(ByVal _Size As Double)
		Me.New(CInt(_Size * SampleRate))
	End Sub
	
	Public Function GetMax(ByVal _From As Integer, ByVal _To As Integer) As Double
		Dim i As Integer
		Dim max As Double = -999
		If _From < 0 Then _From = 0
		If _To < 0 Then _To = 0
		For i = _From To _To
			If Data(i) > max Then max = Data(i)
		Next
		Return max
	End Function
	
	Public Function GetMin(ByVal _From As Integer, ByVal _To As Integer) As Double
		Dim i As Integer
		Dim min As Double = 999
		If _From < 0 Then _From = 0
		If _To < 0 Then _To = 0
		For i = _From To _To
			If Data(i) < min Then min = Data(i)
		Next
		Return min
	End Function
	
	Public Sub Save(ByVal File As String)
		SyncLock Lock
			MixerWriterEffector.SetFileOutput(File)
			Dim i As Integer
			For i = 0 To Pointer
				MixerWriterEffector.Write(Data(i))
			Next
			MixerWriterEffector.FinishWave()
		End SyncLock
	End Sub
	
	Public Sub Load(ByVal Address As String)
		Dim Loader As BinaryReader
		Dim i As Integer
		Try
			Loader = New BinaryReader(New FileStream(Address, FileMode.Open))
		Catch
			Exit Sub
		End Try
		For i = 1 To 24
			Loader.ReadByte
		Next
		If Loader.ReadInt32 <> 96000 Then
			MsgBox("Does not support 96000HZ wave file!", MsgBoxStyle.Critical, "TDPSMStudio")
			Loader.Close
			Exit Sub
		End If
		For i = 1 To 64
			Loader.ReadByte
		Next
		Pointer = 0
		Try
			For i = 0 To Size
				Data(i) = CDbl(Loader.ReadInt16 / 32767)
			Next
		Catch
		End Try
		Pointer = i
		For i = i To Size
			Data(i) = 0
		Next
		Loader.Close
	End Sub
	
	Public Overloads Sub CopyTo(ByRef Wave As WaveBuffer)
		CopyTo(Wave, 0, Pointer)
	End Sub
	
	Public Overloads Sub CopyTo(ByRef Wave As WaveBuffer, ByVal CpyFrom As Integer, ByVal CpyTo As Integer)
		Dim i As Integer
		For i = CpyFrom To CpyTo
			Wave.Data(i - CpyFrom) = Data(i)
		Next
		Wave.Pointer = CpyTo - CpyFrom
	End Sub
End Class
