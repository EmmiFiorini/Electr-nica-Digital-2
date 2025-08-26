#include <punto2.h>
#fuses INTRC_IO   // Utilizo oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/* Configure el bit 4 del puerto B como salida, el resto como
entradas. Realice una rutina que prenda y apague un led (conectado al bit 4) cada
500ms. Utilice la función delay_ms().*/

/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/
 

void InitGPIO(void);


/*****************************************************************************
 * Main
 ****************************************************************************/

void main(void) {
   InitGPIO();    // Inicializo PORTB
   while(TRUE) {
      output_high(PIN_B4);   // Prende LED
      delay_ms(500);         // Espera 500 ms
      output_low(PIN_B4);    // Apaga LED
      delay_ms(500);         // Espera 500 ms
   }
}

/*****************************************************************************
 * Implementacion de funciones
 ****************************************************************************/

void InitGPIO(void){
    set_tris_b(0b11101111); // RB4 como SALIDA
    output_low(PIN_B4);    // Por defecto salida en estado bajo
}



