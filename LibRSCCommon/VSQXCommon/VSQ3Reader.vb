'    这其实是个局部的xml读取器
'    Actually this is a partial xml reader.
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
Public Class VSQ3Reader
	Public Buffer As String
	Private Reader As StreamReader
	Public Pointer As Integer
	
	Public Sub New(ByVal File As String)
		Reader = New StreamReader(File)
		Buffer = Reader.ReadToEnd()
		Pointer = 1
	End Sub
	
	Public Sub Close()
		Reader.Close()
	End Sub
	
	Public Sub ReadUntil(ByVal _String As String)
		Pointer = InStr(Pointer, Buffer, _String, CompareMethod.Text)
	End Sub
	
	Public Function FindNextPos(ByVal _String As String) As Integer
		Return InStr(Pointer, Buffer, _String, CompareMethod.Text)
	End Function
	
	Public Function FindLastPos(ByVal _String As String, ByVal Before As Integer) As Integer
		Dim i As Integer
		While Before > 0
			For i = 0 To _String.Length - 1
				If GetChar(Buffer, Before - i) <> GetChar(_String, _String.Length - i) Then
					GoTo NotCompatible
				End If
			Next
			Return Before - _String.Length + 1
			NotCompatible:
			Before -= 1
		End While
		Return 0
	End Function
	
	Public Function ReadNextValue(ByVal AttributeName As String) As String
		Dim AttributeStart As Integer = InStr(Pointer, Buffer, "<" & AttributeName & ">", CompareMethod.Text)
		Dim ValueStart As Integer = AttributeStart + AttributeName.Length + 2
		Dim ValueEnd As Integer = InStr(Pointer, Buffer, "</" & AttributeName & ">", CompareMethod.Text)
		Pointer = ValueEnd
		Return Mid(Buffer, ValueStart, ValueEnd - ValueStart)
	End Function
	
	Public Function ReadCDATA(ByVal CDATA As String) As String
		Return Mid(CDATA, 10, CDATA.Length - 12)
	End Function
End Class
