#include <stdint.h>
#include "../incFiles/stm32f103x6.h"

void inicializarUart(void);
void enviarCaracter(uint8_t caracter);
void nuevaLinea(void);
void enviarPalabra(uint8_t cadena[]);

// función existeCaracter dentro de la librería serialUart
// Definir el prototipo en el .h considerando que el valor a devolver será 0 o 1
int existeCaracter(char caracter);
