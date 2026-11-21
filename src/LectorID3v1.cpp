#include "LectorID3v1.h"
#include <fstream>
using namespace std;

void LectorID3v1::copiarCampo(char* destino, int capacidad, const char* origen, int longitud) const {
    int n = longitud;
    while (n > 0 && (origen[n - 1] == ' ' || origen[n - 1] == '\0')) {
        n--;
    }
    if (n >= capacidad) n = capacidad - 1;
    for (int i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
    destino[n] = '\0';
}

int LectorID3v1::convertirAnio(const char* origen) const {
    int anio = 0;
    for (int i = 0; i < 4; i++) {
        if (origen[i] < '0' || origen[i] > '9') return 0;
        anio = anio * 10 + (origen[i] - '0');
    }
    return anio;
}

bool LectorID3v1::leer(const char* ruta, DatosAudio& datos) const {
    if (ruta == nullptr || ruta[0] == '\0') return false;

    ifstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) return false;

    archivo.seekg(0, ios::end);
    long tamano = static_cast<long>(archivo.tellg());
    if (tamano < 128) return false;

    archivo.seekg(-128, ios::end);
    char buffer[128];
    archivo.read(buffer, 128);
    if (!archivo) return false;

    if (buffer[0] != 'T' || buffer[1] != 'A' || buffer[2] != 'G') return false;

    DatosAudio temporal;
    copiarCampo(temporal.titulo, 128, buffer + 3, 30);
    copiarCampo(temporal.artista, 128, buffer + 33, 30);
    copiarCampo(temporal.album, 128, buffer + 63, 30);
    temporal.anio = convertirAnio(buffer + 93);
    temporal.tamanoBytes = tamano;
    datos = temporal;
    return true;
}
