'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Partial Class MainForm
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
		Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(MainForm))
		Me.MainMenuStrip = New System.Windows.Forms.MenuStrip()
		Me.fileToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
		Me.MainToolStrip = New System.Windows.Forms.ToolStrip()
		Me.SynthesisAndPlay = New System.Windows.Forms.ToolStripButton()
		Me.SynthesisStop = New System.Windows.Forms.ToolStripButton()
		Me.toolStripSeparator1 = New System.Windows.Forms.ToolStripSeparator()
		Me.SaveCVS = New System.Windows.Forms.ToolStripButton()
		Me.MainNoteBox = New CEditor.NoteBox()
		Me.NBoxScrollBar = New System.Windows.Forms.HScrollBar()
		Me.VerticalScale = New System.Windows.Forms.TrackBar()
		Me.MainSBox = New CEditor.SingleNoteBox()
		Me.SBoxScrollBar = New System.Windows.Forms.HScrollBar()
		Me.BarUpdateTimer = New System.Windows.Forms.Timer(Me.components)
		Me.MainMenuStrip.SuspendLayout
		Me.MainToolStrip.SuspendLayout
		CType(Me.MainNoteBox,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.VerticalScale,System.ComponentModel.ISupportInitialize).BeginInit
		CType(Me.MainSBox,System.ComponentModel.ISupportInitialize).BeginInit
		Me.SuspendLayout
		'
		'MainMenuStrip
		'
		Me.MainMenuStrip.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.fileToolStripMenuItem})
		Me.MainMenuStrip.Location = New System.Drawing.Point(0, 0)
		Me.MainMenuStrip.Name = "MainMenuStrip"
		Me.MainMenuStrip.Size = New System.Drawing.Size(731, 24)
		Me.MainMenuStrip.TabIndex = 0
		Me.MainMenuStrip.Text = "menuStrip1"
		'
		'fileToolStripMenuItem
		'
		Me.fileToolStripMenuItem.Name = "fileToolStripMenuItem"
		Me.fileToolStripMenuItem.Size = New System.Drawing.Size(35, 20)
		Me.fileToolStripMenuItem.Text = "File"
		'
		'MainToolStrip
		'
		Me.MainToolStrip.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.SynthesisAndPlay, Me.SynthesisStop, Me.toolStripSeparator1, Me.SaveCVS})
		Me.MainToolStrip.Location = New System.Drawing.Point(0, 24)
		Me.MainToolStrip.Name = "MainToolStrip"
		Me.MainToolStrip.Size = New System.Drawing.Size(731, 25)
		Me.MainToolStrip.TabIndex = 1
		Me.MainToolStrip.Text = "toolStrip1"
		'
		'SynthesisAndPlay
		'
		Me.SynthesisAndPlay.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.SynthesisAndPlay.Image = CType(resources.GetObject("SynthesisAndPlay.Image"),System.Drawing.Image)
		Me.SynthesisAndPlay.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.SynthesisAndPlay.Name = "SynthesisAndPlay"
		Me.SynthesisAndPlay.Size = New System.Drawing.Size(23, 22)
		Me.SynthesisAndPlay.Text = "Play"
		AddHandler Me.SynthesisAndPlay.Click, AddressOf Me.SynthesisAndPlayClick
		'
		'SynthesisStop
		'
		Me.SynthesisStop.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.SynthesisStop.Image = CType(resources.GetObject("SynthesisStop.Image"),System.Drawing.Image)
		Me.SynthesisStop.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.SynthesisStop.Name = "SynthesisStop"
		Me.SynthesisStop.Size = New System.Drawing.Size(23, 22)
		Me.SynthesisStop.Text = "Stop"
		AddHandler Me.SynthesisStop.Click, AddressOf Me.SynthesisStopClick
		'
		'toolStripSeparator1
		'
		Me.toolStripSeparator1.Name = "toolStripSeparator1"
		Me.toolStripSeparator1.Size = New System.Drawing.Size(6, 25)
		'
		'SaveCVS
		'
		Me.SaveCVS.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.SaveCVS.Image = CType(resources.GetObject("SaveCVS.Image"),System.Drawing.Image)
		Me.SaveCVS.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.SaveCVS.Name = "SaveCVS"
		Me.SaveCVS.Size = New System.Drawing.Size(23, 22)
		Me.SaveCVS.Text = "Save"
		AddHandler Me.SaveCVS.Click, AddressOf Me.SaveCVSClick
		'
		'MainNoteBox
		'
		Me.MainNoteBox.Location = New System.Drawing.Point(0, 52)
		Me.MainNoteBox.Name = "MainNoteBox"
		Me.MainNoteBox.ScrollBar = Nothing
		Me.MainNoteBox.Size = New System.Drawing.Size(731, 65)
		Me.MainNoteBox.SNoteBox = Nothing
		Me.MainNoteBox.TabIndex = 2
		Me.MainNoteBox.TabStop = false
		'
		'NBoxScrollBar
		'
		Me.NBoxScrollBar.Location = New System.Drawing.Point(0, 119)
		Me.NBoxScrollBar.Name = "NBoxScrollBar"
		Me.NBoxScrollBar.Size = New System.Drawing.Size(731, 21)
		Me.NBoxScrollBar.TabIndex = 3
		'
		'VerticalScale
		'
		Me.VerticalScale.LargeChange = 20
		Me.VerticalScale.Location = New System.Drawing.Point(598, 143)
		Me.VerticalScale.Maximum = 50
		Me.VerticalScale.Minimum = 1
		Me.VerticalScale.Name = "VerticalScale"
		Me.VerticalScale.Size = New System.Drawing.Size(133, 42)
		Me.VerticalScale.TabIndex = 4
		Me.VerticalScale.TickFrequency = 5
		Me.VerticalScale.Value = 6
		AddHandler Me.VerticalScale.Scroll, AddressOf Me.VerticalScaleScroll
		'
		'MainSBox
		'
		Me.MainSBox.Location = New System.Drawing.Point(0, 180)
		Me.MainSBox.Name = "MainSBox"
		Me.MainSBox.ScrollBar = Nothing
		Me.MainSBox.Size = New System.Drawing.Size(731, 32)
		Me.MainSBox.SNoteBox = Nothing
		Me.MainSBox.TabIndex = 5
		Me.MainSBox.TabStop = false
		'
		'SBoxScrollBar
		'
		Me.SBoxScrollBar.Location = New System.Drawing.Point(0, 215)
		Me.SBoxScrollBar.Name = "SBoxScrollBar"
		Me.SBoxScrollBar.Size = New System.Drawing.Size(731, 21)
		Me.SBoxScrollBar.TabIndex = 6
		'
		'BarUpdateTimer
		'
		Me.BarUpdateTimer.Enabled = true
		AddHandler Me.BarUpdateTimer.Tick, AddressOf Me.Timer1Tick
		'
		'MainForm
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 12!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(731, 288)
		Me.Controls.Add(Me.SBoxScrollBar)
		Me.Controls.Add(Me.MainSBox)
		Me.Controls.Add(Me.VerticalScale)
		Me.Controls.Add(Me.NBoxScrollBar)
		Me.Controls.Add(Me.MainNoteBox)
		Me.Controls.Add(Me.MainToolStrip)
		Me.Controls.Add(Me.MainMenuStrip)
		Me.MainMenuStrip = Me.MainMenuStrip
		Me.Name = "MainForm"
		Me.Text = "CEditor"
		AddHandler Load, AddressOf Me.MainFormLoad
		AddHandler Resize, AddressOf Me.MainFormResize
		Me.MainMenuStrip.ResumeLayout(false)
		Me.MainMenuStrip.PerformLayout
		Me.MainToolStrip.ResumeLayout(false)
		Me.MainToolStrip.PerformLayout
		CType(Me.MainNoteBox,System.ComponentModel.ISupportInitialize).EndInit
		CType(Me.VerticalScale,System.ComponentModel.ISupportInitialize).EndInit
		CType(Me.MainSBox,System.ComponentModel.ISupportInitialize).EndInit
		Me.ResumeLayout(false)
		Me.PerformLayout
	End Sub
	Private BarUpdateTimer As System.Windows.Forms.Timer
	Private SaveCVS As System.Windows.Forms.ToolStripButton
	Private toolStripSeparator1 As System.Windows.Forms.ToolStripSeparator
	Private SynthesisStop As System.Windows.Forms.ToolStripButton
	Private SynthesisAndPlay As System.Windows.Forms.ToolStripButton
	Private SBoxScrollBar As System.Windows.Forms.HScrollBar
	Private MainSBox As CEditor.SingleNoteBox
	Private VerticalScale As System.Windows.Forms.TrackBar
	Friend NBoxScrollBar As System.Windows.Forms.HScrollBar
	Friend MainNoteBox As CEditor.NoteBox
	Private MainToolStrip As System.Windows.Forms.ToolStrip
	Private fileToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
	Private MainMenuStrip As System.Windows.Forms.MenuStrip
End Class
