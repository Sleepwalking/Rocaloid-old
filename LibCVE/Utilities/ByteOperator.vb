'    字节级的类型转换。
'    Type changes in byte scale.
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
Public Module ByteOperator
	Public Function ByteToString(ByVal _Byte() As Byte, ByVal _Length As Integer) As String
		Dim i As Integer, Str As String
		Str = ""
		For i = 0 To _Length - 1
			Str += Chr(_Byte(i))
		Next
		Return Str
	End Function
	Public Function ByteToInt16(ByVal ByteArray() As Byte, ByVal position As Integer) As Int16
		Dim b0 As Byte, b1 As Byte
		b0 = ByteArray(position)
		b1 = ByteArray(position + 1)
		If b1 < 128 Then
			'Positive
			Return CShort(b1 * 256 + b0)
		Else
			'Negative
			Return CShort(b1 * 256 + b0 - 65536)
		End If
	End Function
End Module
