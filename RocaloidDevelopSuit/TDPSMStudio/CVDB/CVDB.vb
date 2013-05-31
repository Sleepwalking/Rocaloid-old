'    CVDB 0.6数据读写器
'    Reader and writer for CVDB 0.6.
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
Public Class CVDB
	Public Header As CVDBHeader
	Public ChunkLength() As UInt16
	Public DataQ As Integer
	Public Data() As Double
	
	Public Sub Save(ByVal File As String)
		Dim writer As BinaryWriter = New BinaryWriter(New FileStream(File, FileMode.Create))
		Dim i As Integer
		With writer
			.Write(CByte(Asc("C")))
			.Write(CByte(Asc("V")))
			.Write(CByte(Asc("D")))
			.Write(CByte(Asc("B")))
			.Write(Header.Version)
			If Header.Consonant Then
				.Write(CByte(255))
			Else
				.Write(CByte(254))
			End If
			.Write(Header.StartPosition)
			.Write(Header.PeriodStartPosition)
			.Write(CByte(255))
			.Write(Header.ChunkNumber)
			For i = 0 To Header.ChunkNumber
				.Write(ChunkLength(i))
			Next
			For i = 0 To DataQ
				.Write(CShort(Data(i) * 32767))
			Next
		End With
		writer.Close()
	End Sub
	
	Public Sub Load(ByVal File As String)
		Dim reader As BinaryReader = New BinaryReader(New FileStream(File, FileMode.Open))
		Dim i As Integer
		Dim Head(3) As Byte
		With reader
			Head = .ReadBytes(4)
			If Not (Head(0) = Asc("C") And Head(1) = Asc("V") And Head(2) = Asc("D") And Head(3) = Asc("B")) Then
				Throw New Exception("Invalid file format!")
			End If
			Header.Version = .ReadUInt16()
			If Header.Version <> 2 Then
				Throw New Exception("Unsupported Version!")
			End If
			If .ReadByte() = 255 Then
				Header.Consonant = True
			Else
				Header.Consonant = False
			End If
			Header.StartPosition = .ReadInt32()
			Header.PeriodStartPosition = .ReadInt32()
			.ReadByte()
			Header.ChunkNumber = .ReadUInt16()
			ReDim ChunkLength(Header.ChunkNumber + 1)
			DataQ = 0
			For i = 0 To Header.ChunkNumber
				ChunkLength(i) = .ReadUInt16()
				DataQ += ChunkLength(i)
			Next
			ReDim Data(DataQ + 1)
			Try
				For i = 0 To DataQ + 1
					Data(i) = .ReadInt16() / 32767
				Next
			Catch
			End Try
			DataQ = i - 1
		End With
		reader.Close()
	End Sub
	
	Public Sub OutputToWave(ByRef Wave As WaveBuffer)
		Dim i As Integer
		For i = 0 To DataQ
			Wave.Data(i) = Data(i)
		Next
		Wave.Pointer = DataQ
	End Sub
End Class

Public Structure CVDBHeader
	Public Version As UInt16
	Public Consonant As Boolean
	Public StartPosition As Integer
	Public PeriodStartPosition As Integer
	Public ChunkNumber As UInt16
End Structure