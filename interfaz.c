#include <stdio.h>
#include <math.h>
#include "interfaz.h"
#include "simulador.h"
#include "ventana.h"

#define ANCHO 65
#define ALTO  33
#define RADIO_X 30
#define RADIO_Y 15
#define PUNTOS 180

static int redondear(double x)
{
    return (int)(x < 0 ? x - 0.5 : x + 0.5);
}

void mostrar_trayecto(const NodoSimulacion* ultimo)
{
    char lienzo[ALTO][ANCHO + 1];
    double xs[PUNTOS];
    double ys[PUNTOS];
    double r_km;
    double radio;
    double v;
    double t_seg;
    double dx, dy;
    int fila, col;
    int i;
    int cant;

    if (ultimo == NULL) {
        printf("\nTodavia no hay simulaciones. Haga una desde el menu (opcion 1 o 2).\n");
        return;
    }

    radio = RT + ultimo->altitud;
    r_km = radio * CM_A_KM;
    v = velocidad_orbital(radio);
    t_seg = periodo_orbital(radio, v);

    cant = generar_trayectoria(ultimo->altitud, PUNTOS, xs, ys);

#ifdef USAR_RAYLIB
    printf("\n Abriendo ventana grafica... (ESC para volver al menu)\n");
    ventana_orbita(xs, ys, cant, RT * CM_A_KM, ultimo->altitud * CM_A_KM,
                   v * CM_A_M, t_seg);
    return;
#endif

    for (fila = 0; fila < ALTO; fila++) {
        for (col = 0; col < ANCHO; col++) {
            dx = (double)(col - ANCHO / 2) / RADIO_X;
            dy = (double)(fila - ALTO / 2) / RADIO_Y;
            if (sqrt(dx * dx + dy * dy) <= RT / radio) {
                lienzo[fila][col] = '.';
            } else {
                lienzo[fila][col] = ' ';
            }
        }
        lienzo[fila][ANCHO] = '\0';
    }

    for (i = 0; i < cant; i++) {
        col = ANCHO / 2 + redondear(xs[i] / r_km * RADIO_X);

        fila = ALTO / 2 - redondear(ys[i] / r_km * RADIO_Y);
        if (col >= 0 && col < ANCHO && fila >= 0 && fila < ALTO) {
            lienzo[fila][col] = '*';
        }
    }

    for (i = 0; i < 4; i++) {
        col = ANCHO / 2 + redondear(xs[i * PUNTOS / 4] / r_km * RADIO_X);
        fila = ALTO / 2 - redondear(ys[i * PUNTOS / 4] / r_km * RADIO_Y);
        if (col >= 0 && col < ANCHO && fila >= 0 && fila < ALTO) {
            lienzo[fila][col] = (i == 0) ? 'N' : (char)('0' + i);
        }
    }

    printf("\n TRAYECTO DE LA NAVE (ultima simulacion guardada)\n");
    printf(" Altitud: %.1f km | Velocidad: %.2f m/s | Periodo: %.2f min\n\n",
           ultimo->altitud * CM_A_KM, v * CM_A_M, t_seg / 60.0);
    for (fila = 0; fila < ALTO; fila++) {
        printf(" %s\n", lienzo[fila]);
    }

    printf("\n Referencias:  .  Tierra    *  orbita    N  posicion inicial\n");
    printf("               1, 2, 3  posiciones tras 1/4, 1/2 y 3/4 de vuelta\n");
    printf("               (t = %.1f, %.1f y %.1f min). Sentido: antihorario.\n",
           t_seg / 240.0, t_seg / 120.0, t_seg * 3.0 / 240.0);
    printf(" Nota: el dibujo NO esta a escala real. La altura (%.1f km) es solo el\n",
           ultimo->altitud * CM_A_KM);
    printf(" %.1f %% del radio terrestre, asi que la orbita casi roza la Tierra.\n",
           ultimo->altitud / RT * 100.0);
}