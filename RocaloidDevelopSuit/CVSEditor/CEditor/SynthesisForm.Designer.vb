'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Partial Class SynthesisForm
	Inherits System.Windows.Forms.Form
	
	''' <summary>
	''' Designer variable used to keep track of non-visual components.
	''' </summary>
	Private components As System.ComponentModel.IContainer
	
	''' <summary>
	''' Disposes resources used by the form.
	''' </summary>
	''' <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
	Protected Overrides Sub Dispose(ByVal disposing As Boolean)
		If disposing Then
			If components IsNot Nothing Then
				components.Dispose()
			End If
		End If
		MyBase.Dispose(disposing)
	End Sub
	
	''' <summary>
	''' This method is required for Windows Forms designer support.
	''' Do not change the method contents inside the source code editor. The Forms designer might
	''' not be able to load this method if it was changed manually.
	''' </summary>
	Private Sub InitializeComponent()
		Me.components = New System.ComponentModel.Container()
		Me.Synthesis_Bar = New System.Windows.Forms.ProgressBar()
		Me.Synthesis_State = New System.Windows.Forms.Label()
		Me.UpdateTimer = New System.Windows.Forms.Timer(Me.components)
		Me.SuspendLayout
		'
		'Synthesis_Bar
		'
		Me.Synthesis_Bar.Location = New System.Drawing.Point(12, 12)
		Me.Synthesis_Bar.Name = "Synthesis_Bar"
		Me.Synthesis_Bar.Size = New System.Drawing.Size(303, 21)
		Me.Synthesis_Bar.Step = 1
		Me.Synthesis_Bar.Style = System.Windows.Forms.ProgressBarStyle.Continuous
		Me.Synthesis_Bar.TabIndex = 0
		'
		'Synthesis_State
		'
		Me.Synthesis_State.Location = New System.Drawing.Point(12, 45)
		Me.Synthesis_State.Name = "Synthesis_State"
		Me.Synthesis_State.Size = New System.Drawing.Size(259, 18)
		Me.Synthesis_State.TabIndex = 1
		Me.Synthesis_State.Text = " S / S"
		'
		'UpdateTimer
		'
		Me.UpdateTimer.Enabled = true
		AddHandler Me.UpdateTimer.Tick, AddressOf Me.UpdateTimerTick
		'
		'SynthesisForm
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 12!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(327, 74)
		Me.Controls.Add(Me.Synthesis_State)
		Me.Controls.Add(Me.Synthesis_Bar)
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow
		Me.Name = "SynthesisForm"
		Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
		Me.Text = "CVE Synthesis"
		Me.TopMost = true
		Me.ResumeLayout(false)
	End Sub
	Public UpdateTimer As System.Windows.Forms.Timer
	Private Synthesis_State As System.Windows.Forms.Label
	Private Synthesis_Bar As System.Windows.Forms.ProgressBar
End Class
