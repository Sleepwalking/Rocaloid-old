#!/bin/bash
outfile=$2
loopcount=$1
VERSION="1.6"

if [ $# -lt 2 ]; then
echo $0 " <鬼畜次数> <CVS文件输出>"
exit 0;
fi

echo "#CVS $VERSION" > $outfile
echo "CVS" >> $outfile
echo "	SegmentListQ $loopcount" >> $outfile
echo "	SegmentList" >> $outfile
for ((i=0; i<loopcount; i++));
do
echo "		Segment" >> $outfile 
echo "			TPhoneListQ 4" >> $outfile 
echo "			TPhoneList" >> $outfile 
echo "				TPhone" >> $outfile 
echo "					Start Type New Symbol m3 End" >> $outfile 
echo "					Dest Type New Symbol e End" >> $outfile 
echo "					Transition StartRatio 0 EndRatio 1 Time 0.130843749999999 End" >> $outfile 
echo "				End" >> $outfile 
echo "				TPhone" >> $outfile 
echo "					Start Type Preserved Preserved 2 End" >> $outfile 
echo "					Dest Type New Symbol i End" >> $outfile 
echo "					Transition StartRatio 0 EndRatio 0.6 Time 0.0853333333333328 End" >> $outfile 
echo "				End" >> $outfile 
echo "				TPhone" >> $outfile 
echo "					Start Type Preserved Preserved 1 End" >> $outfile 
echo "					Dest Type Preserved Preserved 2 End" >> $outfile 
echo "					Transition StartRatio 0.6 EndRatio 0.6 Time 0.149333333333332 End" >> $outfile 
echo "				End" >> $outfile 
echo "				TPhone" >> $outfile 
echo "					Start Type Preserved Preserved 1 End" >> $outfile 
echo "					Dest Type Preserved Preserved 2 End" >> $outfile 
echo "					Transition StartRatio 0.6 EndRatio 1 Time 0.106666666666666 End" >> $outfile 
echo "				End" >> $outfile 
echo "			End" >> $outfile 
echo "			FreqListQ 3" >> $outfile 
echo "			FreqList" >> $outfile 
echo "				FreqSet Time 0 Freq 260.1626 End" >> $outfile 
echo "				FreqSet Time 0.130843749999999 Freq 260.1626 End" >> $outfile 
echo "				FreqSet Time 0.472177083333331 Freq 260.1626 End" >> $outfile 
echo "			End" >> $outfile 
echo "			Effects" >> $outfile 
echo "				ElistEnabled True" >> $outfile 
echo "				PElopeEnabled True" >> $outfile 
echo "				EnvelopeListQ 2" >> $outfile 
echo "				EnvelopeList" >> $outfile 
echo "					EnvelopeSet Time 0 Amplitude 1 End" >> $outfile 
echo "					EnvelopeSet Time 0.472177083333331 Amplitude 1 End" >> $outfile 
echo "				End" >> $outfile 
echo "				PresetedEnvelope ADSR" >> $outfile 
echo "				ADSR Amplitude 1 Attack 0.06 Decline 0.1 Release 0.07 End" >> $outfile 
echo "				OpennessList 1 0.7 0.58 0.58 0.5" >> $outfile 
echo "			End" >> $outfile 
echo "			StartTime $i" >> $outfile 
echo "		End" >> $outfile;
done
echo "	End" >> $outfile;
echo "End" >> $outfile;
