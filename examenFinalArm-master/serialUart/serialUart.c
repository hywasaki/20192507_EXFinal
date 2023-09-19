#include "serialUart.h"

void inicializarUart(void)
{
    RCC->APB2ENR |= (1<<0)|(1<<2)|(1<<14);

    //Configuracion del modo de operacion en PA9 y PA10
    GPIOA->CRH &= ~(0xFF << 4);
    GPIOA->CRH |= (1<<10)|(1<<5)|(1<<7);

    USART1->BRR |= (0x34<<4);
    USART1->BRR |= (1<<0);
    USART1->CR1 |= (1<<2)|(1<<3)|(1<<13);
}

void enviarCaracter(uint8_t caracter)
{
    while(!(USART1->SR & (1<<7)));
    USART1->DR &= ~(0xF);
    USART1->DR |= caracter;
    while(!(USART1->SR & (1<<6)));
}

void nuevaLinea()
{
    while(!(USART1->SR & (1<<7)));
    USART1->DR &= ~(0xF);
    USART1->DR |= '\n';
    while(!(USART1->SR & (1<<6)));
}

void enviarPalabra(uint8_t cadena[])
{
    uint8_t i = 0;
    for(i=0;cadena[i] != '\0'; i++)
    {
        enviarCaracter(cadena[i]);
    }
    nuevaLinea();
}

/*La función en el .c debe cumplir la siguiente lógica: En el registro SR del
USART1 el bit nro 5 indica si existe algún dato pendiente de lectura. Usted debe
verificar el valor de dicho bit, si es 1 significa que ha llegado un dato al
microcontrolador y debe retornar un 1; caso contrario debe retornar un 0.
int existeCaracter(char caracter){ */

int existeCaracter(void){
    if(USART1 -> SR & (1<<5)){
        return 1;
    }
    else{
        return 0;
    }
}

/*La lógica es la siguiente: realiar un bucle que se ejecute mientras el valor del bit 5
(RXNE) del registro SR de USART1 sea 0; cuando cambie a 1 se debe terminar el
bucle; seguidamente se debe retornar el valor de los 8 bits menos significativos
del registro DR del USART1.*/
uint8_t leerCaracter(void){
    while(!(USART1->SR & (1<<5))); // Monitorea el valor del bit 5 dentro del registro SR, Si valor del bit 5 es 1 -> !Verdadero -> Falso
    // Sale del bucle
    // 0xFF es 11111111 en binario
    // &0FF devuelve 8 bits menos significativos
    return USART1->DR & (0xFF);
}



