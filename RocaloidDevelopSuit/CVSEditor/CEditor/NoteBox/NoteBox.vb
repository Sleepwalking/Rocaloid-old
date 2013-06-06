'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Public Partial Class NoteBox
	Inherits SecurePictureBox
	Public LBound As Double
	Public Duration As Double
	Public ReadOnly Property RBound As Double
		Get
			Return LBound + Duration
		End Get
	End Property
	Public WithEvents ScrollBar As HScrollBar
	Public WithEvents SNoteBox As SingleNoteBox
	Public SelectBar As Double
	Public SelectBarEnabled As Boolean
	Public EditEnabled As Boolean
	Private InnerCVS As CVSCommon.CVS
	Private Arrangement() As Boolean
	Protected Loaded As Boolean
	Public Event Selected(ByVal SegmentIndex As Integer)
	
	Public Sub New()
		MyBase.New()
		LBound = 0
		Duration = 3
		Loaded = False
		SelectBarEnabled = True
		EditEnabled = True
	End Sub
	
	Public Shadows Sub Scale(ByVal Duration_ As Double)
		Dim CenterPos As Double = LBound + Duration / 2
		Duration = Duration_
		LBound = CenterPos - Duration / 2
		If LBound < 0 Then LBound = 0
		If RBound > ScrollBar.Maximum / 100 Then
			Duration = ScrollBar.Maximum / 100 - LBound
		End If
		ScrollBar.LargeChange = CInt(Duration * 100)
		ScrollBar.Value = CInt(LBound * 100)
		If ScrollBar.Value + ScrollBar.LargeChange > ScrollBar.Maximum Then
			ScrollBar.Value = ScrollBar.Maximum - ScrollBar.LargeChange
		End If
	End Sub
	
	Public Sub LoadCVS(ByRef CVS As CVSCommon.CVS)
		InnerCVS = CVS
		ScrollBar.Maximum = CInt(GetCVSLength(CVS) * 100)
		ScrollBar.LargeChange = CInt(Duration * 100)
		ReDim Arrangement(CVS.SegmentListQ)
		Arrange(InnerCVS, Arrangement)
		ReDim NoteList(CVS.SegmentListQ)
		Loaded = True
		SNoteBox.InnerSegment = CVS.SegmentList(0)
	End Sub
	
	Public Shadows Sub Init()
		MyBase.Init()
	End Sub
	
	Private Sub SNoteBoxUpdate() Handles SNoteBox.SegmentUpdate
		Redraw()
	End Sub
	
	Private Sub NoteBoxUpdate() Handles SNoteBox.ParentNoteBoxUpdate
		ScrollBar.Maximum = CInt(GetCVSLength(InnerCVS) * 100)
		Redraw()
	End Sub
	
	Public Sub ScrollBarDrag(ByVal sender As Object, ByVal e As EventArgs) Handles ScrollBar.Scroll
		LBound = ScrollBar.Value / 100
		Redraw()
	End Sub
	
	Public Shadows Sub Resize(ByVal Width_ As Integer)
		Me.Width = Width_
		ScrollBar.Width = Width
		MyBase.Resize(Width, Height)
		Redraw()
	End Sub
End Class
