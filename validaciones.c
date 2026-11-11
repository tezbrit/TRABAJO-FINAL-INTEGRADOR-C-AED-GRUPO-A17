#include <stdio.h>
#include <stdlib.h> // exit (para terminar el programa si se cierra el teclado)
#include <math.h>   // isfinite (para solo dejar ingresar numeros reales, no nan ni infinito)
#include <ctype.h>  // isspace (dice si un caracter es un espacio)
#include "validaciones.h"


static void entradaCerrada(void)
{
    printf("\nSe cerro la entrada de datos. Fin del programa.\n");
    exit(0);   // termina el programa completo, estemos donde estemos
}

static int limpiarLinea(void)
{
    int c;  // caracter leido como int para poder comparar con EOF
    int sobraba = 0;

    while ((c = getchar()) != '\n' && c != EOF) {   // leemos hasta ENTER o hasta EOF
        if (!isspace(c)) {
            sobraba = 1;
        }
    }
    return sobraba;
}

int pedirEnteroRango(const char* mensaje, int min, int max) {
    int valor;
    int leidos;
    int sobraba;

    do {
        printf("%s", mensaje);
        leidos = scanf("%d", &valor);

        if (leidos == EOF) {
            entradaCerrada();
        }

        sobraba = limpiarLinea();

        if (leidos != 1 || sobraba) {
            printf("Error: Entrada invalida. Ingrese un numero entero.\n");
        } else if (valor < min || valor > max) {
            printf("Error: Opcion incorrecta. Ingrese un numero entre %d y %d.\n", min, max);
        }

    } while (leidos != 1 || sobraba || valor < min || valor > max);

    return valor;
}

double pedirDoublePositivo(const char* mensaje) {
    double valor;
    int leidos;
    int sobraba;

    do {
        printf("%s", mensaje);
        leidos = scanf("%lf", &valor);

        if (leidos == EOF) {
            entradaCerrada();
        }

        sobraba = limpiarLinea();

        if (leidos != 1 || sobraba) {
            printf("Error: Entrada invalida. La nave Orion solo acepta valores numericos.\n");
        } else if (!isfinite(valor)) {
            
            printf("Error: Ese valor no es un numero real (no se aceptan nan ni infinito).\n");
        } else if (valor < 0) {
            printf("Error: Este parametro fisico no puede ser negativo.\n");
        }

    } while (leidos != 1 || sobraba || !isfinite(valor) || valor < 0);

    return valor;
}

double pedirDoubleRango(const char* mensaje, double min, double max) {
    double valor;
    int leidos;
    int sobraba;

    do {
        printf("%s", mensaje);
        leidos = scanf("%lf", &valor);

        if (leidos == EOF) {
            entradaCerrada();
        }

        sobraba = limpiarLinea();

        if (leidos != 1 || sobraba) {
            printf("Error: Entrada invalida. Ingrese un numero.\n");
        } else if (!isfinite(valor)) {
            printf("Error: Ese valor no es un numero real (no se aceptan nan ni infinito).\n");
        } else if (valor < min || valor > max) {
            printf("Error: Valor fuera de rango de orbita LEO. Debe estar entre %.2e y %.2e cm.\n", min, max);
        }

    } while (leidos != 1 || sobraba || !isfinite(valor) || valor < min || valor > max);

    return valor;
}