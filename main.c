#include <stdio.h>          // printf
#include "artemis.h"        // NodoSimulacion y ejecutar_simulacion (modulo de logica)
#include "validaciones.h"   // pedirEnteroRango (ingreso seguro de datos)
#include "simulador.h"      // resolver_caso_consigna, mostrar_historial, contar_estados
#include "interfaz.h"       // mostrar_trayecto (dibujo de la orbita en consola)

static void mostrar_menu(int guardadas)
{
    printf("\n============================================================\n");
    printf("   ARTEMIS - ORION EN ORBITA TERRESTRE BAJA (LEO)\n");
    printf("============================================================\n");
    printf("  1) Simular con mis propios datos (altitud y pulso)\n");
    printf("  2) Resolver el caso de la consigna (las 4 preguntas)\n");
    printf("  3) Ver historial de simulaciones (%d guardadas)\n", guardadas);
    printf("  4) Ver el trayecto de la nave (dibujo de la ultima simulacion)\n");
    printf("  0) Salir\n");
    printf("============================================================\n");
}


int main(void)
{
    NodoSimulacion* prim = NULL;
    NodoSimulacion* ult = NULL;
    int opcion;

    printf("\n  Bienvenido al simulador de la mision ARTEMIS.\n");
    printf("  Situacion-Problema 2: insercion y estabilidad en orbita LEO.\n");

    do {
        mostrar_menu(contar_estados(prim));
        opcion = pedirEnteroRango("Elija una opcion (0-4): ", 0, 4);    // valida tipo y rango

        switch (opcion) {
        case 1:
            ejecutar_simulacion(&prim, &ult);
            break;
        case 2:
            resolver_caso_consigna(&prim, &ult);
            break;
        case 3:
            mostrar_historial(prim);
            break;
        case 4:
            mostrar_trayecto(ult);
            break;
        case 0:
            printf("\n  ¡Fin de la simulacion!\n");
            break;
        }
    } while (opcion != 0);

    liberar_cola(&prim, &ult);
    return 0;
}