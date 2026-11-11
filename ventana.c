#ifdef USAR_RAYLIB

#include <math.h>
#include "raylib.h"
#include "ventana.h"

#define ANCHO_VENTANA   900
#define ALTO_VENTANA    720
#define RADIO_ORBITA_PX 280.0f
#define SEG_POR_VUELTA  12.0f

// FUNCION VENTANA ORBITA: dibuja la orbita y la nave en una ventana grafica a partir de los puntos calculados en simulador.c
void ventana_orbita(const double xs[], const double ys[], int cantidad,
                    double radio_tierra_km, double altitud_km,
                    double velocidad_ms, double periodo_seg)
{
    const int cx = ANCHO_VENTANA / 2;
    const int cy = ALTO_VENTANA / 2;
    float escala;
    float tierra_px;
    float tiempo = 0.0f;
    float multiplicador = 1.0f;
    int pausa = 0;
    float vueltas;
    float posicion;
    float fraccion;
    int i0, i1;
    int i;
    int nx, ny;
    float x, y;

    if (cantidad < 2) {
        return;
    }

    escala = RADIO_ORBITA_PX / (float)(radio_tierra_km + altitud_km);
    tierra_px = (float)radio_tierra_km * escala;

    SetTraceLogLevel(LOG_WARNING); // quitamos mensajes de raylib, dejamos solo errores y advertencias
    InitWindow(ANCHO_VENTANA, ALTO_VENTANA, "ARTEMIS - Orion en orbita terrestre baja (LEO)");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        
        if (IsKeyPressed(KEY_SPACE)) {
            pausa = !pausa;
        }
        if (IsKeyPressed(KEY_UP) && multiplicador < 8.0f) {
            multiplicador *= 2.0f;
        }
        if (IsKeyPressed(KEY_DOWN) && multiplicador > 0.25f) {
            multiplicador /= 2.0f;
        }
        if (!pausa) {
            tiempo += GetFrameTime() * multiplicador;
        }

        vueltas = tiempo / SEG_POR_VUELTA;
        posicion = (float)fmod(vueltas, 1.0) * cantidad;
        i0 = (int)posicion;
        i1 = (i0 + 1) % cantidad;
        fraccion = posicion - (float)i0;
        x = (float)(xs[i0] + (xs[i1] - xs[i0]) * fraccion);
        y = (float)(ys[i0] + (ys[i1] - ys[i0]) * fraccion);
        nx = cx + (int)(x * escala);
        ny = cy - (int)(y * escala);

        BeginDrawing();
        ClearBackground((Color){ 10, 12, 30, 255 });

        DrawCircle(cx, cy, tierra_px, (Color){ 30, 90, 200, 255 });

        for (i = 0; i < cantidad; i++) {
            int j = (i + 1) % cantidad;
            DrawLine(cx + (int)(xs[i] * escala), cy - (int)(ys[i] * escala),
                     cx + (int)(xs[j] * escala), cy - (int)(ys[j] * escala), LIGHTGRAY);
        }

        DrawCircle(cx + (int)(xs[0] * escala), cy - (int)(ys[0] * escala), 3.0f, YELLOW);
        DrawCircle(nx, ny, 6.0f, GREEN);
        DrawText("Orion", nx + 10, ny - 8, 16, WHITE);

        // Panel de datos (TextFormat arma un texto como printf)
        DrawText(TextFormat("Altitud: %.1f km", altitud_km), 20, 20, 20, WHITE);
        DrawText(TextFormat("Velocidad orbital: %.2f m/s", velocidad_ms), 20, 46, 20, WHITE);
        DrawText(TextFormat("Periodo: %.2f min", periodo_seg / 60.0), 20, 72, 20, WHITE);
        DrawText(TextFormat("Tiempo simulado: %.1f min", vueltas * periodo_seg / 60.0), 20, 98, 20, SKYBLUE);
        DrawText(TextFormat("Vuelta numero: %d", (int)vueltas + 1), 20, 124, 20, SKYBLUE);
        DrawText(TextFormat("Animacion: x%.2f %s", multiplicador, pausa ? "(PAUSA)" : ""), 20, 150, 20, YELLOW);

        DrawText(TextFormat("A escala real: la altura (%.0f km) es el %.1f %% del radio terrestre.",
                            altitud_km, altitud_km / radio_tierra_km * 100.0),
                    20, ALTO_VENTANA - 62, 18, GRAY);
        DrawText("ESPACIO: pausa | FLECHAS ARRIBA/ABAJO: velocidad | ESC: volver al menu",
                    20, ALTO_VENTANA - 34, 18, GRAY);

        EndDrawing();
    }

    CloseWindow();
}

#else
typedef int ventana_no_compilada;

#endif