'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Imports CVSCommon
Public Structure NoteSet
	Public StartPos As Double
	Public Duration As Double
	Public ReadOnly Property EndPos As Double
		Get 
			Return StartPos + Duration
		End Get
	End Property
End Structure
Public Partial Class NoteBox
	Protected NoteList() As NoteSet
	Protected LNoteNum As Integer
	Protected RNoteNum As Integer
	Public Overridable Sub Redraw()
		SyncLock Me
		GraphicControl.Clear(Color.White)
		If Not Loaded Then Exit Sub
		GraphicControl.DrawLine(New Pen(Color.Black), 0, CInt(Height / 2), Width, CInt(Height / 2))
		DrawBars()
		If SelectBarEnabled Then
			DrawSelectBar()
		End If
		End SyncLock
		Invalidate()
	End Sub
	Public Overridable Sub DrawSelectBar()
		If LBound < SelectBar AndAlso SelectBar < RBound Then
			Dim SelectBarPen As New Pen(Color.Green)
			Dim x As Integer = AbsoluteToRelative(SelectBar)
			GraphicControl.DrawLine(SelectBarPen, x, 0, x, 64)
			GraphicControl.DrawLine(SelectBarPen, x + 1, 0, x + 1, 64)
		End If
	End Sub
	Public Overridable Sub DrawBars()
		Dim i As Integer
		Dim StartTime As Double, EndTime As Double
		Dim xbound As Integer
		Dim xdur As Integer
		Dim y As Integer
		Dim UpperBrush As New SolidBrush(Color.LightBlue)
		Dim LowerBrush As New SolidBrush(Color.LightBlue)
		Dim SelectedBrush As New SolidBrush(Color.Pink)
		Dim TextBrush As New SolidBrush(Color.Black)
		Dim CurrentBrush As SolidBrush
		Dim CurrentPen As New Pen(Color.DimGray)
		
		LNoteNum = -1
		RNoteNum = -1
		
		With InnerCVS
			For i = 0 To .SegmentListQ
				StartTime = .SegmentList(i).StartTime
				EndTime = GetEndTime(.SegmentList(i))
				If EndTime > LBound And StartTime < RBound Then
					If LNoteNum = -1 Then LNoteNum = i
					RNoteNum = i
					
					xbound = AbsoluteToRelative(StartTime)
					xdur = CInt((EndTime - StartTime) / Duration * Width)
					
					NoteList(i).StartPos = xbound
					NoteList(i).Duration = xdur
					
					If Arrangement(i) Then
						'Lower
						y = 33
						CurrentBrush = LowerBrush
					Else
						'Upper
						y = 0
						CurrentBrush = UpperBrush
					End If
					
					If i = DragNoteNum Then
						CurrentBrush = SelectedBrush
					End If
					
					GraphicControl.FillRectangle(CurrentBrush, xbound, y, xdur, 31)
					GraphicControl.DrawRectangle(CurrentPen, xbound, y, xdur, 31)
					GraphicControl.DrawString("#" & CStr(i), New Font("Arial", 12), TextBrush, xbound + 3, y + 7)
				End If
			Next
		End With
	End Sub
	
	#Region "PositionCalculation"
	Public Function AbsoluteToRelative(ByVal Absolute As Double) As Integer
		Return CInt((Absolute - LBound) / Duration * Width)
	End Function
	Public Function RelativeToAbsolute(ByVal Relative As Double) As Double
		Return Relative / Width * Duration + LBound
	End Function
	#End Region
End Class
