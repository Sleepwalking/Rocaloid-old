'    提供波形数据的输出和混音，与时间同步。
'    Provides outputing and mixing of wave data, synchronize with time.
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
	Public Shared ReadOnly WaveHead() As Byte =
	{
		&H52,&H49,&H46,&H46,&H24,&H10,&H1F,&H00, _
		&H57,&H41,&H56,&H45,&H66,&H6D,&H74,&H20, _
		&H10,&H00,&H00,&H00,&H01,&H00,&H01,&H00, _
		&H44,&HAC,&H00,&H00,&H00,&HEE,&H02,&H00, _
		&H02,&H00,&H10,&H00,&H64,&H61,&H74,&H61, _
		&H00,&H10,&H1F,&H00
	}
	Private Shared Writer As BinaryWriter
	Private Shared FileName As String
	Public Shared SynthesisMode As SynthesisState
	Public Shared LastWrite As Short
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
		Write(CShort(_Double * 32767))
	End Sub
	Public Shared Overloads Sub Write(ByVal _Short As Short)
		If SynthesisMode = SynthesisState.RTSynthesis Then
			Dim TimePassed As Integer = CInt((DateTime.Now - Operation.SoundStartTime).TotalMilliSeconds)
			While Operation.SoundCounter > TimePassed / 1000 * 44100 + 150000
				Threading.Thread.Sleep(5)
				'CONSOLE
				My.Forms.Console.Send("  MixerWriterEffector -> Write : Waiting...")
				My.Forms.Console.Send("    SoundCounter = " & Operation.SoundCounter)
				My.Forms.Console.Send("    TimePassed = " & TimePassed / 1000 * 44100)
				TimePassed = CInt((DateTime.Now - Operation.SoundStartTime).TotalMilliSeconds)
			End While
			If Operation.SoundCounter / 44100 * 96000 < Operation.SoundCounter96 Then
				Marshal.WriteInt16(Operation.SoundBuffer, (Operation.SoundCounter Mod Operation.SoundLength) * 2 + 44, CShort((_Short + LastWrite) / 2))
				LastWrite = _Short
				Operation.SoundCounter += 1
			End If
			Operation.SoundCounter96 += 1
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
