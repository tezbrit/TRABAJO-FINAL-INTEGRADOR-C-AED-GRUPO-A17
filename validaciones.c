#include <stdio.h>
#include "validaciones.h"
int pedirEnteroRango(const char* mensaje, int min, int max) {
    int valor;
    int leidos;
    
    do {
        printf("%s", mensaje);
        leidos = scanf("%d", &valor);
        
        // Limpia el buffer para evitar el bucle infinito
        while(getchar() != '\n'); 
        
        if (leidos != 1) {
            printf("Error: Entrada invalida. Ingrese un numero entero.\n");
        } else if (valor < min || valor > max) {
            printf("Error: Opcion incorrecta. Ingrese un numero entre %d y %d.\n", min, max);
        }
        
    } while (leidos != 1 || valor < min || valor > max);
    
    return valor;
}