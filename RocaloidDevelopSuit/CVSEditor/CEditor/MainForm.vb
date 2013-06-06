'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Public Partial Class MainForm
	Public Sub New()
		' The Me.InitializeComponent call is required for Windows Forms designer support.
		Me.InitializeComponent()
		'
		' TODO : Add constructor code after InitializeComponents
		'
	End Sub
	
	Public Shared Sub UpdateScrollBar(ByVal Position As Integer)
		MainForm.NBoxScrollBar.Value = Position
	End Sub
	
	Sub MainFormLoad(sender As Object, e As EventArgs)
		Operation.LoadCVS("x.cvs")
		MainNoteBox.ScrollBar = NBoxScrollBar
		MainNoteBox.SNoteBox = MainSBox
		MainNoteBox.LoadCVS(Operation.MainCVS)
		
		MainNoteBox.Init()
		MainNoteBox.Resize(Width - 8)
		
		MainSBox.ScrollBar = SBoxScrollBar
		MainSBox.Init()
		
		Operation.SynthesizerInit()
		Operation.SoundInit()
	End Sub
	
	Sub MainFormResize(sender As Object, e As EventArgs)
		MainNoteBox.Resize(Width - 8)
		MainSBox.Resize(Width - 8)
		VerticalScale.Left = Width - 141
	End Sub
	
	Sub VerticalScaleScroll(sender As Object, e As EventArgs)
		MainNoteBox.Scale(VerticalScale.Value / 2)
		MainNoteBox.Redraw()
	End Sub
	
	Sub SaveCVSClick(sender As Object, e As EventArgs)
		Operation.SaveCVS("output.cvs")
	End Sub
	
	Sub SynthesisAndPlayClick(sender As Object, e As EventArgs)
		Operation.StartSynthesis(MainNoteBox.SelectBar)
	End Sub
	
	Sub SynthesisStopClick(sender As Object, e As EventArgs)
		Operation.StopSynthesis()
	End Sub
	
	Sub Timer1Tick(sender As Object, e As EventArgs)
		Dim CurrentNoteNum As Integer
		If Operation.SoundIsPlaying Then
			'This seems to be a bug of ScrollBar, that you need to change the value twice, the first time should be a lower level, and then it will be updated.
			NBoxScrollBar.Value = 0
			NBoxScrollBar.Value = CInt(Operation.MainNoteBox.LBound * 100)
			CurrentNoteNum = CVSOperation.GetSegment(Operation.MainCVS, MainNoteBox.SelectBar)
			If CurrentNoteNum <> MainNoteBox.DragNoteNum Then
				MainNoteBox.DragNoteNum = CurrentNoteNum
				MainNoteBox.SNoteBox.LoadSegment(Operation.MainCVS.SegmentList(CurrentNoteNum))
				MainNoteBox.SNoteBox.Redraw()
			End If
		End If
	End Sub
	
	Sub ConsoleToolStripMenuItemClick(sender As Object, e As EventArgs)
		My.Forms.Console.Show()
	End Sub
End Class
