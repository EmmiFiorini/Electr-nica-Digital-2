#include <Ejercicio 1 Timer.h>

#fuses INTRC_IO   // Utilizo oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/*Realice una rutina que, por intermedio del Timer 0, cambie el
valor del pin RB1 cada 500ms. A su vez, el pin RB1 debe estar conectado al pin
RB0 de forma que active la interrupción externa del RB0 y en esta interrupción
cambie el estado de un led en el pin RB7 (ver figura).*/

// CREO MI VARIABLE GLOBAL
volatile int overflow_count=0; //mi contador q uso en el timer

// DEFINICION DE FUNCIONES
void InitGPIO(void); //inicializo los puesrtos
void InitTimer0(void);  //inicializo el timer 0
void InitInterrupts(void); //inicializo las interrupciones por el cambio de estado de las patitas PB7-4

// HABILITO INTERRUPCION
#INT_TIMER0
void TIMER0_ISR(void) {
   set_timer0(12);       // recargo timer
   overflow_count++; 
   output_low(PIN_B1);

   if (overflow_count == 8) { // 0.5s
      output_toggle(PIN_B1);  // cambio el estado de RB1
      overflow_count = 0;
   }else
   output_low(PIN_B1);
}

#INT_EXT
void RB0_ISR(void){
   output_toggle(PIN_B7); // cambio estado LED en RB7
}


//MAIN
void main()
{
   InitGPIO();    // Inicializo el PORTA y PORTB
   InitTimer0(); //inicalizo el timer0 en el main
   InitInterrupts(); //inicializo las interrupciones x cambio de estado de las patas PB7-PB4
   
   while(TRUE)
   {
   }

}

//INICIALIZACION FUNCIONES
void InitGPIO(void) {
   //1)Defino las entradas y salidas
   set_tris_b(0b10000001); // RB7 salida, RB1 salida, RB0 entrada
  // 2) los inicializo en low
   output_b(0x00);// inicio en 0
}

void InitTimer0(void){
// configurar Timer0: reloj interno (Tcy), prescaler 256
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
   set_timer0(12); // carga inicial
   enable_interrupts(INT_TIMER0); // habilita interrupción del Timer0
  
}

void InitInterrupts(void){
   ext_int_edge(L_TO_H);//flanco ascendente
   enable_interrupts(INT_EXT);// interrupción externa RB0
   enable_interrupts(GLOBAL);
}
