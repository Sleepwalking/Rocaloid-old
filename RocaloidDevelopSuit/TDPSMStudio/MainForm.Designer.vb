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
		Me.menuStrip1 = New System.Windows.Forms.MenuStrip()
		Me.viewToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
		Me.preprocessToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
		Me.analyzerToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
		Me.modeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
		Me.waveEditorToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
		Me.wavCbvToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
		Me.cbvQualityControlToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
		Me.Button_About = New System.Windows.Forms.ToolStripMenuItem()
		Me.toolStrip1 = New System.Windows.Forms.ToolStrip()
		Me.toolStripLabel1 = New System.Windows.Forms.ToolStripLabel()
		Me.Textbox_Symbol = New System.Windows.Forms.ToolStripTextBox()
		Me.toolStripLabel2 = New System.Windows.Forms.ToolStripLabel()
		Me.Textbox_Pitch = New System.Windows.Forms.ToolStripTextBox()
		Me.toolStripSeparator1 = New System.Windows.Forms.ToolStripSeparator()
		Me.Button_Prev = New System.Windows.Forms.ToolStripButton()
		Me.Button_Open = New System.Windows.Forms.ToolStripButton()
		Me.Button_Next = New System.Windows.Forms.ToolStripButton()
		Me.toolStripSeparator2 = New System.Windows.Forms.ToolStripSeparator()
		Me.Button_Analyze = New System.Windows.Forms.ToolStripButton()
		Me.Button_AnalyzeAll = New System.Windows.Forms.ToolStripButton()
		Me.toolStripSeparator3 = New System.Windows.Forms.ToolStripSeparator()
		Me.Button_ViewAll = New System.Windows.Forms.ToolStripButton()
		Me.Button_StopView = New System.Windows.Forms.ToolStripButton()
		Me.toolStripSeparator8 = New System.Windows.Forms.ToolStripSeparator()
		Me.Button_AdjustToAll = New System.Windows.Forms.ToolStripButton()
		Me.MainContainer = New System.Windows.Forms.SplitContainer()
		Me.groupBox1 = New System.Windows.Forms.GroupBox()
		Me.CheckBox_Balance = New System.Windows.Forms.CheckBox()
		Me.label4 = New System.Windows.Forms.Label()
		Me.TextBox_DataLength = New System.Windows.Forms.TextBox()
		Me.label2 = New System.Windows.Forms.Label()
		Me.CheckBox_Consonant = New System.Windows.Forms.CheckBox()
		Me.label3 = New System.Windows.Forms.Label()
		Me.ProgressBar_Completeness = New System.Windows.Forms.ProgressBar()
		Me.label1 = New System.Windows.Forms.Label()
		Me.AmplitudeController = New System.Windows.Forms.TrackBar()
		Me.statusStrip1 = New System.Windows.Forms.StatusStrip()
		Me.Status = New System.Windows.Forms.ToolStripStatusLabel()
		Me.timer1 = New System.Windows.Forms.Timer(Me.components)
		Me.EditorToolStrip = New System.Windows.Forms.ToolStrip()
		Me.Tool_Play = New System.Windows.Forms.ToolStripButton()
		Me.Tool_Stop = New System.Windows.Forms.ToolStripButton()
		Me.toolStripSeparator4 = New System.Windows.Forms.ToolStripSeparator()
		Me.Tool_Copy = New System.Windows.Forms.ToolStripButton()
		Me.toolStripSeparator5 = New System.Windows.Forms.ToolStripSeparator()
		Me.Tool_Cut = New System.Windows.Forms.ToolStripButton()
		Me.Tool_Mix = New System.Windows.Forms.ToolStripButton()
		Me.toolStripSeparator6 = New System.Windows.Forms.ToolStripSeparator()
		Me.Tool_ChangeVolume = New System.Windows.Forms.ToolStripButton()
		Me.Tool_Smoothen = New System.Windows.Forms.ToolStripButton()
		Me.Tool_Normalize = New System.Windows.Forms.ToolStripButton()
		Me.Tool_Shrink = New System.Windows.Forms.ToolStripButton()
		Me.toolStripSeparator7 = New System.Windows.Forms.ToolStripSeparator()
		Me.Tool_Silence = New System.Windows.Forms.ToolStripButton()
		Me.Tool_FadeIn = New System.Windows.Forms.ToolStripButton()
		Me.Tool_Weaken = New System.Windows.Forms.ToolStripButton()
		Me.Tool_Adjust = New System.Windows.Forms.ToolStripButton()
		Me.Strip_WeakenSettings = New System.Windows.Forms.ContextMenuStrip(Me.components)
		Me.weakenStrengthToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
		Me.Weaken_09 = New System.Windows.Forms.ToolStripMenuItem()
		Me.Weaken_08 = New System.Windows.Forms.ToolStripMenuItem()
		Me.Weaken_07 = New System.Windows.Forms.ToolStripMenuItem()
		Me.Weaken_06 = New System.Windows.Forms.ToolStripMenuItem()
		Me.Weaken_05 = New System.Windows.Forms.ToolStripMenuItem()
		Me.Weaken_04 = New System.Windows.Forms.ToolStripMenuItem()
		Me.Weaken_03 = New System.Windows.Forms.ToolStripMenuItem()
		Me.Weaken_02 = New System.Windows.Forms.ToolStripMenuItem()
		Me.Weaken_01 = New System.Windows.Forms.ToolStripMenuItem()
		Me.Weaken_00 = New System.Windows.Forms.ToolStripMenuItem()
		Me.Strip_FadeLowSettings = New System.Windows.Forms.ContextMenuStrip(Me.components)
		Me.lowEndToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
		Me.FadeLow_05 = New System.Windows.Forms.ToolStripMenuItem()
		Me.FadeLow_04 = New System.Windows.Forms.ToolStripMenuItem()
		Me.FadeLow_03 = New System.Windows.Forms.ToolStripMenuItem()
		Me.FadeLow_02 = New System.Windows.Forms.ToolStripMenuItem()
		Me.FadeLow_01 = New System.Windows.Forms.ToolStripMenuItem()
		Me.FadeLow_00 = New System.Windows.Forms.ToolStripMenuItem()
		Me.Strip_WaveBoxClick = New System.Windows.Forms.ContextMenuStrip(Me.components)
		Me.WBox_SelectAll = New System.Windows.Forms.ToolStripMenuItem()
		Me.WBox_SelectView = New System.Windows.Forms.ToolStripMenuItem()
		Me.WBox_ViewAll = New System.Windows.Forms.ToolStripMenuItem()
		Me.menuStrip1.SuspendLayout
		Me.toolStrip1.SuspendLayout
		CType(Me.MainContainer,System.ComponentModel.ISupportInitialize).BeginInit
		Me.MainContainer.Panel2.SuspendLayout
		Me.MainContainer.SuspendLayout
		Me.groupBox1.SuspendLayout
		CType(Me.AmplitudeController,System.ComponentModel.ISupportInitialize).BeginInit
		Me.statusStrip1.SuspendLayout
		Me.EditorToolStrip.SuspendLayout
		Me.Strip_WeakenSettings.SuspendLayout
		Me.Strip_FadeLowSettings.SuspendLayout
		Me.Strip_WaveBoxClick.SuspendLayout
		Me.SuspendLayout
		'
		'menuStrip1
		'
		Me.menuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.viewToolStripMenuItem, Me.modeToolStripMenuItem, Me.Button_About})
		Me.menuStrip1.Location = New System.Drawing.Point(0, 0)
		Me.menuStrip1.Name = "menuStrip1"
		Me.menuStrip1.Size = New System.Drawing.Size(713, 24)
		Me.menuStrip1.TabIndex = 0
		Me.menuStrip1.Text = "menuStrip1"
		'
		'viewToolStripMenuItem
		'
		Me.viewToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.preprocessToolStripMenuItem, Me.analyzerToolStripMenuItem})
		Me.viewToolStripMenuItem.Name = "viewToolStripMenuItem"
		Me.viewToolStripMenuItem.Size = New System.Drawing.Size(58, 20)
		Me.viewToolStripMenuItem.Text = "Settings"
		'
		'preprocessToolStripMenuItem
		'
		Me.preprocessToolStripMenuItem.Name = "preprocessToolStripMenuItem"
		Me.preprocessToolStripMenuItem.Size = New System.Drawing.Size(127, 22)
		Me.preprocessToolStripMenuItem.Text = "Preprocess"
		AddHandler Me.preprocessToolStripMenuItem.Click, AddressOf Me.PreprocessToolStripMenuItemClick
		'
		'analyzerToolStripMenuItem
		'
		Me.analyzerToolStripMenuItem.Name = "analyzerToolStripMenuItem"
		Me.analyzerToolStripMenuItem.Size = New System.Drawing.Size(127, 22)
		Me.analyzerToolStripMenuItem.Text = "Analyzer"
		AddHandler Me.analyzerToolStripMenuItem.Click, AddressOf Me.AnalyzerToolStripMenuItemClick
		'
		'modeToolStripMenuItem
		'
		Me.modeToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.waveEditorToolStripMenuItem, Me.wavCbvToolStripMenuItem, Me.cbvQualityControlToolStripMenuItem})
		Me.modeToolStripMenuItem.Name = "modeToolStripMenuItem"
		Me.modeToolStripMenuItem.Size = New System.Drawing.Size(45, 20)
		Me.modeToolStripMenuItem.Text = "Mode"
		'
		'waveEditorToolStripMenuItem
		'
		Me.waveEditorToolStripMenuItem.Name = "waveEditorToolStripMenuItem"
		Me.waveEditorToolStripMenuItem.Size = New System.Drawing.Size(175, 22)
		Me.waveEditorToolStripMenuItem.Text = "Wave Editor"
		AddHandler Me.waveEditorToolStripMenuItem.Click, AddressOf Me.ModeSwitch_WavEditor
		'
		'wavCbvToolStripMenuItem
		'
		Me.wavCbvToolStripMenuItem.Checked = true
		Me.wavCbvToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked
		Me.wavCbvToolStripMenuItem.Name = "wavCbvToolStripMenuItem"
		Me.wavCbvToolStripMenuItem.Size = New System.Drawing.Size(175, 22)
		Me.wavCbvToolStripMenuItem.Text = "Wave Analyzer"
		AddHandler Me.wavCbvToolStripMenuItem.Click, AddressOf Me.ModeSwitch_WavAnalysis
		'
		'cbvQualityControlToolStripMenuItem
		'
		Me.cbvQualityControlToolStripMenuItem.Name = "cbvQualityControlToolStripMenuItem"
		Me.cbvQualityControlToolStripMenuItem.Size = New System.Drawing.Size(175, 22)
		Me.cbvQualityControlToolStripMenuItem.Text = "CVDB Quality Control"
		AddHandler Me.cbvQualityControlToolStripMenuItem.Click, AddressOf Me.ModeSwitch_CVQC
		'
		'Button_About
		'
		Me.Button_About.Name = "Button_About"
		Me.Button_About.Size = New System.Drawing.Size(48, 20)
		Me.Button_About.Text = "About"
		AddHandler Me.Button_About.Click, AddressOf Me.Button_AboutClick
		'
		'toolStrip1
		'
		Me.toolStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.toolStripLabel1, Me.Textbox_Symbol, Me.toolStripLabel2, Me.Textbox_Pitch, Me.toolStripSeparator1, Me.Button_Prev, Me.Button_Open, Me.Button_Next, Me.toolStripSeparator2, Me.Button_Analyze, Me.Button_AnalyzeAll, Me.toolStripSeparator3, Me.Button_ViewAll, Me.Button_StopView, Me.toolStripSeparator8, Me.Button_AdjustToAll})
		Me.toolStrip1.Location = New System.Drawing.Point(0, 24)
		Me.toolStrip1.Name = "toolStrip1"
		Me.toolStrip1.Size = New System.Drawing.Size(713, 25)
		Me.toolStrip1.TabIndex = 2
		Me.toolStrip1.Text = "toolStrip1"
		'
		'toolStripLabel1
		'
		Me.toolStripLabel1.Name = "toolStripLabel1"
		Me.toolStripLabel1.Size = New System.Drawing.Size(41, 22)
		Me.toolStripLabel1.Text = "Symbol"
		'
		'Textbox_Symbol
		'
		Me.Textbox_Symbol.Name = "Textbox_Symbol"
		Me.Textbox_Symbol.Size = New System.Drawing.Size(50, 25)
		'
		'toolStripLabel2
		'
		Me.toolStripLabel2.Name = "toolStripLabel2"
		Me.toolStripLabel2.Size = New System.Drawing.Size(30, 22)
		Me.toolStripLabel2.Text = "Pitch"
		'
		'Textbox_Pitch
		'
		Me.Textbox_Pitch.Name = "Textbox_Pitch"
		Me.Textbox_Pitch.Size = New System.Drawing.Size(50, 25)
		'
		'toolStripSeparator1
		'
		Me.toolStripSeparator1.Name = "toolStripSeparator1"
		Me.toolStripSeparator1.Size = New System.Drawing.Size(6, 25)
		'
		'Button_Prev
		'
		Me.Button_Prev.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
		Me.Button_Prev.Image = CType(resources.GetObject("Button_Prev.Image"),System.Drawing.Image)
		Me.Button_Prev.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Button_Prev.Name = "Button_Prev"
		Me.Button_Prev.Size = New System.Drawing.Size(45, 22)
		Me.Button_Prev.Text = "<-Prev"
		AddHandler Me.Button_Prev.Click, AddressOf Me.Button_Prev_Click
		'
		'Button_Open
		'
		Me.Button_Open.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
		Me.Button_Open.Image = CType(resources.GetObject("Button_Open.Image"),System.Drawing.Image)
		Me.Button_Open.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Button_Open.Name = "Button_Open"
		Me.Button_Open.Size = New System.Drawing.Size(37, 22)
		Me.Button_Open.Text = "Open"
		AddHandler Me.Button_Open.Click, AddressOf Me.Button_Open_Click
		'
		'Button_Next
		'
		Me.Button_Next.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
		Me.Button_Next.Image = CType(resources.GetObject("Button_Next.Image"),System.Drawing.Image)
		Me.Button_Next.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Button_Next.Name = "Button_Next"
		Me.Button_Next.Size = New System.Drawing.Size(46, 22)
		Me.Button_Next.Text = "Next->"
		AddHandler Me.Button_Next.Click, AddressOf Me.Button_Next_Click
		'
		'toolStripSeparator2
		'
		Me.toolStripSeparator2.Name = "toolStripSeparator2"
		Me.toolStripSeparator2.Size = New System.Drawing.Size(6, 25)
		'
		'Button_Analyze
		'
		Me.Button_Analyze.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
		Me.Button_Analyze.ForeColor = System.Drawing.Color.Red
		Me.Button_Analyze.Image = CType(resources.GetObject("Button_Analyze.Image"),System.Drawing.Image)
		Me.Button_Analyze.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Button_Analyze.Name = "Button_Analyze"
		Me.Button_Analyze.Size = New System.Drawing.Size(82, 22)
		Me.Button_Analyze.Text = "Analyze Frame"
		AddHandler Me.Button_Analyze.Click, AddressOf Me.Button_AddFrame_Click
		'
		'Button_AnalyzeAll
		'
		Me.Button_AnalyzeAll.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
		Me.Button_AnalyzeAll.ForeColor = System.Drawing.Color.Red
		Me.Button_AnalyzeAll.Image = CType(resources.GetObject("Button_AnalyzeAll.Image"),System.Drawing.Image)
		Me.Button_AnalyzeAll.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Button_AnalyzeAll.Name = "Button_AnalyzeAll"
		Me.Button_AnalyzeAll.Size = New System.Drawing.Size(111, 22)
		Me.Button_AnalyzeAll.Text = "Analyze Frame To All"
		AddHandler Me.Button_AnalyzeAll.Click, AddressOf Me.Button_AnalysisAll_Click
		'
		'toolStripSeparator3
		'
		Me.toolStripSeparator3.Name = "toolStripSeparator3"
		Me.toolStripSeparator3.Size = New System.Drawing.Size(6, 25)
		'
		'Button_ViewAll
		'
		Me.Button_ViewAll.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
		Me.Button_ViewAll.ForeColor = System.Drawing.Color.FromArgb(CType(CType(0,Byte),Integer), CType(CType(192,Byte),Integer), CType(CType(0,Byte),Integer))
		Me.Button_ViewAll.Image = CType(resources.GetObject("Button_ViewAll.Image"),System.Drawing.Image)
		Me.Button_ViewAll.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Button_ViewAll.Name = "Button_ViewAll"
		Me.Button_ViewAll.Size = New System.Drawing.Size(47, 22)
		Me.Button_ViewAll.Text = "View All"
		AddHandler Me.Button_ViewAll.Click, AddressOf Me.Button_ViewAllClick
		'
		'Button_StopView
		'
		Me.Button_StopView.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
		Me.Button_StopView.ForeColor = System.Drawing.Color.FromArgb(CType(CType(192,Byte),Integer), CType(CType(0,Byte),Integer), CType(CType(0,Byte),Integer))
		Me.Button_StopView.Image = CType(resources.GetObject("Button_StopView.Image"),System.Drawing.Image)
		Me.Button_StopView.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Button_StopView.Name = "Button_StopView"
		Me.Button_StopView.Size = New System.Drawing.Size(33, 22)
		Me.Button_StopView.Text = "Stop"
		AddHandler Me.Button_StopView.Click, AddressOf Me.Button_StopViewClick
		'
		'toolStripSeparator8
		'
		Me.toolStripSeparator8.Name = "toolStripSeparator8"
		Me.toolStripSeparator8.Size = New System.Drawing.Size(6, 25)
		'
		'Button_AdjustToAll
		'
		Me.Button_AdjustToAll.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
		Me.Button_AdjustToAll.Enabled = false
		Me.Button_AdjustToAll.ForeColor = System.Drawing.Color.Red
		Me.Button_AdjustToAll.Image = CType(resources.GetObject("Button_AdjustToAll.Image"),System.Drawing.Image)
		Me.Button_AdjustToAll.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Button_AdjustToAll.Name = "Button_AdjustToAll"
		Me.Button_AdjustToAll.Size = New System.Drawing.Size(71, 22)
		Me.Button_AdjustToAll.Text = "Adjust To All"
		AddHandler Me.Button_AdjustToAll.Click, AddressOf Me.Button_AdjustAll_Click
		'
		'MainContainer
		'
		Me.MainContainer.BackColor = System.Drawing.SystemColors.Control
		Me.MainContainer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
		Me.MainContainer.ForeColor = System.Drawing.SystemColors.ControlText
		Me.MainContainer.Location = New System.Drawing.Point(24, 49)
		Me.MainContainer.Name = "MainContainer"
		Me.MainContainer.Orientation = System.Windows.Forms.Orientation.Horizontal
		'
		'MainContainer.Panel2
		'
		Me.MainContainer.Panel2.Controls.Add(Me.groupBox1)
		Me.MainContainer.Panel2.Controls.Add(Me.label3)
		Me.MainContainer.Panel2.Controls.Add(Me.ProgressBar_Completeness)
		Me.MainContainer.Panel2.Controls.Add(Me.label1)
		Me.MainContainer.Panel2.Controls.Add(Me.AmplitudeController)
		Me.MainContainer.Size = New System.Drawing.Size(689, 349)
		Me.MainContainer.SplitterDistance = 233
		Me.MainContainer.TabIndex = 3
		'
		'groupBox1
		'
		Me.groupBox1.Controls.Add(Me.CheckBox_Balance)
		Me.groupBox1.Controls.Add(Me.label4)
		Me.groupBox1.Controls.Add(Me.TextBox_DataLength)
		Me.groupBox1.Controls.Add(Me.label2)
		Me.groupBox1.Controls.Add(Me.CheckBox_Consonant)
		Me.groupBox1.Location = New System.Drawing.Point(84, 48)
		Me.groupBox1.Name = "groupBox1"
		Me.groupBox1.Size = New System.Drawing.Size(598, 45)
		Me.groupBox1.TabIndex = 10
		Me.groupBox1.TabStop = false
		Me.groupBox1.Text = "Control"
		'
		'CheckBox_Balance
		'
		Me.CheckBox_Balance.Checked = true
		Me.CheckBox_Balance.CheckState = System.Windows.Forms.CheckState.Checked
		Me.CheckBox_Balance.Location = New System.Drawing.Point(299, 20)
		Me.CheckBox_Balance.Name = "CheckBox_Balance"
		Me.CheckBox_Balance.Size = New System.Drawing.Size(107, 17)
		Me.CheckBox_Balance.TabIndex = 4
		Me.CheckBox_Balance.Text = "Balance Wave"
		Me.CheckBox_Balance.UseVisualStyleBackColor = true
		AddHandler Me.CheckBox_Balance.CheckedChanged, AddressOf Me.CheckBox_BalanceCheckedChanged
		'
		'label4
		'
		Me.label4.Location = New System.Drawing.Point(265, 21)
		Me.label4.Name = "label4"
		Me.label4.Size = New System.Drawing.Size(60, 14)
		Me.label4.TabIndex = 3
		Me.label4.Text = "s."
		'
		'TextBox_DataLength
		'
		Me.TextBox_DataLength.Location = New System.Drawing.Point(191, 18)
		Me.TextBox_DataLength.Name = "TextBox_DataLength"
		Me.TextBox_DataLength.Size = New System.Drawing.Size(68, 21)
		Me.TextBox_DataLength.TabIndex = 2
		Me.TextBox_DataLength.Text = "0.5"
		Me.TextBox_DataLength.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'label2
		'
		Me.label2.Location = New System.Drawing.Point(107, 22)
		Me.label2.Name = "label2"
		Me.label2.Size = New System.Drawing.Size(82, 17)
		Me.label2.TabIndex = 1
		Me.label2.Text = "Data Length:"
		'
		'CheckBox_Consonant
		'
		Me.CheckBox_Consonant.Checked = true
		Me.CheckBox_Consonant.CheckState = System.Windows.Forms.CheckState.Checked
		Me.CheckBox_Consonant.Location = New System.Drawing.Point(11, 19)
		Me.CheckBox_Consonant.Name = "CheckBox_Consonant"
		Me.CheckBox_Consonant.Size = New System.Drawing.Size(95, 19)
		Me.CheckBox_Consonant.TabIndex = 0
		Me.CheckBox_Consonant.Text = "Consonant"
		Me.CheckBox_Consonant.UseVisualStyleBackColor = true
		'
		'label3
		'
		Me.label3.Location = New System.Drawing.Point(84, 5)
		Me.label3.Name = "label3"
		Me.label3.Size = New System.Drawing.Size(85, 17)
		Me.label3.TabIndex = 9
		Me.label3.Text = "Completeness"
		'
		'ProgressBar_Completeness
		'
		Me.ProgressBar_Completeness.Location = New System.Drawing.Point(84, 25)
		Me.ProgressBar_Completeness.Name = "ProgressBar_Completeness"
		Me.ProgressBar_Completeness.Size = New System.Drawing.Size(597, 17)
		Me.ProgressBar_Completeness.TabIndex = 8
		'
		'label1
		'
		Me.label1.Location = New System.Drawing.Point(4, 5)
		Me.label1.Name = "label1"
		Me.label1.Size = New System.Drawing.Size(85, 17)
		Me.label1.TabIndex = 5
		Me.label1.Text = "Amplitude"
		'
		'AmplitudeController
		'
		Me.AmplitudeController.Location = New System.Drawing.Point(11, 17)
		Me.AmplitudeController.Maximum = 200
		Me.AmplitudeController.Name = "AmplitudeController"
		Me.AmplitudeController.Orientation = System.Windows.Forms.Orientation.Vertical
		Me.AmplitudeController.Size = New System.Drawing.Size(42, 85)
		Me.AmplitudeController.TabIndex = 4
		Me.AmplitudeController.TickFrequency = 10
		Me.AmplitudeController.Value = 10
		AddHandler Me.AmplitudeController.Scroll, AddressOf Me.AmplitudeControllerScroll
		'
		'statusStrip1
		'
		Me.statusStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.Status})
		Me.statusStrip1.Location = New System.Drawing.Point(0, 398)
		Me.statusStrip1.Name = "statusStrip1"
		Me.statusStrip1.Size = New System.Drawing.Size(713, 22)
		Me.statusStrip1.TabIndex = 4
		Me.statusStrip1.Text = "statusStrip1"
		'
		'Status
		'
		Me.Status.Name = "Status"
		Me.Status.Size = New System.Drawing.Size(76, 17)
		Me.Status.Text = "No file loaded."
		'
		'timer1
		'
		Me.timer1.Enabled = true
		Me.timer1.Interval = 1000
		AddHandler Me.timer1.Tick, AddressOf Me.Timer1Tick
		'
		'EditorToolStrip
		'
		Me.EditorToolStrip.Dock = System.Windows.Forms.DockStyle.Left
		Me.EditorToolStrip.Enabled = false
		Me.EditorToolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden
		Me.EditorToolStrip.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.Tool_Play, Me.Tool_Stop, Me.toolStripSeparator4, Me.Tool_Copy, Me.toolStripSeparator5, Me.Tool_Cut, Me.Tool_Mix, Me.toolStripSeparator6, Me.Tool_ChangeVolume, Me.Tool_Smoothen, Me.Tool_Normalize, Me.Tool_Shrink, Me.toolStripSeparator7, Me.Tool_Silence, Me.Tool_FadeIn, Me.Tool_Weaken, Me.Tool_Adjust})
		Me.EditorToolStrip.Location = New System.Drawing.Point(0, 49)
		Me.EditorToolStrip.Name = "EditorToolStrip"
		Me.EditorToolStrip.Size = New System.Drawing.Size(24, 349)
		Me.EditorToolStrip.TabIndex = 5
		Me.EditorToolStrip.Text = "toolStrip2"
		'
		'Tool_Play
		'
		Me.Tool_Play.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_Play.Image = CType(resources.GetObject("Tool_Play.Image"),System.Drawing.Image)
		Me.Tool_Play.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_Play.Name = "Tool_Play"
		Me.Tool_Play.Size = New System.Drawing.Size(21, 20)
		Me.Tool_Play.Text = "Play"
		AddHandler Me.Tool_Play.Click, AddressOf Me.Tool_PlayClick
		'
		'Tool_Stop
		'
		Me.Tool_Stop.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_Stop.Image = CType(resources.GetObject("Tool_Stop.Image"),System.Drawing.Image)
		Me.Tool_Stop.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_Stop.Name = "Tool_Stop"
		Me.Tool_Stop.Size = New System.Drawing.Size(21, 20)
		Me.Tool_Stop.Text = "Stop"
		AddHandler Me.Tool_Stop.Click, AddressOf Me.Tool_StopClick
		'
		'toolStripSeparator4
		'
		Me.toolStripSeparator4.Name = "toolStripSeparator4"
		Me.toolStripSeparator4.Size = New System.Drawing.Size(21, 6)
		'
		'Tool_Copy
		'
		Me.Tool_Copy.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_Copy.Image = CType(resources.GetObject("Tool_Copy.Image"),System.Drawing.Image)
		Me.Tool_Copy.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_Copy.Name = "Tool_Copy"
		Me.Tool_Copy.Size = New System.Drawing.Size(21, 20)
		Me.Tool_Copy.Text = "Copy"
		AddHandler Me.Tool_Copy.Click, AddressOf Me.Tool_CopyClick
		'
		'toolStripSeparator5
		'
		Me.toolStripSeparator5.Name = "toolStripSeparator5"
		Me.toolStripSeparator5.Size = New System.Drawing.Size(21, 6)
		'
		'Tool_Cut
		'
		Me.Tool_Cut.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_Cut.Image = CType(resources.GetObject("Tool_Cut.Image"),System.Drawing.Image)
		Me.Tool_Cut.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_Cut.Name = "Tool_Cut"
		Me.Tool_Cut.Size = New System.Drawing.Size(21, 20)
		Me.Tool_Cut.Text = "Cut"
		AddHandler Me.Tool_Cut.Click, AddressOf Me.Tool_CutClick
		'
		'Tool_Mix
		'
		Me.Tool_Mix.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_Mix.Image = CType(resources.GetObject("Tool_Mix.Image"),System.Drawing.Image)
		Me.Tool_Mix.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_Mix.Name = "Tool_Mix"
		Me.Tool_Mix.Size = New System.Drawing.Size(21, 20)
		Me.Tool_Mix.Text = "Mix"
		AddHandler Me.Tool_Mix.Click, AddressOf Me.Tool_MixClick
		'
		'toolStripSeparator6
		'
		Me.toolStripSeparator6.Name = "toolStripSeparator6"
		Me.toolStripSeparator6.Size = New System.Drawing.Size(21, 6)
		'
		'Tool_ChangeVolume
		'
		Me.Tool_ChangeVolume.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_ChangeVolume.Image = CType(resources.GetObject("Tool_ChangeVolume.Image"),System.Drawing.Image)
		Me.Tool_ChangeVolume.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_ChangeVolume.Name = "Tool_ChangeVolume"
		Me.Tool_ChangeVolume.Size = New System.Drawing.Size(21, 20)
		Me.Tool_ChangeVolume.Text = "Change Volume"
		AddHandler Me.Tool_ChangeVolume.Click, AddressOf Me.Tool_ChangeVolumeClick
		'
		'Tool_Smoothen
		'
		Me.Tool_Smoothen.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_Smoothen.Image = CType(resources.GetObject("Tool_Smoothen.Image"),System.Drawing.Image)
		Me.Tool_Smoothen.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_Smoothen.Name = "Tool_Smoothen"
		Me.Tool_Smoothen.Size = New System.Drawing.Size(21, 20)
		Me.Tool_Smoothen.Text = "Smoothen"
		AddHandler Me.Tool_Smoothen.Click, AddressOf Me.Tool_SmoothenClick
		'
		'Tool_Normalize
		'
		Me.Tool_Normalize.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_Normalize.Image = CType(resources.GetObject("Tool_Normalize.Image"),System.Drawing.Image)
		Me.Tool_Normalize.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_Normalize.Name = "Tool_Normalize"
		Me.Tool_Normalize.Size = New System.Drawing.Size(21, 20)
		Me.Tool_Normalize.Text = "Normalize"
		AddHandler Me.Tool_Normalize.Click, AddressOf Me.Tool_NormalizeClick
		'
		'Tool_Shrink
		'
		Me.Tool_Shrink.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_Shrink.Image = CType(resources.GetObject("Tool_Shrink.Image"),System.Drawing.Image)
		Me.Tool_Shrink.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_Shrink.Name = "Tool_Shrink"
		Me.Tool_Shrink.Size = New System.Drawing.Size(21, 20)
		Me.Tool_Shrink.Text = "Tool_Shrink"
		AddHandler Me.Tool_Shrink.Click, AddressOf Me.Tool_ShrinkClick
		'
		'toolStripSeparator7
		'
		Me.toolStripSeparator7.Name = "toolStripSeparator7"
		Me.toolStripSeparator7.Size = New System.Drawing.Size(21, 6)
		'
		'Tool_Silence
		'
		Me.Tool_Silence.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_Silence.Image = CType(resources.GetObject("Tool_Silence.Image"),System.Drawing.Image)
		Me.Tool_Silence.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_Silence.Name = "Tool_Silence"
		Me.Tool_Silence.Size = New System.Drawing.Size(21, 20)
		Me.Tool_Silence.Text = "Silence"
		AddHandler Me.Tool_Silence.Click, AddressOf Me.Tool_SilenceClick
		'
		'Tool_FadeIn
		'
		Me.Tool_FadeIn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_FadeIn.Image = CType(resources.GetObject("Tool_FadeIn.Image"),System.Drawing.Image)
		Me.Tool_FadeIn.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_FadeIn.Name = "Tool_FadeIn"
		Me.Tool_FadeIn.Size = New System.Drawing.Size(21, 20)
		Me.Tool_FadeIn.Text = "Fade In"
		AddHandler Me.Tool_FadeIn.MouseUp, AddressOf Me.Tool_FadeInMouseUp
		'
		'Tool_Weaken
		'
		Me.Tool_Weaken.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_Weaken.Image = CType(resources.GetObject("Tool_Weaken.Image"),System.Drawing.Image)
		Me.Tool_Weaken.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_Weaken.Name = "Tool_Weaken"
		Me.Tool_Weaken.Size = New System.Drawing.Size(21, 20)
		Me.Tool_Weaken.Text = "Weaken"
		AddHandler Me.Tool_Weaken.MouseUp, AddressOf Me.Tool_WeakenMouseUp
		'
		'Tool_Adjust
		'
		Me.Tool_Adjust.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
		Me.Tool_Adjust.Image = CType(resources.GetObject("Tool_Adjust.Image"),System.Drawing.Image)
		Me.Tool_Adjust.ImageTransparentColor = System.Drawing.Color.Magenta
		Me.Tool_Adjust.Name = "Tool_Adjust"
		Me.Tool_Adjust.Size = New System.Drawing.Size(21, 20)
		Me.Tool_Adjust.Text = "Automatic Adjust"
		AddHandler Me.Tool_Adjust.Click, AddressOf Me.Tool_AdjustClick
		'
		'Strip_WeakenSettings
		'
		Me.Strip_WeakenSettings.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.weakenStrengthToolStripMenuItem, Me.Weaken_09, Me.Weaken_08, Me.Weaken_07, Me.Weaken_06, Me.Weaken_05, Me.Weaken_04, Me.Weaken_03, Me.Weaken_02, Me.Weaken_01, Me.Weaken_00})
		Me.Strip_WeakenSettings.Name = "Strip_WeakenSettings"
		Me.Strip_WeakenSettings.Size = New System.Drawing.Size(159, 246)
		'
		'weakenStrengthToolStripMenuItem
		'
		Me.weakenStrengthToolStripMenuItem.BackColor = System.Drawing.SystemColors.ActiveBorder
		Me.weakenStrengthToolStripMenuItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
		Me.weakenStrengthToolStripMenuItem.Enabled = false
		Me.weakenStrengthToolStripMenuItem.ForeColor = System.Drawing.SystemColors.ControlText
		Me.weakenStrengthToolStripMenuItem.ImageTransparentColor = System.Drawing.Color.White
		Me.weakenStrengthToolStripMenuItem.Name = "weakenStrengthToolStripMenuItem"
		Me.weakenStrengthToolStripMenuItem.Size = New System.Drawing.Size(158, 22)
		Me.weakenStrengthToolStripMenuItem.Text = "Weaken Strength"
		'
		'Weaken_09
		'
		Me.Weaken_09.Name = "Weaken_09"
		Me.Weaken_09.Size = New System.Drawing.Size(158, 22)
		Me.Weaken_09.Text = "0.9"
		AddHandler Me.Weaken_09.Click, AddressOf Me.Weaken_09Click
		'
		'Weaken_08
		'
		Me.Weaken_08.Name = "Weaken_08"
		Me.Weaken_08.Size = New System.Drawing.Size(158, 22)
		Me.Weaken_08.Text = "0.8"
		AddHandler Me.Weaken_08.Click, AddressOf Me.Weaken_08Click
		'
		'Weaken_07
		'
		Me.Weaken_07.Checked = true
		Me.Weaken_07.CheckState = System.Windows.Forms.CheckState.Checked
		Me.Weaken_07.Name = "Weaken_07"
		Me.Weaken_07.Size = New System.Drawing.Size(158, 22)
		Me.Weaken_07.Text = "0.7"
		AddHandler Me.Weaken_07.Click, AddressOf Me.Weaken_07Click
		'
		'Weaken_06
		'
		Me.Weaken_06.Name = "Weaken_06"
		Me.Weaken_06.Size = New System.Drawing.Size(158, 22)
		Me.Weaken_06.Text = "0.6"
		AddHandler Me.Weaken_06.Click, AddressOf Me.Weaken_06Click
		'
		'Weaken_05
		'
		Me.Weaken_05.Name = "Weaken_05"
		Me.Weaken_05.Size = New System.Drawing.Size(158, 22)
		Me.Weaken_05.Text = "0.5"
		AddHandler Me.Weaken_05.Click, AddressOf Me.Weaken_05Click
		'
		'Weaken_04
		'
		Me.Weaken_04.Name = "Weaken_04"
		Me.Weaken_04.Size = New System.Drawing.Size(158, 22)
		Me.Weaken_04.Text = "0.4"
		AddHandler Me.Weaken_04.Click, AddressOf Me.Weaken_04Click
		'
		'Weaken_03
		'
		Me.Weaken_03.Name = "Weaken_03"
		Me.Weaken_03.Size = New System.Drawing.Size(158, 22)
		Me.Weaken_03.Text = "0.3"
		AddHandler Me.Weaken_03.Click, AddressOf Me.Weaken_03Click
		'
		'Weaken_02
		'
		Me.Weaken_02.Name = "Weaken_02"
		Me.Weaken_02.Size = New System.Drawing.Size(158, 22)
		Me.Weaken_02.Text = "0.2"
		AddHandler Me.Weaken_02.Click, AddressOf Me.Weaken_02Click
		'
		'Weaken_01
		'
		Me.Weaken_01.Name = "Weaken_01"
		Me.Weaken_01.Size = New System.Drawing.Size(158, 22)
		Me.Weaken_01.Text = "0.1"
		AddHandler Me.Weaken_01.Click, AddressOf Me.Weaken_01Click
		'
		'Weaken_00
		'
		Me.Weaken_00.Name = "Weaken_00"
		Me.Weaken_00.Size = New System.Drawing.Size(158, 22)
		Me.Weaken_00.Text = "0"
		AddHandler Me.Weaken_00.Click, AddressOf Me.Weaken_00Click
		'
		'Strip_FadeLowSettings
		'
		Me.Strip_FadeLowSettings.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.lowEndToolStripMenuItem, Me.FadeLow_05, Me.FadeLow_04, Me.FadeLow_03, Me.FadeLow_02, Me.FadeLow_01, Me.FadeLow_00})
		Me.Strip_FadeLowSettings.Name = "Strip_FadeInSettings"
		Me.Strip_FadeLowSettings.Size = New System.Drawing.Size(153, 180)
		'
		'lowEndToolStripMenuItem
		'
		Me.lowEndToolStripMenuItem.Enabled = false
		Me.lowEndToolStripMenuItem.Name = "lowEndToolStripMenuItem"
		Me.lowEndToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
		Me.lowEndToolStripMenuItem.Text = "Lower End"
		'
		'FadeLow_05
		'
		Me.FadeLow_05.Name = "FadeLow_05"
		Me.FadeLow_05.Size = New System.Drawing.Size(152, 22)
		Me.FadeLow_05.Text = "0.5"
		AddHandler Me.FadeLow_05.Click, AddressOf Me.FadeLow_05Click
		'
		'FadeLow_04
		'
		Me.FadeLow_04.Name = "FadeLow_04"
		Me.FadeLow_04.Size = New System.Drawing.Size(152, 22)
		Me.FadeLow_04.Text = "0.4"
		AddHandler Me.FadeLow_04.Click, AddressOf Me.FadeLow_04Click
		'
		'FadeLow_03
		'
		Me.FadeLow_03.Name = "FadeLow_03"
		Me.FadeLow_03.Size = New System.Drawing.Size(152, 22)
		Me.FadeLow_03.Text = "0.3"
		AddHandler Me.FadeLow_03.Click, AddressOf Me.FadeLow_03Click
		'
		'FadeLow_02
		'
		Me.FadeLow_02.Name = "FadeLow_02"
		Me.FadeLow_02.Size = New System.Drawing.Size(152, 22)
		Me.FadeLow_02.Text = "0.2"
		AddHandler Me.FadeLow_02.Click, AddressOf Me.FadeLow_02Click
		'
		'FadeLow_01
		'
		Me.FadeLow_01.Name = "FadeLow_01"
		Me.FadeLow_01.Size = New System.Drawing.Size(152, 22)
		Me.FadeLow_01.Text = "0.1"
		AddHandler Me.FadeLow_01.Click, AddressOf Me.FadeLow_01Click
		'
		'FadeLow_00
		'
		Me.FadeLow_00.Checked = true
		Me.FadeLow_00.CheckState = System.Windows.Forms.CheckState.Checked
		Me.FadeLow_00.Name = "FadeLow_00"
		Me.FadeLow_00.Size = New System.Drawing.Size(152, 22)
		Me.FadeLow_00.Text = "0"
		AddHandler Me.FadeLow_00.Click, AddressOf Me.FadeLow_00Click
		'
		'Strip_WaveBoxClick
		'
		Me.Strip_WaveBoxClick.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.WBox_SelectAll, Me.WBox_SelectView, Me.WBox_ViewAll})
		Me.Strip_WaveBoxClick.Name = "Strip_WaveBoxClick"
		Me.Strip_WaveBoxClick.Size = New System.Drawing.Size(153, 92)
		'
		'WBox_SelectAll
		'
		Me.WBox_SelectAll.Enabled = false
		Me.WBox_SelectAll.Name = "WBox_SelectAll"
		Me.WBox_SelectAll.Size = New System.Drawing.Size(152, 22)
		Me.WBox_SelectAll.Text = "Select All"
		AddHandler Me.WBox_SelectAll.Click, AddressOf Me.WBox_SelectAllClick
		'
		'WBox_SelectView
		'
		Me.WBox_SelectView.Enabled = false
		Me.WBox_SelectView.Name = "WBox_SelectView"
		Me.WBox_SelectView.Size = New System.Drawing.Size(152, 22)
		Me.WBox_SelectView.Text = "Select View"
		AddHandler Me.WBox_SelectView.Click, AddressOf Me.WBox_SelectViewClick
		'
		'WBox_ViewAll
		'
		Me.WBox_ViewAll.Name = "WBox_ViewAll"
		Me.WBox_ViewAll.Size = New System.Drawing.Size(152, 22)
		Me.WBox_ViewAll.Text = "View All"
		AddHandler Me.WBox_ViewAll.Click, AddressOf Me.WBox_ViewAllClick
		'
		'MainForm
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 12!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(713, 420)
		Me.Controls.Add(Me.EditorToolStrip)
		Me.Controls.Add(Me.statusStrip1)
		Me.Controls.Add(Me.MainContainer)
		Me.Controls.Add(Me.toolStrip1)
		Me.Controls.Add(Me.menuStrip1)
		Me.MainMenuStrip = Me.menuStrip1
		Me.Name = "MainForm"
		Me.Text = "TDPSMStudio 1.05 (Wave Analyzer Mode)"
		AddHandler Load, AddressOf Me.MainFormLoad
		Me.menuStrip1.ResumeLayout(false)
		Me.menuStrip1.PerformLayout
		Me.toolStrip1.ResumeLayout(false)
		Me.toolStrip1.PerformLayout
		Me.MainContainer.Panel2.ResumeLayout(false)
		Me.MainContainer.Panel2.PerformLayout
		CType(Me.MainContainer,System.ComponentModel.ISupportInitialize).EndInit
		Me.MainContainer.ResumeLayout(false)
		Me.groupBox1.ResumeLayout(false)
		Me.groupBox1.PerformLayout
		CType(Me.AmplitudeController,System.ComponentModel.ISupportInitialize).EndInit
		Me.statusStrip1.ResumeLayout(false)
		Me.statusStrip1.PerformLayout
		Me.EditorToolStrip.ResumeLayout(false)
		Me.EditorToolStrip.PerformLayout
		Me.Strip_WeakenSettings.ResumeLayout(false)
		Me.Strip_FadeLowSettings.ResumeLayout(false)
		Me.Strip_WaveBoxClick.ResumeLayout(false)
		Me.ResumeLayout(false)
		Me.PerformLayout
	End Sub
	Private CheckBox_Balance As System.Windows.Forms.CheckBox
	Private Tool_Shrink As System.Windows.Forms.ToolStripButton
	Private WBox_ViewAll As System.Windows.Forms.ToolStripMenuItem
	Private WBox_SelectView As System.Windows.Forms.ToolStripMenuItem
	Private WBox_SelectAll As System.Windows.Forms.ToolStripMenuItem
	Private Strip_WaveBoxClick As System.Windows.Forms.ContextMenuStrip
	Private Button_AdjustToAll As System.Windows.Forms.ToolStripButton
	Private toolStripSeparator8 As System.Windows.Forms.ToolStripSeparator
	Private FadeLow_00 As System.Windows.Forms.ToolStripMenuItem
	Private FadeLow_01 As System.Windows.Forms.ToolStripMenuItem
	Private FadeLow_02 As System.Windows.Forms.ToolStripMenuItem
	Private FadeLow_03 As System.Windows.Forms.ToolStripMenuItem
	Private FadeLow_04 As System.Windows.Forms.ToolStripMenuItem
	Private FadeLow_05 As System.Windows.Forms.ToolStripMenuItem
	Private lowEndToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
	Private Strip_FadeLowSettings As System.Windows.Forms.ContextMenuStrip
	Private weakenStrengthToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
	Private Weaken_00 As System.Windows.Forms.ToolStripMenuItem
	Private Weaken_01 As System.Windows.Forms.ToolStripMenuItem
	Private Weaken_02 As System.Windows.Forms.ToolStripMenuItem
	Private Weaken_03 As System.Windows.Forms.ToolStripMenuItem
	Private Weaken_04 As System.Windows.Forms.ToolStripMenuItem
	Private Weaken_05 As System.Windows.Forms.ToolStripMenuItem
	Private Weaken_06 As System.Windows.Forms.ToolStripMenuItem
	Private Weaken_07 As System.Windows.Forms.ToolStripMenuItem
	Private Weaken_08 As System.Windows.Forms.ToolStripMenuItem
	Private Weaken_09 As System.Windows.Forms.ToolStripMenuItem
	Private Strip_WeakenSettings As System.Windows.Forms.ContextMenuStrip
	Private Tool_Adjust As System.Windows.Forms.ToolStripButton
	Private Tool_Weaken As System.Windows.Forms.ToolStripButton
	Private Tool_FadeIn As System.Windows.Forms.ToolStripButton
	Private Tool_Silence As System.Windows.Forms.ToolStripButton
	Private toolStripSeparator7 As System.Windows.Forms.ToolStripSeparator
	Private Tool_Normalize As System.Windows.Forms.ToolStripButton
	Private Tool_Smoothen As System.Windows.Forms.ToolStripButton
	Private Tool_ChangeVolume As System.Windows.Forms.ToolStripButton
	Private toolStripSeparator6 As System.Windows.Forms.ToolStripSeparator
	Private Tool_Mix As System.Windows.Forms.ToolStripButton
	Private Tool_Cut As System.Windows.Forms.ToolStripButton
	Private toolStripSeparator5 As System.Windows.Forms.ToolStripSeparator
	Private Tool_Copy As System.Windows.Forms.ToolStripButton
	Private toolStripSeparator4 As System.Windows.Forms.ToolStripSeparator
	Private Tool_Stop As System.Windows.Forms.ToolStripButton
	Private Tool_Play As System.Windows.Forms.ToolStripButton
	Private EditorToolStrip As System.Windows.Forms.ToolStrip
	Private waveEditorToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
	Private timer1 As System.Windows.Forms.Timer
	Private Button_StopView As System.Windows.Forms.ToolStripButton
	Private Button_ViewAll As System.Windows.Forms.ToolStripButton
	Private toolStripSeparator3 As System.Windows.Forms.ToolStripSeparator
	Private analyzerToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
	Private preprocessToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
	Private Button_About As System.Windows.Forms.ToolStripMenuItem
	Private cbvQualityControlToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
	Private wavCbvToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
	Private Button_AnalyzeAll As System.Windows.Forms.ToolStripButton
	Private label2 As System.Windows.Forms.Label
	Public TextBox_DataLength As System.Windows.Forms.TextBox
	Private label4 As System.Windows.Forms.Label
	Public CheckBox_Consonant As System.Windows.Forms.CheckBox
	Private groupBox1 As System.Windows.Forms.GroupBox
	Public Status As System.Windows.Forms.ToolStripStatusLabel
	Public ProgressBar_Completeness As System.Windows.Forms.ProgressBar
	Private label3 As System.Windows.Forms.Label
	Private statusStrip1 As System.Windows.Forms.StatusStrip
	Private label1 As System.Windows.Forms.Label
	Private AmplitudeController As System.Windows.Forms.TrackBar
	Private MainContainer As System.Windows.Forms.SplitContainer
	Private Button_Analyze As System.Windows.Forms.ToolStripButton
	Private toolStripSeparator2 As System.Windows.Forms.ToolStripSeparator
	Private Button_Next As System.Windows.Forms.ToolStripButton
	Private Button_Open As System.Windows.Forms.ToolStripButton
	Private Button_Prev As System.Windows.Forms.ToolStripButton
	Private toolStripSeparator1 As System.Windows.Forms.ToolStripSeparator
	Private Textbox_Pitch As System.Windows.Forms.ToolStripTextBox
	Private toolStripLabel2 As System.Windows.Forms.ToolStripLabel
	Private Textbox_Symbol As System.Windows.Forms.ToolStripTextBox
	Private toolStripLabel1 As System.Windows.Forms.ToolStripLabel
	Private toolStrip1 As System.Windows.Forms.ToolStrip
	Private modeToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
	Private viewToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
	Private menuStrip1 As System.Windows.Forms.MenuStrip
	
	Sub ToolStrip2ItemClicked(sender As Object, e As ToolStripItemClickedEventArgs)
		
	End Sub
	
	Sub TopToolStripPanelClick(sender As Object, e As EventArgs)
		
	End Sub
End Class
