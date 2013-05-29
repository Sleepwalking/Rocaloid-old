'    wav波形缓冲器。可以直接输出到文件。目前不能读取wav。
'    Buffer for .wav files. Ready to output. Cannot read or input .wav yet.
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
Friend Class WaveBuffer
	Inherits Buffer
	Public Data() As Double
	Public Pointer As Integer
	Public Sub New()
		Length=0
		Name=""
		Pointer =0
	End Sub
	Public Sub New(ByVal _Length As Integer, ByVal Optional _Name As String = "")
		Length=_Length
		Name=_Name
		Pointer =0
		ReDim Data(Length)
		#If DebugLevel > 0 Then
			CreateLog("Wave Buffer Constructed, Length:" & Length & " Name:" & Name)
		#End If
	End Sub
	Public Sub New(ByVal _Length As Double, ByVal Optional _Name As String = "")
		Length=CInt(_Length * SampleRate)
		Name=_Name
		Pointer =0
		ReDim Data(Length)
		#If DebugLevel > 0 Then
			CreateLog("Wave Buffer Constructed, Length:" & Length & " Name:" & Name)
		#End If
	End Sub
	Public Overloads Sub Write(ByVal _Data As Double)
		Data(Pointer) = _Data
		Pointer +=1
	End Sub
	Public Overloads Sub Write(ByVal Frame As FrameBuffer)
		Dim i As Integer
		For i = 0 To Frame.Length
			Data(Pointer) = Frame.Data(i)
			Pointer += 1
		Next
	End Sub
	Public Sub OutputToBinary(ByVal FileName As String)
		Dim Output As BinaryWriter
		Try
			Output = New BinaryWriter(New FileStream(FileName, FileMode.Create))
		Catch
			CreateLog("ERROR. " & FileName & " is occupied by another program.")
			Exit Sub
		End Try
		Dim i As Integer
		For i = 0 To Pointer
			Output.Write(CShort(Data(i) * 32767))
		Next
		Output.Close
	End Sub
	Public Sub OutputToWave(ByVal FileName As String)
		Dim Output As BinaryWriter
		Try
			Output = New BinaryWriter(New FileStream(FileName, FileMode.Create))
		Catch
			CreateLog("ERROR. " & FileName & " is occupied by another program.")
			Exit Sub
		End Try
		'Write Wave Head
		Dim i As Integer
		Dim BinaryLength As Integer
		For i = 0 To WaveHeadLength - 1
			Output.Write(WaveHead(i))
		Next
		'Write Data
		For i = 0 To Pointer
			Output.Write(CShort(Data(i) * 32767))
		Next
		'Rewrite Wave Head
		BinaryLength = WaveHeadLength + Pointer * 2 + 2
		Output.Close
		Output = New BinaryWriter(New FileStream(FileName, FileMode.OpenOrCreate))
		For i = 0 To 3
			Output.Write(WaveHead(i))
		Next
		Output.Write(BinaryLength - 8)
		For i = 8 To 39
			Output.Write(WaveHead(i))
		Next
		Output.Write(BinaryLength - 44)
		Output.Close
	End Sub
End Class
