#ifndef CDT3READER_H
#define CDT3READER_H

#include "CDT3.h"
#include "RUtil/Structure/String.h"

extern int CDTReader_Open(String* Src);
extern void CDTReader_Close();

extern int SGtorSyllable_Read(SGtorSyllable* Dest);

extern int DBLayerEntry_Read(DBLayerEntry* Dest);
extern int SymbolLayerEntry_Read(SymbolLayerEntry* Dest);
extern int FreqLayerEntry_Read(FreqLayerEntry* Dest);
extern int FormantLayerEntry_Read(FormantLayerEntry* Dest);
extern int TransitionLayerEntry_Read(TransitionLayerEntry* Dest);

extern int CDTMap_Read(CDTMap* Dest);

extern int CDT3_Read(CDT3* Dest);

#endif
