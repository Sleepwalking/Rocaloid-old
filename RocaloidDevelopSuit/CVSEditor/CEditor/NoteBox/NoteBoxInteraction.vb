'    NoteBox的交互函数。
'    The interaction functions in NoteBox.
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

Public Partial Class NoteBox
	Protected MouseDownX As Integer
	Protected MouseDownOffset As Integer
	Protected MouseX As Integer
	Protected IsMouseDown As Boolean = False
	Protected IsDragging As Boolean = False
	Protected Friend DragNoteNum As Integer
	
	Public Overridable Sub NBoxMouseDown(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseDown
		If Not EditEnabled Then Exit Sub
		MouseDownX = e.X
		IsMouseDown = True
		Dim i As Integer
		If LNoteNum < 0 Then Exit Sub
		For i = LNoteNum To RNoteNum
			If NoteList(i).StartPos < e.X And NoteList(i).EndPos > e.X Then
				If (Arrangement(i) And e.Y > 32) Or (Not Arrangement(i) And e.Y < 32) Then
					DragNoteNum = i
					IsDragging = True
					MouseDownOffset = MouseDownX - AbsoluteToRelative(InnerCVS.SegmentList(i).StartTime)
					SNoteBox.LoadSegment(InnerCVS.SegmentList(i))
					SNoteBox.Redraw()
					Redraw()
					RaiseEvent Selected(DragNoteNum)
					Exit For
				End If
			End If
		Next
	End Sub
	Public Overridable Sub NBoxMouseMove(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseMove
		Focus()
		If Not EditEnabled Then Exit Sub
		MouseX = e.X
		If IsMouseDown Then
			'Drag
			If IsDragging Then
				InnerCVS.SegmentList(DragNoteNum).StartTime = RelativeToAbsolute(MouseX - MouseDownOffset)
				If InnerCVS.SegmentList(DragNoteNum).StartTime < 0 Then
					InnerCVS.SegmentList(DragNoteNum).StartTime = 0
				End If
				Redraw()
			End If
		End If
	End Sub
	Public Overridable Sub NBoxMouseUp(ByVal sender As Object, ByVal e As MouseEventArgs) Handles Me.MouseUp
		If Not EditEnabled Then Exit Sub
		IsMouseDown = False
		IsDragging = False
		MouseX = e.X
		SelectBar = RelativeToAbsolute(MouseX)
		ScrollBar.Maximum = CInt(GetCVSLength(InnerCVS) * 100)
		Redraw()
	End Sub
End Class
