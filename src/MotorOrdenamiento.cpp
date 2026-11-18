#include "../include/MotorOrdenamiento.h"

void MotorOrdenamiento::intercambiar(Cancion*& a, Cancion*& b) {
    Cancion* temp = a;
    a = b;
    b = temp;
}

void MotorOrdenamiento::ordenarInsercion(Cancion** arreglo, int cantidad) {
    if (arreglo == nullptr || cantidad <= 1) return;

    for (int i = 1; i < cantidad; i++) {
        Cancion* clave = *(arreglo + i);
        int j = i - 1;

        while (j >= 0 && *clave < *(*(arreglo + j))) {
            *(arreglo + j + 1) = *(arreglo + j);
            j--;
        }
        *(arreglo + j + 1) = clave;
    }
}

int MotorOrdenamiento::particionar(Cancion** arreglo, int bajo, int alto) {
    Cancion* pivote = *(arreglo + alto);
    int i = bajo - 1;

    for (int j = bajo; j < alto; j++) {
        if (*(*(arreglo + j)) < *pivote) {
            i++;
            intercambiar(*(arreglo + i), *(arreglo + j));
        }
    }
    intercambiar(*(arreglo + i + 1), *(arreglo + alto));
    return i + 1;
}

void MotorOrdenamiento::quickSortRecursivo(Cancion** arreglo, int bajo, int alto) {
    if (bajo < alto) {
        int pi = particionar(arreglo, bajo, alto);
        quickSortRecursivo(arreglo, bajo, pi - 1);
        quickSortRecursivo(arreglo, pi + 1, alto);
    }
}

void MotorOrdenamiento::ordenarQuickSort(Cancion** arreglo, int cantidad) {
    if (arreglo == nullptr || cantidad <= 1) return;
    quickSortRecursivo(arreglo, 0, cantidad - 1);
}

void MotorOrdenamiento::mezclar(Cancion** arreglo, int izquierda, int medio, int derecha) {
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    Cancion** L = new Cancion*[n1];
    Cancion** R = new Cancion*[n2];

    for (int i = 0; i < n1; i++) {
        *(L + i) = *(arreglo + izquierda + i);
    }
    for (int j = 0; j < n2; j++) {
        *(R + j) = *(arreglo + medio + 1 + j);
    }

    int i = 0;
    int j = 0;
    int k = izquierda;

    while (i < n1 && j < n2) {
        if (*(*(L + i)) < *(*(R + j)) || *(*(L + i)) == *(*(R + j))) {
            *(arreglo + k) = *(L + i);
            i++;
        } else {
            *(arreglo + k) = *(R + j);
            j++;
        }
        k++;
    }

    while (i < n1) {
        *(arreglo + k) = *(L + i);
        i++;
        k++;
    }

    while (j < n2) {
        *(arreglo + k) = *(R + j);
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void MotorOrdenamiento::mergeSortRecursivo(Cancion** arreglo, int izquierda, int derecha) {
    if (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        mergeSortRecursivo(arreglo, izquierda, medio);
        mergeSortRecursivo(arreglo, medio + 1, derecha);
        mezclar(arreglo, izquierda, medio, derecha);
    }
}

void MotorOrdenamiento::ordenarMergeSort(Cancion** arreglo, int cantidad) {
    if (arreglo == nullptr || cantidad <= 1) return;
    mergeSortRecursivo(arreglo, 0, cantidad - 1);
}