#include <stdio.h>
#include <stdlib.h>     // malloc (pedir memoria) y free (devolverla)
#include <math.h>       // sqrt (raiz cuadrada) y fabs (valor absoluto)
#include "simulador.h"

#define GRAVEDAD_SUPERFICIE_SI 9.80665   // [m/s^2]

// FUNCION VELOCIDAD ORBITAL: calcula la velocidad que necesita la nave para mantenerse en orbita circular
double velocidad_orbital(double r)
{
    return sqrt((G * MT) / r);   // G y MT vienen de artemis.h
}

// FUNCION PERIODO ORBITAL: calcula cuanto tarda la nave en dar una vuelta completa
double periodo_orbital(double r, double v)
{
    return (2.0 * PI * r) / v;   // PI esta definido en artemis.h
}

// FUNCION ACELERACION CENTRIPETA: calcula la aceleracion que sienten los astronautas
double aceleracion_centripeta(double v, double r)
{
    return (v * v) / r;   // v al cuadrado dividido r
}

// FUNCION FUERZA GRAVITATORIA: calcula la fuerza que hace la Tierra sobre la nave
double fuerza_gravitatoria(double m, double r)
{
    return (G * MT * m) / (r * r);   // r*r = r al cuadrado
}

// FUNCION DESVIACION LATERAL: calcula cuanto se desplaza la nave lateralmente si recibe un pulso lateral
double desviacion_lateral(double a, double dt)
{
    return 0.5 * a * (dt * dt);
}

// FUNCION ENCOLAR: agrega un estado al final de la cola de simulaciones
void encolar(NodoSimulacion** prim, NodoSimulacion** ult,
        double altitud, double velocidad, double desviacion)
{
    NodoSimulacion* q = (NodoSimulacion*)malloc(sizeof(NodoSimulacion));

    if (q == NULL) {
        printf("Error: no hay memoria suficiente para guardar el estado.\n");
        return;
    }

    q->altitud = altitud;
    q->velocidad = velocidad;
    q->desviacion = desviacion;
    q->prox = NULL;

    if (*prim == NULL) {
        *prim = q;
        *ult = q;
    } else {
        (*ult)->prox = q;
        *ult = q;
    }
}

// FUNCION LIBERAR COLA: borra todos los estados guardados en la cola de simulaciones
void liberar_cola(NodoSimulacion** prim, NodoSimulacion** ult)
{
    NodoSimulacion* actual = *prim;
    NodoSimulacion* siguiente;

    while (actual != NULL) {
        siguiente = actual->prox;
        free(actual);
        actual = siguiente;
    }

    *prim = NULL;
    *ult = NULL;
}

// MOSTRAR RESULTADOS

// FUNCION CONTAR ESTADOS: devuelve la cantidad de estados guardados en la cola
int contar_estados(const NodoSimulacion* prim)
{
    int cantidad = 0;
    const NodoSimulacion* actual = prim;

    while (actual != NULL) {
        cantidad++;
        actual = actual->prox;
    }
    return cantidad;
}

// FUNCION MOSTRAR HISTORIAL: muestra todos los estados guardados en la cola de simulaciones
void mostrar_historial(const NodoSimulacion* prim)
{
    const NodoSimulacion* actual = prim;
    int numero = 1;

    if (prim == NULL) {
        printf("\nTodavia no hay simulaciones guardadas. Haga una desde el menu.\n");
        return;
    }

    printf("\n HISTORIAL DE SIMULACIONES (%d guardadas)\n", contar_estados(prim));
    printf(" Nro | Altitud [km] | Vel. orbital [m/s] | Desviacion [m]\n");
    printf(" ----+--------------+--------------------+---------------\n");

    while (actual != NULL) {
        printf(" %3d | %12.2f | %18.2f | %13.2f\n",
            numero,
                actual->altitud * CM_A_KM,      // cm -> km
                actual->velocidad * CM_A_M,     // cm/s -> m/s
                actual->desviacion * CM_A_M);   // cm -> m
        actual = actual->prox;
        numero++;
    }
}

// FUNCION GENERAR TRAYECTORIA: calcula los puntos de la orbita circular para graficar 
int generar_trayectoria(double altitud, int cantidad, double xs[], double ys[])
{
    double r;
    double angulo; // en radianes
    int i; // numero de punto

    if (cantidad < 1 || cantidad > MAX_PUNTOS) {
        return 0;
    }

    r = RT + altitud;

    for (i = 0; i < cantidad; i++) {
        angulo = 2.0 * PI * i / cantidad;
        xs[i] = r * cos(angulo) * CM_A_KM;
        ys[i] = r * sin(angulo) * CM_A_KM;
    }
    return cantidad;
}

// FUNCION RESOLVER CASO CONSIGNA: calcula y muestra los resultados del caso de la consigna
void resolver_caso_consigna(NodoSimulacion** prim, NodoSimulacion** ult)
{
    double r;
    double v;
    double fg;
    double fc;
    double dif;
    double t_seg;
    double ac;
    double v_lat;
    double desv;

    r = RT + H_ORBITA;
    v = velocidad_orbital(r);
    fg = fuerza_gravitatoria(M_ORION, r); // pregunta 1: fuerza de gravedad
    fc = (M_ORION * v * v) / r;           // pregunta 1: fuerza centripeta necesaria
    dif = fabs(fg - fc);
    t_seg = periodo_orbital(r, v);        // pregunta 2
    ac = aceleracion_centripeta(v, r);    // pregunta 3
    v_lat = A_LAT * DT_PULSO;             // pregunta 4: velocidad lateral = a * dt
    desv = desviacion_lateral(A_LAT, DT_PULSO);   // pregunta 4: desviacion

    printf("\n============================================================\n");
    printf(" CASO DE LA CONSIGNA (h = %.0f km, m = %.0f kg)\n",
           H_ORBITA * CM_A_KM, M_ORION * G_A_KG);
    printf("============================================================\n");

    printf("\n PREGUNTA 1 - Fuerza centripeta y velocidad orbital\n");
    printf("  Si la gravedad hace de fuerza centripeta:\n");
    printf("     G*MT*m/r^2 = m*v^2/r   ->   v = raiz(G*MT/r)\n");
    printf("  Fg = %.2f N\n", fg * DINA_A_N);
    printf("  Fc = %.2f N\n", fc * DINA_A_N);
    printf("  Diferencia = %.2e N -> son iguales (queda demostrado)\n", dif * DINA_A_N);
    printf("  Velocidad orbital v = %.2f m/s (%.2f km/s)\n",
           v * CM_A_M, v * CM_A_M / 1000.0);

    printf("\n PREGUNTA 2 - Periodo orbital\n");
    printf("  T = 2*pi*r / v = %.2f s = %.2f min\n", t_seg, t_seg / 60.0);

    printf("\n PREGUNTA 3 - Aceleracion centripeta de los astronautas\n");
    printf("  ac = v^2 / r = %.4f m/s^2 (%.3f g)\n",
           ac * CM_A_M, ac * CM_A_M / GRAVEDAD_SUPERFICIE_SI);
    printf("  (Flotan porque estan en caida libre, no porque falte gravedad.)\n");

    printf("\n PREGUNTA 4 - Pulso lateral de %.2f m/s^2 durante %.1f s\n",
           A_LAT * CM_A_M, DT_PULSO);
    printf("  Velocidad lateral ganada: a*dt = %.2f m/s\n", v_lat * CM_A_M);
    printf("  Desviacion lateral: 1/2*a*dt^2 = %.2f m\n", desv * CM_A_M);
    printf("  Trayectoria: la orbita deja de ser un circulo perfecto y pasa a\n");
    printf("  ser una elipse, porque ya no se cumple v = raiz(G*MT/r).\n");

    encolar(prim, ult, H_ORBITA, v, desv);   // guardamos este resultado en el historial
    printf("\n (Resultado guardado en el historial.)\n");
}