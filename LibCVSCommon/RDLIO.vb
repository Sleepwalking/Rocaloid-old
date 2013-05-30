'    RDL（Rocaloid描述性语言）的基本输入输出支持
'    RDLIO is the basic support for the input/output of Rocaloid Descriptive Language(RDL)
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

Public Module StringUtil
	Public Const INFINITY = 99999
	Public Function Trim(ByRef _String As String) As String
		If _String = "" Then
			Return ""
		End If
		Dim i As Integer = 1
		While i <= _String.Length AndAlso (Mid(_String, i, 1) = " " OrElse Mid(_String, i, 1) = "	")
			i += 1
		End While
		_String = Right(_String, _String.Length - i + 1)
		If _String = "" Then
			Return ""
		End If
		i = _String.Length
		While i >= 0 AndAlso (Mid(_String, i, 1) = " " OrElse Mid(_String, i, 1) = "	")
			i -= 1
		End While
		_String = Left(_String, i)
		Return _String
	End Function
	Public Function SliceTo(ByRef _String As String, ByRef LineBuff() As String) As Integer
		Dim i As Integer
		Dim c As Integer = 0
		Dim wordbuff As String = ""
		i = 1
		_String = Trim(_String)
		For i = i To _String.Length
			If Mid(_String, i ,1) <> " " AndAlso Mid(_String, i, 1) <> "	" Then
				wordbuff += Mid(_String, i, 1)
			Else
				'Skip All Spaces And Tabs
				While Mid(_String, i, 1) = " " OrElse Mid(_String, i, 1) = "	"
					i += 1
				End While
				i -= 1
				LineBuff(c) = wordbuff
				wordbuff = ""
				c += 1
				If c = 200 Then
					c -= 1
					_String = Right(_String, _String.Length - i + 1)
					Return c
				End If
			End If
		Next
		_String = Right(_String, _String.Length - i + 1)
		LineBuff(c) = wordbuff
		Return c
	End Function
	Public Function TestIfIsDouble(ByVal _String As String) As Double
		Try
			Return CDbl(_String)
		Catch
			Throw New Exception(_String & " is not a number!")
		End Try
	End Function
	Public Function TestIfIsInt(ByVal _String As String) As Integer
		Try
			Return CInt(_String)
		Catch
			Throw New Exception(_String & " is not a number!")
		End Try
	End Function
	Public Function TestIfIsDoubleAndPositive(ByVal _String As String) As Double
		Dim dbl As Double
		Try
			dbl = CDbl(_String)
			If dbl > 0 Then
				Return CDbl(_String)
			End If
		Catch
			Throw New Exception(_String & " is not a number!")
		End Try
		Throw New Exception(_String & " is not a positive number!")
		Return -INFINITY
	End Function
	Public Function TestIfIsIntAndPositive(ByVal _String As String) As Integer
		Dim int As Integer
		Try
			int = CInt(_String)
			If int > 0 Then
				Return CInt(_String)
			End If
		Catch
			Throw New Exception(_String & " is not a number!")
		End Try
		Throw New Exception(_String & " is not a positive number!")
		Return -INFINITY
	End Function
	Public Function TestIfIsDoubleNotNegative(ByVal _String As String) As Double
		Dim dbl As Double
		Try
			dbl = CDbl(_String)
			If dbl >= 0 Then
				Return CDbl(_String)
			End If
		Catch
			Throw New Exception(_String & " is not a number!")
		End Try
		Throw New Exception(_String & " is not a positive number or 0!")
		Return -INFINITY
	End Function
	Public Function TestIfIsIntNotNegative(ByVal _String As String) As Integer
		Dim int As Integer
		Try
			int = CInt(_String)
			If int >= 0 Then
				Return CInt(_String)
			End If
		Catch
			Throw New Exception(_String & " is not a number!")
		End Try
		Throw New Exception(_String & " is not a positive number or 0!")
		Return -INFINITY
	End Function
	Public Function TestIfIsBoolean(ByVal _String As String) As Boolean
		Dim str As String = _String.ToLower()
		If str = "true" Then
			Return True
		ElseIf str = "false" Then
			Return False
		Else
			Throw New Exception(_String & " is not a boolean. Only true or false are allowed.")
		End If
		Return False
	End Function
	Public Function TestIfIsPresetedEnvelope(ByVal _String As String) As Integer
		Select Case _String
			Case "ADSR"
				Return 0
			Case Else
				Throw New Exception(_String & " is not a valid PresetedEnvelope!")
		End Select
		Return -INFINITY
	End Function
End Module
Public Class RDLReader
	Private Reader As StreamReader
	Private LineBuffer(200) As String
	Private LineBufferQ As Integer
	Private LineBufferPointer As Integer
	Private StrStore As String
	Public Sub New(ByVal File As String)
		Reader = New StreamReader(File)
		LineBufferQ = 0
		LineBufferPointer = 0
	End Sub
	Public Function Read() As String
		If LineBufferPointer = LineBufferQ Then
			If StrStore = "" Then
				'Read Next Line
				StrStore = Reader.ReadLine()
			End If
			'Read up to 200 words.
			LineBufferQ = SliceTo(StrStore, LineBuffer) + 1
			LineBufferPointer = 1
			Return LineBuffer(0)
		Else
			LineBufferPointer += 1
			Return LineBuffer(LineBufferPointer - 1)
		End If
	End Function
	Public Sub Close()
		Reader.Close()
	End Sub
End Class
Public Class RDLWriter
	Public Shared NewLineValid As Boolean = True
	Private Writer As StreamWriter
	Private Indent As String
	Private LastWrite As Integer '0:Empty 1:NewLine 2:Word
	Public Sub New(ByVal File As String)
		Writer = New StreamWriter(File)
		Indent = ""
		LastWrite = 0
	End Sub
	Public Overloads Sub WriteWord(ByRef _String As String)
		Select Case LastWrite
			Case 0
				Writer.Write(_String)
			Case 1
				Writer.Write(Indent & _String)
			Case 2
				Writer.Write(" " & _String)
		End Select
		LastWrite = 2
	End Sub
	Public Overloads Sub WriteWord(ByVal _Integer As Integer)
		WriteWord(CStr(_Integer))
	End Sub
	Public Overloads Sub WriteWord(ByVal _Double As Double)
		WriteWord(CStr(_Double))
	End Sub
	Public Overloads Sub WriteWord(ByVal _Boolean As Boolean)
		WriteWord(CStr(_Boolean))
	End Sub
	Public Sub WritePresetedEnvelope(ByVal _Envelopes As Integer)
		Select Case _Envelopes
			Case Envelopes.ADSR
				WriteWord("ADSR")
		End Select
	End Sub
	Public Sub NewLine()
		If NewLineValid Then
			Writer.WriteLine()
			LastWrite = 1
		End If
	End Sub
	Public Sub IndentPush()
		If NewLineValid Then
			Indent += "	"
		End If
	End Sub
	Public Sub IndentPop()
		If NewLineValid Then
			Indent = Left(Indent, Indent.Length - 1)
		End If
	End Sub
	Public Sub Close()
		Writer.Close()
	End Sub
End Class
