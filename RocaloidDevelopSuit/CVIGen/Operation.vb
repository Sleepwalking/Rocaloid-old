'    和UI关联的操作
'    Actions corresponding to UI.
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
Public Class Operation
	Public Shared Reader As BinaryReader
	Public Shared Writer As StreamWriter
	
	Public Shared Sub Reader_Open(ByVal Path As String)
		Reader = New BinaryReader(New FileStream(Path, FileMode.Open))
	End Sub
	
	Public Shared Sub Reader_Close()
		Reader.Close()
	End Sub
	
	Public Shared Function GetSymbolFullName(ByVal Str As String) As String
		Dim pos As Integer = InStrRev(Str, "\")
		Return Mid(Str, pos + 1, Str.Length - pos - 4)
	End Function
	
	Public Shared Function GetPitch(ByVal Symbol As String) As String
		Dim pos As Integer = InStr(Symbol, "_")
		Return Right(Symbol, Symbol.Length - pos)
	End Function
	
	Public Shared Function GetSymbol(ByVal Symbol As String) As String
		Dim pos As Integer = InStr(Symbol, "_")
		Return Left(Symbol, pos - 1)
	End Function
	
	Public Shared Sub Start(ByVal Collect As ListBox.ObjectCollection, ByVal Path As String, ByVal Indent As Integer)
		Dim i As Integer
		Dim str As String, indentstr As String
		Dim SymbolFullName As String
		Dim VOT As Integer, hasVOT As Boolean
		Dim counter As Integer = 0
		Dim Dict As RSCCommon.CDTCommon.CDT = New RSCCommon.CDTCommon.CDT()
		Dim PhoneSet As RSCCommon.CDTCommon.PhoneSet
		Dim VOTLimit As Integer
		Dim PreShrink As Integer
		Dim Ratio As Double
		Dim TargetVOT As Integer
		
		RSCCommon.CDTCommon.Reader_Open("HMCHNDICT.cdt")
		RSCCommon.CDTCommon.CDT_Read(Dict)
		RSCCommon.CDTCommon.Reader_Close()
		
		Writer = New StreamWriter(Path)
		indentstr = ""
		For i = 0 To Indent - 1
			indentstr += "	"
		Next
		For i = 0 To Collect.Count - 1
			str = Collect.Item(i)
			Reader_Open(str)
			SymbolFullName = GetSymbolFullName(str)
			Reader.BaseStream.Position = 4
			hasVOT = False
			PhoneSet = RSCCommon.CDTCommon.GetPhoneSet(Dict, SymbolFullName)
			
			If Reader.ReadInt16() = 2 Then
				If Reader.ReadByte() = 255 Then
					VOT = Reader.ReadInt32()
					hasVOT = True
				End If
			Else
				If Reader.ReadByte() = 255 Then
					VOT = Reader.ReadInt32() - 2500
					hasVOT = True
				End If				
			End If
			
			If hasVOT Then
				If VOT < 0 Then VOT = 0
					counter += 1
					PreShrink = 0
					If PhoneSet.Type <> RSCCommon.CDTCommon.PhoneType.Vowel AndAlso VOT > 5000 Then
						VOTLimit = CInt(PhoneSet.DataPoint(0, 3) * 96000)
						Ratio = (VOT - 5000) / 4000
						If Ratio > 1 Then Ratio = 1
						If VOT > VOTLimit Then
							TargetVOT = CInt(VOTLimit * Ratio + VOT * (1 - Ratio))
							PreShrink = VOT - TargetVOT
							VOT = TargetVOT
						End If
					End If
					If PreShrink = 0 Then
						Writer.WriteLine(indentstr & _
							"DBSet	Pho " & GetSymbol(SymbolFullName) & _
							"	Pit " & GetPitch(SymbolFullName) & _
							"	VOT " & CStr(VOT) & "	End")
					Else
						Writer.WriteLine(indentstr & _
							"DBSet	Pho " & GetSymbol(SymbolFullName) & _
							"	Pit " & GetPitch(SymbolFullName) & _
							"	VOT " & CStr(VOT) & _
							"	PSnk " & CStr(PreShrink) & "	End")
					End If
			End If
			
			Reader_Close()
		Next
		Writer.WriteLine(counter)
		Writer.Close()
	End Sub
	
End Class
