#pragma once
#include "Cancion.h"
#include <iostream>

using namespace std;

class MotorOrdenamiento {
private:
    static void intercambiar(Cancion*& a, Cancion*& b);
    static int particionar(Cancion** arreglo, int bajo, int alto);
    static void quickSortRecursivo(Cancion** arreglo, int bajo, int alto);
    static void mezclar(Cancion** arreglo, int izquierda, int medio, int derecha);
    static void mergeSortRecursivo(Cancion** arreglo, int izquierda, int derecha);

public:
    static void ordenarInsercion(Cancion** arreglo, int cantidad);
    static void ordenarQuickSort(Cancion** arreglo, int cantidad);
    static void ordenarMergeSort(Cancion** arreglo, int cantidad);
};