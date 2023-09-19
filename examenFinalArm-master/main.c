#include <stdint.h>
#include "incFiles/stm32f103x6.h"

#include "motorDriver/motorDriver.h"
#include "serialUart/serialUart.h"

int main(void)
{
	while(1){
		if(existeCaracter()){
			uint8_t instruccion = leerCaracter();
			if(instruccion=='a'){ //ejecutar avanzar(1)
				avanzar(1);
			}
			else if(instruccion=='w'){//ejecutar avanzar(2)
				avanzar(2);
			}
			else if(instruccion=='b'){//ejecutar retroceder(1)
				retroceder(1);
			}
			else if(instruccion=='s'){//ejecutar retroceder(2)
				retroceder(2);
			}
			else if(instruccion=='q'){//ejecutar girarDerecha()
				girarDerecha();
			}
			else if(instruccion=='e'){//ejecutar girarIzquierda()
				girarIzquierda();
			}
		}
		
	}
}