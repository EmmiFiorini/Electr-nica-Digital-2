#include <Ejercicio 1 Timer.h>

#fuses INTRC_IO   // Utilizo oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/*Realice una rutina que, por intermedio del Timer 0, cambie el
valor del pin RB1 cada 500ms. A su vez, el pin RB1 debe estar conectado al pin
RB0 de forma que active la interrupción externa del RB0 y en esta interrupción
cambie el estado de un led en el pin RB7 (ver figura).*/

// CREO MIS VARIABLES
volatile int overflow_count=0; //mi contador q uso en el timer
volatile int rb1_state = 0;   // 0 = LOW, 1 = HIGH

int rb0_prev = 0;             // Estado anterior de RB0
int led_state = 0;             // 0 = OFF, 1 = ON

// DEFINICION DE FUNCIONES
void InitGPIO(void); //inicializo los puesrtos
void InitTimer0(void);  //inicializo el timer 0


// HABILITO INTERRUPCION
#INT_TIMER0
void TIMER0_ISR(void) {
   set_timer0(178);// Recarga para 10ms
   overflow_count++; 

   if (overflow_count >= 50) {   // 50 × 10ms = 500ms
      overflow_count = 0;
      rb1_state = !rb1_state;  
      output_bit(PIN_B1, rb1_state);
   }
   clear_interrupt(INT_TIMER0);
}



//MAIN
void main() {
    InitGPIO();    // Inicializo el PORTA y PORTB
   InitTimer0(); //inicalizo el timer0 en el main

    while(TRUE) {
        //MODELO DE ESTADOS PARA RB0 Y LED
        int rb0_curr = input(PIN_B0);

        switch(rb0_prev) {
            case 0: // RB0 estaba LOW
                if(rb0_curr) {  // sube flanco
                    led_state = !led_state;
                    output_bit(PIN_B7, led_state);
                }
                break;
            case 1: // RB0 estaba HIGH
                if(!rb0_curr) { // baja flanco
                    led_state = !led_state;
                    output_bit(PIN_B7, led_state);
                }
                break;
        }

        rb0_prev = rb0_curr;
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
  set_timer0(178);
  enable_interrupts(INT_TIMER0);
  enable_interrupts(GLOBAL);
  clear_interrupt(INT_TIMER0);
}


