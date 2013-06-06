'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Public Partial Class SynthesisForm
	Public Sub New()
		' The Me.InitializeComponent call is required for Windows Forms designer support.
		Me.InitializeComponent()
		
		'
		' TODO : Add constructor code after InitializeComponents
		'
	End Sub
	
	Sub UpdateTimerTick(sender As Object, e As EventArgs)
		Synthesis_Bar.Value = Math.Min(100, CInt(100 * (CybervoiceEngine.MixerWriterEffector.WriterCounter / CybervoiceEngine.MixerWriterEffector.TotalCount) + 0.5))
		Synthesis_State.Text = CSng(CybervoiceEngine.MixerWriterEffector.WriterCounter / 96000) & " sec / " & CSng(CybervoiceEngine.MixerWriterEffector.TotalCount / 96000) & " sec."
		If Synthesis_Bar.Value >= 100 Then
			Me.Hide()
		End If
	End Sub
End Class
