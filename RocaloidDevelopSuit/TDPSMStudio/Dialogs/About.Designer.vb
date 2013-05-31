'
' Created by SharpDevelop.
' Sleepwalking
' 
'
Partial Class About
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
		Me.label1 = New System.Windows.Forms.Label()
		Me.label2 = New System.Windows.Forms.Label()
		Me.label3 = New System.Windows.Forms.Label()
		Me.label4 = New System.Windows.Forms.Label()
		Me.button1 = New System.Windows.Forms.Button()
		Me.SuspendLayout
		'
		'label1
		'
		Me.label1.Location = New System.Drawing.Point(12, 9)
		Me.label1.Name = "label1"
		Me.label1.Size = New System.Drawing.Size(186, 16)
		Me.label1.TabIndex = 0
		Me.label1.Text = "TDPSMStudio 1.05"
		'
		'label2
		'
		Me.label2.Location = New System.Drawing.Point(12, 24)
		Me.label2.Name = "label2"
		Me.label2.Size = New System.Drawing.Size(291, 38)
		Me.label2.TabIndex = 1
		Me.label2.Text = "The combination of a wave analyzer, a CVDB viewer and a wave editor, exclusively "& _ 
		"designed for TDPSM algorism."
		'
		'label3
		'
		Me.label3.Location = New System.Drawing.Point(12, 64)
		Me.label3.Name = "label3"
		Me.label3.Size = New System.Drawing.Size(249, 16)
		Me.label3.TabIndex = 2
		Me.label3.Text = "Designed and Coded by Sleepwalking."
		'
		'label4
		'
		Me.label4.Location = New System.Drawing.Point(12, 80)
		Me.label4.Name = "label4"
		Me.label4.Size = New System.Drawing.Size(116, 21)
		Me.label4.TabIndex = 3
		Me.label4.Text = "May, 2013."
		'
		'button1
		'
		Me.button1.Location = New System.Drawing.Point(219, 100)
		Me.button1.Name = "button1"
		Me.button1.Size = New System.Drawing.Size(84, 24)
		Me.button1.TabIndex = 4
		Me.button1.Text = "OK"
		Me.button1.UseVisualStyleBackColor = true
		AddHandler Me.button1.Click, AddressOf Me.Button1Click
		'
		'About
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 12!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(319, 136)
		Me.Controls.Add(Me.button1)
		Me.Controls.Add(Me.label4)
		Me.Controls.Add(Me.label3)
		Me.Controls.Add(Me.label2)
		Me.Controls.Add(Me.label1)
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
		Me.MaximizeBox = false
		Me.MinimizeBox = false
		Me.Name = "About"
		Me.ShowInTaskbar = false
		Me.Text = "About"
		Me.TopMost = true
		Me.ResumeLayout(false)
	End Sub
	Private button1 As System.Windows.Forms.Button
	Private label4 As System.Windows.Forms.Label
	Private label3 As System.Windows.Forms.Label
	Private label2 As System.Windows.Forms.Label
	Private label1 As System.Windows.Forms.Label
End Class
