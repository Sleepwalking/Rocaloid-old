'    这个类仅仅是为了存贮一个语音帧的数据。
'    This class simply stores data of a single frame.
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
Friend Class FrameBuffer
	Inherits Buffer
	Public Data() As Double
	Public Sub New()
		Length=0
		Name=""
	End Sub
	Public Sub New(ByVal _Length As Integer, ByVal Optional _Name As String = "")
		Length=_Length
		Name=_Name
		ReDim Data(Length)
	End Sub
End Class
