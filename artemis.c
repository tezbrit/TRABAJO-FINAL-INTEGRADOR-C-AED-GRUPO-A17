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

    // 2. Ejecución de algoritmos de simulación en CGS
    r = RT + h;
    v = sqrt((G * MT) / r); 
    T_seg = (2.0 * M_PI * r) / v;
    T_min = T_seg / 60.0;
    ac = (v * v) / r;
    desviacion = 0.5 * A_LAT * (dt * dt);

    printf("\n--- RESULTADOS ---\n");
    printf("Velocidad orbital: %.2f cm/s\n", v);
    printf("Período: %.2f s (%.2f min)\n", T_seg, T_min);
    printf("Aceleración centrípeta: %.2f cm/s^2\n", ac);
    printf("Desviación lateral: %.2f cm\n\n", desviacion);
}