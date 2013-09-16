#include "Demapper.h"
#include <string.h>

_Constructor_ (FormantLayerPartialEntry)
{
    memset(Dest, sizeof(FormantLayerPartialEntry), 1);
    String_Ctor(& Dest -> FPhone);
}

_Destructor_ (FormantLayerPartialEntry)
{
    String_Dtor(& Dest -> FPhone);
}
