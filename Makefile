# Makefile del Simulador ARTEMIS - LEO
#   make               -> compila SIN ventana grafica (dibujo en consola)
#   make RAYLIB=1      -> compila CON ventana grafica (hace falta raylib instalada)
#   make run           -> compila y ejecuta
#   make clean         -> borra lo generado (HACERLO al cambiar entre modos)
CC = gcc
CFLAGS = -Wall -Wextra
TARGET = artemis
OBJS = main.o artemis.o simulador.o interfaz.o ventana.o validaciones.o

ifeq ($(RAYLIB),1)
	CFLAGS += -DUSAR_RAYLIB
	ifeq ($(OS),Windows_NT)
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -lm
else
    LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif
else
	LIBS = -lm
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

main.o: main.c artemis.h simulador.h interfaz.h validaciones.h
	$(CC) $(CFLAGS) -c main.c

artemis.o: artemis.c artemis.h validaciones.h
	$(CC) $(CFLAGS) -c artemis.c

simulador.o: simulador.c simulador.h artemis.h
	$(CC) $(CFLAGS) -c simulador.c

interfaz.o: interfaz.c interfaz.h simulador.h ventana.h artemis.h
	$(CC) $(CFLAGS) -c interfaz.c

ventana.o: ventana.c ventana.h
	$(CC) $(CFLAGS) -c ventana.c

validaciones.o: validaciones.c validaciones.h
	$(CC) $(CFLAGS) -c validaciones.c

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe