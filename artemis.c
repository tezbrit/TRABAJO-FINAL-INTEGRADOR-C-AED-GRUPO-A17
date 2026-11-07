#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simulador.h"


void ejecutar_simulacion(NodoSimulacion** prim) {
    
    // 1. Declaración de variables
    double h, dt, r, v, T_seg, T_min, ac, desviacion;

    printf("Ingrese la altitud de la órbita (h) en centímetros: ");
    scanf("%lf", &h);
    
    printf("Ingrese duración del pulso lateral (dt) en segundos: ");
    scanf("%lf", &dt);

    printf("\n--- RESULTADOS ---\n");
    printf("calculando trayectoria...\n")
}