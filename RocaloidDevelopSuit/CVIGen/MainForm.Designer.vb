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
		Me.groupBox1 = New System.Windows.Forms.GroupBox()
		Me.label1 = New System.Windows.Forms.Label()
		Me.TextBox_SaveTo = New System.Windows.Forms.TextBox()
		Me.button1 = New System.Windows.Forms.Button()
		Me.label2 = New System.Windows.Forms.Label()
		Me.TextBox_Indent = New System.Windows.Forms.TextBox()
		Me.SuspendLayout
		'
		'groupBox1
		'
		Me.groupBox1.Location = New System.Drawing.Point(12, 12)
		Me.groupBox1.Name = "groupBox1"
		Me.groupBox1.Size = New System.Drawing.Size(599, 249)
		Me.groupBox1.TabIndex = 0
		Me.groupBox1.TabStop = false
		Me.groupBox1.Text = "Drop cbv here."
		AddHandler Me.groupBox1.DragDrop, AddressOf Me.GroupBox1DragDrop
		AddHandler Me.groupBox1.Enter, AddressOf Me.GroupBox1Enter
		'
		'label1
		'
		Me.label1.Location = New System.Drawing.Point(12, 273)
		Me.label1.Name = "label1"
		Me.label1.Size = New System.Drawing.Size(174, 18)
		Me.label1.TabIndex = 1
		Me.label1.Text = "Save to :"
		'
		'TextBox_SaveTo
		'
		Me.TextBox_SaveTo.Location = New System.Drawing.Point(76, 270)
		Me.TextBox_SaveTo.Name = "TextBox_SaveTo"
		Me.TextBox_SaveTo.Size = New System.Drawing.Size(535, 21)
		Me.TextBox_SaveTo.TabIndex = 2
		Me.TextBox_SaveTo.Text = "data.cvi"
		'
		'button1
		'
		Me.button1.Location = New System.Drawing.Point(520, 297)
		Me.button1.Name = "button1"
		Me.button1.Size = New System.Drawing.Size(91, 35)
		Me.button1.TabIndex = 3
		Me.button1.Text = "Start"
		Me.button1.UseVisualStyleBackColor = true
		AddHandler Me.button1.Click, AddressOf Me.Button_StartClick
		'
		'label2
		'
		Me.label2.Location = New System.Drawing.Point(12, 308)
		Me.label2.Name = "label2"
		Me.label2.Size = New System.Drawing.Size(86, 17)
		Me.label2.TabIndex = 4
		Me.label2.Text = "Indent :"
		'
		'TextBox_Indent
		'
		Me.TextBox_Indent.Location = New System.Drawing.Point(76, 305)
		Me.TextBox_Indent.Name = "TextBox_Indent"
		Me.TextBox_Indent.Size = New System.Drawing.Size(136, 21)
		Me.TextBox_Indent.TabIndex = 5
		Me.TextBox_Indent.Text = "2"
		'
		'MainForm
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 12!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(623, 338)
		Me.Controls.Add(Me.TextBox_Indent)
		Me.Controls.Add(Me.label2)
		Me.Controls.Add(Me.button1)
		Me.Controls.Add(Me.TextBox_SaveTo)
		Me.Controls.Add(Me.label1)
		Me.Controls.Add(Me.groupBox1)
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
		Me.MaximizeBox = false
		Me.Name = "MainForm"
		Me.Text = "CVIGen"
		AddHandler Load, AddressOf Me.MainFormLoad
		Me.ResumeLayout(false)
		Me.PerformLayout
	End Sub
	Private TextBox_Indent As System.Windows.Forms.TextBox
	Private label2 As System.Windows.Forms.Label
	Private button1 As System.Windows.Forms.Button
	Private TextBox_SaveTo As System.Windows.Forms.TextBox
	Private label1 As System.Windows.Forms.Label
	Private groupBox1 As System.Windows.Forms.GroupBox
End Class
