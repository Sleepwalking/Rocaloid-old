#ifndef CDT3WRITER_H
#define CDT3WRITER_H

#include "../../../RUtil/RUtil.h"
#include "CDT3.h"

extern void CDTWriter_Save();
extern void CDTWriter_Write(String* Src);

extern int SGtorSyllable_Write(SGtorSyllable* Dest);

extern int DBLayerEntry_Write(DBLayerEntry* Dest);
extern int SymbolLayerEntry_Write(SymbolLayerEntry* Dest);
extern int FreqLayerEntry_Write(FreqLayerEntry* Dest);
extern int FormantLayerEntry_Write(FormantLayerEntry* Dest);
extern int TransitionLayerEntry_Write(TransitionLayerEntry* Dest);

extern int CDTMap_Write(CDTMap* Dest);

extern int CDT3_Write(CDT3* Dest);

#endif
