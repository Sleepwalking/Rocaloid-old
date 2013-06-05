'    提供波形数据的输出和混音。
'    Provides outputing and mixing of wave data.
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
Imports CybervoiceEngine
Imports System.Runtime.InteropServices

Public Enum SynthesisState
	PreSynthesis = 0
	RTSynthesis = 1
End Enum

Public Class MixerWriterEffector
	Private Shared Writer As BinaryWriter
	Private Shared FileName As String
	Public Shared SynthesisMode As SynthesisState
	Public Shared SynthesisDestCounter As Integer
	
	Public Shared Sub SetMemoryOutput(ByRef Buffer() As Byte)
		Try
			Writer = New BinaryWriter(New MemoryStream(Buffer))
		Catch
			CreateLog("ERROR. Cannot access to memory.")
			Exit Sub
		End Try
		'Write Wave Head
		Dim i As Integer
		For i = 0 To WaveHeadLength - 1
			Writer.Write(WaveHead(i))
		Next
	End Sub
	Public Shared Overloads Sub Write(ByVal _Double As Double)
		If SynthesisMode = SynthesisState.RTSynthesis Then
			Dim TimePassed As Integer = CInt((DateTime.Now - Operation.SoundStartTime).TotalMilliSeconds)
			While Operation.SoundCounter > TimePassed / 1000 * 96000 + 300000
				TimePassed = CInt((DateTime.Now - Operation.SoundStartTime).TotalMilliSeconds)
				Threading.Thread.Sleep(5)
			End While
			Marshal.WriteInt16(Operation.SoundBuffer, (Operation.SoundCounter Mod Operation.SoundLength) * 2 + 44, CShort(_Double * 32767))
			Operation.SoundCounter += 1
		Else
			If SynthesisDestCounter <= 0 Then
				Threading.Thread.Sleep(1)
			End If
			SynthesisDestCounter -= 1
		End If
	End Sub
	Public Shared Overloads Sub Write(ByVal _Short As Short)
		If SynthesisMode = SynthesisState.RTSynthesis Then
			Dim TimePassed As Integer = CInt((DateTime.Now - Operation.SoundStartTime).TotalMilliSeconds)
			While Operation.SoundCounter > TimePassed / 1000 * 96000 + 300000
				TimePassed = CInt((DateTime.Now - Operation.SoundStartTime).TotalMilliSeconds)
				Threading.Thread.Sleep(5)
			End While
			Marshal.WriteInt16(Operation.SoundBuffer, (Operation.SoundCounter Mod Operation.SoundLength) * 2 + 44, _Short)
			Operation.SoundCounter += 1	
		Else
			If SynthesisDestCounter <= 0 Then
				Threading.Thread.Sleep(1)
			End If
			SynthesisDestCounter -= 1
		End If
	End Sub
	Public Shared Overloads Sub Write(ByVal Wave As WaveBuffer, ByVal Start As Integer, ByVal Dest As Integer)
		Dim i As Integer
		If Dest > Wave.Pointer Then
			For i = Start To Wave.Pointer - 1
				Write(Wave.Data(i))
			Next
			WriteBlank(Dest - Wave.Pointer)
		Else
			For i = Start To Dest - 1
				Write(Wave.Data(i))
			Next
		End If
	End Sub
	Public Shared Sub MixAndWrite(ByVal Wave1 As WaveBuffer, ByVal Wave2 As WaveBuffer, _
								  ByVal S1 As Integer, ByVal S2 As Integer, ByVal Duration As Integer)
		Dim i As Integer
		For i = 0 To Duration - 1
			Write(Wave1.Data(S1 + i) + Wave2.Data(S2 + i))
		Next
	End Sub
	Public Shared Sub WriteBlank(ByVal Duration As Integer)
		Dim i As Integer
		For i = 0 To Duration - 1
			Write(0)
		Next
	End Sub
	Public Shared Sub WriteWaveHeader(ByVal Buffer As IntPtr, ByVal Length As Integer)
		Dim i As Integer
		For i = 0 To 43
			Marshal.WriteByte(Buffer, i, WaveHead(i))
		Next
		Marshal.WriteInt32(Buffer, 4, Length * 2 + 44 - 8)
		Marshal.WriteInt32(Buffer, 40, Length * 2)
	End Sub
End Class
