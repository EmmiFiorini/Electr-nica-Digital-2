#include <Ejercicio3_compuertas.h>

#fuses INTRC_IO   // Utilizo oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog


/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/

void InitGPIO(void);

/*****************************************************************************
 * Main
 ****************************************************************************/

void main(void) { 
   InitGPIO(); // Inicializo PORTB
   while(TRUE) { 
   
      // Leo el estado de RB1 y RB2
      int sw1 = input(PIN_B1); 
      int sw2 = input(PIN_B2);

      // Si los dos interruptores tienen el mismo estado
      if(sw1 == sw2) {
         output_high(PIN_B4);  // Prendo LED
         delay_ms(500); 
         output_low(PIN_B4);   // Apago LED
         delay_ms(500);
      }
      else {
         output_low(PIN_B4);   // Si no son iguales, LED apagado
      }
   } 

}

void InitGPIO(void){ 
      set_tris_b(0b11101111); // RB4 salida, resto entradas 
      output_low(PIN_B4); // LED apagado al inicio 
}

