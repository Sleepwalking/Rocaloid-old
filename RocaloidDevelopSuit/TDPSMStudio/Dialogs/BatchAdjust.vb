'    批量波形调整对话框
'    Batch Adjust Dialog
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
Public Partial Class BatchAdjust
	Public Sub New()
		' The Me.InitializeComponent call is required for Windows Forms designer support.
		Me.InitializeComponent()
		
		'
		' TODO : Add constructor code after InitializeComponents
		'
	End Sub
	
	Sub BatchAdjustLoad(sender As Object, e As EventArgs)
		CheckBox_AutoAdj.Checked = Setting_Editor_Batch_Adjust
		CheckBox_LimitC.Checked = Setting_Editor_Batch_LimitConsonants
		CheckBox_SmoothenVOT.Checked = Setting_Editor_Batch_SmoothenVOT
		TextBox_AutoAdj.Text = CStr(Setting_Editor_Batch_Adjust_Magnitude)
		TextBox_LimitC.Text = CStr(Setting_Editor_Batch_LimitConsonants_Magnitude)
		TextBox_Strength.Text = CStr(Setting_Editor_Batch_SmoothenVOT_Strength)
		TextBox_SmoothenLen.Text = CStr(Setting_Editor_Batch_SmoothenVOT_Length)
		TextBox_Limit.Text = CStr(Setting_Editor_Batch_SmoothenVOT_Limit)
		TextBox_ShrinkBy.Text = CStr(Setting_Editor_Batch_ConsonantShrink_ShrinkBy)
		CheckBox_ConsonantFI.Checked = Setting_Editor_Batch_ConsonantFI
		CFI_Quarter.Checked = Setting_Editor_Batch_ConsonantFI_Field = 0.25
		CFI_Half.Checked = Setting_Editor_Batch_ConsonantFI_Field = 0.5
		CFI_Whole.Checked = Setting_Editor_Batch_ConsonantFI_Field = 1
		CheckBox_ShrinkC.Checked = Setting_Editor_Batch_ConsonantShrink
		CFI_Times.Text = CStr(Setting_Editor_Batch_ConsonantFI_Times)
		TextBox_Until.Text = OverAll.PitchList(Setting_Editor_Batch_Until)
	End Sub
	
	Sub Button_StartClick(sender As Object, e As EventArgs)
		Setting_Editor_Batch_Adjust = CheckBox_AutoAdj.Checked
		Setting_Editor_Batch_LimitConsonants = CheckBox_LimitC.Checked
		Setting_Editor_Batch_SmoothenVOT = CheckBox_SmoothenVOT.Checked
		Setting_Editor_Batch_ConsonantShrink = CheckBox_ShrinkC.Checked
		Setting_Editor_Batch_Adjust_Magnitude = CDbl(TextBox_AutoAdj.Text)
		Setting_Editor_Batch_LimitConsonants_Magnitude = CDbl(TextBox_LimitC.Text)
		Setting_Editor_Batch_SmoothenVOT_Strength = CDbl(TextBox_Strength.Text)
		Setting_Editor_Batch_SmoothenVOT_Length = CInt(TextBox_SmoothenLen.Text)
		Setting_Editor_Batch_SmoothenVOT_Limit = CInt(TextBox_Limit.Text)
		Setting_Editor_Batch_ConsonantShrink_ShrinkBy = CDbl(TextBox_ShrinkBy.Text)
		Setting_Editor_Batch_ConsonantFI = CheckBox_ConsonantFI.Checked
		If CFI_Quarter.Checked Then Setting_Editor_Batch_ConsonantFI_Field = 0.25
		If CFI_Half.Checked Then Setting_Editor_Batch_ConsonantFI_Field = 0.5
		If CFI_Whole.Checked Then Setting_Editor_Batch_ConsonantFI_Field = 1
		Setting_Editor_Batch_ConsonantFI_Times = CInt(CFI_Times.Text)
		Setting_Editor_Batch_Until = OverAll.GetNumByPitch(TextBox_Until.Text)
		Setting_Multithread = True
		UpdateSettings()
		Operation.AdjustAll()
		Me.Hide()
	End Sub
End Class
