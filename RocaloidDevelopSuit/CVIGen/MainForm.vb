'    这个实用工具通过给定的CBV文件生成DBInfo
'    This utility tool generates DBInfo by given CBV files.
'    Copyright (C) 2013 Sleepwalking
'
'    This program is free software: you can redistribute it and/or modify
'    it under the terms of the GNU General Public License as published by
'    the Free Software Foundation, either version 3 of the License, or
'    (at your option) any later version.
'
'    This program is distributed in the hope that it will be useful,
'    but WITHOUT ANY WARRANTY; without even the implied warranty of
'    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
'    GNU General Public License for more details.
'
'    You should have received a copy of the GNU General Public License
'    along with this program.  If not, see <http://www.gnu.org/licenses/>.

Public Partial Class MainForm
	Public LB As New ListBox()	
	Public Sub New()
		' The Me.InitializeComponent call is required for Windows Forms designer support.
		Me.InitializeComponent()
		
		'
		' TODO : Add constructor code after InitializeComponents
		'
	End Sub
	
	Sub GroupBox1DragDrop(sender As Object, e As DragEventArgs)
		
	End Sub
	
	
	
	Sub GroupBox1Enter(sender As Object, e As EventArgs)
		
	End Sub
	
	Sub MainFormLoad(sender As Object, e As EventArgs)
        With LB
            .Dock = DockStyle.Fill
            .AllowDrop = True '接受拖放
            AddHandler LB.DragEnter, AddressOf LB_DragEnter '委托拖放数据事件
            AddHandler LB.DragDrop, AddressOf LB_DragDrop '委托数据处理事件
        End With
        groupBox1.Controls.Add(LB)		
	End Sub
	
	
    Private Sub LB_DragDrop(ByVal sender As Object, ByVal e As System.Windows.Forms.DragEventArgs)
    	LB.Items.Clear() '清理列表
        For Each str As String In e.Data.GetData(DataFormats.FileDrop) '循环枚举数据
        	LB.Items.Add(str)
        Next
    End Sub

    Private Sub LB_DragEnter(ByVal sender As Object, ByVal e As System.Windows.Forms.DragEventArgs)
        e.Effect = DragDropEffects.Link '接受拖放数据，启用拖放效果
    End Sub
	
	Sub Button_StartClick(sender As Object, e As EventArgs)
		Operation.Start(LB.Items, TextBox_SaveTo.Text, CInt(TextBox_Indent.Text))
	End Sub
End Class
