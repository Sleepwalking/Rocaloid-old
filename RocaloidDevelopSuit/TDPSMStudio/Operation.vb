'    和UI相关联的操作
'    The actions corresponding to the UI.
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

Imports System.Threading
Public Module Operation
	Public MainBox As WaveBox	
	Public MainWave As WaveBuffer
	Public MainWave_Smooth As WaveBuffer
	Public MainEnvelope As PointList
	Public MainRecognization As PointList
	Public MainPeriod As PointList
	Public MainBar As BarList
	Public MainWave_StartPosition As Integer
	Public CopyWave As WaveBuffer
	Public LoadedCVDB As CVDB = New CVDB()
	
	Public Setting_Consonant As Boolean = True
	Public Setting_DataLength As Integer = 48000
	Public Setting_Balance As Boolean = True
	Public Setting_Multithread As Boolean = False
	Public Setting_Mode As EditMode = EditMode.WavAnalysis
	Public Setting_UseMovingAverage As Boolean = True
	Public Setting_MovingAverageLength As Double = 0.333
	Public Setting_TwiceMovingAverage As Boolean = True
	Public Setting_ExtraMovingAverage As Boolean = False
	Public Setting_EnvelopePrecision As Integer = 1
	Public Setting_StartPositionFixed As Boolean = False
	Public Setting_StartPositionTime As Integer = 9600
	Public Setting_SilentThreshold As Double = 0.005
	Public Setting_Algorism As Algorism = Algorism.Correlation
	Public Setting_SearchWindow_Low As Double = 0.5
	Public Setting_SearchWindow_High As Double = 1.5
	Public Setting_AllowingError As Double = 0.25
	Public Setting_Editor_WeakenStrength As Double = 0.7
	Public Setting_Editor_FadeLowerEnd As Double = 0
	Public Setting_Editor_Batch_Adjust As Boolean = True
	Public Setting_Editor_Batch_Adjust_Magnitude As Double = 0.1
	Public Setting_Editor_Batch_LimitConsonants As Boolean = False
	Public Setting_Editor_Batch_LimitConsonants_Magnitude As Double = 0.1
	Public Setting_Editor_Batch_SmoothenVOT As Boolean = False
	Public Setting_Editor_Batch_SmoothenVOT_Strength As Double = 0.5
	Public Setting_Editor_Batch_SmoothenVOT_Length As Integer = 1500
	Public Setting_Editor_Batch_SmoothenVOT_Limit As Double = 0.03
	Public Setting_Editor_Batch_ConsonantFI As Boolean = False
	Public Setting_Editor_Batch_ConsonantFI_Field As Double = 1
	Public Setting_Editor_Batch_ConsonantFI_Times As Integer = 3
	Public Setting_Editor_Batch_ConsonantShrink As Boolean = False
	Public Setting_Editor_Batch_ConsonantShrink_ShrinkBy As Double = 0.05
	Public Setting_Editor_Batch_Until As Integer = Pitch_C5
	
	Public State_Viewing As Boolean = False
	Public State_MixEnabled As Boolean = False
	
	Public PBar As ProgressBar
	Public StatusBox As ToolStripStatusLabel
	
	Public SoundDevice As Microsoft.DirectX.DirectSound.Device
	Public SoundBuffer As Microsoft.DirectX.DirectSound.SecondaryBuffer
	Public SoundFormat As Microsoft.DirectX.DirectSound.WaveFormat
	Public SoundDesc As Microsoft.DirectX.DirectSound.BufferDescription
	Public SoundPlaying As Boolean = False
	Public SoundLength As Integer
	Public SoundStartPosition As Integer
	Public WithEvents SoundTimer As System.Timers.Timer
	
	Public LoadThread As New Thread(AddressOf Operation.LoadWave)
	
	#Region "Wave Editor"
	Public Sub PlaySound()
		If Setting_Mode <> EditMode.WavEditor Then Exit Sub
		If SoundPlaying Then StopSound()
		Dim StartPosition As Integer, EndPosition As Integer, Size As Integer
		StartPosition = MainBox.SelectedArea.SelectFrom
		EndPosition = MainBox.SelectedArea.SelectTo
		Size = EndPosition - StartPosition
		If StartPosition < 0 Or Size <= 0 Then Exit Sub
		Dim Buffer(Size) As Int16
		Dim i As Integer
		For i = StartPosition To EndPosition - 1
			Buffer(i - StartPosition) = CShort(MainWave.Data(i) * 32767)
			If State_MixEnabled AndAlso i > CopyWave.Offset AndAlso i < CopyWave.Offset + CopyWave.Pointer Then
				Buffer(i - StartPosition) += CShort(CopyWave.Data(i - CopyWave.Offset) * 32767)
			End If
		Next
		SoundDesc.BufferBytes = Size * 2 + 2
		SoundBuffer = New Microsoft.DirectX.DirectSound.SecondaryBuffer(SoundDesc, SoundDevice)
		SoundBuffer.Write(0, Buffer, Microsoft.DirectX.DirectSound.LockFlag.None)
		SoundBuffer.Play(0, Microsoft.DirectX.DirectSound.BufferPlayFlags.Default)
		SoundPlaying = True
		SoundLength = Size \ 96
		SoundStartPosition = StartPosition
		SoundTimer.Start()
		MainBar.Style.Show = True
	End Sub
	
	Public Sub OnSoundTimer(ByVal sender As Object, ByVal Args As System.Timers.ElapsedEventArgs)
		MainBar.Bars(0) = CInt(SoundBuffer.PlayPosition \ 2) + SoundStartPosition
		MainBar.BarQ = 0
		If Not SoundBuffer.Status.Playing Then
			StopSound()
			MainBar.BarQ = -1
		End If
		MainBox.Refresh()
	End Sub
	
	Public Sub StopSound()
		If Not SoundPlaying Then Exit Sub
		SoundBuffer.Stop()
		SoundBuffer.Dispose()
		SoundTimer.Stop()
		SoundPlaying = False
		MainBar.BarQ = -1
		MainBar.Style.Show = False
	End Sub
	
	Public Sub CopySound(ByVal _From As Integer, ByVal _To As Integer)
		MainWave.CopyTo(CopyWave, _From, _To)
	End Sub
	
	Public Sub CutSound(ByVal _From As Integer, ByVal _To As Integer)
		WaveEffects.CutWave(MainWave, _From, _To)
	End Sub
	
	Public Sub ChangeVolume(ByVal _From As Integer, ByVal _To As Integer)
		Dim ChgVol As Double = CDbl(InputBox("Volume Multiplier:", "Change Volume", "1"))
		WaveEffects.ChgVolume(MainWave, _From, _To, ChgVol)
	End Sub
	
	Public Sub Smoothen(ByVal _From As Integer, ByVal _To As Integer)
		Dim Strength As Double = CDbl(InputBox("Strength:", "Smoothen", "1"))
		Dim Length As Integer = CInt(InputBox("Length:", "Smoothen", "50"))
		WaveEffects.SelfMovingAverage(MainWave, Length, Strength, _From, _To)
	End Sub
	
	Public Sub Silence(ByVal _From As Integer, ByVal _To As Integer)
		WaveEffects.Silence(MainWave, _From, _To, 50)
	End Sub
	
	Public Sub Shrink(ByVal _From As Integer, ByVal _To As Integer)
		Dim Length As Integer = CInt(CDbl(InputBox("Shrink by:", "Shrink", "0.05")) * 96000)
		WaveEffects.Shrink(MainWave, _From, _To, Length)
	End Sub
	
	Public Sub FadeIn(ByVal _From As Integer, ByVal _To As Integer)
		WaveEffects.FadeIn(MainWave, _From, _To, 200, Setting_Editor_FadeLowerEnd)
	End Sub
	
	Public Sub Weaken(ByVal _From As Integer, ByVal _To As Integer)
		WaveEffects.Weaken(MainWave, _From, _To, Setting_Editor_WeakenStrength)
	End Sub
	
	Public Sub MixSound(ByVal Position As Integer)
		CopyWave.Offset = Position
		MainBox.Show(2)
	End Sub
	
	Public Sub Normalize(ByVal _From As Integer, ByVal _To As Integer)
		Dim VolumeLimit As Double = CDbl(InputBox("Volume Limit:", "Normalize", "0.1"))
		WaveEffects.Normalize(MainWave, _From, _To, VolumeLimit)
	End Sub
	
	Public Sub Adjust(ByVal _From As Integer, ByVal _To As Integer)
		If Setting_Balance Then WaveEffects.LowPassBalance(MainWave, _From, _To)
		WaveEffects.Normalize(MainWave, _From, _To, _
			Math.Min(
				0.1, _
				Analysis.GetAverageVolume(MainWave, _
					_From, _
					_To)
			)
		)
	End Sub
	
	Public Sub SaveWave(ByVal Name As String)
		Dim TempBuffer As WaveBuffer = New WaveBuffer(10.0)
		Dim i As Integer
		For i = 0 To MainWave.Pointer
			TempBuffer.Data(i) = MainWave.Data(i)
			If State_MixEnabled AndAlso i > CopyWave.Offset AndAlso i < CopyWave.Offset + CopyWave.Pointer Then
				TempBuffer.Data(i) += CopyWave.Data(i - CopyWave.Offset)
			End If
		Next
		TempBuffer.Pointer = MainWave.Pointer
		MixerWriterEffector.SetFileOutput(Name)
		MixerWriterEffector.Write(TempBuffer, 0, TempBuffer.Pointer)
		MixerWriterEffector.FinishWave()
	End Sub
	
	Public Sub AutomaticAdujst(ByRef Wave As WaveBuffer, ByRef Wave_Smooth As WaveBuffer, _
							   ByVal BasePeriod As Integer, ByVal StartPosition As Integer)
		Dim VOT As Integer, SOT As Integer
		Dim ENDT As Integer
		
		VOT = SearchFrame.FindVOT(Wave_Smooth, StartPosition, BasePeriod)
		SOT = SearchFrame.FindStart(Wave, VOT, BasePeriod) - BasePeriod
		If SOT <= 0 Then SOT = 0
		ENDT = Wave.Pointer
		If Setting_Editor_Batch_Adjust Then
			If Setting_Balance Then WaveEffects.LowPassBalance(Wave, SOT, ENDT)
			WaveEffects.Normalize(Wave, SOT, ENDT, _
				Math.Min(
					Setting_Editor_Batch_Adjust_Magnitude, _
					Analysis.GetAverageVolume(Wave, _
						SOT, _
						ENDT)
				)
			)
		End If
		VOT = SearchFrame.FindVOT(Wave_Smooth, StartPosition, BasePeriod)
		SOT = SearchFrame.FindStart(Wave, VOT, BasePeriod) - BasePeriod
		If SOT <= 0 Then SOT = 0
		If Setting_Editor_Batch_LimitConsonants Then
			WaveEffects.Normalize(Wave, SOT, VOT - 1800, Setting_Editor_Batch_LimitConsonants_Magnitude)
		End If
		If Setting_Editor_Batch_ConsonantFI Then
			Dim i As Integer
			For i = 1 To Setting_Editor_Batch_ConsonantFI_Times
				WaveEffects.FadeIn(Wave, SOT, CInt(SOT + (VOT - SOT) * Setting_Editor_Batch_ConsonantFI_Field), 0, 0)
			Next
		End If
		If Setting_Editor_Batch_SmoothenVOT Then
			Dim Envelope As PointList = New PointList()
			Analysis.GenerateEnvelope(Envelope, Wave, BasePeriod)
			If Analysis.FindMaximumSlopeInEnvelopeList(Envelope, VOT, VOT + 1000) > Setting_Editor_Batch_SmoothenVOT_Limit Then
				WaveEffects.Weaken(Wave, _
								   CInt(VOT - Setting_Editor_Batch_SmoothenVOT_Length * 0.35), _
								   CInt(VOT + Setting_Editor_Batch_SmoothenVOT_Length * 0.65), _
								   Setting_Editor_Batch_SmoothenVOT_Strength)
			End If
		End If
		If Setting_Editor_Batch_ConsonantShrink Then
			WaveEffects.Shrink(Wave, SOT, VOT + 2000, CInt(Setting_Editor_Batch_ConsonantShrink_ShrinkBy * 96000))
		End If
	End Sub
	
	Public Sub DoAdjust(ByVal Info As Object)
		Dim Wave As WaveBuffer = New WaveBuffer(5.0)
		Dim Wave_Smooth As WaveBuffer = New WaveBuffer(5.0)
		Dim Envelope As PointList = New PointList()
		Dim Recognization As PointList = New PointList()
		Dim WaveInfo As LoadResult
		Dim _Info As AnalysisInfo = CType(Info, AnalysisInfo)
		
		WaveInfo = LoadWave_MT(Wave, Wave_Smooth, Envelope, Recognization, _Info.Symbol, _Info.Pitch)
		AutomaticAdujst(Wave, Wave_Smooth, WaveInfo.BasePeriod, WaveInfo.StartPosition)
		Wave.Save(Directory & _Info.Symbol & "_" & _Info.Pitch & ".wav")
	End Sub
	
	Public Sub AdjustAll()
		Dim Threads() As Thread
		Dim ThreadQ As Integer = Environment.ProcessorCount - 1
		Dim i As Integer
		Dim PitchNum As Integer
		Dim TInfo As AnalysisInfo
		TInfo.Symbol = CurrentSymbol
		PitchNum = GetNumByPitch(CurrentPitch)
		
		ReDim Threads(ThreadQ + 1)
		'Initialization
		For i = 0 To ThreadQ
			Threads(i) = New Thread(AddressOf DoAdjust)
		Next
		While True
			For i = 0 To ThreadQ
				If Threads(i).ThreadState = ThreadState.Stopped OrElse Threads(i).ThreadState = ThreadState.Unstarted Then
					PBar.Value = CInt((PitchNum - Pitch_C2) / (Pitch_C5 - Pitch_C2) * 100)
					Threads(i) = New Thread(AddressOf DoAdjust)
					TInfo.Pitch = PitchList(PitchNum)
					Threads(i).Start(TInfo)
					PitchNum += 1
					If PitchNum > Setting_Editor_Batch_Until Then Exit While
				End If
				Thread.Sleep(10)
			Next
		End While
	End Sub
	#End Region
	
	Public Sub UpdateLists()	
		Analysis.GenerateEnvelope(MainEnvelope, MainWave, CurrentBasePeriod * Setting_EnvelopePrecision)
		Analysis.GenerateRecoList(MainRecognization, MainEnvelope)
	End Sub
	
	Public Sub UpdateSettings()
		Setting_Consonant = MainForm.CheckBox_Consonant.Checked
		Setting_DataLength = CInt(CDbl(MainForm.TextBox_DataLength.Text) * 96000)
	End Sub
	
	Public Sub DoAnalysis(ByVal Info As Object)
		Dim Wave As WaveBuffer = New WaveBuffer(5.0)
		Dim Wave_Smooth As WaveBuffer = New WaveBuffer(5.0)
		Dim Envelope As PointList = New PointList()
		Dim Recognization As PointList = New PointList()
		Dim WaveInfo As LoadResult
		Dim _CVDB As CVDB
		Dim _Info As AnalysisInfo = CType(Info, AnalysisInfo)
		
		WaveInfo = LoadWave_MT(Wave, Wave_Smooth, Envelope, Recognization, _Info.Symbol, _Info.Pitch)
		_CVDB = AddFrame(Wave, Wave_Smooth, WaveInfo.BasePeriod, WaveInfo.StartPosition)
		_CVDB.Save(Directory & _Info.Symbol & "_" & _Info.Pitch & ".cbv")
	End Sub
	
	Public Sub AnalysisAll()
		Dim Threads() As Thread
		Dim ThreadQ As Integer = Environment.ProcessorCount - 1
		Dim i As Integer
		Dim PitchNum As Integer
		Dim TInfo As AnalysisInfo
		TInfo.Symbol = CurrentSymbol
		PitchNum = GetNumByPitch(CurrentPitch)
		
		ReDim Threads(ThreadQ + 1)
		'Initialization
		For i = 0 To ThreadQ
			Threads(i) = New Thread(AddressOf DoAnalysis)
		Next
		While True
			For i = 0 To ThreadQ
				If Threads(i).ThreadState = ThreadState.Stopped OrElse Threads(i).ThreadState = ThreadState.Unstarted Then
					PBar.Value = CInt((PitchNum - Pitch_C2) / (Pitch_C5 - Pitch_C2) * 100)
					Threads(i) = New Thread(AddressOf DoAnalysis)
					TInfo.Pitch = PitchList(PitchNum)
					Threads(i).Start(TInfo)
					PitchNum += 1
					If PitchNum > Pitch_C5 Then Exit While
				End If
				Thread.Sleep(10)
			Next
		End While
	End Sub
	
	Public Sub LoadWave(ByVal FileName As Object)
		PBar.Value = 20
		
		MainWave.Load(Directory & CStr(FileName))
		If Setting_Balance Then LowPassBalance(MainWave)
		
		CurrentBasePeriod = CInt(96000 / GetFreqByPitch(CurrentPitch))
		
		If Setting_UseMovingAverage Then
			WaveEffects.MovingAverage(MainWave, MainWave_Smooth, CInt(CurrentBasePeriod * Setting_MovingAverageLength), 1)
			PBar.Value = 40
			If Setting_TwiceMovingAverage Then
				WaveEffects.MovingAverage(MainWave_Smooth, MainWave_Smooth, CInt(CurrentBasePeriod * Setting_MovingAverageLength), 1)
				If Setting_ExtraMovingAverage Then WaveEffects.MovingAverage(MainWave_Smooth, MainWave_Smooth, CInt(CurrentBasePeriod * Setting_MovingAverageLength), 1)
			End If
			PBar.Value = 60
			LowPassBalance(MainWave_Smooth)
		Else
			MainWave.CopyTo(MainWave_Smooth)
		End If
		
		If MainBox.WindowSize = 0 Or MainBox.WindowSize > MainBox.MaximumPointer _
			Then MainBox.WindowSize = MainBox.MaximumPointer
		Analysis.GenerateEnvelope(MainEnvelope, MainWave, CurrentBasePeriod * Setting_EnvelopePrecision)
		Analysis.GenerateRecoList(MainRecognization, MainEnvelope)
		PBar.Value = 80
		
		If Setting_StartPositionFixed Then
			MainBar.Bars(0) = _
				Analysis.FindIdealAnalysisStartPoint(
					MainWave_Smooth, _
					Setting_StartPositionTime, _
					CurrentBasePeriod)
		Else
			MainBar.Bars(0) = _
				Analysis.FindIdealAnalysisStartPoint(
					MainWave_Smooth, _
					Analysis.FindPeriodStartPosition(
						MainEnvelope, MainWave_Smooth, CurrentBasePeriod) + Setting_StartPositionTime, _
					CurrentBasePeriod)
		End If
		
		MainWave_StartPosition = MainBar.Bars(0)
		MainBar.Bars(1) = SearchFrame.FindNext(MainWave, MainBar.Bars(0), CurrentBasePeriod)
		MainBar.BarQ = 1
		StatusBox.Text = CStr(FileName) & ", Base period: " & CurrentBasePeriod & _
			", Base frequency: " & CInt(96000 / CurrentBasePeriod) & "HZ"
		PBar.Value = 100
		
		If Setting_Mode = EditMode.WavEditor Then
			MainBox.InnerClickBar = SearchFrame.FindVOT(MainWave_Smooth, MainWave_StartPosition, CurrentBasePeriod)
		End If
		
		MainBox.Refresh()
	End Sub
	
	Public Sub LoadCVDB(ByVal FileName As Object)
		PBar.Value = 20
		Dim i As Integer
		LoadedCVDB.Load(Directory & CStr(FileName))
		LoadedCVDB.OutputToWave(MainWave)
		
		If Setting_Balance Then LowPassBalance(MainWave)
		CurrentBasePeriod = CInt(96000 / GetFreqByPitch(CurrentPitch))
		
		If Setting_UseMovingAverage Then
			WaveEffects.MovingAverage(MainWave, MainWave_Smooth, CInt(CurrentBasePeriod * Setting_MovingAverageLength), 1)
			PBar.Value = 40
			If Setting_TwiceMovingAverage Then
				WaveEffects.MovingAverage(MainWave_Smooth, MainWave_Smooth, CInt(CurrentBasePeriod * Setting_MovingAverageLength), 1)
				If Setting_ExtraMovingAverage Then WaveEffects.MovingAverage(MainWave_Smooth, MainWave_Smooth, CInt(CurrentBasePeriod * Setting_MovingAverageLength), 1)
			End If
			PBar.Value = 60
			LowPassBalance(MainWave_Smooth)
		Else
			MainWave.CopyTo(MainWave_Smooth)
		End If
		
		If MainBox.WindowSize = 0 Or MainBox.WindowSize > MainBox.MaximumPointer _
			Then MainBox.WindowSize = MainBox.MaximumPointer
		Analysis.GenerateEnvelope(MainEnvelope, MainWave, CurrentBasePeriod * Setting_EnvelopePrecision)
		Analysis.GenerateRecoList(MainRecognization, MainEnvelope)
		PBar.Value = 80
		
		If Setting_StartPositionFixed Then
			MainBar.Bars(0) = _
				Analysis.FindIdealAnalysisStartPoint(
					MainWave_Smooth, _
					Setting_StartPositionTime, _
					CurrentBasePeriod)
		Else
			MainBar.Bars(0) = _
				Analysis.FindIdealAnalysisStartPoint(
					MainWave_Smooth, _
					Analysis.FindPeriodStartPosition(
						MainEnvelope, MainWave_Smooth, CurrentBasePeriod) + Setting_StartPositionTime, _
					CurrentBasePeriod)
		End If
		MainWave_StartPosition = MainBar.Bars(0)
		
		MainBar.Bars(0) = 0
		For i = 1 To LoadedCVDB.Header.ChunkNumber + 1
			MainBar.Bars(i) = MainBar.Bars(i - 1) + LoadedCVDB.ChunkLength(i - 1)
			MainPeriod.Points(i).X = MainBar.Bars(i)
			MainPeriod.Points(i).Y = CSng(LoadedCVDB.ChunkLength(i - 1) / 2000)
		Next
		MainBar.BarQ = LoadedCVDB.Header.ChunkNumber
		MainPeriod.PointQ = LoadedCVDB.Header.ChunkNumber
		
		StatusBox.Text = CStr(FileName) & ", Base period: " & CurrentBasePeriod & _
			", Base frequency: " & CInt(96000 / CurrentBasePeriod) & "HZ"
		PBar.Value = 100
		
		MainBox.InnerClickBar = LoadedCVDB.Header.StartPosition
		MainBox.Refresh()
	End Sub
	
	Public Function LoadWave_MT(ByRef Wave As WaveBuffer, ByRef Wave_Smooth As WaveBuffer, _
								ByRef Envelope As PointList, ByRef Recognization As PointList, _
								ByVal Symbol As String, ByVal Pitch As String) As LoadResult
		Dim ret As LoadResult
		
		Wave.Load(Directory & Symbol & "_" & Pitch & ".wav")
		If Setting_Balance Then LowPassBalance(Wave)
		ret.BasePeriod = CInt(96000 / GetFreqByPitch(Pitch))
		
		If Setting_UseMovingAverage Then
			WaveEffects.MovingAverage(Wave, Wave_Smooth, CInt(ret.BasePeriod * Setting_MovingAverageLength), 1)
			If Setting_TwiceMovingAverage Then
				WaveEffects.MovingAverage(Wave_Smooth, Wave_Smooth, CInt(ret.BasePeriod * Setting_MovingAverageLength), 1)
				If Setting_ExtraMovingAverage Then WaveEffects.MovingAverage(Wave_Smooth, Wave_Smooth, CInt(ret.BasePeriod * Setting_MovingAverageLength), 1)
			End If
			LowPassBalance(Wave_Smooth)
		Else
			MainWave.CopyTo(Wave_Smooth)
		End If
		
		Analysis.GenerateEnvelope(Envelope, Wave, ret.BasePeriod * Setting_EnvelopePrecision)
		Analysis.GenerateRecoList(Recognization, Envelope)
		
		If Setting_StartPositionFixed Then
			ret.StartPosition = _
				Analysis.FindIdealAnalysisStartPoint(
					Wave_Smooth, _
					Setting_StartPositionTime, _
					ret.BasePeriod)
		Else
			ret.StartPosition = _
				Analysis.FindIdealAnalysisStartPoint(
					Wave_Smooth, _
					Analysis.FindPeriodStartPosition(
						Envelope, Wave_Smooth, ret.BasePeriod) + Setting_StartPositionTime, _
					ret.BasePeriod)
		End If
		Return ret
	End Function
	
	Public Function AddFrame(ByRef Wave As WaveBuffer, _
							 ByRef Wave_Smooth As WaveBuffer, _
							 ByVal BasePeriod As Integer, _
							 ByVal StartPosition As Integer) As CVDB
		Dim Forward(3000) As Integer
		Dim Backward(3000) As Integer
		Dim ForwardNum As Integer, BackwardNum As Integer, FillNum As Integer
		Dim PeriodStartPosition As Integer
		Dim DataStartPosition As Integer
		Dim DataEndPosition As Integer
		Dim FSearchResult As SearchResult
		Dim BSearchResult As SearchResult
		Dim BFillResult As SearchResult
		Dim _CVDB As CVDB = New CVDB()
		
		FSearchResult = SearchFrame.ForwardSearch(Forward, Wave_Smooth, StartPosition, BasePeriod, Setting_DataLength)
		ForwardNum = FSearchResult.Num
		DataEndPosition = FSearchResult.Position
		BackwardNum = 0
		FillNum = 0
		
		If Setting_Consonant Then
			BSearchResult = SearchFrame.BackwardSearch(Backward, Wave_Smooth, StartPosition, BasePeriod)
			BackwardNum = BSearchResult.Num
			PeriodStartPosition = BSearchResult.Position
		
			BFillResult = SearchFrame.BackwardFill(Wave, PeriodStartPosition, BasePeriod)
			FillNum = BFillResult.Num
			DataStartPosition = BFillResult.Position
		Else
			DataStartPosition = StartPosition
			PeriodStartPosition = StartPosition
		End If
		
		ReDim _CVDB.ChunkLength(ForwardNum + BackwardNum + FillNum + 2)
		
		Dim i As Integer, c As Integer
		c = 0
		
		If Setting_Consonant Then
			For i = 0 To FillNum - 1
				_CVDB.ChunkLength(c) = CUShort(BasePeriod)
				c += 1
			Next
			
			For i = 0 To BackwardNum
				_CVDB.ChunkLength(c) = CUShort(Backward(BackwardNum - i))
				c += 1
			Next
		End If
		
		For i = 0 To ForwardNum
			_CVDB.ChunkLength(c) = CUShort(Forward(i))
			c += 1
		Next
		
		_CVDB.Header.Version = 2
		_CVDB.Header.Consonant = Setting_Consonant
		_CVDB.Header.StartPosition = PeriodStartPosition + 2000 - DataStartPosition
		_CVDB.Header.PeriodStartPosition = PeriodStartPosition - DataStartPosition
		_CVDB.Header.ChunkNumber = CUShort(ForwardNum + BackwardNum + FillNum - 4)
		'In avoid of unstable end.
		
		_CVDB.DataQ = DataEndPosition - DataStartPosition
		ReDim _CVDB.Data(_CVDB.DataQ + 1)
		For i = DataStartPosition To _CVDB.DataQ + DataStartPosition
			_CVDB.Data(i - DataStartPosition) = Wave.Data(i)
		Next
		
		If Not Setting_Multithread Then
			Array.Resize(MainBar.Bars, 2000)
			MainBar.Bars(0) = DataStartPosition
			
			For i = 0 To _CVDB.ChunkLength.Length - 1
				MainBar.Bars(i + 1) = MainBar.Bars(i) + _CVDB.ChunkLength(i)
			Next
			MainBar.BarQ = ForwardNum + BackwardNum + FillNum
			MainBox.Refresh()
		End If
		Return _CVDB
	End Function
End Module
