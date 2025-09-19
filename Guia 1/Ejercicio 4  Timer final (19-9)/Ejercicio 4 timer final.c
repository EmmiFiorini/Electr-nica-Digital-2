#include <Ejercicio 4 timer final.h>

#fuses INTRC_IO   // Utilizo oscilador interno con pines RA6 y RA7 como GPIO
#fuses NOMCLR     // Desactivo el MCLR
#fuses NOWDT      // Desactivo el watchdog

// CREO MI VARIABLE GLOBAL
volatile int overflow_count=0; //mi contador q uso en el timer
volatile int led_rb4=0; //flag para controlar el LED de RB4 con timer0 
volatile int led_rb5=0; //flag para controlar el LED de RB5 

// DEFINICION DE FUNCIONES
void InitGPIO(void); //inicializo los puesrtos
void InitTimer0(void);  //inicializo el timer 0
void InitInterrupts(void); //inicializo las interrupciones por el cambio de estado de las patitas PB7-4

// HABILITO INTERRUPCION
#INT_TIMER0
void TIMER0_ISR(void) {
   set_timer0(12); //para prescaler 256 => 256-12=244
   overflow_count++; //cuento las interrupciones
   
   // Caso PB4
   if(led_rb4) { //control del LED de RB4 con timer0 
      if(overflow_count >=8) { // aprox 0,5s
         output_low(PIN_B0); 
         led_rb4=0; 
      } 
   } 
   
   //CASO PB5
   if (led_rb5) { 
      if (overflow_count == 16) { //1s
         output_high(PIN_B1);// prendo LED
      }
      if (overflow_count == 32) { //sigo contando hasta llegar a 2s
         output_low(PIN_B1); //apago LED
         overflow_count = 0; //reinicio contaodr
      }
   } 
 

#INT_RB
void RB_ISR(void){
   //patita PB4: prendo led, espero 500 ms y lo apago
   if(input(PIN_B4)){
   output_high(PIN_B0); //prendo el led
   led_rb4=1; 
   overflow_count=0; 
   }
   
   //patita PB5: disparo timer0, 1s prende, 1s apago
     if(input(PIN_B5)) {
      overflow_count=0; //reinicion mi contador para usar en el timer
     }
     
   //patita PB6: copio PB0-PB3 a PA0-PA3
   if(input(PIN_B6)){ 
      if(input(PIN_BO)){ 
         output_high(PIN_A0); 
         else
            output_low(PIN_A0); 
      } 
      if(input(PIN_B1)){ 
         output_high(PIN_A1); 
         else
            output_low(PIN_A1); 
      } 
      if(input(PIN_B2)){ 
         output_high(PIN_A2); 
         else
            output_low(PIN_A2); 
      } 
      if(input(PIN_B3)){ 
         output_high(PIN_A3); 
         else
            output_low(PIN_A3); 
      } 
    } 
      
   //patita PB7: prendo todos los LED B0-B3 
   if (input(PIN_B7)) { 
   output_high(PIN_B0); 
   output_high(PIN_B1); 
   output_high(PIN_B2); 
   output_high(PIN_B3); 
   }
   
   
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
setup_adc_ports(NO_ANALOGS); // Todos los pines como digitales
  
   // 1) defino a mis puertos como entrada y salida
 set_tris_b(0b11110000); //RB7–RB4 entradas, RB3–RB0 salidas
 set_tris_a(0b11110000); // RA7–RA4 entradas, RA3–RA0 salidas


   // 2) los inicializo en low
   output_low(PIN_B0);
   output_low(PIN_B1);
   output_low(PIN_B2);
   output_low(PIN_B3);
   // no inicializo mis puertos A, asi se puede complir la consigna

}

void InitTimer0(void){
   // configurar Timer0: reloj interno (Tcy), prescaler 256
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
   set_timer0(12); // carga inicial
   enable_interrupts(INT_TIMER0); // habilita interrupción del Timer0
   enable_interrupts(GLOBAL); // habilita interrupciones globales
}

void InitInterrupts(void){
   enable_interrupts(INT_RB);    // Habilita interrupción en RB4-RB7
   enable_interrupts(GLOBAL);    // Habilita todas las interrupciones

}
