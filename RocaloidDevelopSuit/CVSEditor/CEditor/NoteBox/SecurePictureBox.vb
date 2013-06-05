'    一个扩展的，线程安全的PictureBox
'    A extended picture box which is thread-safe.
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

Public Class SecurePictureBox
	Inherits PictureBox
	Public GraphicControl As Graphics
	
	Protected Overrides Sub OnPaint(pe As PaintEventArgs)
		SyncLock Me
			MyBase.OnPaint(pe)
		End SyncLock
	End Sub
	
	Public Sub Init()
		Dim _Bitmap As Bitmap = New Bitmap(Size.Width, Size.Height)
		Image = _Bitmap
		GraphicControl = Graphics.FromImage(Me.Image)
		Invalidate()
	End Sub
	
	Public Shadows Sub Resize(ByVal _x As Integer, ByVal _y As Integer)
		Width = _x
		Height = _y
		Init()
	End Sub
	
	Public Sub Clear(ByVal _Color As Color)
		GraphicControl.Clear(_Color)
		Invalidate()
	End Sub
End Class
