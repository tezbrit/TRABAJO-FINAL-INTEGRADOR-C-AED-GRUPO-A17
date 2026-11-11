
#ifndef SIMULADOR_H

#include "artemis.h"

void resolver_caso_consigna(NodoSimulacion** prim, NodoSimulacion** ult);

void mostrar_historial(const NodoSimulacion* prim);

int contar_estados(const NodoSimulacion* prim);

#define MAX_PUNTOS 360

int generar_trayectoria(double altitud, int cantidad, double xs[], double ys[]);

#endif