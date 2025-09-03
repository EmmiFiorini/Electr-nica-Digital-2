#include <(Timer)Ejercicio2_main.h>

#fuses INTRC_IO   // Utilizo oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog


/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/

void InitGPIO(void);

void InitTimer0(void);

/*****************************************************************************
 * Interrupcion
 ****************************************************************************/

#INT_TIMER0
void TIMER0_ISR() {
   output_toggle(PIN_B0); // Vaya invirtiendo su estado
   set_timer0(100);   // Reinicio el timer 0
}

/*****************************************************************************
 * Main
 ****************************************************************************/

void main(void) {
   InitGPIO();    // Inicializo el PORTA y PORTB
   InitTimer0();  // Inicializo el Timer1
   while (TRUE) {
   
   }
}

/*****************************************************************************
 * Implementacion de funciones
 ****************************************************************************/

void InitGPIO(void){
    set_tris_b(0b11111110); // RB0 como SALIDA
    port_b_pullups(TRUE);  // Habilito pull ups del PORTB
    output_low(PIN_B0);    // Por defecto salida en estado bajo
}

void InitTimer0(void){
    setup_timer_0(RTCC_INTERNAL | RTCC_8_BIT | RTCC_DIV_8); // Timer interno de 8 bit con preescaler de 1:8
    set_timer0(100); // Recarga el timer0 
    enable_interrupts(INT_TIMER0);    // Desactivo Interrupcion timer1
    enable_interrupts(GLOBAL);        // Desactivo Interrupciones globales
}



