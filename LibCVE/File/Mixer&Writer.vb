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
Friend Class MixerWriterEffector
	Private Shared Writer As BinaryWriter
	Private Shared FileName As String
	Public Shared Sub SetFileOutput(ByVal File As String)
		Try
			Writer = New BinaryWriter(New FileStream(File, FileMode.Create))
		Catch
			CreateLog("ERROR. " & File & " is occupied by another program.")
			Exit Sub
		End Try
		'Write Wave Head
		Dim i As Integer
		For i = 0 To WaveHeadLength - 1
			Writer.Write(WaveHead(i))
		Next
		FileName = File
	End Sub
	Public Shared Overloads Sub Write(ByVal _Double As Double)
		Try
			Writer.Write(CShort(_Double * 32767))
		Catch
			CreateLog("ERROR. File occupied by another program.")
		End Try
	End Sub
	Public Shared Overloads Sub Write(ByVal _Short As Short)
		Try
			Writer.Write(_Short)
		Catch
			CreateLog("ERROR. File occupied by another program.")
		End Try
	End Sub
	Public Shared Overloads Sub Write(ByVal Wave As WaveBuffer, ByVal Start As Integer, ByVal Dest As Integer)
		Dim i As Integer
		If Dest > Wave.Pointer Then
			For i = Start To Wave.Pointer - 1
				Writer.Write(CShort(Wave.Data(i) * 32767))
				'Write(Wave.Data(i))
			Next
			WriteBlank(Dest - Wave.Pointer)
		Else
			For i = Start To Dest - 1
				Writer.Write(CShort(Wave.Data(i) * 32767))
				'Write(Wave.Data(i))
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
	Public Shared Sub FinishWave()
		Dim BinaryLength As Integer
		Dim i As Integer
		Writer.Close()
		Writer.Dispose()
		
		'Get the length of wav file.
		Dim LenGet As FileStream = New FileStream(FileName, FileMode.Open)
		BinaryLength = CInt(LenGet.Length)
		LenGet.Close()
		LenGet.Dispose()
		
		Writer = New BinaryWriter(New FileStream(FileName, FileMode.OpenOrCreate))
		'Rewrite header.
		For i = 0 To 3
			Writer.Write(WaveHead(i))
		Next
		Writer.Write(BinaryLength - 8)
		'Rewrite head.
		For i = 8 To 39
			Writer.Write(WaveHead(i))
		Next
		Writer.Write(BinaryLength - 44)
		
		Writer.Close()
		Writer.Dispose()
	End Sub
End Class
