#include "LectorAudio.h"
public:
    virtual bool leer(const char* ruta, DatosAudio& datos) const = 0;
    virtual ~LectorAudio() {}
};
