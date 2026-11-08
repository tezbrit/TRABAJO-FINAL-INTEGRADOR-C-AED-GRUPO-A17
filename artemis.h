#ifndef ARTEMIS_H
#define ARTEMIS_H

// Constantes físicas en sistema CGS (centímetros, gramos, segundos)
#define G 6.674e-8
#define MT 5.972e27
#define RT 6.371e8
#define A_LAT_CGS 50.0
#define A_LAT A_LAT_CGS

// Datos del escenario en CGS
#define H_ORBITA 1.92e7
#define M_ORION 3.3e7
#define DT_PULSO 10.0
#define PI 3.14159265358979

// Rango válido de altitud para la órbita LEO en CGS (160 km a 2.000 km)
#define H_MIN 1.6e7
#define H_MAX 2.0e8

// Factores de conversión de CGS a SI
#define CM_A_M 0.01
#define CM_A_KM 1.0e-5
#define G_A_KG 0.001
#define DINA_A_N 1.0e-5

// Definición de la estructura de datos (Nodo de la cola)
typedef struct NodoSimulacion {
    double altitud;
    double velocidad;
    double desviacion;
    struct NodoSimulacion* prox;
} NodoSimulacion;

// Prototipos de funciones de cálculo físico
double velocidad_orbital(double r);
double periodo_orbital(double r, double v);
double aceleracion_centripeta(double v, double r);
double fuerza_gravitatoria(double m, double r);
double desviacion_lateral(double a, double dt);

// Prototipos de funciones de manejo de la cola
void encolar(NodoSimulacion** prim, NodoSimulacion** ult, double altitud, double velocidad, double desviacion);
void liberar_cola(NodoSimulacion** prim, NodoSimulacion** ult);

// Prototipos de funciones públicas
void ejecutar_simulacion(NodoSimulacion** prim, NodoSimulacion** ult);

#endif
