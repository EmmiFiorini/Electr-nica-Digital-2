#include <Ejercicio4_timer.h>
#fuses INTRC_IO   // Utilizo oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

/*****************************************************************************
 * Funciones de Inicializacion de Perifericos
 ****************************************************************************/
// DEFINO MIS FUNCIONES
void InitGPIO(void); //inicializo puertas
void InitTimer0(void); //inicializo timer
void copiar_pin(int pin_in, int pin_out); //funcion q copia estados

//INTERRUPCIONES
#INT_TIMER0
void TIMER0_ISR() {
   static int contador = 0; //contador de interrupciones
   set_timer0(100);   // Reinicio el timer 0
   contador++;
   if(contador >= 500){ //paso 1s
      if(PIN_B1==0)
         output_high(PIN_B1);
      else
         output_low(PIN_B1);
      contador = 0; //reinicio el contador
   }
}

//MAIN:
void main (void){
   InitGPIO();
   while (TRUE) {
      if (input(PIN_B4)) {
         output_high(PIN_B0); // Prende LED 
         delay_ms(500); // Espera 500 ms 
         output_low(PIN_B0); // Apaga LED 
      }
      if (input(PIN_B5)) {

      }
      if (input(PIN_B6)) {
         copiar_pin(PIN_A0,PIN_B0);
         copiar_pin(PIN_A1,PIN_B1);
         copiar_pin(PIN_A2,PIN_B2);
         copiar_pin(PIN_A3,PIN_B3);
      }
      if (input(PIN_B7)) {
   
         output_high(PIN_B0); // Prende LED 
         output_high(PIN_A0);
         delay_ms(500); // Espera 500 ms 
         output_low(PIN_B0); // Apaga LED 
         output_low(PIN_A0);
      
         output_high(PIN_B1); // Prende LED 
         output_low(PIN_A1);
         delay_ms(500); // Espera 500 ms 
         output_low(PIN_B1); // Apaga LED 
         output_low(PIN_A1);
      
         output_high(PIN_B2); // Prende LED 
         output_low(PIN_A2);
         delay_ms(500); // Espera 500 ms 
         output_low(PIN_B2); // Apaga LED 
         output_low(PIN_A2);
      
         output_high(PIN_B3); // Prende LED 
         output_low(PIN_A3);
         delay_ms(500); // Espera 500 ms 
         output_low(PIN_B3); // Apaga LED 
         output_low(PIN_A3);
      }
   }
}


//INICIALIZO FUNCIONES
void copiar_pin(int pin_in, int pin_out){
   int estado;
   estado = input(pin_in);         // Leo la entrada
   output_bit(pin_out, estado);    // Copio a la salida
}

void InitGPIO(void){
   set_tris_b(0b11110000); // RB0, RB1, RB2 , RB4 como SALIDA Y el resto como ENTRADA
   set_tris_a(0b11110000); // RA3..RA0 salidas, RA7..RA4 entradas (si los necesitás)

   // Inicializo salidas en 0
   output_b(0x00);
   output_a(0x00);
}

void InitTimer0(void){
   setup_timer_0(RTCC_INTERNAL | RTCC_8_BIT | RTCC_DIV_8); // Timer0 interno con prescaler 1:8
   set_timer0(100); // precarga inicial
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
}


