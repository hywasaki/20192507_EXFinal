#include "motorDriver.h"

void iniciarModulo(void){
    // Habilitar la señal de reloj para el puerto GPIOA, GPIOC, UART4 y funciones alternas en los registros de configuración de fuentes de reloj

    // RCC_APB1ENR
    // Bit 19 UART4EN: USART 4 clock enable
    RCC->APB1ENR |=(1<<19);

    // RCC_APB2ENR
    // Bit 4 IOPCEN: IO port C clock enable
    // Bit 2 IOPAEN: IO port A clock enable
    // Bit 0 FIOEN: Alternate function IO clock enable
    RCC->APB2ENR |=(1<<0)|(1<<2)|(1<<4); 


   // valores iniciales en LOW (0 Volt) en los registros GPIOA->CRL,GPIOA->ODR, GPIOC->CRH y GPIOC->ODR.
    GPIOA->CRL&= ~(0xFFFFFFFF);
    GPIOA->ODR&= ~(0xFFFFFFFF); 
    GPIOC->CRH&= ~(0xFFFFFFFF);
    GPIOC->ODR&= ~(0xFFFFFFFF); 

    // Puertos PA4, PA5, PA6, PA7 y PC13 como salidas digitales
    // CRL puertos 0-7
    // CRH puertos 8-15

    // PA4 configurado a través de los bits 16 17 18 19 del registro CRL
    // PA5 configurado a través de los bits 20 21 22 23 del registro CRL
    // PA6 configurado a través de los bits 24 25 26 27 del registro CRL
    // PC13 configurado a través de los bits 20 21 22 23 del registro CRH

    // Salida digital 
    // CNFy[1:0]: Port x configuration bits. In output mode (MODE[1:0] >00): 00: General purpose output push-pull
    // MODEy [1:0]:10: Output mode, max speed 2 MHz.
    // 0010 -> 0XF (En hexadecimal)
    GPIOA->CRL|=(0x2 << 16)|(0x2 << 20)|(0x2 << 24); // 0010000000000000 | 00100000000000000000 | 001000000000000000000000 
    GPIOC->CRH|= (0x2 <<20);  // 001000000000000000000
   

    // puertos PB8 y PB9 como salidas digitales de funciones alternas en el registro GPIOB->CRH

    // PB8 configurado a través de los bits 0 1 2 3 del registro CRH
    // PB9 configurado a través de los bits 4 5 6 7 del registro CRH

    // CNFy[1:0]: In output mode (MODE[1:0] >00):10: Alternate function output Push-pull
    // MODEy[1:0] 10: Output mode, max speed 2 MHz.
    // 1010 -> A
    GPIOB->CRH |= (0xA<<0)|(0xA<<4);// 1010 | 10100000

    //Configurar el timer
    //En el registro TIM4->CCMR2 escribir el valor ((0x68 << 8)|(0x68<<0))
    TIM4->CCMR2= ((0x68 << 8) | (0x68 << 0));
    //En el registro TIM4->BDTR escribir 1 en el bit 15
    TIM4->BDTR|= (1 << 15);
    //En el registro TIM4->CCER escribir 1 en el bit 12 y en el bit 8
    TIM4->CCER|= (1 << 12) | (1 << 8);
    //Configurar el registro TIM4->PSC con un valor de 7
    TIM4->PSC = 7;
    //Configurar el valor correspondiente en TIM4->ARR para generar una onda PWM de 100Hz de frecuencia.
    TIM4->ARR= 10000;
    //Inicializar el valor de TIM4->CCR4 y TIM4->CCR3 en 0 para que inicialmente el ciclo de reloj sea 0%.
    TIM4->CCR4=0;
    TIM4->CCR3=0;
    // Habilitar el temporizador escribiendo un 1 en los bits 7 y 0 del registro
    TIM4->CR1|= (1 << 7) | (1 << 0);



}
/*
Implementar el codigo fuente de las fuciones
iniciarModulo(),
avanzar(),
retroceder(),
girarDerecha(),
girarIzquierda()

*/