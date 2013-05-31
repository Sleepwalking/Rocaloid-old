'    预处理对话框
'    Pre-Process Dialog
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
Public Partial Class PreProcess
	Public Sub New()
		' The Me.InitializeComponent call is required for Windows Forms designer support.
		Me.InitializeComponent()
		
		'
		' TODO : Add constructor code after InitializeComponents
		'
	End Sub
	
	Sub Button_Apply_Click(sender As Object, e As EventArgs)
		Setting_UseMovingAverage = MA_Enabled.Checked
		Setting_TwiceMovingAverage = MA_Twice.Checked
		Setting_ExtraMovingAverage = MA_Extra.Checked And MA_Extra.Enabled
		If MA_23.Checked Then Setting_MovingAverageLength = 0.667
		If MA_12.Checked Then Setting_MovingAverageLength = 0.5
		If MA_13.Checked Then Setting_MovingAverageLength = 0.333
		If MA_14.Checked Then Setting_MovingAverageLength = 0.25
		If EM_1.Checked Then Setting_EnvelopePrecision = 1
		If EM_2.Checked Then Setting_EnvelopePrecision = 2
		If EM_4.Checked Then Setting_EnvelopePrecision = 4
		Setting_StartPositionFixed = SP_Fixed.Checked
		Setting_StartPositionTime = CInt(CDbl(SP_Time.Text) * 96000)
	End Sub
	
	Sub PreProcessLoad(sender As Object, e As EventArgs)
		MA_Enabled.Checked = Setting_UseMovingAverage
		MA_Twice.Checked = Setting_TwiceMovingAverage
		MA_Extra.Enabled = Setting_TwiceMovingAverage
		MA_Extra.Checked = Setting_ExtraMovingAverage And MA_Twice.Checked
		MA_12.Checked = False
		MA_13.Checked = False
		MA_14.Checked = False
		MA_23.Checked = False
		Select Case Setting_MovingAverageLength
			Case < 0.3
				MA_14.Checked = True
			Case < 0.4
				MA_13.Checked = True
			Case < 0.6
				MA_12.Checked = True
			Case < 0.8
				MA_23.Checked = True
		End Select
		EM_1.Checked = False
		EM_2.Checked = False
		EM_4.Checked = False
		Select Case Setting_EnvelopePrecision
			Case 1
				EM_1.Checked = True
			Case 2
				EM_2.Checked = True
			Case 4
				EM_4.Checked = True
		End Select
		SP_Fixed.Checked = Setting_StartPositionFixed
		SP_Time.Text = CStr(CSng(Setting_StartPositionTime / 96000))
	End Sub
	
	Sub MA_TwiceCheckedChanged(sender As Object, e As EventArgs)
		If MA_Twice.Checked Then 
			MA_Extra.Enabled = True
		Else
			MA_Extra.Enabled = False
		End If
	End Sub
End Class
