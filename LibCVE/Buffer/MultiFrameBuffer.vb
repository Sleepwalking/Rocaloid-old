'    存储一堆连续语音帧。
'    Stores a bunch of consecutive frames.
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
Public Class MultiFrameBuffer	
	Inherits Buffer
	Public Data() As FrameBuffer
	Public Sub New()
		Length = 0
		Name = ""		
	End Sub
	Public Sub New(ByVal _Length As Integer, ByVal Optional _Name As String = "")
		Length = _Length
		Name = _Name
		ReDim Data(Length)
	End Sub
	Public Sub New(ByVal _Length As Integer, ByVal _InnerLength As Integer, ByVal Optional _Name As String ="")
		Length = _Length
		Name = _Name
		ReDim Data(Length)
		Dim i As Integer
		For i = 0 To Length
			Data(i) = New FrameBuffer(_InnerLength)
		Next
	End Sub
End Class
