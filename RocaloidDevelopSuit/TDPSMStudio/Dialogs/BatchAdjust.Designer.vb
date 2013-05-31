'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Partial Class BatchAdjust
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
		Me.Button_Start = New System.Windows.Forms.Button()
		Me.groupBox1 = New System.Windows.Forms.GroupBox()
		Me.CFI_Times = New System.Windows.Forms.TextBox()
		Me.label4 = New System.Windows.Forms.Label()
		Me.CFI_Quarter = New System.Windows.Forms.RadioButton()
		Me.CFI_Whole = New System.Windows.Forms.RadioButton()
		Me.CFI_Half = New System.Windows.Forms.RadioButton()
		Me.CheckBox_ConsonantFI = New System.Windows.Forms.CheckBox()
		Me.TextBox_Limit = New System.Windows.Forms.TextBox()
		Me.label3 = New System.Windows.Forms.Label()
		Me.label2 = New System.Windows.Forms.Label()
		Me.TextBox_SmoothenLen = New System.Windows.Forms.TextBox()
		Me.label1 = New System.Windows.Forms.Label()
		Me.TextBox_Strength = New System.Windows.Forms.TextBox()
		Me.CheckBox_SmoothenVOT = New System.Windows.Forms.CheckBox()
		Me.TextBox_AutoAdj = New System.Windows.Forms.TextBox()
		Me.TextBox_LimitC = New System.Windows.Forms.TextBox()
		Me.CheckBox_LimitC = New System.Windows.Forms.CheckBox()
		Me.CheckBox_AutoAdj = New System.Windows.Forms.CheckBox()
		Me.label5 = New System.Windows.Forms.Label()
		Me.TextBox_Until = New System.Windows.Forms.TextBox()
		Me.CheckBox_ShrinkC = New System.Windows.Forms.CheckBox()
		Me.label6 = New System.Windows.Forms.Label()
		Me.TextBox_ShrinkBy = New System.Windows.Forms.TextBox()
		Me.groupBox1.SuspendLayout
		Me.SuspendLayout
		'
		'Button_Start
		'
		Me.Button_Start.Location = New System.Drawing.Point(312, 268)
		Me.Button_Start.Name = "Button_Start"
		Me.Button_Start.Size = New System.Drawing.Size(261, 35)
		Me.Button_Start.TabIndex = 1
		Me.Button_Start.Text = "Start"
		Me.Button_Start.UseVisualStyleBackColor = true
		AddHandler Me.Button_Start.Click, AddressOf Me.Button_StartClick
		'
		'groupBox1
		'
		Me.groupBox1.Controls.Add(Me.TextBox_ShrinkBy)
		Me.groupBox1.Controls.Add(Me.label6)
		Me.groupBox1.Controls.Add(Me.CheckBox_ShrinkC)
		Me.groupBox1.Controls.Add(Me.CFI_Times)
		Me.groupBox1.Controls.Add(Me.label4)
		Me.groupBox1.Controls.Add(Me.CFI_Quarter)
		Me.groupBox1.Controls.Add(Me.CFI_Whole)
		Me.groupBox1.Controls.Add(Me.CFI_Half)
		Me.groupBox1.Controls.Add(Me.CheckBox_ConsonantFI)
		Me.groupBox1.Controls.Add(Me.TextBox_Limit)
		Me.groupBox1.Controls.Add(Me.label3)
		Me.groupBox1.Controls.Add(Me.label2)
		Me.groupBox1.Controls.Add(Me.TextBox_SmoothenLen)
		Me.groupBox1.Controls.Add(Me.label1)
		Me.groupBox1.Controls.Add(Me.TextBox_Strength)
		Me.groupBox1.Controls.Add(Me.CheckBox_SmoothenVOT)
		Me.groupBox1.Controls.Add(Me.TextBox_AutoAdj)
		Me.groupBox1.Controls.Add(Me.TextBox_LimitC)
		Me.groupBox1.Controls.Add(Me.CheckBox_LimitC)
		Me.groupBox1.Controls.Add(Me.CheckBox_AutoAdj)
		Me.groupBox1.Location = New System.Drawing.Point(12, 12)
		Me.groupBox1.Name = "groupBox1"
		Me.groupBox1.Size = New System.Drawing.Size(561, 224)
		Me.groupBox1.TabIndex = 2
		Me.groupBox1.TabStop = false
		Me.groupBox1.Text = "Operations"
		'
		'CFI_Times
		'
		Me.CFI_Times.Location = New System.Drawing.Point(434, 102)
		Me.CFI_Times.Name = "CFI_Times"
		Me.CFI_Times.Size = New System.Drawing.Size(109, 21)
		Me.CFI_Times.TabIndex = 17
		Me.CFI_Times.Text = "3"
		Me.CFI_Times.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'label4
		'
		Me.label4.Location = New System.Drawing.Point(315, 105)
		Me.label4.Name = "label4"
		Me.label4.Size = New System.Drawing.Size(57, 14)
		Me.label4.TabIndex = 16
		Me.label4.Text = "Times"
		'
		'CFI_Quarter
		'
		Me.CFI_Quarter.Location = New System.Drawing.Point(315, 80)
		Me.CFI_Quarter.Name = "CFI_Quarter"
		Me.CFI_Quarter.Size = New System.Drawing.Size(80, 22)
		Me.CFI_Quarter.TabIndex = 15
		Me.CFI_Quarter.Text = "Quarter"
		Me.CFI_Quarter.UseVisualStyleBackColor = true
		'
		'CFI_Whole
		'
		Me.CFI_Whole.Checked = true
		Me.CFI_Whole.Location = New System.Drawing.Point(486, 80)
		Me.CFI_Whole.Name = "CFI_Whole"
		Me.CFI_Whole.Size = New System.Drawing.Size(57, 22)
		Me.CFI_Whole.TabIndex = 14
		Me.CFI_Whole.TabStop = true
		Me.CFI_Whole.Text = "Whole"
		Me.CFI_Whole.UseVisualStyleBackColor = true
		'
		'CFI_Half
		'
		Me.CFI_Half.Location = New System.Drawing.Point(401, 80)
		Me.CFI_Half.Name = "CFI_Half"
		Me.CFI_Half.Size = New System.Drawing.Size(57, 22)
		Me.CFI_Half.TabIndex = 13
		Me.CFI_Half.Text = "Half"
		Me.CFI_Half.UseVisualStyleBackColor = true
		'
		'CheckBox_ConsonantFI
		'
		Me.CheckBox_ConsonantFI.Location = New System.Drawing.Point(298, 51)
		Me.CheckBox_ConsonantFI.Name = "CheckBox_ConsonantFI"
		Me.CheckBox_ConsonantFI.Size = New System.Drawing.Size(143, 23)
		Me.CheckBox_ConsonantFI.TabIndex = 12
		Me.CheckBox_ConsonantFI.Text = "Consonant Fading In"
		Me.CheckBox_ConsonantFI.UseVisualStyleBackColor = true
		'
		'TextBox_Limit
		'
		Me.TextBox_Limit.Location = New System.Drawing.Point(145, 129)
		Me.TextBox_Limit.Name = "TextBox_Limit"
		Me.TextBox_Limit.Size = New System.Drawing.Size(109, 21)
		Me.TextBox_Limit.TabIndex = 11
		Me.TextBox_Limit.Text = "0.03"
		Me.TextBox_Limit.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'label3
		'
		Me.label3.Location = New System.Drawing.Point(26, 132)
		Me.label3.Name = "label3"
		Me.label3.Size = New System.Drawing.Size(104, 14)
		Me.label3.TabIndex = 10
		Me.label3.Text = "Limit"
		'
		'label2
		'
		Me.label2.Location = New System.Drawing.Point(26, 105)
		Me.label2.Name = "label2"
		Me.label2.Size = New System.Drawing.Size(104, 14)
		Me.label2.TabIndex = 9
		Me.label2.Text = "Smoothen Length"
		'
		'TextBox_SmoothenLen
		'
		Me.TextBox_SmoothenLen.Location = New System.Drawing.Point(145, 102)
		Me.TextBox_SmoothenLen.Name = "TextBox_SmoothenLen"
		Me.TextBox_SmoothenLen.Size = New System.Drawing.Size(109, 21)
		Me.TextBox_SmoothenLen.TabIndex = 8
		Me.TextBox_SmoothenLen.Text = "1500"
		Me.TextBox_SmoothenLen.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'label1
		'
		Me.label1.Location = New System.Drawing.Point(26, 78)
		Me.label1.Name = "label1"
		Me.label1.Size = New System.Drawing.Size(57, 14)
		Me.label1.TabIndex = 7
		Me.label1.Text = "Strength"
		'
		'TextBox_Strength
		'
		Me.TextBox_Strength.Location = New System.Drawing.Point(145, 75)
		Me.TextBox_Strength.Name = "TextBox_Strength"
		Me.TextBox_Strength.Size = New System.Drawing.Size(109, 21)
		Me.TextBox_Strength.TabIndex = 6
		Me.TextBox_Strength.Text = "0.5"
		Me.TextBox_Strength.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'CheckBox_SmoothenVOT
		'
		Me.CheckBox_SmoothenVOT.Location = New System.Drawing.Point(9, 51)
		Me.CheckBox_SmoothenVOT.Name = "CheckBox_SmoothenVOT"
		Me.CheckBox_SmoothenVOT.Size = New System.Drawing.Size(245, 24)
		Me.CheckBox_SmoothenVOT.TabIndex = 5
		Me.CheckBox_SmoothenVOT.Text = "Smoothen at VOT"
		Me.CheckBox_SmoothenVOT.UseVisualStyleBackColor = true
		'
		'TextBox_AutoAdj
		'
		Me.TextBox_AutoAdj.Location = New System.Drawing.Point(145, 20)
		Me.TextBox_AutoAdj.Name = "TextBox_AutoAdj"
		Me.TextBox_AutoAdj.Size = New System.Drawing.Size(109, 21)
		Me.TextBox_AutoAdj.TabIndex = 4
		Me.TextBox_AutoAdj.Text = "0.1"
		Me.TextBox_AutoAdj.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'TextBox_LimitC
		'
		Me.TextBox_LimitC.Location = New System.Drawing.Point(434, 20)
		Me.TextBox_LimitC.Name = "TextBox_LimitC"
		Me.TextBox_LimitC.Size = New System.Drawing.Size(109, 21)
		Me.TextBox_LimitC.TabIndex = 3
		Me.TextBox_LimitC.Text = "0.05"
		Me.TextBox_LimitC.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'CheckBox_LimitC
		'
		Me.CheckBox_LimitC.Location = New System.Drawing.Point(298, 20)
		Me.CheckBox_LimitC.Name = "CheckBox_LimitC"
		Me.CheckBox_LimitC.Size = New System.Drawing.Size(173, 24)
		Me.CheckBox_LimitC.TabIndex = 2
		Me.CheckBox_LimitC.Text = "Limit Consonants"
		Me.CheckBox_LimitC.UseVisualStyleBackColor = true
		'
		'CheckBox_AutoAdj
		'
		Me.CheckBox_AutoAdj.Location = New System.Drawing.Point(9, 20)
		Me.CheckBox_AutoAdj.Name = "CheckBox_AutoAdj"
		Me.CheckBox_AutoAdj.Size = New System.Drawing.Size(173, 24)
		Me.CheckBox_AutoAdj.TabIndex = 1
		Me.CheckBox_AutoAdj.Text = "Automatic Adjust"
		Me.CheckBox_AutoAdj.UseVisualStyleBackColor = true
		'
		'label5
		'
		Me.label5.Location = New System.Drawing.Point(11, 245)
		Me.label5.Name = "label5"
		Me.label5.Size = New System.Drawing.Size(60, 16)
		Me.label5.TabIndex = 3
		Me.label5.Text = "Until"
		'
		'TextBox_Until
		'
		Me.TextBox_Until.Location = New System.Drawing.Point(56, 242)
		Me.TextBox_Until.Name = "TextBox_Until"
		Me.TextBox_Until.Size = New System.Drawing.Size(107, 21)
		Me.TextBox_Until.TabIndex = 4
		Me.TextBox_Until.Text = "C5"
		Me.TextBox_Until.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'CheckBox_ShrinkC
		'
		Me.CheckBox_ShrinkC.Location = New System.Drawing.Point(9, 156)
		Me.CheckBox_ShrinkC.Name = "CheckBox_ShrinkC"
		Me.CheckBox_ShrinkC.Size = New System.Drawing.Size(245, 24)
		Me.CheckBox_ShrinkC.TabIndex = 18
		Me.CheckBox_ShrinkC.Text = "Shrink Consonants"
		Me.CheckBox_ShrinkC.UseVisualStyleBackColor = true
		'
		'label6
		'
		Me.label6.Location = New System.Drawing.Point(26, 183)
		Me.label6.Name = "label6"
		Me.label6.Size = New System.Drawing.Size(93, 16)
		Me.label6.TabIndex = 19
		Me.label6.Text = "Shrink by"
		'
		'TextBox_ShrinkBy
		'
		Me.TextBox_ShrinkBy.Location = New System.Drawing.Point(145, 180)
		Me.TextBox_ShrinkBy.Name = "TextBox_ShrinkBy"
		Me.TextBox_ShrinkBy.Size = New System.Drawing.Size(109, 21)
		Me.TextBox_ShrinkBy.TabIndex = 20
		Me.TextBox_ShrinkBy.Text = "0.05"
		Me.TextBox_ShrinkBy.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'BatchAdjust
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 12!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(583, 312)
		Me.Controls.Add(Me.TextBox_Until)
		Me.Controls.Add(Me.label5)
		Me.Controls.Add(Me.groupBox1)
		Me.Controls.Add(Me.Button_Start)
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
		Me.MaximizeBox = false
		Me.Name = "BatchAdjust"
		Me.ShowIcon = false
		Me.ShowInTaskbar = false
		Me.Text = "Batch Process"
		Me.TopMost = true
		AddHandler Load, AddressOf Me.BatchAdjustLoad
		Me.groupBox1.ResumeLayout(false)
		Me.groupBox1.PerformLayout
		Me.ResumeLayout(false)
		Me.PerformLayout
	End Sub
	Private CheckBox_ShrinkC As System.Windows.Forms.CheckBox
	Private label6 As System.Windows.Forms.Label
	Private TextBox_ShrinkBy As System.Windows.Forms.TextBox
	Private TextBox_Until As System.Windows.Forms.TextBox
	Private label5 As System.Windows.Forms.Label
	Private CheckBox_ConsonantFI As System.Windows.Forms.CheckBox
	Private CFI_Half As System.Windows.Forms.RadioButton
	Private CFI_Whole As System.Windows.Forms.RadioButton
	Private CFI_Quarter As System.Windows.Forms.RadioButton
	Private label4 As System.Windows.Forms.Label
	Private CFI_Times As System.Windows.Forms.TextBox
	Private label3 As System.Windows.Forms.Label
	Private TextBox_Limit As System.Windows.Forms.TextBox
	Private label1 As System.Windows.Forms.Label
	Private TextBox_SmoothenLen As System.Windows.Forms.TextBox
	Private label2 As System.Windows.Forms.Label
	Private CheckBox_SmoothenVOT As System.Windows.Forms.CheckBox
	Private TextBox_Strength As System.Windows.Forms.TextBox
	Private CheckBox_LimitC As System.Windows.Forms.CheckBox
	Private TextBox_LimitC As System.Windows.Forms.TextBox
	Private TextBox_AutoAdj As System.Windows.Forms.TextBox
	Private CheckBox_AutoAdj As System.Windows.Forms.CheckBox
	Private groupBox1 As System.Windows.Forms.GroupBox
	Private Button_Start As System.Windows.Forms.Button
End Class
