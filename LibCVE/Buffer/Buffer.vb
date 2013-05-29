'    这是FrameBuffer、MultiFrameBuffer、WaveBuffer类的基类，本身不做任何事。
'    This class is the base class for FrameBuffer, MultiFrameBuffer, and WaveBuffer. It does nothing itself.
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
Friend MustInherit Class Buffer
	Public Length As Integer
	Public Name As String
	Public Sub New()
		Length=0
		Name=""
	End Sub
	Public Sub New(ByVal _Name As String)
		Length=0
		Name=_Name
	End Sub
End Class
