#include "Synthesizer.h"
#include "CVEGlobal.h"
#include "DSPInclude.h"
#include <malloc.h>

_Constructor_ (Synthesizer)
{
    SpeechMixer_Ctor(& Dest -> SubSynth);
    Dest -> SynthBuffer = (float*)malloc(sizeof(float) * SampleRate * 1);
    Dest -> CurrentTime = 0;
    Dest -> CurrentSylIndex = 0;
    Dest -> BufferPos = 0;
}

_Destructor_ (Synthesizer)
{
    SpeechMixer_Dtor(& Dest -> SubSynth);
    free(Dest -> SynthBuffer);
}

void SynthesizerSendback_Free(SynthesizerSendback *Dest)
{
    free(Dest -> Data);
}

void Synthesizer_SetCVS(Synthesizer *Dest, CVS3 *Src)
{
    Dest -> VocalScript = Src;
    Dest -> CurrentTime = 0;
    Dest -> CurrentSylIndex = 0;
    Dest -> BufferPos = 0;
    Boost_FloatSet(Dest -> SynthBuffer, 0, SampleRate);
}

#define VocalScript (Dest -> VocalScript)
#define CurrentTime (Dest -> CurrentTime)
#define CurrentSylIndex (Dest -> CurrentSylIndex)
#define CurrentSyllable (VocalScript -> SyllableList[CurrentSylIndex])
#define NextSyllable (VocalScript -> SyllableList[CurrentSylIndex + 1])
SynthesizerSendback Synthesizer_Synthesis(Synthesizer *Dest)
{
    SynthesizerSendback Ret;
    if(CurrentSylIndex == VocalScript -> SyllableList_Index)
    {
        //Last Syllable
    }else if(CurrentTime < CurrentSyllable.EndTime && CurrentTime < NextSyllable.StartTime)
    {
        //Default Synthesis
        //Only CurrentTime is changed
    }else if(CurrentSyllable.EndTime < NextSyllable.StartTime)
    {
        //Silence Synthesis
        //Switch to next syllable when finished.
    }else
    {
        //Mix Synthesis
        //Synthesize CurrentSyllable first, then synthesize NextSyllable
        //    until CurrentSyllable ends.
        //Switch to next syllable when finished.
    }
    return Ret;
}
