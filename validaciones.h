#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// Pide un numero entero entre min y max
int pedirEnteroRango(const char* mensaje, int min, int max);

// Pide un numero real que no sea negativo
double pedirDoublePositivo(const char* mensaje);

// Pide un numero real entre min y max
double pedirDoubleRango(const char* mensaje, double min, double max);

#endif