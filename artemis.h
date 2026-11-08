#ifndef ARTEMIS_H
#define ARTEMIS_H

/*
 * artemis.h - Situación Problema 2: Inserción y estabilidad en órbita LEO
 * Declaraciones de constantes, tipos y prototipos de la lógica de simulación.
 *
 * Todas las magnitudes internas están en sistema CGS (cm, g, s).
 * Para mostrar resultados en SI usar los factores de conversión de abajo.
 */

/* ---------- Constantes físicas (CGS) ---------- */
#define G          6.674e-8   /* Constante de gravitación [cm^3 / (g s^2)] */
#define MT         5.972e27   /* Masa de la Tierra [g]                     */
#define RT         6.371e8    /* Radio terrestre medio [cm]                */
#define A_LAT_CGS  50.0       /* Aceleración del propulsor lateral [cm/s^2] (0,50 m/s^2) */
#define A_LAT      A_LAT_CGS  /* Alias: artemis.c usa este nombre                          */

/* ---------- Datos del escenario (CGS) ---------- */
#define H_ORBITA   1.92e7     /* Altitud de la órbita de estacionamiento [cm] (192 km) */
#define M_ORION    3.3e7      /* Masa de Orion en órbita [g] (33.000 kg)               */
#define DT_PULSO   10.0       /* Duración del pulso lateral [s]                        */
#define PI         3.14159265358979

/* ---------- Rangos válidos para validar entradas (CGS) ---------- */
#define H_MIN      1.6e7      /* 160 km: por debajo, el rozamiento atmosférico impide la órbita */
#define H_MAX      2.0e8      /* 2.000 km: límite superior de la órbita terrestre baja (LEO)    */

/* ---------- Conversión CGS -> SI ---------- */
#define CM_A_M     0.01       /* cm   -> m    */
#define CM_A_KM    1.0e-5     /* cm   -> km   */
#define G_A_KG     0.001      /* g    -> kg   */
#define DINA_A_N   1.0e-5     /* dina -> N    */

/* ---------- Estructura de datos: nodo de la cola de simulación ---------- */
typedef struct NodoSimulacion {
    double altitud;              /* Altitud sobre la superficie [cm]        */
    double velocidad;            /* Velocidad orbital [cm/s]                */
    double desviacion;           /* Desviación lateral acumulada [cm]       */
    struct NodoSimulacion* prox; /* Siguiente nodo de la cola (NULL = fin)  */
} NodoSimulacion;

/* ---------- Prototipos: cálculos físicos ---------- */
double velocidad_orbital(double r);                  /* v = sqrt(G*MT / r)        */
double periodo_orbital(double r, double v);          /* T = 2*PI*r / v            */
double aceleracion_centripeta(double v, double r);   /* ac = v^2 / r              */
double fuerza_gravitatoria(double m, double r);      /* F = G*MT*m / r^2          */
double desviacion_lateral(double a, double dt);      /* d = 0,5 * a * dt^2        */

/* ---------- Prototipos: manejo de la cola ---------- */
void encolar(NodoSimulacion** prim, NodoSimulacion** ult,
             double altitud, double velocidad, double desviacion);
void liberar_cola(NodoSimulacion** prim, NodoSimulacion** ult);

/* ---------- Prototipo principal ---------- */
void ejecutar_simulacion(NodoSimulacion** prim, NodoSimulacion** ult);

#endif /* ARTEMIS_H */
